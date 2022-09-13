#include "utils.h"

#include <stdio.h>
#include <cpu.h>

#include "types.h"


unsigned char* int2bin(caoss_word num, unsigned char *buffer, unsigned size, op_size data_size) {

   /* if (data_size == BYTE)
        num >>= 8;
*/
    while (size--) {
        if (size && (size < data_size*8) && ((size % 8) == 0))
            buffer[size--] = ' ';

        buffer[size] = ((char) (num & 1)) + '0';
        num >>= 1;
    }

    return buffer;
}


int is_binary_operation(alu_opcode opcode) {
    return opcode == ADD || opcode == SUB || opcode == AND || opcode == OR || opcode == SAL || opcode == SAR;
}


void error(char* msg) {
    fprintf (stderr, "%s: %s.", CAOSS_ERROR, msg);
}

int register_number(const byte reg) {
    return reg+1;
}

void print_alu_instruction(const caoss_word instruction, const alu_opcode opcode, const byte size, const byte reg_in_1, const byte reg_in_2, const byte reg_out) {

    if (is_binary_operation(opcode))
        printf ("ALU instruction 0x%x --> type = %d, opcode = %d, size = %d, reg_in_1 = %d (r%d), reg_in_2 = %d (r%d), reg_out = %d (r%d)\n",
                instruction, ALU, opcode, size, reg_in_1, register_number(reg_in_1),
                reg_in_2, register_number(reg_in_2), reg_out, register_number(reg_out));
    else
        printf ("ALU instruction 0x%x --> type = %d, opcode = %d, size = %d, reg_in_1 = %d (r%d), reg_in_2 = (ignored), reg_out = %d (r%d)\n",
                instruction, ALU, opcode, size, reg_in_1, register_number(reg_in_1), reg_out, register_number(reg_out));
}

void print_load_store(const caoss_word instruction, const ls_opcode opcode, const caoss_word address, const byte reg ) {
    printf ("Memory instruction 0x%x --> type = %d, opcode = %d, address = %d, register = %d (r%d)\n",
            instruction, MEMORY, opcode, address, reg, register_number(reg));
}

void print_load_immediate(const caoss_word instruction, const caoss_word value, const byte reg ) {
    printf ("Load immediate instruction 0x%x --> type = %d, value = %d, register = %d (r%d)\n",
            instruction, LOAD_IMMEDIATE, (short) value, reg, register_number(reg));
}

void print_interrupt(const caoss_word instruction, const caoss_word int_number) {
    printf ("Interrupt instruction 0x%x --> type = %d, interrupt number = %d\n",
            instruction, INT, int_number);
}