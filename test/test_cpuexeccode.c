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


    //SHR
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

    //SUBN
    initCPU(cpuExecOpCode);
    cpuExecOpCode->V[8] = 0xF;
    cpuExecOpCode->V[0xA] = 0xA;
    execOpCodeCPU(cpuExecOpCode, 17, 8, 0xA);
    processTest(t + offset + i,
                "execOpCodeCPU(17 , V[8], V[0xA]) (SUBN Vx, Vy)",
                (cpuExecOpCode->V[8] == 0xFE) && (cpuExecOpCode->V[0xF] == 0));

    i++;

    initCPU(cpuExecOpCode);
    cpuExecOpCode->V[8] = 0xA;
    cpuExecOpCode->V[0xA] = 0xB;
    execOpCodeCPU(cpuExecOpCode, 17, 8, 0xA);
    processTest(t + offset + i,
                "execOpCodeCPU(17 , V[8], V[0xA]) (SUBN Vx, Vy)",
                (cpuExecOpCode->V[8] == 0x1) && (cpuExecOpCode->V[0xF] == 1));

    i++;

    //SHL
    initCPU(cpuExecOpCode);
    cpuExecOpCode->V[8] = 0x7A;
    execOpCodeCPU(cpuExecOpCode, 18, 8, 0xA);
    processTest(t + offset + i,
                "execOpCodeCPU(16 , V[8], V[0xA]) (SHL Vx) when V[8] == 0x7A",
                (cpuExecOpCode->V[8] == 0x7A << 1) && (cpuExecOpCode->V[0xF] == 0));

    i++;

    initCPU(cpuExecOpCode);
    cpuExecOpCode->V[8] = 0xAA;
    execOpCodeCPU(cpuExecOpCode, 18, 8, 0xA);
    processTest(t + offset + i,
                "execOpCodeCPU(16 , V[8], V[0xA]) (SHL Vx) when V[8] == 0xAA",
                (cpuExecOpCode->V[8] == 0xB << 1) && (cpuExecOpCode->V[0xF] == 1));

    i++;
    //SNE
    initCPU(cpuExecOpCode);
    cpuExecOpCode->V[1] = 0xF0;
    cpuExecOpCode->V[2] = 0xF0;
    execOpCodeCPU(cpuExecOpCode, 19, 1, 2);
    processTest(t + offset + i, "execOpCodeCPU(19, V[1], V[2]) (SNE egal)", cpuExecOpCode->PC == 0x200);

    i++;

    initCPU(cpuExecOpCode);
    cpuExecOpCode->V[1] = 0xF0;
    cpuExecOpCode->V[2] = 0xA0;
    execOpCodeCPU(cpuExecOpCode, 19, 1, 2);
    processTest(t + offset + i, "execOpCodeCPU(19, V[1], 2) (SE not egal)", cpuExecOpCode->PC == 0x202);

    i++;
    //LD I,nnn
    initCPU(cpuExecOpCode);
    execOpCodeCPU(cpuExecOpCode, 20, 0xAAA, 0xAAA );
    processTest(t + offset + i, "execOpCodeCPU(20, x, x) (LD I,nnn)", cpuExecOpCode->I == 0xAAA);

    i++;

    //JP NNN (nnn + V[0])
    initCPU(cpuExecOpCode);
    cpuExecOpCode->V[0] = 0x5;
    execOpCodeCPU(cpuExecOpCode, 20, 0xBBB, 0xBBB);
    processTest(t + offset + i, "execOpCodeCPU(20, x, x) (LD I,nnn)", cpuExecOpCode->PC == (0xbbb + 0x5));

    i++;

    //DRW
    processTest(t + offset + i, "execOpCodeCPU(23, x, x) (DRW)",false);

    i++; 

    //SKP
    processTest(t + offset + i, "execOpCodeCPU(24, x, x) (SKP)",false);
    
    i++; 

    //SKNP
    processTest(t + offset + i, "execOpCodeCPU(24, x, x) (SKNP)",false);

    i++;

    //LD Vx DT
    initCPU(cpuExecOpCode);
    cpuExecOpCode->DT = 0xA;
    execOpCodeCPU(cpuExecOpCode, 26, 3, 3);
    processTest(t + offset + i, "execOpCodeCPU(26, V[3], V[3]) (LD Vx, DT)", cpuExecOpCode->V[3] == 0xA);

    i++;

    //LD Vx,DT
    initCPU(cpuExecOpCode);
    cpuExecOpCode->DT = 0xA;
    execOpCodeCPU(cpuExecOpCode, 26, 3, 3);
    processTest(t + offset + i, "execOpCodeCPU(27, V[3], V[3]) (LD Vx, DT)", cpuExecOpCode->V[3] == 0xA);

    i++;

    //LD Vx,k
    processTest(t + offset + i, "execOpCodeCPU(27, Vx, k) LD Vx, k", false);

    i++;

    //LD DT, Vx
    initCPU(cpuExecOpCode);
    cpuExecOpCode->V[5] = 0xAA;
    execOpCodeCPU(cpuExecOpCode, 28, 0x5, 0x5);
    processTest(t + offset + i, "execOpCodeCPU(28, Vx) LD DT, Vx", cpuExecOpCode->DT == 0xAA);

    i++;

    //LD ST, Vx
    initCPU(cpuExecOpCode);
    cpuExecOpCode->V[5] = 0xAA;
    execOpCodeCPU(cpuExecOpCode, 29, 0x5, 0x5);
    processTest(t + offset + i, "execOpCodeCPU(29, Vx) LD ST, Vx", cpuExecOpCode->ST == 0xAA);

    i++;

    //LD ADD I, Vx
    initCPU(cpuExecOpCode);
    cpuExecOpCode->V[5] = 0xAA;
    cpuExecOpCode->I = 0xAAA;
    execOpCodeCPU(cpuExecOpCode, 30, 0x5, 0x5);
    processTest(t + offset + i, "execOpCodeCPU(30, Vx) ADD I, Vx", cpuExecOpCode->I == 0xAAA + 0xAA);

    i++;

    //LD F, Vx
    processTest(t + offset + i, "execOpCodeCPU(31, F, Vx) LD F,Vx", false);
    i++;
    //LD B, Vx
    processTest(t + offset + i, "execOpCodeCPU(32, B, Vx) LD B,Vx", false);
    i++;
    //LD [I], Vx
    processTest(t + offset + i, "execOpCodeCPU(33, [I], Vx) LD [I],Vx", false);
    i++;
    //LD Vx, [I]
    processTest(t + offset + i, "execOpCodeCPU(34, Vx, [I]) LD Vx,[I]", false);

    free(cpuExecOpCode);
    return NBRTESTEXECOPCODECPU;
}
