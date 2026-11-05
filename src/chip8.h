#pragma once 

#include <stdint.h>

#define TRUE 1
#define FALSE 0
#define RAM_SIZE 0xFFF

/* Keyboard mapping */
#define KEY_0 13
#define KEY_1 0
#define KEY_2 1
#define KEY_3 2
#define KEY_4 4
#define KEY_5 5
#define KEY_6 6
#define KEY_7 8
#define KEY_8 9
#define KEY_9 10
#define KEY_A 12
#define KEY_B 14
#define KEY_C 3
#define KEY_D 7
#define KEY_E 11
#define KEY_F 15


typedef struct FrameBuffer_t {
    uint64_t buffer[32];
    uint8_t modified;
} FrameBuffer_t;

typedef struct Chip8_t {
    FrameBuffer_t frame_buffer;
    uint16_t stack[16];
    uint16_t I;
    uint16_t PC;
    uint8_t RAM[RAM_SIZE];
    uint8_t keyboard[16];
    uint8_t registers[16];
    uint8_t delay;
    uint8_t sound;
    uint8_t SP;
    uint8_t running;
} Chip8_t ;


Chip8_t initChip8(void);

void runChip8(Chip8_t * chip8, int cycles);
