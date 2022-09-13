#ifndef CAOSS_OS_H
#define CAOSS_OS_H

#include "types.h"

extern caoss_word registers[NREGISTERS];

/**
 * Call the system call identified by syscall_number
 * @param syscall_number The number of the system call
 */
void syscall(caoss_word syscall_number);

int load_program(char *file_name);

#endif //CAOSS_OS_H
