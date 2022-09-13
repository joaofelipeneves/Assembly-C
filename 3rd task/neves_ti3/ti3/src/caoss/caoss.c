#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "caoss.h"
#include "utils.h"
#include "cache.h"

int main(int argc , char* argv[]) {

    if (argc != 4) {
        fprintf(stderr, "usage: %s file_name number_sets number_lines_per_set\n", argv[0]);
        return 1;
    }

    long mem_size = MAX_MEM_SIZE;

    if (setup_memory(mem_size) == -1) {
        perror(CAOSS_ERROR);
        return errno;
    }

    unsigned number_sets = atoi(argv[2]);
    unsigned number_lines_per_set = atoi(argv[3]);
    unsigned blocksize = 16;

    if (setup_cache(number_sets, number_lines_per_set, blocksize) == -1) {
        perror(CAOSS_ERROR);
        return errno;
    }

    if (load_program(argv[1]) == -1) {
        perror(CAOSS_ERROR);
        return errno;
    }

    cpu_run();
}



