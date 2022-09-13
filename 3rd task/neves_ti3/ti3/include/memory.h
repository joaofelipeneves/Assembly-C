//
// Created by Hervé Paulino on 19/03/2022.
//

#ifndef CAOSS_MEMORY_H
#define CAOSS_MEMORY_H

#include "types.h"

extern byte* data;
extern byte* code;

/**
 * Auxiliary array that keeps information on whether a position of the data segment has been writen.
 */
extern byte* dirty;

/**
 * Setup the data and code segments
 * @param mem_size Size of the segments
 * @return 0, if success, -1 if error
 */
char setup_memory(long mem_size);

/**
 * Show the state of the data segment
 */
void show_memory();

/**
 * Read a value from data[address] and copy it to register reg
 * @param address The source address in the data segment
 * @param reg The target register
 */
void read_data(caoss_address address, caoss_word* reg);

/**
 * Write the given register value to data[address]
 * @param value The value to store
 * @param address The target address in the data segment
 */
void write_data(caoss_word value, caoss_address address);

/**
 * Read a value from data[address] and copy it to register reg
 * @param address The source address in the code segment
 * @param reg The target register
 */
void read_code(caoss_address address, caoss_word* reg);

#endif //CAOSS_MEMORY_H
