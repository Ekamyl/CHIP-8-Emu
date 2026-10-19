#include <stdio.h>
#include <stdlib.h>


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

int main(int argv, char * argc[]) {
    
    Chip8_t chip8; 
    chip8.RAM[0] = 0x0C;
    chip8.RAM[1] = 0x0B;
    chip8.PC = 0;

    uint16_t opcode = chip8.RAM[chip8.PC++] << 8 | chip8.RAM[chip8.PC++];

    printf("opcode : 0x%x\n", opcode >> 8);

    // decode  
    switch (opcode >> 12) {
        case 0x0 : 
            goto print;
            break;
    }

    printf("Je suis avant le goto\n");

    // execute 
    print:
        printf("je suis le goto print\n");
        goto end;

    printf("je suis apres le goto\n");

    end :
        return 0;

    return 0;
} 
