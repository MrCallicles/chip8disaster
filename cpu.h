#ifndef CPU_H
#define CPU_H
#include <stdbool.h>
#include "stack.h"

#define SIZEOPSTRING 16
#define NBRREG 16
#define NBRNEST 16
#define MEMSIZE 4096
#define INSTRUCTIONADRESSINIT 0x200
#define DEBUGMEMLIST 20

//represent the CPU for
//gdbASM
typedef struct{
    uint8_t V[NBRREG]; //general registers
    uint16_t I; //Instruction pointer
    uint8_t DT; //Delay timer
    uint8_t ST; //Sound timer
    uint16_t PC; //Program counter
    uint8_t SP; //Stack Pointer
    uint16_t stack[NBRNEST]; //Nested (stack)
    uint8_t mem[MEMSIZE]; //memoire
} Cpu;

void decrementDelaySound(Cpu *cpu);

void initCPU(Cpu *cpu);
void loadRomCPU(Cpu* cpu, char* pathRom, FILE* rom, uint32_t* size);
void debugCPU(Cpu* cpu);
void debugRegCPU(Cpu* cpu);
void debugMemCPU(Cpu* cpu);
void runCPU(Cpu *cpu,
            bool step,
            uint16_t masque[NBRINSTRUCTION],
            uint16_t id[NBRINSTRUCTION]);
void execCPU(Cpu *cpu,
             uint16_t masque[NBRINSTRUCTION],
             uint16_t id[NBRINSTRUCTION]);
void execOpCodeCPU(Cpu *cpu,
                  uint16_t instruction,
                  uint16_t opOne,
                  uint16_t opTwo);

#endif
