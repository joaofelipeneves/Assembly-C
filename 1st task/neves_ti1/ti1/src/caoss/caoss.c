#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "caoss.h"
#include "utils.h"

int main(int argc , char* argv[]) {

    if (argc < 2 || argc > 4) {
        fprintf(stderr, "usage: %s file_name [mem_size]\n", argv[0]);
        return 1;
    }

    long mem_size = argc == 3 ? strtol(argv[2], 0, 10) : MAX_MEM_SIZE;

    if (setup_memory(mem_size) == -1) {
        fprintf(stderr, "Memory size too long. The maximum is %d bytes.", (MAX_MEM_SIZE));
        return 1;
    }

    if (load_program(argv[1]) == -1) {
        perror(CAOSS_ERROR);
        return errno;
    }

    cpu_run();
}



