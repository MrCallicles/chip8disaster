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

uint32_t testGetOpTwoValue(Test *t, uint32_t offset)
{
    offset -= NBRTESTGETOPTWOVALUE;
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

    processTest(t + offset + 0,"getOpTwoValue(0x0111) = 0x111", getOpTwoValue(0x0111, masque, id) == 0x111);
    processTest(t + offset + 1,"getOpTwoValue(0x00E0) = 0x0",   getOpTwoValue(0x00E0, masque, id) == 0x0);
    processTest(t + offset + 2,"getOpTwoValue(0x00EE) = 0x0",   getOpTwoValue(0x00EE, masque, id) == 0x0);
    processTest(t + offset + 3,"getOpTwoValue(0x1222) = 0x222", getOpTwoValue(0x1222, masque, id) == 0x222);
    processTest(t + offset + 4,"getOpTwoValue(0x2222) = 0x222", getOpTwoValue(0x2222, masque, id) == 0x222);
    processTest(t + offset + 5,"getOpTwoValue(0x3A55) = 0x55",  getOpTwoValue(0x3A55, masque, id) == 0x55);
    processTest(t + offset + 6,"getOpTwoValue(0x4A55) = 0x55",  getOpTwoValue(0x4A55, masque, id) == 0x55);
    processTest(t + offset + 7,"getOpTwoValue(0x5A50) = 0x5",   getOpTwoValue(0x5A50, masque, id) == 0x5);
    processTest(t + offset + 8,"getOpTwoValue(0x6A50) = 0x50",  getOpTwoValue(0x6A50, masque, id) == 0x50);
    processTest(t + offset + 9,"getOpTwoValue(0x7B44) = 0x44",  getOpTwoValue(0x7B44, masque, id) == 0x44);
    processTest(t + offset + 10,"getOpTwoValue(0x8CA0) = 0xA",   getOpTwoValue(0x8CA0, masque, id) == 0xA);
    processTest(t + offset + 11,"getOpTwoValue(0x89A1) = 0xA",   getOpTwoValue(0x89A1, masque, id) == 0xA);
    processTest(t + offset + 12,"getOpTwoValue(0x89A2) = 0xA",   getOpTwoValue(0x89A2, masque, id) == 0xA);
    processTest(t + offset + 13,"getOpTwoValue(0x89A3) = 0xA",   getOpTwoValue(0x89A3, masque, id) == 0xA);
    processTest(t + offset + 14,"getOpTwoValue(0x89A4) = 0xA",   getOpTwoValue(0x89A4, masque, id) == 0xA);
    processTest(t + offset + 15,"getOpTwoValue(0x89A5) = 0xA",   getOpTwoValue(0x89A5, masque, id) == 0xA);
    processTest(t + offset + 16,"getOpTwoValue(0x89A6) = 0xA",   getOpTwoValue(0x89A6, masque, id) == 0xA);
    processTest(t + offset + 17,"getOpTwoValue(0x89A7) = 0xA",   getOpTwoValue(0x89A7, masque, id) == 0xA);
    processTest(t + offset + 18,"getOpTwoValue(0x89AE) = 0xA",   getOpTwoValue(0x89AE, masque, id) == 0xA);
    processTest(t + offset + 19,"getOpTwoValue(0x95F0) = 0xF",   getOpTwoValue(0x95F0, masque, id) == 0xF);
    processTest(t + offset + 20,"getOpTwoValue(0xA555) = 0x555", getOpTwoValue(0xA555, masque, id) == 0x555);
    processTest(t + offset + 21,"getOpTwoValue(0xB555) = 0x555", getOpTwoValue(0xB555, masque, id) == 0x555);
    processTest(t + offset + 22,"getOpTwoValue(0xCB77) = 0x77",  getOpTwoValue(0xCB77, masque, id) == 0x77);
    processTest(t + offset + 23,"getOpTwoValue(0xD347) = 0x47",  getOpTwoValue(0xD347, masque, id) == 0x47);
    processTest(t + offset + 24,"getOpTwoValue(0xEA9E) = 0x0",   getOpTwoValue(0xEA9E, masque, id) == 0x0);
    processTest(t + offset + 25,"getOpTwoValue(0xEAA1) = 0x0",   getOpTwoValue(0xEAA1, masque, id) == 0x0);
    processTest(t + offset + 26,"getOpTwoValue(0xF107) = 0x1",   getOpTwoValue(0xF107, masque, id) == 0x1);
    processTest(t + offset + 27,"getOpTwoValue(0xF20A) = 0x2",   getOpTwoValue(0xF20A, masque, id) == 0x2);
    processTest(t + offset + 28,"getOpTwoValue(0xF515) = 0x5",   getOpTwoValue(0xF515, masque, id) == 0x5);
    processTest(t + offset + 29,"getOpTwoValue(0xF818) = 0x8",   getOpTwoValue(0xF818, masque, id) == 0x8);
    processTest(t + offset + 30,"getOpTwoValue(0xFC1E) = 0xC",   getOpTwoValue(0xFC1E, masque, id) == 0xC);
    processTest(t + offset + 31,"getOpTwoValue(0xFD29) = 0xD",   getOpTwoValue(0xFD29, masque, id) == 0xD);
    processTest(t + offset + 32,"getOpTwoValue(0xFE33) = 0xE",   getOpTwoValue(0xFE33, masque, id) == 0xE);
    processTest(t + offset + 33,"getOpTwoValue(0xFA55) = 0xA",   getOpTwoValue(0xfA55, masque, id) == 0xA);
    processTest(t + offset + 34,"getOpTwoValue(0xF965) = 0x0",   getOpTwoValue(0xf965, masque, id) == 0x0);
    return NBRTESTGETOPTWOVALUE;
}
