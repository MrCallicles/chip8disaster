#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "cpu.h"
#include "stack.h"
#include "define.h"
#include "init.h"
#include "format.h"
#include "test.h"

#define DISPLAY_PASSED 1
#define DISPLAY_NOT_PASSED 2
#define DISPLAY_STATISTICS 4

void formatTest(Test t[BUFFERTEST],bool passed, bool not_passed, uint32_t size){
    /*
     * Flag
     * Constante qui peut être égale à
     * DISPLAY_PASSED --> affiche les tests réussi
     * DISPLAY_NOT_PASSED --> affiche les tests ratés
     * DISPLAY_STATISTICS --> affiche des statistiques sur les test
     *
     */
    uint32_t nPassed = 0;
    uint32_t nNotPassed = 0;
    for(uint8_t i = 0; i < size; i++)
    {
        t[i].pass ? ++nPassed : ++nNotPassed;

        if(t[i].pass && passed)
        {
             printf("\x1B[32m"
                    "PASSED : "
                    "%s"
                    "\x1B[0m"
                    "\n",
                    t[i].strCondition);
        }
        if(!t[i].pass && not_passed)
        {
             printf("\x1B[31m"
                    "NOT PASSED: "
                    "%s"
                    "\x1B[0m"
                    "\n",
                    t[i].strCondition);
        }
            printf("%d test(s) passed\n"
                   "%d test(s) not passed\n",
                   nPassed, nNotPassed);
    }
}

void processTest(Test *t, char* strCond, bool condition)
{
    t->pass = condition;
    if(strlen(strCond) > 128) strncpy(t->strCondition, strCond, 128);
    else strcpy(t->strCondition, strCond);
}

int main(void)
{
    Test t[BUFFERTEST];
    processTest(&t[0], "(getOpcode 0x11 0x22) == 0x1122", (getOpcode(0x11, 0x22) == 0x1122));
    formatTest(t, false, true, 1);
    exit(EXIT_SUCCESS);
}
