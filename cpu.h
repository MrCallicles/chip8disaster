#ifndef CPU_H
#define CPU_H
#include <stdbool.h>
#include "stack.h"

#define SIZEOPSTRING 16
#define NBRREG 16
#define NBRNEST 16
#define MEMSIZE 4096
#define INSTRUCTIONADRESSINIT 512

//represent the CPU for
//gdbASM
typedef struct{
    uint8_t V[16];
    uint16_t I;
    uint8_t DT;
    uint8_t ST;
    uint16_t PC;
    uint8_t SP;
    uint16_t N[16];
    uint8_t mem[4096];
} Cpu;

void initCPU(Cpu *cpu);
void loadRomCPU(Cpu* cpu, char* pathRom, FILE* rom, uint32_t* size);
void debugCPU(Cpu* cpu);
void debugRegCPU(Cpu* cpu);
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
