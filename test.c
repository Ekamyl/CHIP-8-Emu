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

    FILE * f = fopen("roms/2-ibm-logo.ch8", "rb");
    if (f == NULL) {
        fprintf(stderr, "Error while opening roms/2-ibm-logo.ch8 file");
        return 1;
    }

    uint8_t tab[4];
    size_t length = sizeof(tab[0]);
    size_t num = sizeof(tab) / length;
    fread(tab, length, num, f);

    for(int i = 0; i < 4; i++) {
        printf("%d ", tab[i]);
    }
    printf("\n");

    // afficher le nombre de bytes 
    fseek(f, 0, SEEK_END);
    long nbytes = ftell(f);
    printf("n bytes : %ld\n", nbytes);

    fclose(f);

    return 0;
} 
