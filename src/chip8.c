#include <stdio.h>
#include <stdlib.h>
#include "chip8.h"


#define DISPATCH() {\
    if(chip8->running == FALSE) return;\
    if(cycles == 0) return;\
    opcode = chip8->RAM[chip8->PC] << 8 | chip8->RAM[chip8->PC + 1];\
    chip8->PC += 2;\
    cycles--;\
    goto * lookUp_table[opcode >> 12];\
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

    for (int i = 0; i < 32; i++) {
        if (i % 2 == 0)
            chip8.frame_buffer.buffer[i] = 0xAAAAAAAAAAAAAAAA;
        else 
            chip8.frame_buffer.buffer[i] = 0xAAAAAAAAAAAAAAAA >> 0x1;
    }
    
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


void runChip8(Chip8_t * chip8, int cycles) {

    const void * lookUp_table[16] = {
        &&op_0xxx, &&op_1xxx, &&op_2xxx, &&op_3xxx,
        &&op_4xxx, &&op_5xxx, &&op_6xxx, &&op_7xxx,
        &&op_8xxx, &&op_9xxx, &&op_Axxx, &&op_Bxxx,
        &&op_Cxxx, &&op_Dxxx, &&op_Exxx, &&op_Fxxx
    };

    uint64_t opcode ;

    DISPATCH();

    op_0xxx:
        // readRam(chip8);
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
