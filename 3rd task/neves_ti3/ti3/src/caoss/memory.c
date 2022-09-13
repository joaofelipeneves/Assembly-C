//
// Created by Hervé Paulino on 19/03/2022.
//

#include "memory.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include "cache.h"

byte* data;
byte* code;

/**
 * Auxiliary array that keeps information on whether a position of the data segment has been writen.
 */
byte* dirty;


int mem_size;

char setup_memory(long size) {
    if (MAX_MEM_SIZE < size)
        return -1;
    mem_size = size;
    data = (byte *) calloc (size, 1);
    code = (byte *) calloc (MAX_CODE_SIZE, 1);
    dirty = (byte *) calloc (size, 1);
    return 0;
}


void read_data(caoss_address address, caoss_word* reg) {

    if (has_cache())
        read_cache(address, reg);
    else
        memcpy(reg, &data[address], sizeof(caoss_word));
}

void write_data(caoss_word value, caoss_address address) {

    if (has_cache())
        write_cache(value, address);
    else
        memcpy(&data[address], &value, sizeof(caoss_word));


    // Do not alter
    dirty[address] = 1;
    dirty[address+1] = 1;
}

void read_code(caoss_address address, caoss_word* reg) {
    memcpy(reg, &code[address], sizeof(caoss_word));
}


void show_memory() {

    unsigned size = sizeof(byte)*9 - 1; // extra spaces for separating bytes
    unsigned char value[size+1];
    value[size] = 0;

    printf("Data segment:\n");
    for (int i = 0; i < mem_size; i++) {
        if (dirty[i])
            printf("\t%5d: [%5d] \t [%s]\n", i, data[i], int2bin(data[i], value, size, BYTE));
    }
}