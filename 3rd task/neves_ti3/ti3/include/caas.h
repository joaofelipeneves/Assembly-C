//
// Created by Hervé Paulino on 19/03/2022.
//

#ifndef CAAS_CAAS_H
#define CAAS_CAAS_H

#include "types.h"
#include "cpu.h"


/**
 * Encode the header of the binary file
 */
void encode_header();


/**
 * Encode a global data definitions
 * @param size Size of the data to be stored
 * @param value Value to be stored
 */
void encode_global(const op_size size, const caoss_word value);

/**
 * Update the number of global data definitions in the header
 */
void update_number_of_globals();




/**
 * Encode ALU binary instruction
 *
 * @param opcode Opcode of the instruction
 * @param size Size of the instruction
 * @param reg1 First operand
 * @param reg2 Second operand
 * @param reg_out Result register
 */
void encode_binary_alu_instruction(const alu_opcode opcode, const op_size size, const byte reg1, const byte reg2, const byte reg_out);

/**
 * Encode ALU binary instruction
 *
 * @param opcode Opcode of the instruction
 * @param size Size of the instruction
 * @param reg Operand register
 * @param reg_out Result register
 */
void encode_unary_alu_instruction(const alu_opcode opcode, const op_size size, const byte reg, const byte reg_out);

/**
 * Encode a load/store memory operation
 * @param opcode The opcode
 * @param address The memory address to read or write from/to
 * @param reg The register to load ot store
 */
void encode_load_store(const ls_opcode opcode, const caoss_address address, const byte reg);

/**
 * Encode a load immediate operation
 * @param opcode The size of the operation
 * @param value The value to load
 * @param reg The target register
 */
void encode_load_immediate(const op_size size, const caoss_word value, const byte reg);

/**
 * Encode an interrupt operation
 *
 * @param interrupt_number The number of the interrupt
 */
void encode_interrupt(const caoss_word interrupt_number);



#endif //CAAS_CAAS_H
