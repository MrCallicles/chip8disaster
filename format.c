#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "format.h"
#include "stack.h"
#include "define.h"

void formatStack(FILE *stream, uint8_t stack[STACK]){
    /*
     *
     * Print la stack à la manière d'un hexdump
     * permet de debug stack
     */
    uint32_t list = 1;
    if(stream != NULL)
    {
        rewind(stream);
        for(uint16_t i = 0; i < STACK; i++)
        {
            if(stack[i] > 0xF){
                printf("%x ", stack[i]);
            }
            else
            {
                printf("0%x ", stack[i]);
            }
            if(list % 8 == 0) printf(" ");
            if(list % 16 == 0)
            {
                printf("\n");
            }
            list++;
            if(getc(stream) == EOF )
            {
                break;
            }
        }

    }
    else
    {
        perror(0);
        fprintf(stderr,"Impossible d'ouvrir le fichier");
    }
}

void formatOpcode(uint16_t stackOpcode[STACK/2], uint32_t size)
{
    /*
     * Print le fichier ROM
     * avec une stack en uint16_t
     * permet de faire du débug de la stackOpcode
     *
     */
    for(uint16_t i = 0; i < size/2; i++)
    {
        if(i % 16 == 0)
        {
            printf("\n");
        }
        if(stackOpcode[i] < 0xFFF) printf("0");
        if(stackOpcode[i] < 0xFF) printf("0");
        if(stackOpcode[i] < 0xF) printf("0");
        printf("%x ", stackOpcode[i]);
    }
    printf("\n");
}

void formatASM(uint16_t stackOpcode[STACK/2],
               uint16_t instructionStack[STACK/2],
               uint16_t masque[NBRINSTRUCTION],
               uint16_t id[NBRINSTRUCTION],
               char* instructionASM[NBRINSTRUCTION],
               uint32_t size)
{
    char str[16];
    for(uint32_t i = 0, j = 0x200;i < size/2; i++, j+=2)
    {
        printf("\x1B[1m");
        printf("<0x%3x> ", j);
        printf("\x1B[0m");
        printf("\x1B[36m");
        printf("%4x", stackOpcode[i]); //affiche l'hexadecimal
        printf("\x1B[0m");
        printf("\x1B[31m");
        printf("%6s ", getInstructionASM(stackOpcode[i], masque, id, instructionASM));
        printf("\x1B[0m");
        getOpOne(stackOpcode[i], masque, id, str);
        printf("\x1B[1m");
        printf("%6s", str);
        printf("\x1B[0m");
        printf(", ");
        getOpTwo(stackOpcode[i], masque, id, str);
        printf("\x1B[1m");
        printf("%s", str);
        printf("\x1B[0m");
        printf("\n");
    }
}

