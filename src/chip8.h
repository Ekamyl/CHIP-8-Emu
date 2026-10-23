#pragma once 

#include <stdint.h>

#define TRUE 1
#define FALSE 0
#define DISPATCH() {\
    if(chip8->running == FALSE) return;\
    if(cycles == 0) return;\
    opcode = chip8->RAM[chip8->PC] << 8 | chip8->RAM[chip8->PC + 1];\
    chip8->PC += 2;\
    cycles--;\
    goto * lookUp_table[opcode >> 12];\
}

typedef struct Chip8_t {
    uint8_t RAM[4096];
    uint8_t registers[16];
    uint16_t I;
    uint8_t delay;
    uint8_t sound;
    uint16_t PC;
    uint8_t SP;
    uint16_t stack[16];
    uint8_t running;
} Chip8_t ;


Chip8_t initChip8(void);

void runChip8(Chip8_t * chip8, int cycles);
