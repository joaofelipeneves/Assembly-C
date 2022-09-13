#include <stdio.h>

int step = 0;
int compulsory_misses = 0;
int conflict_misses = 0;
int hits = 0;
int writes = 0;

void add_miss(unsigned char valid) {
	step += 1;

    if (valid)
        conflict_misses += 1;
    else
        compulsory_misses++;

}

void add_hit(void) {
    step += 1;
    hits += 1;
}

void add_write(void) {
	writes += 1;
}

void print_cache_stats(void) {
    printf("Cache stats: \n\tnumber of accesses = %8u \n", step);
    printf("\thits               = %8u \n", hits);
    printf("\tconflict misses    = %8u \n", conflict_misses);
    printf("\tcompulsory misses  = %8u \n", compulsory_misses);
    printf("\teffective writes   = %8u \n", writes);
    printf("\thit ratio = %5.1f%%\n", 100.0 * ((double)hits / step));
}
