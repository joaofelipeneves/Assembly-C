
/*
 * Assume-se que:
 *  - o CPU tem enderecos de 32 bits
 *  - cache com linhas/blocos de 32 bytes
 *    logo o no. de bloco dado pelos 27 bits mais significativos (32-5)
 */

#ifndef CAOSS_CACHE_H
#define CAOSS_CACHE_H

#include "types.h"

/**
 * Setup the cache
 * @param nsets Number of sets
 * @param nways Size of each set, i.e., the number of ways
 * @param blocksize size of the block
 * @return 0, if success, -1 if error
 */
unsigned setup_cache(int nsets, int nways, int blocksize);

/**
 * Has a cache been configured
 * @return 0 (false) ou 1 (true)
 */
unsigned char has_cache();

/**
 * Read a value from the cache and copy it to register reg
 * @param address The source address
 * @param reg The target register
 */
void read_cache(caoss_address address, caoss_word* reg);

void write_cache(caoss_word value, caoss_address address);


/**
 * Show the state of the cache
 */
void show_cache();

#endif