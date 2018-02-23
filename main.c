#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "define.h"
#include "format.h"
#include "init.h"
#include "stack.h"
#include "cpu.h"

#define GETROMARGV argv[1]


void gdbASM(Cpu *cpu,
            uint16_t masque[NBRINSTRUCTION],
            uint16_t id[NBRINSTRUCTION]);

int main(int argc, char* argv[argc+1])
{
    uint8_t stack[STACK];
    uint16_t stackOpcode[STACK/2];
    uint16_t instructionStack[STACK/2];
    uint16_t masque[NBRINSTRUCTION];
    uint16_t id[NBRINSTRUCTION];
    char* instructionASM[NBRINSTRUCTION];
    FILE* rom = NULL;
    uint32_t size = 0;
    Cpu cpu;
    if(argc < 2)
    { 
        fprintf(stderr, "Chemin de la rom manquant\n");
        exit(EXIT_FAILURE); 
    } 
    init(stack, stackOpcode, instructionStack, 
         masque, id, instructionASM, GETROMARGV, 
         rom, &size);
    if(argc >= 3) 
    {
        initCPU(&cpu);
        loadRomCPU(&cpu, GETROMARGV, rom, &size);
        gdbASM(&cpu, masque, id);
    }
    else if(argc == 2)
    {
        formatASM(stackOpcode, instructionStack,
                masque, id, instructionASM, size); 
    }
    if(rom != NULL) fclose(rom);
    exit(EXIT_SUCCESS);
}

void gdbASM(Cpu *cpu, uint16_t masque[NBRINSTRUCTION],
            uint16_t id[NBRINSTRUCTION])
{
    char command[512];
    while(1)
    {
        printf("chip8gdb >");
        fflush(stdout);
        scanf("%511s", command);
        if(!strcmp(command, "exit"))
        {
            printf("Bye !\n");
            break;
        }
        else if(!strcmp(command, "cpu"))
        {
            printf("debugCPU : \n");
            debugCPU(cpu);
            printf("\n");
        }
        else if(!strcmp(command, "reg") || !strcmp(command, "register"))
        {
            printf("debugReg : \n");
            debugRegCPU(cpu);
            printf("\n");
        }
        else if(!strcmp(command, "run") || !strcmp(command, "r"))
        {
            printf("Run : \n");
            runCPU(cpu, false, masque, id);
        }
        else if(!strcmp(command, "runstep") || !strcmp(command, "rs"))
        {
            printf("Run : \n");
            runCPU(cpu, true, masque, id);
        }
        else if(!strcmp(command, "step") || !strcmp(command, "s"))
        {
            execCPU(cpu, masque, id);
        }
    }
}

