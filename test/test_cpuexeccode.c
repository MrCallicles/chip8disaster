#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h> 
#include "../cpu.h"
#include "../stack.h"
#include "../define.h"
#include "../init.h"
#include "../format.h"
#include "test.h"

uint32_t testCPUExecOpCode(Test *t, uint32_t offset)
{
    offset -= NBRTESTEXECOPCODECPU;
    Cpu *cpuExecOpCode = malloc(sizeof(Cpu));
    uint32_t i = 0;

    initCPU(cpuExecOpCode);
    execOpCodeCPU(cpuExecOpCode, 0, 0x0, 0x0);
    processTest(t + offset + i, "execOpCodeCPU(0, 0x111, 0x111) (CLS)",false);

    i++;

    initCPU(cpuExecOpCode);
    cpuExecOpCode->stack[0] = 0x200;
    cpuExecOpCode->SP = 1;
    execOpCodeCPU(cpuExecOpCode, 1, 0x0, 0x0);
    //RET
    processTest(t + offset + i, "execOpCodeCPU(1, 0x0, 0x0) (RET)", cpuExecOpCode->PC == 0x200 && cpuExecOpCode->SP == 0);

    i++;

    initCPU(cpuExecOpCode);
    execOpCodeCPU(cpuExecOpCode, 2, 0x0, 0x0);
    //not implemented SYS
    processTest(t + offset + i, "execOpCodeCPU(2, 0x0, 0x0) (SYS)", true);

    i++;

    initCPU(cpuExecOpCode);
    execOpCodeCPU(cpuExecOpCode, 3, 0x200, 0x200);
    processTest(t + offset + i, "execOpCodeCPU(3, 0x200, 0x200) (JMP)",
                cpuExecOpCode->PC == 0x200);

    i++;

    initCPU(cpuExecOpCode);
    execOpCodeCPU(cpuExecOpCode, 4, 0x400, 0x400);
    processTest(t + offset + i, "execOpCodeCPU(0x2000, 0x150, 0x150) (CALL)",
                cpuExecOpCode->stack[0] == 0 ||
                cpuExecOpCode->PC == 0x400 ||
                cpuExecOpCode->SP == 1
            );

    i++;

    initCPU(cpuExecOpCode);
    cpuExecOpCode->V[1] = 0xF0;
    execOpCodeCPU(cpuExecOpCode, 5, 1, 0xF0);
    processTest(t + offset + i, "execOpCodeCPU(5, V[1], 0xF0) (SE egal)", cpuExecOpCode->PC == 0x202);

    i++;

    initCPU(cpuExecOpCode);
    cpuExecOpCode->V[1] = 0xF0;
    execOpCodeCPU(cpuExecOpCode, 5, 1, 0xF0);
    execOpCodeCPU(cpuExecOpCode, 5, 1, 0xF0);
    processTest(t + offset + i, "execOpCodeCPU(5, V[1], 0xF0) (SE egal)", cpuExecOpCode->PC == 0x204);

    i++;

    initCPU(cpuExecOpCode);
    cpuExecOpCode->V[1] = 0xF0;
    execOpCodeCPU(cpuExecOpCode, 5, 1, 0xC0);
    processTest(t + offset + i, "execOpCodeCPU(5, V[1], 0xC0) (SE not egal)", cpuExecOpCode->PC == 0x200);

    i++;

    initCPU(cpuExecOpCode);
    cpuExecOpCode->V[1] = 0xF0;
    execOpCodeCPU(cpuExecOpCode, 6, 1, 0xF0);
    processTest(t + offset + i, "execOpCodeCPU(6, V[1], 0xC0) (SNE egal)", cpuExecOpCode->PC == 0x200);

    i++;

    initCPU(cpuExecOpCode);
    cpuExecOpCode->V[1] = 0xF0;
    execOpCodeCPU(cpuExecOpCode, 6, 1, 0xD0);
    processTest(t + offset + i, "execOpCodeCPU(6, V[1], 0xC0) (SNE not egal)", cpuExecOpCode->PC == 0x202);

    i++;

    initCPU(cpuExecOpCode);
    cpuExecOpCode->V[1] = 0xF0;
    cpuExecOpCode->V[0xB] = 0xF0;
    execOpCodeCPU(cpuExecOpCode, 7, 1, 0xb);
    processTest(t + offset + i, "execOpCodeCPU(7, V[1], V[B]) (SE Vx,Vy egal)", cpuExecOpCode->PC == 0x202);

    i++;

    initCPU(cpuExecOpCode);
    cpuExecOpCode->V[1] = 0xF0;
    cpuExecOpCode->V[0xB] = 0xD0;
    execOpCodeCPU(cpuExecOpCode, 7, 1, 0xb);
    processTest(t + offset + i, "execOpCodeCPU(7, V[1], V[1]) (SE Vx,Vy not egal)", cpuExecOpCode->PC == 0x200);

    i++;

    initCPU(cpuExecOpCode);
    cpuExecOpCode->V[1] = 0xF0;
    cpuExecOpCode->V[0xB] = 0xD0;
    execOpCodeCPU(cpuExecOpCode, 7, 1, 0xb);
    processTest(t + offset + i, "execOpCodeCPU(7, V[1], V[B]) (SE Vx,Vy not egal)", cpuExecOpCode->PC == 0x200);

    i++;

    initCPU(cpuExecOpCode);
    execOpCodeCPU(cpuExecOpCode, 8, 1, 0xFF);
    processTest(t + offset + i, "execOpCodeCPU(8, V[1], 0xFF) (LD Vx,NN)", cpuExecOpCode->V[1] == 0xFF);

    i++;

    initCPU(cpuExecOpCode);
    cpuExecOpCode->V[1] = 0x5;
    execOpCodeCPU(cpuExecOpCode, 9, 1, 0x5);
    processTest(t + offset +i, "execOpCodeCPU(9, V[1], 0xFF) (ADD Vx,NN)", cpuExecOpCode->V[1] == (0x5 + 0x5));

    i++;

    initCPU(cpuExecOpCode);
    cpuExecOpCode->V[3] = 0x5;
    cpuExecOpCode->V[5] = 0xD0;
    execOpCodeCPU(cpuExecOpCode, 10, 3, 5);
    processTest(t + offset + i, "execOpCodeCPU(10, V[3], V[5]) (LD Vx,Vy)", cpuExecOpCode->V[3] == 0xD0);

    i++;

    initCPU(cpuExecOpCode);
    cpuExecOpCode->V[3] = 0xEA;
    cpuExecOpCode->V[5] = 0xD0;
    execOpCodeCPU(cpuExecOpCode, 11, 3, 5);
    processTest(t + offset + i, "execOpCodeCPU(11, V[3], V[5]) (OR Vx, Vy)", (cpuExecOpCode->V[3] == 0xEA) |
           (cpuExecOpCode->V[5] == 0xD0));

    i++;

    initCPU(cpuExecOpCode);
    cpuExecOpCode->V[3] = 0xEA;
    cpuExecOpCode->V[5] = 0xD0;
    execOpCodeCPU(cpuExecOpCode, 12, 3, 5);
    processTest(t + offset + i, "execOpCodeCPU(12, V[3], V[5]) (AND Vx, Vy)",
                (cpuExecOpCode->V[3] == (0xEA & 0xD0)));

    i++;

    initCPU(cpuExecOpCode);
    cpuExecOpCode->V[3] = 0xEA;
    cpuExecOpCode->V[5] = 0xD0;
    execOpCodeCPU(cpuExecOpCode, 13, 3, 5);
    processTest(t + offset + i, "execOpCodeCPU(13, V[3], V[5]) (XOR Vx, Vy)", cpuExecOpCode->V[3] == (0xEA ^ 0xD0));

    i++;

    initCPU(cpuExecOpCode);
    cpuExecOpCode->V[3] = 0x0A;
    cpuExecOpCode->V[5] = 0xD0;
    execOpCodeCPU(cpuExecOpCode, 14, 3, 5);
    processTest(t + offset + i,
                "execOpCodeCPU(14 , V[3], V[5]) (ADD Vx, Vy with carry)",
                (cpuExecOpCode->V[3] == (0x0A + 0xD0)) && (cpuExecOpCode->V[0xF] == 0));

    i++;

    initCPU(cpuExecOpCode);
    cpuExecOpCode->V[3] = 0xFF;
    cpuExecOpCode->V[5] = 0x05;
    execOpCodeCPU(cpuExecOpCode, 14, 3, 5);
    processTest(t + offset + i,
                "execOpCodeCPU(14 , V[3], V[5]) (ADD Vx, Vy with carry)",
                (cpuExecOpCode->V[3] == 0x04) && (cpuExecOpCode->V[0xF] == 1));

    i++;

    initCPU(cpuExecOpCode);
    cpuExecOpCode->V[3] = 0xF0;
    cpuExecOpCode->V[5] = 0x0F;
    execOpCodeCPU(cpuExecOpCode, 14, 3, 5);
    processTest(t + offset + i,
                "execOpCodeCPU(14 , V[3], V[5]) (ADD Vx, Vy with carry)",
                (cpuExecOpCode->V[3] == 0xFF) && (cpuExecOpCode->V[0xF] == 0));

    i++;

    initCPU(cpuExecOpCode);
    cpuExecOpCode->V[3] = 0xF0;
    cpuExecOpCode->V[5] = 0x0F;
    execOpCodeCPU(cpuExecOpCode, 14, 3, 5);
    processTest(t + offset + i,
                "execOpCodeCPU(14 , V[3], V[5]) (ADD Vx, Vy with carry)",
                (cpuExecOpCode->V[3] == 0xFF) && (cpuExecOpCode->V[0xF] == 0));

    i++;

    initCPU(cpuExecOpCode);
    cpuExecOpCode->V[3] = 0xF0;
    cpuExecOpCode->V[5] = 0x0F;
    execOpCodeCPU(cpuExecOpCode, 15, 3, 5);
    processTest(t + offset + i,
                "execOpCodeCPU(15 , V[3], V[5]) (SUB Vx, Vy with carry)",
                (cpuExecOpCode->V[3] == (0xF0 - 0x0F)) && (cpuExecOpCode->V[0xF] == 1));

    i++;

    initCPU(cpuExecOpCode);
    cpuExecOpCode->V[3] = 0xA;
    cpuExecOpCode->V[5] = 0xF;
    execOpCodeCPU(cpuExecOpCode, 15, 3, 5);
    processTest(t + offset + i,
                "execOpCodeCPU(15 , V[3], V[5]) (SUB Vx, Vy with carry)",
                (cpuExecOpCode->V[3] == (0xFB)) && (cpuExecOpCode->V[0xF] == 0));

    i++;

    initCPU(cpuExecOpCode);
    cpuExecOpCode->V[8] = 0xA;
    execOpCodeCPU(cpuExecOpCode, 16, 8, 0xA);
    processTest(t + offset + i,
                "execOpCodeCPU(16 , V[8], V[0xA]) (SHR Vx)",
                (cpuExecOpCode->V[8] == 0xA >> 1) && (cpuExecOpCode->V[0xF] == 0));

    i++;

    initCPU(cpuExecOpCode);
    cpuExecOpCode->V[8] = 0xB;
    execOpCodeCPU(cpuExecOpCode, 16, 8, 0xA);
    processTest(t + offset + i,
                "execOpCodeCPU(16 , V[8], V[0xA]) (SHR Vx)",
                (cpuExecOpCode->V[8] == 0xB >> 1) && (cpuExecOpCode->V[0xF] == 1));

    i++;



    free(cpuExecOpCode);
    return NBRTESTEXECOPCODECPU;
}
