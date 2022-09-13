// JOAO FELIPE RIBEIRO NEVES ----------------- LEI


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "types.h"
#include "cache.h"
#include "stats.h"
#include "memory.h"


extern void  show_registers();
/**
 * Number of sets in a cache
 *      1 for fully associative caches
 */
unsigned number_sets;

/**
 * Size of a set. Number of lines (or number of ways).
 *      1 for direct-mapped caches; number_sets for fully associative caches.
 */
unsigned number_lines;

/**
 * Size of a block
 */
unsigned block_size;

/**
 * Type of a line
 */
typedef struct {
    unsigned char valid;
    unsigned char dirty;
    unsigned char lru;
    unsigned int tag;
    unsigned char* block;
} line_t;

/**
 * Type of a set (an array of lines)
 */
typedef line_t* set_t;

/**
 * The cache (an array of sets)
 */
set_t* cache;


void show_line(unsigned set, unsigned line) {

    printf ("\t\tLine %d: valid=%d, tag=%d, dirty=%d, lru=%d, block=", line, cache[set][line].valid, cache[set][line].tag, cache[set][line].dirty, cache[set][line].lru);
    for (int k = 0; k < block_size; k++)
        printf ("%d ", cache[set][line].block[k]);
    printf ("\n");
}


void show_cache() {
    printf("Cache:\n");
    for (int i = 0; i < number_sets; i++) {
        printf ("\tSet %d: \n", i);
        for (int j = 0; j < number_lines; j++)
            show_line(i, j);
    }
}


unsigned get_block(caoss_address addr) {
    //DONE
    return addr / block_size;     //you can get the block dividing the addr by the block size
}

unsigned get_offset(caoss_address addr) {
    //DONE
    return addr % block_size;     //you can get the offset of the adress 
}

unsigned get_set(unsigned block) {
    //DONE
    return block % number_sets;   //gets the the by calling the function of block and number of sets 
}

unsigned get_tag(unsigned block) {
    //DONE
    return block / number_sets;   // gets the specific tag by dividing the block by the number of lines 
}



/**
 * Returns the line in the set where the block is, if the block was found; -1 otherwise
 *
 * @param block the number of the block to find
 *  @return The number of the line where the block was found or -1, if not found
 */
int find_in_set(unsigned set, unsigned tag) {
    //done
    //will verify trhough a for cicle if the cache valid position and tag position are equals to the tag , if not returns the number that is odd
    int nmbrl = number_lines;

        for (int i = 0; i < nmbrl; i++) {
            if (cache[set][i].valid && cache[set][i].tag == tag){
        
              return i;
            
      }
    }
    return -1; // not found
}

/**
 * Find the first free line in given set
 * @param set The set
 * @return The number of the free line found or -1, if none
 */

//will execute a for cicle until 4 to see if all the positions in the sets are valid 
int find_free(unsigned set) {
    //done
    //will looop trough the cache to see if valid is equals to 0 , if so , return the j position of the loop

    int tamanho_final = number_lines;

        for (int j = 0; j < tamanho_final; j++) {
            if (cache[set][j].valid == 0)
                 return j;
    }

    return -1; // not found
}

unsigned select_victim(unsigned set) {
    for (int i=0; i < number_lines; i++)
        if (cache[set][i].lru == 0) {
#ifdef DEBUG_CACHE
            printf ("Set %u: selected victim %u\n", set, i);
#endif
            return i;
        }

    for (int i=0; i < number_lines; i++)
        cache[set][i].lru = 0;

#ifdef DEBUG_CACHE
    printf ("Set %u: reset LRU bit and selected victim %u\n", set, 0);
#endif
    return 0;
}


unsigned find_in_cache(caoss_address address, unsigned set, unsigned block) {

    unsigned tag = get_tag(block);
    int  line = find_in_set(set, tag);

    if (line == -1) { // MISS
        line = find_free(set); // find free line

        if (line == -1) {
            // no free line found
            line = select_victim(set); // select a victim

            // TODO: write back
            if (cache[set][line].dirty) {
                unsigned write_block = (cache[set][line].tag * number_sets) + set; // done
                // TODO: write block write_block to the memory: use memcpy   
                //done
                memcpy(&data[write_block * block_size], cache[set][line].block, block_size);

#ifdef DEBUG_CACHE
                printf("Write back line %d of set %u with tag %u (block %u)\n", line, set, cache[set][line].tag, write_block);
#endif
                
            }
        }
        else {
#ifdef DEBUG_CACHE
            printf ("Set %u: found free line %d\n", set, line);
#endif
        }

        add_miss(cache[set][line].valid); // statistics

        // TODO: update cache line: set the dirty bit to 0.
        //done



        address = address - get_offset(address); // set the addres to the offset done previously 
        memcpy(cache[set][line].block , &data[address] , block_size); //will receive and set stuff as the line 170 does as well 


        cache[set][line].valid = 1; //set valid to 1 

        cache[set][line].lru = 1; //set lru to 1 
        
        cache[set][line].tag = tag; //set tag that will be the same value as tag itself
        cache[set][line].dirty = 0; //set the dirty of the cache to 0

        
        


        

        
        
        
      

#ifdef DEBUG_CACHE
        printf ("Address %u: block %u --> MISS on set %u, loaded to line %d\n", address, block, set, line);
#endif
    }
    else { // HIT
        add_hit(); // statistics
        cache[set][line].lru = 1;

#ifdef DEBUG_CACHE
        printf ("Address %u: block %u --> HIT on set %u line %u\n", address, block, set, line);
#endif
    }

    return line;
}

void read_cache(caoss_address address, caoss_word* reg) {

    unsigned block = get_block(address);
    unsigned set = get_set(block);
    unsigned offset = get_offset(address);

    unsigned line = find_in_cache(address, set, block);
    memcpy(reg, &cache[set][line].block[offset], sizeof(caoss_word)); // read value from cache to the register

#ifdef DEBUG_CACHE
    show_line(set, line);
    printf ("\t\tRead a word (2 bytes) from offset=%u\n", offset);
#endif
}


void write_cache(caoss_word value, caoss_address address) {

    unsigned block = get_block(address);
    unsigned set = get_set(block);
    unsigned offset = get_offset(address);

    unsigned line = find_in_cache(address, set, block);
    memcpy(&cache[set][line].block[offset], &value, sizeof(caoss_word)); // write value to cache
    cache[set][line].dirty = 1;

    add_write();

#ifdef DEBUG_CACHE
    show_line(set, line);
    printf ("\t\tWrite a word (2 bytes) with value %u to offset=%u\n", value, offset);
#endif
}



unsigned setup_cache(int nsets, int nlines, int blocksize) {
     number_sets = nsets;
    number_lines = nlines;
    block_size = blocksize;

    const unsigned set_size = number_lines * sizeof(line_t);

    cache = malloc(number_sets * sizeof(set_t *));

    if (cache == NULL)
        return errno;

    for (int i = 0; i < number_sets; i++) {
        cache[i] = malloc(set_size);
        for (int j = 0; j < number_lines; j++) {
            cache[i][j].valid = 0;
            // Allocate space for blocks
            cache[i][j].block = malloc(blocksize);
        }
    }

     printf("CACHE SIZE = %d bytes (%d sets x %d lines x %d bytes)\n",
           number_sets * set_size * blocksize, number_sets, number_lines, blocksize);

    return 0;
}




unsigned char has_cache() {
    return number_sets > 0;
}
