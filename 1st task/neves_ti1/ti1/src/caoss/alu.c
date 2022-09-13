#include "alu.h"
// @author JOAO FELIPE RIBEIRO NEVES -------------------- LEI;

// TODO: implement the operation  //DONE
void add(op_size size, byte register_in1, byte register_in2, byte register_out) {

    if (size == BYTE) {
        int masks_result_add = (registers[register_out] & (255 << 8));
        int masks_add = (registers[register_in2] + registers[register_in1]) & 255;
        registers[register_out] = masks_add + masks_result_add;
    }
    else {
        registers[register_out] = registers[register_in1] + registers[register_in2];
    }
}

// TODO: implement the operation   //DONE
void sub(op_size size, byte register_in1, byte register_in2, byte register_out) {
    if (size == BYTE) {
        int masks_result_sub = (registers[register_out] & (255 << 8));
        int masks_sub = (registers[register_in1] - registers[register_in2]) & 255;
        registers[register_out] = masks_result_sub - masks_sub;
    }
    else {
        registers[register_out] = registers[register_in1] - registers[register_in2];
    }
}

// TODO: implement the operation   //DONE 
void and(op_size size, byte register_in1, byte register_in2, byte register_out) {
    if (size == BYTE) {
        int masks_result_and = (registers[register_out] & (255 << 8));
        int masks_and = (registers[register_in2] & registers[register_in1]) & 255;
        registers[register_out] = masks_result_and + masks_and;
    }
    else {
        registers[register_out] = registers[register_in1] & registers[register_in2];
    }
}

// TODO: implement the operation     //ok
void or(op_size size, byte register_in1, byte register_in2, byte register_out) {
    if (size == BYTE) {
        int masks_result_or = (registers[register_out] & (255 << 8));
        int masks_or = (registers[register_in2] | registers[register_in1]) & 255;
        registers[register_out] = masks_result_or + masks_or;
    }
    else {
        registers[register_out] = registers[register_in1] | registers[register_in2];
    }
}

// TODO: implement the operation    // ok
void sal(op_size size, byte register_in1, byte register_in2, byte register_out) {
    if (size == BYTE) {
        int masks_result_sal = (registers[register_out] & (255 << 8));
        int masks_sal = (registers[register_in1] << registers[register_in2]) & 255;
        registers[register_out] = masks_result_sal + masks_sal;
    }
    else {
        registers[register_out] = registers[register_in1] << registers[register_in2];
    }
}

// TODO: implement the operation  //ok
void sar(op_size size, byte register_in1, byte register_in2, byte register_out) {
    if (size == BYTE) {
        int masks_result_sar = (registers[register_out] & (255 << 8));
        int masks_sar = (registers[register_in1] >> registers[register_in2]) & 255;
        registers[register_out] = masks_result_sar + masks_sar;
    }
    else {
        registers[register_out] = registers[register_in1] >> registers[register_in2];
    }
}

// TODO: implement the operation
void neg(op_size size, byte register_in, byte register_out) {
    if (size == BYTE) {
        int masks_result_neg = (registers[register_out] & (255 << 8));
        int masks_neg = (-registers[register_in]) & 255;
        registers[register_out] = masks_result_neg + masks_neg;
    }
    else {
        registers[register_out] = (-registers[register_in]);
    }
}

// TODO: implement the operation
void not(op_size size, byte register_in, byte register_out) {
    if (size == BYTE) {
        int masks_result_not = (registers[register_out] & (255 << 8));
        int masks_not = (~registers[register_in]) & 255;
        registers[register_out] = masks_result_not + masks_not;
    }
    else {
        registers[register_out] = (~registers[register_in]);
    }
}