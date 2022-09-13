//
// Created by Hervé Paulino on 28/03/2022.
//

#ifndef CAOSS_UTILS_H
#define CAOSS_UTILS_H

#include "types.h"
#include "cpu.h"


/**
 * Is the ALU operation a binary operation?
 *
 * @param opcode
 * @return
 */
int is_binary_operation(alu_opcode opcode);


unsigned char* int2bin(caoss_word num, unsigned char *buffer, unsigned size, op_size data_op_size);

void error(char* msg);

void print_alu_instruction(const caoss_word instruction, const alu_opcode opcode, const byte size, const byte reg_in_1, const byte reg_in_2, const byte reg_out);

void print_load_store(const caoss_word instruction, const ls_opcode opcode, const caoss_word address, const byte reg );

void print_load_immediate(const caoss_word instruction, const caoss_word value, const byte reg );

void print_interrupt(const caoss_word instruction, const caoss_word int_number);

#endif //CAOSS_UTILS_H
