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

uint32_t testInitCPU(Test *t, uint32_t offset)
{
    //initCPU
    offset = offset - NBRTESTINITCPU;
    Cpu *cpuInitCPU = malloc(sizeof(Cpu));
    initCPU(cpuInitCPU);
    processTest(t + offset + 0, "initCPU() -> V[0] == 0", cpuInitCPU->V[0] == 0);
    processTest(t + offset + 1, "initCPU() -> V[1] == 0", cpuInitCPU->V[1] == 0);
    processTest(t + offset + 2, "initCPU() -> V[2] == 0", cpuInitCPU->V[2] == 0);
    processTest(t + offset + 3, "initCPU() -> V[3] == 0", cpuInitCPU->V[3] == 0);
    processTest(t + offset + 4, "initCPU() -> V[4] == 0", cpuInitCPU->V[4] == 0);
    processTest(t + offset + 5, "initCPU() -> V[5] == 0", cpuInitCPU->V[5] == 0);
    processTest(t + offset + 6, "initCPU() -> V[6] == 0", cpuInitCPU->V[6] == 0);
    processTest(t + offset + 7, "initCPU() -> V[7] == 0", cpuInitCPU->V[7] == 0);
    processTest(t + offset + 8, "initCPU() -> V[8] == 0", cpuInitCPU->V[8] == 0);
    processTest(t + offset + 9, "initCPU() -> V[9] == 0", cpuInitCPU->V[9] == 0);
    processTest(t + offset + 10, "initCPU() -> V[0xA] == 0", cpuInitCPU->V[0xA] == 0);
    processTest(t + offset + 11, "initCPU() -> V[0xC] == 0", cpuInitCPU->V[0xB] == 0);
    processTest(t + offset + 12, "initCPU() -> V[0xC] == 0", cpuInitCPU->V[0xC] == 0);
    processTest(t + offset + 13, "initCPU() -> V[0xD] == 0", cpuInitCPU->V[0xD] == 0);
    processTest(t + offset + 14, "initCPU() -> V[0xE] == 0", cpuInitCPU->V[0xE] == 0);
    processTest(t + offset + 15, "initCPU() -> V[0xF] == 0", cpuInitCPU->V[0xF] == 0);
    processTest(t + offset + 16, "initCPU() -> I == 0", cpuInitCPU->I == 0);
    processTest(t + offset + 17, "initCPU() -> DT == 0", cpuInitCPU->DT == 0);
    processTest(t + offset + 18, "initCPU() -> ST == 0", cpuInitCPU->ST == 0);
    processTest(t + offset + 19, "initCPU() -> PC == 0x200", cpuInitCPU->PC == 0x200);
    free(cpuInitCPU);
    //return nbr test
    return NBRTESTINITCPU;
}

