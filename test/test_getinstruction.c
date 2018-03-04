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

uint32_t testGetInstruction(Test *t, uint32_t offset)
{
    offset = offset - NBRTESTGETINSTRUCTION;
    uint8_t stack[STACK];
    uint16_t stackOpcode[STACK/2];
    uint16_t instructionStack[STACK/2];
    uint16_t masque[NBRINSTRUCTION];
    uint16_t id[NBRINSTRUCTION];
    char* instructionASM[NBRINSTRUCTION];
    FILE* rom = NULL;
    uint32_t size = 0;
    //Cpu cpu;
    init(stack, stackOpcode, instructionStack,
         masque, id, instructionASM, "roms/PONG",
         rom, &size);
    /* execCPU */
    //getInstruction
    processTest(t + offset + 0,"getInstruction(0x0444) = 0", getInstruction(0x0444, masque, id) == 0);
    processTest(t + offset + 1,"getInstruction(0x00E0) = 0x00E0", getInstruction(0x00E0, masque, id) == 0x00E0);
    processTest(t + offset + 2,"getInstruction(0x00EE) = 0x00EE", getInstruction(0x00EE, masque, id) == 0x00EE);
    processTest(t + offset + 3,"getInstruction(0x1222) = 0x1000", getInstruction(0x1222, masque, id) == 0x1000);
    processTest(t + offset + 4,"getInstruction(0x2222) = 0x2000", getInstruction(0x2222, masque, id) == 0x2000);
    processTest(t + offset + 5,"getInstruction(0x3222) = 0x3000", getInstruction(0x3222, masque, id) == 0x3000);
    processTest(t + offset + 6,"getInstruction(0x4222) = 0x4000", getInstruction(0x4222, masque, id) == 0x4000);
    processTest(t + offset + 7,"getInstruction(0x5220) = 0x5000", getInstruction(0x5222, masque, id) == 0x5000);
    processTest(t + offset + 8,"getInstruction(0x6222) = 0x6000", getInstruction(0x6222, masque, id) == 0x6000);
    processTest(t + offset + 9,"getInstruction(0x7222) = 0x7000", getInstruction(0x7222, masque, id) == 0x7000);
    processTest(t + offset + 10,"getInstruction(0x8220) = 0x8000", getInstruction(0x8220, masque, id) == 0x8000);
    processTest(t + offset + 11,"getInstruction(0x8221) = 0x8001", getInstruction(0x8221, masque, id) == 0x8001);
    processTest(t + offset + 12,"getInstruction(0x8222) = 0x8002", getInstruction(0x8222, masque, id) == 0x8002);
    processTest(t + offset + 13,"getInstruction(0x8223) = 0x8003", getInstruction(0x8223, masque, id) == 0x8003);
    processTest(t + offset + 14,"getInstruction(0x8224) = 0x8004", getInstruction(0x8224, masque, id) == 0x8004);
    processTest(t + offset + 15,"getInstruction(0x8225) = 0x8005", getInstruction(0x8225, masque, id) == 0x8005);
    processTest(t + offset + 16,"getInstruction(0x8226) = 0x8006", getInstruction(0x8226, masque, id) == 0x8006);
    processTest(t + offset + 17,"getInstruction(0x8227) = 0x8007", getInstruction(0x8227, masque, id) == 0x8007);
    processTest(t + offset + 18,"getInstruction(0x822E) = 0x800E", getInstruction(0x822E, masque, id) == 0x800E);
    processTest(t + offset + 19,"getInstruction(0x9D00) = 0x9000", getInstruction(0x9D00, masque, id) == 0x9000);
    processTest(t + offset + 20,"getInstruction(0xAD00) = 0xA000", getInstruction(0xAD00, masque, id) == 0xA000);
    processTest(t + offset + 21,"getInstruction(0xBD00) = 0xB000", getInstruction(0xBD00, masque, id) == 0xB000);
    processTest(t + offset + 22,"getInstruction(0xCD00) = 0xC000", getInstruction(0xCD00, masque, id) == 0xC000);
    processTest(t + offset + 23,"getInstruction(0xDD00) = 0xD000", getInstruction(0xDD00, masque, id) == 0xD000);
    processTest(t + offset + 24,"getInstruction(0xEB9E) = 0xE09E", getInstruction(0xEB9E, masque, id) == 0xE09E);
    processTest(t + offset + 25,"getInstruction(0xEBA1) = 0xE0A1", getInstruction(0xEBA1, masque, id) == 0xE0A1);
    processTest(t + offset + 26,"getInstruction(0xFB07) = 0xF007", getInstruction(0xFB07, masque, id) == 0xF007);
    processTest(t + offset + 27,"getInstruction(0xFB0A) = 0xF00A", getInstruction(0xFB0A, masque, id) == 0xF00A);
    processTest(t + offset + 28,"getInstruction(0xFB15) = 0xF015", getInstruction(0xFB15, masque, id) == 0xF015);
    processTest(t + offset + 29,"getInstruction(0xFB18) = 0xF018", getInstruction(0xFB18, masque, id) == 0xF018);
    processTest(t + offset + 30,"getInstruction(0xFB1E) = 0xF01E", getInstruction(0xFB1E, masque, id) == 0xF01E);
    processTest(t + offset + 31,"getInstruction(0xFB29) = 0xF029", getInstruction(0xFB29, masque, id) == 0xF029);
    processTest(t + offset + 32,"getInstruction(0xFB33) = 0xF033", getInstruction(0xFB33, masque, id) == 0xF033);
    processTest(t + offset + 33,"getInstruction(0xFB55) = 0xF055", getInstruction(0xFB55, masque, id) == 0xF055);
    processTest(t + offset + 34,"getInstruction(0xFB65) = 0xF065", getInstruction(0xFB65, masque, id) == 0xF065);

    return NBRTESTGETINSTRUCTION;
}
