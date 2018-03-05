#pragma once

#define BUFFERTEST 4096
#define STRTEST 128

#define NBRTESTINITCPU 20
#define NBRTESTDECREMENTDELAYSOUND 3
#define NBRTESTGETINSTRUCTION 35
#define NBRTESTGETINSTRUCTIONID 35
#define NBRTESTGETINSTRUCTIONASM 35
#define NBRTESTGETOPONEVALUE 35
#define NBRTESTGETOPTWOVALUE 35
#define NBRTESTEXECOPCODECPU 35

typedef struct{
    bool pass;
    char strCondition[STRTEST];
} Test;

void initTest(Test *t, uint32_t *size, uint32_t nbrTest, uint32_t (*f)(Test *t, uint32_t offset));

void processTest(Test *t, char* strCond, bool condition);
void formatTest(Test *t,bool passed, bool not_passed, uint32_t size);

uint32_t testInitCPU(Test *t, uint32_t offset);
uint32_t testDecrementDelaySound(Test *t, uint32_t offset);
uint32_t testGetInstruction(Test *t, uint32_t offset);
uint32_t testGetInstructionID(Test *t, uint32_t offset);
uint32_t testGetInstructionASM(Test *t, uint32_t offset);
uint32_t testGetOpOneValue(Test *t, uint32_t offset);
uint32_t testGetOpTwoValue(Test *t, uint32_t offset);
uint32_t testCPUExecOpCode(Test *t, uint32_t offset);


