#pragma once 

#include <stdint.h>

#define TRUE 1
#define FALSE 0
#define RAM_SIZE 0xFFF


typedef struct FrameBuffer_t {
    uint64_t buffer[32];
    uint8_t modified;
} FrameBuffer_t;

typedef struct Chip8_t {
    FrameBuffer_t frame_buffer;
    uint8_t RAM[RAM_SIZE];
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
