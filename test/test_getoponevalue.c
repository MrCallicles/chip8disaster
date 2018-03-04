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

uint32_t testGetOpOneValue(Test *t, uint32_t offset)
{
    offset -= NBRTESTGETOPONEVALUE;
    uint8_t stack[STACK];
    uint16_t stackOpcode[STACK/2];
    uint16_t instructionStack[STACK/2];
    uint16_t masque[NBRINSTRUCTION];
    uint16_t id[NBRINSTRUCTION];
    char* instructionASM[NBRINSTRUCTION];
    FILE* rom = NULL;
    uint32_t size = 0;
    init(stack, stackOpcode, instructionStack,
         masque, id, instructionASM, "roms/PONG",
         rom, &size);

    processTest(t + offset + 0,"getOpOneValue(0x0111) = 0x111", getOpOneValue(0x0111, masque, id) == 0x111);
    processTest(t + offset + 1,"getOpOneValue(0x00E0) = 0x0", getOpOneValue(0x00E0, masque, id) == 0x0);
    processTest(t + offset + 2,"getOpOneValue(0x00EE) = 0x0", getOpOneValue(0x00EE, masque, id) == 0x0);
    processTest(t + offset + 3,"getOpOneValue(0x1222) = 0x222", getOpOneValue(0x1222, masque, id) == 0x222);
    processTest(t + offset + 4,"getOpOneValue(0x2222) = 0x222", getOpOneValue(0x2222, masque, id) == 0x222);
    processTest(t + offset + 5,"getOpOneValue(0x3A55) = 0xA", getOpOneValue(0x3A55, masque, id) == 0xA);
    processTest(t + offset + 6,"getOpOneValue(0x4A55) = 0xA", getOpOneValue(0x4A55, masque, id) == 0xA);
    processTest(t + offset + 7,"getOpOneValue(0x5A50) = 0xA", getOpOneValue(0x5A50, masque, id) == 0xA);
    processTest(t + offset + 8,"getOpOneValue(0x6A50) = 0xA", getOpOneValue(0x6A50, masque, id) == 0xA);
    processTest(t + offset + 9,"getOpOneValue(0x7B44) = 0xB", getOpOneValue(0x7B44, masque, id) == 0xB);
    processTest(t + offset + 10,"getOpOneValue(0x8CA0) = 0xC", getOpOneValue(0x8CA0, masque, id) == 0xC);
    processTest(t + offset + 11,"getOpOneValue(0x89A1) = 0x9", getOpOneValue(0x89A1, masque, id) == 0x9);
    processTest(t + offset + 12,"getOpOneValue(0x89A2) = 0x9", getOpOneValue(0x89A2, masque, id) == 0x9);
    processTest(t + offset + 13,"getOpOneValue(0x89A3) = 0x9", getOpOneValue(0x89A3, masque, id) == 0x9);
    processTest(t + offset + 14,"getOpOneValue(0x89A4) = 0x9", getOpOneValue(0x89A4, masque, id) == 0x9);
    processTest(t + offset + 15,"getOpOneValue(0x89A5) = 0x9", getOpOneValue(0x89A5, masque, id) == 0x9);
    processTest(t + offset + 16,"getOpOneValue(0x89A6) = 0x9", getOpOneValue(0x89A6, masque, id) == 0x9);
    processTest(t + offset + 17,"getOpOneValue(0x89A7) = 0x9", getOpOneValue(0x89A7, masque, id) == 0x9);
    processTest(t + offset + 18,"getOpOneValue(0x89AE) = 0x9", getOpOneValue(0x89AE, masque, id) == 0x9);
    processTest(t + offset + 19,"getOpOneValue(0x95F0) = 0x5", getOpOneValue(0x95F0, masque, id) == 0x5);
    processTest(t + offset + 20,"getOpOneValue(0xA555) = 0x555", getOpOneValue(0xA555, masque, id) == 0x555);
    processTest(t + offset + 21,"getOpOneValue(0xB555) = 0x555", getOpOneValue(0xB555, masque, id) == 0x555);
    processTest(t + offset + 22,"getOpOneValue(0xCB77) = 0xB", getOpOneValue(0xCB77, masque, id) == 0xB);
    processTest(t + offset + 23,"getOpOneValue(0xD347) = 0x3", getOpOneValue(0xD347, masque, id) == 0x3);
    processTest(t + offset + 24,"getOpOneValue(0xEA9E) = 0xA", getOpOneValue(0xEA9E, masque, id) == 0xA);
    processTest(t + offset + 25,"getOpOneValue(0xEAA1) = 0xA", getOpOneValue(0xEAA1, masque, id) == 0xA);
    processTest(t + offset + 26,"getOpOneValue(0xF107) = 0x1", getOpOneValue(0xF107, masque, id) == 0x1);
    processTest(t + offset + 27,"getOpOneValue(0xF20A) = 0x2", getOpOneValue(0xF20A, masque, id) == 0x2);
    processTest(t + offset + 28,"getOpOneValue(0xF515) = 0x5", getOpOneValue(0xF515, masque, id) == 0x5);
    processTest(t + offset + 29,"getOpOneValue(0xF818) = 0x8", getOpOneValue(0xF818, masque, id) == 0x8);
    processTest(t + offset + 30,"getOpOneValue(0xFC1E) = 0xC", getOpOneValue(0xFC1E, masque, id) == 0xC);
    processTest(t + offset + 31,"getOpOneValue(0xFD29) = 0xD", getOpOneValue(0xFD29, masque, id) == 0xD);
    processTest(t + offset + 32,"getOpOneValue(0xFE33) = 0xE", getOpOneValue(0xFE33, masque, id) == 0xE);
    processTest(t + offset + 33,"getOpOneValue(0xFA55) = 0xA", getOpOneValue(0xfA55, masque, id) == 0xA);
    processTest(t + offset + 34,"getOpOneValue(0xF965) = 0x9", getOpOneValue(0xf965, masque, id) == 0x9);
    return NBRTESTGETOPONEVALUE;
}

