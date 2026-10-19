#pragma once 

#include <stdint.h>

typedef struct Chip8_t {
    uint8_t RAM[4096];
    uint8_t registers[16];
    uint16_t I;
    uint8_t delay;
    uint8_t sound;
    uint16_t PC;
    uint8_t SP;
    uint16_t stack[16];
} Chip8_t ;


Chip8_t initChip8(void);

void chip8Cycle(Chip8_t * chip8);
