#include <stdio.h>
#include "chip8.h"


Chip8_t initChip8(void) {

    Chip8_t chip8 = {
        .delay = 0,
        .sound = 0,
        .PC = 0x200,
        .SP = 0
    };

    return chip8 ;
}


void chip8Cycle(Chip8_t * chip8) {

    

}
