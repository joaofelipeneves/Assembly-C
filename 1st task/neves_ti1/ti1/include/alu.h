

#ifndef CAOSS_ALU_H
#define CAOSS_ALU_H

#include "types.h"
#include "cpu.h"

extern caoss_word registers[NREGISTERS];

void add(op_size size, byte register_in1, byte register_in2, byte register_out);

void sub(op_size size, byte register_in1, byte register_in2, byte register_out);

void and(op_size size, byte register_in1, byte register_in2, byte register_out);

void or(op_size size, byte register_in1, byte register_in2, byte register_out);

void sal(op_size size, byte register_in1, byte register_in2, byte register_out);

void sar(op_size size, byte register_in1, byte register_in2, byte register_out);

void neg(op_size size, byte register_in, byte register_out);

void not(op_size size, byte register_in, byte register_out);

#endif //CAOSS_ALU_H
