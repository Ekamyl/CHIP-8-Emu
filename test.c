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

void print_bin(uint64_t v, int nbits) {
    for (int i = nbits - 1; i >= 0; i--) {
        putchar('0' + ((v >> i) & 1));
        if (i % 8 == 0 && i) putchar(' ');
    }
    puts("");
}

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


    // test getAddr()
    opcode = 0x16E5;
    printf("addr de 0x16E5 : 0x%x == %d\n", getAddr(opcode), getAddr(opcode));
    printf("nibble de 0x16E5 : 0x%x == %d\n", getNibble(opcode), getNibble(opcode));
    printf("x de 0x16E5 : 0x%x == %d\n", getX(opcode), getX(opcode));
    printf("y de 0x16E5 : 0x%x == %d\n", getY(opcode), getY(opcode));

    printf("|------------------------------\n");
    uint64_t v = 0xFFFFFFFFFFFFFFFF;
    uint8_t a = (uint8_t)v >> 2 << 2;
    print_bin(a, 8);
    uint8_t val_max = 0b11111111;
    uint8_t val_test = (uint8_t)v;
    printf("max = %d, test = %d\n", val_max, val_test);


    printf("|------------------------------\n");
    uint16_t buffer[8] = {0};
    buffer[0] =  0b0010011011000000; 
    uint8_t byte = 0b10101010;
    uint8_t shift = 15 - 2 - 7;
    print_bin(buffer[0], 16);
    buffer[0] = buffer[0] ^ ((uint16_t)byte << shift);
    print_bin(buffer[0], 16);

    printf("|------------------------------\n");
    buffer[1] = 0b1010000011111111;
    print_bin(buffer[1], 16);
    byte = buffer[1] >> (16 - 3);
    printf("byte = ");
    print_bin(byte, 8);
    buffer[1] = (uint16_t)byte;
    print_bin(buffer[1], 16);

    return 0;
} 
