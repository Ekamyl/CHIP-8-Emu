#include <stdio.h>
#include <stdlib.h>
#include "chip8.h"


#define DISPATCH() {\
    if(chip8->running == FALSE) return;\
    if(cycles == 0) return;\
    opcode = chip8->RAM[chip8->PC] << 8 | chip8->RAM[chip8->PC + 1];\
    /*chip8->PC += 2;*/\
    cycles--;\
    printf("goto opcode 0x%04x\nPC : %d\n", opcode, chip8->PC);\
    goto * lookUp_table[opcode >> 12];\
}

Chip8_t initChip8(void);
static inline void readRam(Chip8_t * chip8);
static inline uint16_t getAddr(uint16_t opcode);
static inline uint8_t getNibble(uint16_t opcode);
static inline uint8_t getX(uint16_t opcode);
static inline uint8_t getY(uint16_t opcode);
static inline uint8_t getByte(uint16_t opcode);


void runChip8(Chip8_t * chip8, int cycles) {

    // update delay and sound timers 
    if (chip8->delay > 0) chip8->delay--;
    if (chip8->sound > 0) chip8->sound--;

    const void * lookUp_table[16] = {
        &&op_0xxx, &&op_1xxx, &&op_2xxx, &&op_3xxx,
        &&op_4xxx, &&op_5xxx, &&op_6xxx, &&op_7xxx,
        &&op_8xxx, &&op_9xxx, &&op_Axxx, &&op_Bxxx,
        &&op_Cxxx, &&op_Dxxx, &&op_Exxx, &&op_Fxxx
    };

    uint16_t opcode ;

    DISPATCH();

    op_0xxx:
        if (opcode == 0x00E0) {
            for (int i = 0; i < 32; i++) {
                chip8->frame_buffer.buffer[i] = 0x0;
            }
        }
        else {
            chip8->PC = chip8->stack[chip8->SP];
            chip8->SP--;
        }
        DISPATCH();

    op_1xxx:
        chip8->PC = getAddr(opcode);
        DISPATCH();
    
    op_2xxx:
        if (chip8->SP != 0) chip8->SP++;
        chip8->stack[chip8->SP] = chip8->PC;
        chip8->PC = getAddr(opcode);
        DISPATCH();

    op_3xxx:
        if (chip8->registers[getX(opcode)] == getByte(opcode)) chip8->PC += 2;
        DISPATCH();

    op_4xxx:
        if (chip8->registers[getX(opcode)] != getByte(opcode)) chip8->PC += 2;
        DISPATCH();

    op_5xxx:
        if (chip8->registers[getX(opcode)] == chip8->registers[getY(opcode)]) chip8->PC += 2;
        DISPATCH();

    op_6xxx:
        chip8->registers[getX(opcode)] = getByte(opcode);
        DISPATCH();

    op_7xxx:
        chip8->registers[getX(opcode)] += getByte(opcode);
        DISPATCH();

    op_8xxx:
        switch(getNibble(opcode)) {
            case 0 : 
                chip8->registers[getX(opcode)] = chip8->registers[getY(opcode)];
                break;
            case 1 :
                chip8->registers[getX(opcode)] = chip8->registers[getX(opcode)] | chip8->registers[getY(opcode)];
                break;
            case 2 : 
                chip8->registers[getX(opcode)] = chip8->registers[getX(opcode)] & chip8->registers[getY(opcode)];
                break;
            case 3 : 
                chip8->registers[getX(opcode)] = chip8->registers[getX(opcode)] ^ chip8->registers[getY(opcode)];
                break;
            case 4 : 
                {
                uint16_t result = chip8->registers[getX(opcode)] + chip8->registers[getY(opcode)];
                chip8->registers[getX(opcode)] = getByte(result);
                chip8->registers[0xF] = result >> 8; 
                }
                break;
            case 5 :
                if (chip8->registers[getX(opcode)] > chip8->registers[getY(opcode)]) chip8->registers[0xF] = 1;
                chip8->registers[getX(opcode)] = chip8->registers[getX(opcode)] - chip8->registers[getY(opcode)];
                break;
            case 6 : 
                if (chip8->registers[getX(opcode)] & 0x1) chip8->registers[0xF] = 1;
                chip8->registers[getX(opcode)] = chip8->registers[getX(opcode)] >> 1;
                break;
            case 7 : 
                if (chip8->registers[getY(opcode)] > chip8->registers[getX(opcode)]) chip8->registers[0xF] = 1;
                chip8->registers[getX(opcode)] = chip8->registers[getX(opcode)] - chip8->registers[getY(opcode)];
                break;
            case 0xe :
                if (chip8->registers[getX(opcode)] & 0x8) chip8->registers[0xF] = 1;
                chip8->registers[getX(opcode)] = chip8->registers[getX(opcode)] << 1; 
        }
        DISPATCH();

    op_9xxx:
        if (chip8->registers[getX(opcode)] != chip8->registers[getY(opcode)]) chip8->PC += 2;
        DISPATCH();

    op_Axxx:
        chip8->I = getAddr(opcode);
        DISPATCH();

    op_Bxxx:
        chip8->PC = getAddr(opcode) + chip8->registers[0x0];
        DISPATCH();

    op_Cxxx:
        chip8->registers[getX(opcode)] = (rand() % 256) & getByte(opcode);
        DISPATCH();

    op_Dxxx:
        if (getNibble(opcode) > 15) {
            fprintf(stderr, "Error : Sprite size must be beetween 1 and 15, %d here\n", getNibble(opcode));
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < getNibble(opcode); i++) {
            uint8_t byte = chip8->RAM[chip8->I + i];
            uint8_t target = chip8->frame_buffer.buffer[getY(opcode)] >> (63 - getX(opcode) - 7);
            if ((target & byte) != 0) chip8->registers[0xF] = 1;
            chip8->frame_buffer.buffer[getY(opcode)] = chip8->frame_buffer.buffer[getY(opcode)] ^ (uint64_t)byte << (63 - getX(opcode) + 7); 
        }
        DISPATCH();

    op_Exxx:
        DISPATCH();

    op_Fxxx:
        DISPATCH();


}


Chip8_t initChip8(void) {

    // init attributes base values 
    Chip8_t chip8 = {
        .frame_buffer.modified = 1,
        .RAM = {0},
        .delay = 0,
        .sound = 0,
        .PC = 0x200,
        .SP = 0,
        .running = TRUE
    };
    
    // open rom file 
    FILE * rom;
    if ( !(rom = fopen("roms/2-ibm-logo.ch8", "rb")) ) {
        fprintf(stderr, "Error while opening rom file\n");
        exit(EXIT_FAILURE);
    }

    // check the file's size 
    fseek(rom, 0, SEEK_END); 
    size_t nbytes = ftell(rom);

    if (nbytes > (RAM_SIZE - 0x200)) {
        printf("Rom's size too large ( %ld bytes ), should be less than %d bytes.\n", nbytes, RAM_SIZE - 0x200);
        fclose(rom);
        exit(EXIT_FAILURE);
    }

    // writes the rom's bytes into the ram 
    fseek(rom, 0, SEEK_SET);
    size_t bytes_readed = fread(chip8.RAM + 0x200, sizeof(chip8.RAM[0]), nbytes, rom);

    // check if all bytes have been writed
    if (nbytes != bytes_readed) {
        printf("Rom's bytes not loaded correctly\n");
        fclose(rom);
        exit(EXIT_FAILURE);
    }
    
    return chip8;
}


static inline void readRam(Chip8_t * chip8) {

    FILE * rom;
    if ( !(rom = fopen("roms/2-ibm-logo.ch8", "rb")) ) {
        fprintf(stderr, "Error while opening rom file\n");
        exit(EXIT_FAILURE);
    }

    fseek(rom, 0, SEEK_END);
    long nbytes = ftell(rom);

    int count = 0;
    for (int i = 0; i < nbytes; i++) {
        printf("%02x ", chip8->RAM[0x200 + i]);
        count++;
        if(count == 20) {
            printf("\n");
            count = 0;
        }
    }
    printf("\n");

}


static inline uint16_t getAddr(uint16_t opcode) {
    return opcode & 0x0FFF;
}
static inline uint8_t getNibble(uint16_t opcode) {
    return opcode & 0x000F;
}
static inline uint8_t getX(uint16_t opcode) {
    return (opcode >> 8) & 0x000F;
}
static inline uint8_t getY(uint16_t opcode) {
    return (opcode >> 4) & 0x000F;
}
static inline uint8_t getByte(uint16_t opcode) {
    return opcode & 0x00FF;
}

