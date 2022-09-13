//
// Created by Hervé Paulino on 19/03/2022.
// @author JOAO FELIPE RIBEIRO NEVES ------------ LEI
//

#include "memory.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

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
    code = (byte *) calloc (size, 1);
    dirty = (byte *) calloc (size, 1);
    return 0;
}

void read_data(caoss_address address, caoss_word* reg) {
    //
    *reg = (data[address + 1] << 8) | data[address];
}

void write_data(caoss_word value, caoss_address address) {
    // TODO: write value to data[address] according to the Little Endian order

    //adress + 1 , passa o bit , e da o shift right no value
    data[address + 1] = value >> 8;
    data[address] = value; 
    // Do not alter
    dirty[address] = 1;
    dirty[address+1] = 1;
}

void read_code(caoss_address address, caoss_word* reg) {
    // TODO: read word from code[address] and place it on reg
    // similar ao read data
    *reg = (code[address + 1] << 8) | code[address];
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