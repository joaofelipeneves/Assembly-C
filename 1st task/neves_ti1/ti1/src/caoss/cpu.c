//
// Created by Hervé Paulino on 19/03/2022.
// @author JOAO FELIPE RIBEIRO NEVES -------------- LEI
//

#include "types.h"
#include "memory.h"
#include "cpu.h"
#include "alu.h"
#include "os.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>

// Registers
caoss_word registers[NREGISTERS];
caoss_address pc = 0;
caoss_instruction ir;


/**
 * Uses read_code to load instruction at code[pc] to ir (the instruction register)
 */
void fetch() {
    read_code(pc, &ir);
}

void memory_operation() {
    //0b == indicar que um numero eh binario 
    //0h == indicar que é hexadecimal
    // TODO: decode the instruction. Put in variable opcode the identifier of the instruction in register ir.
    ls_opcode opcode = (ir & 0b0010000000000000 >> 13); // > 13 pq adress 10 + 3 register
    caoss_word address = (ir & 0b0001111111111000 >> 3);  // > 3 000 dpois do 1 , por causa que é o 4 bit da ordem
    byte reg = (ir & 0b0000000000000111);  // pronto  , msm logica para os outros 

#ifdef DEBUG
    print_load_store(ir, opcode, address, reg);
#endif

    switch (opcode) {
        case LOAD_MEM:
            read_data(address, &registers[reg]);
            break;

        case STORE_MEM:
            write_data(registers[reg], address);
    }
}

void load_immediate_operation() {
    // uma vez hexadecimal , colocar todas as vezes , pra n dar problema
    caoss_word value = (ir & 0x3FF8) >> 3;
    if (value & 0x0400) // extend the signal to 16 bytes, to support negative numbers
        value = value | 0xF800;
    byte reg = (ir & 0x7); 
    // será que pode colocar o numero em binario ?

#ifdef DEBUG
    print_load_immediate(ir, value, reg);
#endif

    registers[reg] = value;
}




void alu_operation() {

    // TODO: decode the instruction. Put in variable opcode the identifier of the instruction in register ir.
    alu_opcode opcode =  (ir & 0b0011110000000000 >> 10); // TODO
    op_size size =  (ir & 0b0000001000000000 >> 9); // TODO
    byte reg_in_1 = (ir & 0b0000000111000000 >> 6); // TODO
    byte reg_out =  (ir & 0b0000000000000111); // TODO

    if (is_binary_operation(opcode)) {
            // Binary operation
            byte reg_in_2 = (ir & 0b0000000000111000 >> 3); // rgi2 pronto 

#ifdef DEBUG
        print_alu_instruction(ir, opcode, size, reg_in_1, reg_in_2, reg_out);
#endif

            size = size+1; // convert bit value (0/1) to actual size in bytes (1/2)

            switch (opcode) {
                case ADD:
                    add(size, reg_in_1, reg_in_2, reg_out);
                    break;
                case SUB:
                    sub(size, reg_in_1, reg_in_2, reg_out);
                    break;
                case AND:
                    and(size, reg_in_1, reg_in_2, reg_out);
                    break;
                case OR:
                    or(size, reg_in_1, reg_in_2, reg_out);
                    break;
                case SAR:
                    sar(size, reg_in_1, reg_in_2, reg_out);
                    break;
                case SAL:
                    sal(size, reg_in_1, reg_in_2, reg_out);
                    break;

                default:
                    error("Unknown opcode\n");
            }
        }
        else {
            // unary operation

#ifdef DEBUG
        print_alu_instruction(ir, opcode, size, reg_in_1, 0, reg_out);
#endif
            size = size+1; // convert bit value (0/1) to actual size in bytes (1/2)
            switch (opcode) {
                case NEG:
                    neg(size, reg_in_1, reg_out);
                    break;
                case NOT:
                    not(size, reg_in_1, reg_out);
                    break;

                default:
                    error("Unknown opcode\n");
            }
    }

}


void interrupt_operation() {

    caoss_word int_number = (byte) (ir & 0X3FFF);

#ifdef DEBUG
    print_interrupt(ir, int_number);
#endif

    switch (int_number) {
        case 0:
            syscall(registers[0]);
            break;

        default:
            fprintf(stderr, "%s: invalid interrupt %d\n", CAOSS_ERROR, int_number);
            exit(1);
    }
}

/**
 * Decode the instruction in ir and call the respective function to carry out the operation's execution
 */
void decode_and_execute() {

#ifdef DEBUG
    printf ("Decoding instruction 0x%x at address %d\n", ir, pc);
#endif

    instruction_type inst_type = (ir >> 0xC000) >> 14;
    // 14 em hexa vai fazer com q o programa feche 

    switch (inst_type) {
        case MEMORY:
            memory_operation();
            break;

        case LOAD_IMMEDIATE:
            load_immediate_operation();
            break;

        case ALU:
            alu_operation();
            break;

        case INT:
            interrupt_operation();
            break;

        default:
            error("instruction type not known.");
            exit(1);
    }
}

void cpu_run() {

    while (1) {
#ifdef DEBUG
        show_memory();
        show_registers();
#endif
        fetch();
        decode_and_execute();
        pc+=2;
    }
}



void show_registers() {

    unsigned size = sizeof(caoss_word)*9 - 1; // extra spaces for separating bytes
    unsigned char intNum[size+1];
    intNum[size] = 0;

    printf("Registers:\n");
    printf ("\tpc [%5u] \t [%s]\n", pc, int2bin(pc, intNum, size, WORD));
    printf ("\tir [%5u] \t [%s]\n\n", ir, int2bin(ir, intNum, size, WORD));
    for (int i = 0; i<NREGISTERS; i++) {
        printf ("\tr%d [%5d] [%5d] [%s]\n", (i+1), registers[i], (short) registers[i], int2bin(registers[i], intNum, size, WORD));
    }
}