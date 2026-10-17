#include "chip8.h"


Chip8_t initChip8() {

    Chip8_t chip8 = {
        .delay = 0,
        .sound = 0,
        .PC = 0,
        .SP = 0
    };

    return chip8 ;
}