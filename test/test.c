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

#define DISPLAY_PASSED 1
#define DISPLAY_NOT_PASSED 2
#define DISPLAY_STATISTICS 4

void formatTest(Test *t,bool passed, bool not_passed, uint32_t size)
{
    /*
     * Flag
     * Constante qui peut être égale à
     * DISPLAY_PASSED --> affiche les tests réussi
     * DISPLAY_NOT_PASSED --> affiche les tests ratés
     * DISPLAY_STATISTICS --> affiche des statistiques sur les test
     * Ne fonctionne pas pour l'instant, remplacé par deux bool
     *
     */
    uint32_t nPassed = 0;
    uint32_t nNotPassed = 0;
    for(uint8_t i = 0; i < size; i++)
    {
        (t + i)->pass ? ++nPassed : ++nNotPassed;

        if((t + i)->pass && passed)
        {
             printf("\x1B[32m"
                    "PASSED %d : "
                    "%s"
                    "\x1B[0m"
                    "\n",
                    i,
                    (t + i)->strCondition);
        }
        if(!(t + i)->pass && not_passed)
        {
             printf("\x1B[31m"
                    "NOT PASSED %d : "
                    "%s"
                    "\x1B[0m"
                    "\n",
                    i,
                    (t + i)->strCondition);
        }
    }
            printf("%d test(s) passed\n"
                   "%d test(s) not passed\n",
                   nPassed, nNotPassed);
}

void processTest(Test *t, char* strCond, bool condition)
{
    t->pass = condition;
    if(strlen(strCond) > 128) strncpy(t->strCondition, strCond, 128);
    else strcpy(t->strCondition, strCond);
}

int main(void){
    Test* t = NULL;
    uint32_t size = 0;

    size += NBRTESTINITCPU;
    t = malloc((sizeof(Test) * size));
    if (t == NULL)
    {
        fprintf(stderr, "ERREUR");
        exit(EXIT_FAILURE);
    }
    testInitCPU(t, size);

    size += NBRTESTDECREMENTDELAYSOUND;
    t = realloc(t,sizeof(Test)* size);
    if (t == NULL)
    {
        fprintf(stderr, "ERREUR");
        exit(EXIT_FAILURE);
    }
    testDecrementDelaySound(t, size);

    size += NBRTESTGETINSTRUCTION;
    t = realloc(t, sizeof(Test)* size);
    if (t == NULL)
    {
        fprintf(stderr, "ERREUR");
        exit(EXIT_FAILURE);
    }
    testGetInstruction(t, size);

    size += NBRTESTGETINSTRUCTIONID;
    t = realloc(t, sizeof(Test)* size);
    if (t == NULL)
    {
        fprintf(stderr, "ERREUR");
        exit(EXIT_FAILURE);
    }
    testGetInstructionID(t, size);

    size += NBRTESTGETINSTRUCTIONASM;
    t = realloc(t, sizeof(Test)* size);
    if (t == NULL)
    {
        fprintf(stderr, "ERREUR");
        exit(EXIT_FAILURE);
    }
    testGetInstructionASM(t, size);

    size += NBRTESTGETOPONEVALUE;
    t = realloc(t, sizeof(Test)* size);
    if (t == NULL)
    {
        fprintf(stderr, "ERREUR");
        exit(EXIT_FAILURE);
    }
    testGetOpOneValue(t, size);

    size += NBRTESTGETOPTWOVALUE;
    t = realloc(t, sizeof(Test)* size);
    if (t == NULL)
    {
        fprintf(stderr, "ERREUR");
        exit(EXIT_FAILURE);
    }
    testGetOpTwoValue(t, size);

    size += NBRTESTEXECOPCODECPU;
    t = realloc(t, sizeof(Test)* size);
    if (t == NULL)
    {
        fprintf(stderr, "ERREUR");
        exit(EXIT_FAILURE);
    }
    testCPUExecOpCode(t, size);

    formatTest(t,false,true,size);

    free(t);
    exit(EXIT_SUCCESS);
}

// int main(void)
// {
//     Test* t = NULL;
//     t = malloc(0);
//     uint32_t sizeTestArray = 0;
//
//     initTest(t, &sizeTestArray, NBRTESTINITCPU, testInitCPU);
//     initTest(t, &sizeTestArray, NBRTESTDECREMENTDELAYSOUND, testDecrementDelaySound);
//     initTest(t, &sizeTestArray, NBRTESTGETINSTRUCTION, testGetInstruction);
//     initTest(t, &sizeTestArray, NBRTESTGETINSTRUCTIONID, testGetInstructionID);
//     //initTest(t, &sizeTestArray, NBRTESTGETINSTRUCTIONASM, testGetInstructionASM);
//     //initTest(t, &sizeTestArray, NBRTESTGETOPONEVALUE, testGetOpOneValue);
//     //initTest(t, &sizeTestArray, NBRTESTGETOPTWOVALUE, testGetOpTwoValue);
//     //initTest(t, &sizeTestArray, NBRTESTEXECOPCODECPU, testCPUExecOpCode);
//
//     formatTest(t,true,true,sizeTestArray);
//
//     free(t);
//     exit(EXIT_SUCCESS);
// }
//

void initTest(Test *t, uint32_t *sizeTestArray, uint32_t nbrTest, uint32_t (*f)(Test *t, uint32_t offset))
{
    *sizeTestArray += nbrTest;
    t = realloc(t,sizeof(t) + (sizeof(Test) * (*sizeTestArray)));
    if (t == NULL)
    {
        fprintf(stderr, "ERROR init test !\n");
        exit(EXIT_FAILURE);
    }
    (*f)(t, *sizeTestArray);
}
