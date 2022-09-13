#include <stdio.h>


#include "caas.h"
#include "caas_lexer.h"
#include "caas_parser.h"

#include "utils.h"

extern int yyparse (void);

/**
 * Number of globals
 */
caoss_word num_globals = 0;


void encode_header() {
#ifdef DEBUG
    printf ("Write header\n");
#endif
    fwrite(&num_globals, 2, 1, yyout);
}


void encode_global(const op_size size, const caoss_word value) {

    if (value > ((1 << (size+1)*8)-1)) {
       fprintf(stderr, "line %d: value %d to big too be represented in the selected data size", yylineno, value);
       exit(1);
    }

    fwrite(&size, 1, 1, yyout);
    fwrite(&value, size, 1, yyout);

#ifdef DEBUG
    printf("Global data %d\n", value);
#endif

    num_globals++;
}



void encode_binary_alu_instruction(const alu_opcode opcode, const op_size size, const byte reg1, const byte reg2, const byte reg_out) {

    caoss_word inst = (ALU << 14) | (opcode << 10) | ((size-1) << 9) |
            ((reg1 - 1) << 6) | ((reg2 - 1) << 3) | (reg_out - 1);
    fwrite(&inst, sizeof(caoss_word), 1, yyout);

#ifdef DEBUG
    print_alu_instruction(inst, opcode, (size-1), (reg1 - 1), (reg2 - 1), (reg_out - 1));
#endif
}

void encode_unary_alu_instruction(const alu_opcode opcode, const op_size size, const byte reg, const byte reg_out) {
    encode_binary_alu_instruction(opcode, size, reg, 1, reg_out);
}

void encode_load_store(const ls_opcode opcode, const caoss_word address, const byte reg) {

    caoss_word inst = (MEMORY << 14) | (opcode << 13) | (address << 3) | (reg - 1);
    fwrite(&inst, sizeof(caoss_word), 1, yyout);

#ifdef DEBUG
    print_load_store(inst, opcode, address, (reg-1));
#endif
}


void encode_load_immediate(const op_size size, const caoss_word value, const byte reg) {

    caoss_word inst = (LOAD_IMMEDIATE << 14) |  ((value << 3) & 0x3FFF) |  (reg-1);
    fwrite(&inst, sizeof(caoss_word), 1, yyout);

#ifdef DEBUG
    print_load_immediate(inst, value, (reg-1));
#endif
}


void encode_interrupt(const caoss_word interrupt_number) {
    caoss_word inst = (INT << 14) | (interrupt_number & 0x3FFF);
    fwrite(&inst, sizeof(caoss_word), 1, yyout);

#ifdef DEBUG
    print_interrupt(inst, interrupt_number);
#endif
}

void update_number_of_globals() {
    fseek(yyout, 0, SEEK_SET);
    fwrite(&num_globals, 2, 1, yyout);

#ifdef DEBUG
    printf ("Update header with %d global data initializations.\n", num_globals);
#endif
}


int main(int argc , char* argv[]) {

    if (argc != 3) {
        printf("usage: %s source_file_name executable_name\n", argv[0]);
        return 1;
    }

    yyin = fopen(argv[1], "r");
    if(yyin == NULL) {
        perror("caas");
        return 1;
    }

    yyout = fopen(argv[2], "w");
    if(yyout == NULL) {
        perror("caas");
        return 1;
    }

    yyparse();
}



