#include <stdio.h>
#include <stdlib.h>


int main() {
    uint8_t * var = malloc(sizeof(uint8_t) * 1) ;

    uint8_t * addr = var ; 

    printf("valeur de 'addr' : %p\n", addr);

    uint16_t stack[16];
    uint8_t * p = stack ;

    printf("%d\n", *p);

    printf("taille de pointeur de uint16_t : %lu\ntaille de pointeur de uint8_t : %lu\n", sizeof(uint16_t *), sizeof(uint8_t *));

    return 0;
} 