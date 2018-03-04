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

uint32_t testDecrementDelaySound(Test *t, uint32_t offset)
{
     offset = offset - NBRTESTDECREMENTDELAYSOUND;
     Cpu *cpuDecrement = malloc(sizeof(Cpu));
     initCPU(cpuDecrement);
     cpuDecrement->DT = 2;
     cpuDecrement->ST = 2;
     decrementDelaySound(cpuDecrement);
     processTest(t + offset + 0,
             "decrementDelaySound where DT & ST = 2",
             cpuDecrement->DT == 1 && cpuDecrement->ST == 1);
     decrementDelaySound(cpuDecrement);
     processTest(t + offset + 1,
             "decrementDelaySound where DT & ST = 1",
             cpuDecrement->DT == 0 && cpuDecrement->ST == 0);
     decrementDelaySound(cpuDecrement);
     processTest(t + offset + 2,
             "decrementDelaySound where DT & ST = 0",
             cpuDecrement->DT == 0 && cpuDecrement->ST == 0);
     free(cpuDecrement);
     return NBRTESTDECREMENTDELAYSOUND;
}

