#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "stack.h"
#include "cpu.h"

void decrementDelaySound(Cpu *cpu)
{
    if(cpu->DT > 0) cpu->DT--;
    if(cpu->ST > 0) cpu->ST--;
}

void initCPU(Cpu *cpu)
{
    for(uint8_t i = 0; i < NBRREG; i++){
        cpu->V[i] = 0;
     }
    for(uint8_t i = 0; i < NBRNEST; i++){
        cpu->N[i] = 0;
    }
    for(uint16_t i = 0; i < INSTRUCTIONADRESSINIT; i++){
        cpu->mem[i] = 0;
    }
    cpu->I = 0;
    cpu->DT = 0;
    cpu->ST = 0;
    cpu->PC = INSTRUCTIONADRESSINIT;
    cpu->SP = 0;
}

void loadRomCPU(Cpu* cpu, char* pathRom, FILE* rom, uint32_t* size)
{
    rom = fopen(pathRom, "rb");
    fread(&cpu->mem[cpu->PC], sizeof(uint8_t)*(*size), 1, rom);
    fclose(rom);
}

void debugCPU(Cpu* cpu)
{
    printf("I : 0x%x = %d\n", cpu->I , cpu->I );
    printf("DT: 0x%x = %d\n", cpu->DT, cpu->DT);
    printf("ST: 0x%x = %d\n", cpu->ST, cpu->ST);
    printf("PC: 0x%x = %d\n", cpu->PC, cpu->PC);
    printf("SP: 0x%x = %d\n", cpu->SP, cpu->SP);
}

void debugRegCPU(Cpu* cpu)
{
    for(uint8_t i = 0; i < NBRREG; i++)
    {
        printf("V%x : 0x%x = %d | ", i, cpu->V[i], cpu->V[i]);
        if(i % 2 != 0 && i != 0)
        {
            printf("\n");
        }
    }
}

void runCPU(Cpu *cpu,
            bool step,
            uint16_t masque[NBRINSTRUCTION],
            uint16_t id[NBRINSTRUCTION])
{
    /*
     * Run the rom
     */
    static bool running = false;
    if(!running) running = true;
    else
    {
        printf("The Rom is already running\n");
        return;
    }
    if(step) execCPU(cpu, masque, id);
    else{
        /*
         * Ajouter le contrôle
         * des break point !!
         */
        execCPU(cpu, masque, id);
    }
}

void execCPU(Cpu *cpu,
             uint16_t masque[NBRINSTRUCTION],
             uint16_t id[NBRINSTRUCTION])
{
    uint16_t instruction = 0;
    char opOneString[SIZEOPSTRING];
    char opTwoString[SIZEOPSTRING];
    uint16_t opOne = 0;
    uint16_t opTwo = 0;
    cpu->I = getOpcode(cpu->mem[cpu->PC], cpu->mem[cpu->PC + 1]);
    cpu->PC += 2;
    instruction = getInstruction(cpu->I, masque, id);
    getOpOne(cpu->I, masque, id, opOneString);
    getOpTwo(cpu->I, masque, id, opTwoString);
    printf("0x%x > instruction : %x, opOne : %s, opTwo : %s\n",
           cpu->I ,instruction, opOneString, opTwoString);
    instruction = getInstructionID(cpu->I, masque, id);
    opOne = getOpOneValue(cpu->I, masque, id);
    opTwo = getOpTwoValue(cpu->I, masque, id);
    execOpCodeCPU(cpu, instruction, opOne, opTwo);
    //CPU->I must point to the next instruction ?
    decrementDelaySound(cpu);
    cpu->I = getOpcode(cpu->mem[cpu->PC], cpu->mem[cpu->PC + 1]);
}

void execOpCodeCPU(Cpu *cpu,
                  uint16_t instruction,
                  uint16_t opOne,
                  uint16_t opTwo)
{
    switch(instruction){
        case 0:
            //SYS
            break;
        case 1:
            //CLS
            break;
        case 2:
            //RET
            cpu->PC = cpu->N[cpu->SP];
            cpu->SP -= 1;
            break;
        case 3:
            //JP
            cpu->PC = opOne;
            break;
        case 4:
            //CALL
            cpu->PC += 1;
            cpu->N[cpu->SP] = cpu->PC;
            cpu->PC = opOne;
            break;
        case 5:
            //SE
            if(opOne == opTwo) cpu->PC += 2;
            break;
        case 6:
            //SNE
            if(opOne != opTwo) cpu->PC += 2;
            break;
        case 7:
            //SE Vx, Vy
            if(opOne == opTwo) cpu->PC += 2;
            break;
        case 8:
            //LD Vx, byte
            cpu->V[opOne] = opTwo;
            break;
        case 9:
            //LD 
            cpu->V[opOne] = cpu->V[opOne] + opTwo;
            break;
        case 10:
            cpu->V[opOne] = cpu->V[opTwo];
            break;
        case 11:
            cpu->V[opOne] = cpu->V[opOne] | cpu->V[opTwo];
            break;
        case 12:
            cpu->V[opOne] = cpu->V[opOne] & cpu->V[opTwo];
            break;
        case 13:
            cpu->V[opOne] = cpu->V[opOne] ^ cpu->V[opTwo];
            break;
        case 14:
            //ADD Vx Vy. Pas fini
            if(cpu->V[opOne] + cpu->V[opTwo] > 255)
            {
                uint16_t tmp = 0;
                tmp = cpu->V[opOne] + cpu->V[opTwo];
                cpu->V[opOne] = tmp << 1;
                cpu->V[0xF] = 1;
            }
            else
            {
                cpu->V[opOne] = cpu->V[opOne] + cpu->V[opTwo];
                cpu->V[0xF] = 0;
            }
            break;
        case 15:
            //SUB Vx Vy. Pas fini
            if(cpu->V[opOne] > cpu->V[opTwo])
            {
                cpu->V[0xF] = 1;
            }
            else
            {
                cpu->V[0xF] = 0;
            }
            break;
        case 16:
            //SHR
            if(cpu->V[opOne] & 1) cpu->V[0xF] = 1;
            else cpu->V[0xF] = 0;
            cpu->V[opOne] = cpu->V[opOne] << 2;
            break;
        case 17:
            //SUBN
            break;
        case 18:
            //SHL
            if(cpu->V[opOne] & 128) cpu->V[0xF] = 1; 
            else cpu->V[0xF] = 0;
            cpu->V[opOne] = cpu->V[opOne] << 2;
            break;
        case 19:
            //SNE
            if(cpu->V[opOne] != cpu->V[opTwo]) cpu->PC += 2;
            break;
        case 20:
            cpu->I = opTwo;
            break;
        case 21:
            cpu->PC = cpu->V[0x0] + opTwo;
            break;
        case 22:
            //RND
            break;
        case 23:
            //DRW
            break;
        case 24:
            //SKP
            break;
        case 25:
            //SKNP
            break;
        case 26:
            //LD Vx, DT
            cpu->V[opOne] = cpu->DT;
            break;
        case 27:
            //LD Vx, K
            break;
        case 28:
            //LD DT, Vx
            cpu->DT = cpu->V[opOne];
            break;
        case 29:
            //LD DT, Vx
            cpu->ST = cpu->V[opOne];
            break;
        case 30:
            //ADD I, Vx
            cpu->I = cpu->I + cpu->V[opOne];
            break;
        case 31:
            //LD F, Vx
            break;
        case 32:
            //LD B, Vx
            break;
        case 33:
            //LD [I], Vx
            break;
        case 34:
            //LD Vx, [I]
            break;
    }

}
