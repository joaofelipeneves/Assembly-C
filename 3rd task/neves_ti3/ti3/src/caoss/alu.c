#include "alu.h"
//JOAO FELIPE RIBEIRO NEVES -------------------- LEI


// TODO: implement the operation
void add(op_size size, byte register_in1, byte register_in2, byte register_out) {

    if (size == BYTE) {
        byte result = registers[register_in1] + registers[register_in2];
        byte* halfreg = ((byte*) &registers[register_out]);
        *halfreg = result;
    }
    else {
        // TODO - ok
        registers[register_out] = registers[register_in1] + registers[register_in2];
    }
}

// TODO: implement the operation - ok 
void sub(op_size size, byte register_in1, byte register_in2, byte register_out) {
    if (size == BYTE) {
        byte* halfreg = ((byte*) &registers[register_out]);
        *halfreg = (byte) (registers[register_in1] - registers[register_in2]);
    }
    else
        registers[register_out] = registers[register_in1] - registers[register_in2];
}

// TODO: implement the operation - ok 
void and(op_size size, byte register_in1, byte register_in2, byte register_out) {
    if (size == BYTE) {
        byte* halfreg = ((byte*) &registers[register_out]);
        *halfreg = (byte) (registers[register_in1] & registers[register_in2]);
    }
    else
        registers[register_out] = registers[register_in1] & registers[register_in2];
}

// TODO: implement the operation - ok 
void or(op_size size, byte register_in1, byte register_in2, byte register_out) {
    if (size == BYTE) {
        byte* halfreg = ((byte*) &registers[register_out]);
        *halfreg = (byte) (registers[register_in1] | registers[register_in2]);
    }
    else
        registers[register_out] = registers[register_in1] | registers[register_in2];
}

// TODO: implement the operation - ok
void sal(op_size size, byte register_in1, byte register_in2, byte register_out) {
    if (size == BYTE) {
        byte* halfreg = ((byte*) &registers[register_out]);
        *halfreg = (byte) (((short) registers[register_in1]) << ((short) registers[register_in2]));
    }
    else
        registers[register_out] = (((short) registers[register_in1]) << ((short) registers[register_in2]));
}

// TODO: implement the operation - ok
void sar(op_size size, byte register_in1, byte register_in2, byte register_out) {
    if (size == BYTE) {
        byte* halfreg = ((byte*) &registers[register_out]);
        *halfreg = (byte) (((short) registers[register_in1]) >> ((short) registers[register_in2]));
    }
    else
        registers[register_out] = (((short) registers[register_in1]) >> ((short) registers[register_in2]));
}

// TODO: implement the operation - ok
void neg(op_size size, byte register_in, byte register_out) {
    if (size == BYTE) {
        byte* halfreg = ((byte*) &registers[register_out]);
        *halfreg = (byte) (-registers[register_in]);
    }
    else
        registers[register_out] = -registers[register_in];
}

// TODO: implement the operation - ok
void not(op_size size, byte register_in, byte register_out) {
    if (size == BYTE) {
        byte* halfreg = ((byte*) &registers[register_out]);
        *halfreg = (byte) (~registers[register_in]);
    }
    else
        registers[register_out] = ~registers[register_in];
}