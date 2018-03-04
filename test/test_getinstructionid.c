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

uint32_t testGetInstructionID(Test *t, uint32_t offset)
{
    offset = offset - NBRTESTGETINSTRUCTIONID;

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

    processTest(t + offset + 0,"getInstructionID(0x0444) = 2",  getInstructionID(0x0444, masque, id) == 2);
    processTest(t + offset + 1,"getInstructionID(0x00E0) = 0",  getInstructionID(0x00E0, masque, id) == 0);
    processTest(t + offset + 2,"getInstructionID(0x00EE) = 1",  getInstructionID(0x00EE, masque, id) == 1);
    processTest(t + offset + 3,"getInstructionID(0x1222) = 3",  getInstructionID(0x1222, masque, id) == 3);
    processTest(t + offset + 4,"getInstructionID(0x2222) = 4",  getInstructionID(0x2222, masque, id) == 4);
    processTest(t + offset + 5,"getInstructionID(0x3222) = 5",  getInstructionID(0x3222, masque, id) == 5);
    processTest(t + offset + 6,"getInstructionID(0x4222) = 6",  getInstructionID(0x4222, masque, id) == 6);
    processTest(t + offset + 7,"getInstructionID(0x5220) = 7",  getInstructionID(0x5222, masque, id) == 7);
    processTest(t + offset + 8,"getInstructionID(0x6222) = 8",  getInstructionID(0x6222, masque, id) == 8);
    processTest(t + offset + 9,"getInstructionID(0x7222) = 9",  getInstructionID(0x7222, masque, id) == 9);
    processTest(t + offset + 10,"getInstructionID(0x8220) = 10", getInstructionID(0x8220, masque, id) == 10);
    processTest(t + offset + 11,"getInstructionID(0x8221) = 11", getInstructionID(0x8221, masque, id) == 11);
    processTest(t + offset + 12,"getInstructionID(0x8222) = 12", getInstructionID(0x8222, masque, id) == 12);
    processTest(t + offset + 13,"getInstructionID(0x8223) = 13", getInstructionID(0x8223, masque, id) == 13);
    processTest(t + offset + 14,"getInstructionID(0x8224) = 14", getInstructionID(0x8224, masque, id) == 14);
    processTest(t + offset + 15,"getInstructionID(0x8225) = 15", getInstructionID(0x8225, masque, id) == 15);
    processTest(t + offset + 16,"getInstructionID(0x8226) = 16", getInstructionID(0x8226, masque, id) == 16);
    processTest(t + offset + 17,"getInstructionID(0x8227) = 17", getInstructionID(0x8227, masque, id) == 17);
    processTest(t + offset + 18,"getInstructionID(0x822E) = 18", getInstructionID(0x822E, masque, id) == 18);
    processTest(t + offset + 19,"getInstructionID(0x9D00) = 19", getInstructionID(0x9D00, masque, id) == 19);
    processTest(t + offset + 20,"getInstructionID(0xAD00) = 20", getInstructionID(0xAD00, masque, id) == 20);
    processTest(t + offset + 21,"getInstructionID(0xBD00) = 21", getInstructionID(0xBD00, masque, id) == 21);
    processTest(t + offset + 22,"getInstructionID(0xCD00) = 22", getInstructionID(0xCD00, masque, id) == 22);
    processTest(t + offset + 23,"getInstructionID(0xDD00) = 23", getInstructionID(0xDD00, masque, id) == 23);
    processTest(t + offset + 24,"getInstructionID(0xEB9E) = 24", getInstructionID(0xEB9E, masque, id) == 24);
    processTest(t + offset + 25,"getInstructionID(0xEBA1) = 25", getInstructionID(0xEBA1, masque, id) == 25);
    processTest(t + offset + 26,"getInstructionID(0xFB07) = 26", getInstructionID(0xFB07, masque, id) == 26);
    processTest(t + offset + 27,"getInstructionID(0xFB0A) = 27", getInstructionID(0xFB0A, masque, id) == 27);
    processTest(t + offset + 28,"getInstructionID(0xFB15) = 28", getInstructionID(0xFB15, masque, id) == 28);
    processTest(t + offset + 29,"getInstructionID(0xFB18) = 29", getInstructionID(0xFB18, masque, id) == 29);
    processTest(t + offset + 30,"getInstructionID(0xFB1E) = 30", getInstructionID(0xFB1E, masque, id) == 30);
    processTest(t + offset + 31,"getInstructionID(0xFB29) = 31", getInstructionID(0xFB29, masque, id) == 31);
    processTest(t + offset + 32,"getInstructionID(0xFB33) = 32", getInstructionID(0xFB33, masque, id) == 32);
    processTest(t + offset + 33,"getInstructionID(0xFB55) = 33", getInstructionID(0xFB55, masque, id) == 33);
    processTest(t + offset + 34,"getInstructionID(0xFB65) = 34", getInstructionID(0xFB65, masque, id) == 34);

    return NBRTESTGETINSTRUCTIONID;
}
