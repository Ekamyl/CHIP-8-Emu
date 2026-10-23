#include <stdio.h>
#include <stdlib.h>
#include "chip8.h"


Chip8_t initChip8(void) {

    // init base values 
    Chip8_t chip8 = {
        .delay = 0,
        .sound = 0,
        .PC = 0x200,
        .SP = 0,
        .running = TRUE
    };

    // load rom into the ram
    if (!fopen("roms/2-ibm-logo.ch8", "rb")) {
        fprintf(stderr, "Error while opening rom file\n");
        exit(EXIT_FAILURE);
    }

    return chip8;
}


void runChip8(Chip8_t * chip8, int cycles) {

    void * lookUp_table[16] = {
        &&op_0xxx, &&op_1xxx, &&op_2xxx, &&op_3xxx,
        &&op_4xxx, &&op_5xxx, &&op_6xxx, &&op_7xxx,
        &&op_8xxx, &&op_9xxx, &&op_Axxx, &&op_Bxxx,
        &&op_Cxxx, &&op_Dxxx, &&op_Exxx, &&op_Fxxx
    };

    uint64_t opcode ;

    DISPATCH();

    op_0xxx:
        printf("test\n");
        chip8->running = FALSE;
        DISPATCH();

    op_1xxx:

    
    op_2xxx:


    op_3xxx:


    op_4xxx:


    op_5xxx:


    op_6xxx:


    op_7xxx:


    op_8xxx:


    op_Axxx:


    op_9xxx:


    op_Bxxx:


    op_Cxxx:


    op_Dxxx:


    op_Exxx:


    op_Fxxx:



}
