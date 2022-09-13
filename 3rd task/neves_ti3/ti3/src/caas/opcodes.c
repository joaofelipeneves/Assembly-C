

#include <string.h>
#include "cpu.h"

/**
 * Obtain the opcode of the mnemonic of an ALU instruction.
 *
 * @param mnemonic  The text representation of the mnemonic
 * @return A value of the alu_opcode enumeration, if the mnemonic is known, -1 otherwise.
 */
alu_opcode get_alu_opcode(const char* mnemonic) {

    if (strcmp(mnemonic, "add") == 0)
        return ADD;
    if  (strcmp(mnemonic, "sub") == 0)
        return SUB;
    if  (strcmp(mnemonic, "and") == 0)
        return AND;
    if  (strcmp(mnemonic, "or") == 0)
        return OR;
    if  (strcmp(mnemonic, "neg") == 0)
        return NEG;
    if  (strcmp(mnemonic, "sal") == 0)
        return SAL;
    if  (strcmp(mnemonic, "sar") == 0)
        return SAR;
    if  (strcmp(mnemonic, "not") == 0)
        return NOT;

    return -1;
}