#include <stdio.h>
#include "chip8.h"


Chip8_t initChip8(void) {

    Chip8_t chip8 = {
        .delay = 0,
        .sound = 0,
        .PC = 0x200,
        .SP = 0,
        .running = TRUE
    };

    return chip8 ;
}


void runChip8(Chip8_t * chip8, int cycles) {

    void * lookUp_table[16] = {
        &&op_0xxx,
        &&op_1xxx,
        &&op_2xxx,
        &&op_3xxx,
        &&op_4xxx,
        &&op_5xxx,
        &&op_6xxx,
        &&op_7xxx,
        &&op_8xxx,
        &&op_9xxx,
        &&op_Axxx,
        &&op_Bxxx,
        &&op_Cxxx,
        &&op_Dxxx,
        &&op_Exxx,
        &&op_Fxxx
    };

    DISPATCH();

    op_0xxx:
        printf("test\n");
        return;


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
