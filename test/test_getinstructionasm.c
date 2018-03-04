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

uint32_t testGetInstructionASM(Test *t, uint32_t offset)
{
    offset -= NBRTESTGETINSTRUCTIONASM;
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

    processTest(t + offset + 0,"getInstructionASM(0x0444) = SYS ", strcmp(getInstructionASM(0x0444, masque, id, instructionASM), "SYS ") == 0);
    processTest(t + offset + 1,"getInstructionASM(0x00E0) = CLS ", strcmp(getInstructionASM(0x00E0, masque, id, instructionASM), "CLS ") == 0);
    processTest(t + offset + 2,"getInstructionASM(0x00EE) = RET ", strcmp(getInstructionASM(0x00EE, masque, id, instructionASM), "RET ") == 0);
    processTest(t + offset + 3,"getInstructionASM(0x1222) = JP  ", strcmp(getInstructionASM(0x1222, masque, id, instructionASM), "JP  ") == 0);
    processTest(t + offset + 4,"getInstructionASM(0x2222) = CALL", strcmp(getInstructionASM(0x2222, masque, id, instructionASM), "CALL") == 0);
    processTest(t + offset + 5,"getInstructionASM(0x3222) = SE  ", strcmp(getInstructionASM(0x3222, masque, id, instructionASM), "SE  ") == 0);
    processTest(t + offset + 6,"getInstructionASM(0x4222) = SNE ", strcmp(getInstructionASM(0x4222, masque, id, instructionASM), "SNE ") == 0);
    processTest(t + offset + 7,"getInstructionASM(0x5220) = SE  ", strcmp(getInstructionASM(0x5222, masque, id, instructionASM), "SE  ") == 0);
    processTest(t + offset + 8,"getInstructionASM(0x6222) = LD  ", strcmp(getInstructionASM(0x6222, masque, id, instructionASM), "LD  ") == 0);
    processTest(t + offset + 9,"getInstructionASM(0x7222) = ADD ", strcmp(getInstructionASM(0x7222, masque, id, instructionASM), "ADD ") == 0);
    processTest(t + offset + 10,"getInstructionASM(0x8220) = LD  ", strcmp(getInstructionASM(0x8220, masque, id, instructionASM), "LD  ") == 0);
    processTest(t + offset + 11,"getInstructionASM(0x8221) = OR  ", strcmp(getInstructionASM(0x8221, masque, id, instructionASM), "OR  ") == 0);
    processTest(t + offset + 12,"getInstructionASM(0x8222) = AND ", strcmp(getInstructionASM(0x8222, masque, id, instructionASM), "AND ") == 0);
    processTest(t + offset + 13,"getInstructionASM(0x8223) = XOR ", strcmp(getInstructionASM(0x8223, masque, id, instructionASM), "XOR ") == 0);
    processTest(t + offset + 14,"getInstructionASM(0x8224) = ADD ", strcmp(getInstructionASM(0x8224, masque, id, instructionASM), "ADD ") == 0);
    processTest(t + offset + 15,"getInstructionASM(0x8225) = SUB ", strcmp(getInstructionASM(0x8225, masque, id, instructionASM), "SUB ") == 0);
    processTest(t + offset + 16,"getInstructionASM(0x8226) = SHR ", strcmp(getInstructionASM(0x8226, masque, id, instructionASM), "SHR ") == 0);
    processTest(t + offset + 17,"getInstructionASM(0x8227) = SUBN", strcmp(getInstructionASM(0x8227, masque, id, instructionASM), "SUBN") == 0);
    processTest(t + offset + 18,"getInstructionASM(0x822E) = SHL ", strcmp(getInstructionASM(0x822E, masque, id, instructionASM), "SHL ") == 0);
    processTest(t + offset + 19,"getInstructionASM(0x9D00) = SNE ", strcmp(getInstructionASM(0x9D00, masque, id, instructionASM), "SNE ") == 0);
    processTest(t + offset + 20,"getInstructionASM(0xAD00) = LD  ", strcmp(getInstructionASM(0xAD00, masque, id, instructionASM), "LD  ") == 0);
    processTest(t + offset + 21,"getInstructionASM(0xBD00) = JP  ", strcmp(getInstructionASM(0xBD00, masque, id, instructionASM), "JP  ") == 0);
    processTest(t + offset + 22,"getInstructionASM(0xCD00) = RND ", strcmp(getInstructionASM(0xCD00, masque, id, instructionASM), "RND ") == 0);
    processTest(t + offset + 23,"getInstructionASM(0xDD00) = DRW ", strcmp(getInstructionASM(0xDD00, masque, id, instructionASM), "DRW ") == 0);
    processTest(t + offset + 24,"getInstructionASM(0xEB9E) = SKP ", strcmp(getInstructionASM(0xEB9E, masque, id, instructionASM), "SKP ") == 0);
    processTest(t + offset + 25,"getInstructionASM(0xEBA1) = SKNP", strcmp(getInstructionASM(0xEBA1, masque, id, instructionASM), "SKNP") == 0);
    processTest(t + offset + 26,"getInstructionASM(0xFB07) = LD  ", strcmp(getInstructionASM(0xFB07, masque, id, instructionASM), "LD  ") == 0);
    processTest(t + offset + 27,"getInstructionASM(0xFB0A) = LD  ", strcmp(getInstructionASM(0xFB0A, masque, id, instructionASM), "LD  ") == 0);
    processTest(t + offset + 28,"getInstructionASM(0xFB15) = LD  ", strcmp(getInstructionASM(0xFB15, masque, id, instructionASM), "LD  ") == 0);
    processTest(t + offset + 29,"getInstructionASM(0xFB18) = LD  ", strcmp(getInstructionASM(0xFB18, masque, id, instructionASM), "LD  ") == 0);
    processTest(t + offset + 30,"getInstructionASM(0xFB1E) = ADD ", strcmp(getInstructionASM(0xFB1E, masque, id, instructionASM), "ADD ") == 0);
    processTest(t + offset + 31,"getInstructionASM(0xFB29) = LD  ", strcmp(getInstructionASM(0xFB29, masque, id, instructionASM), "LD  ") == 0);
    processTest(t + offset + 32,"getInstructionASM(0xFB33) = LD  ", strcmp(getInstructionASM(0xFB33, masque, id, instructionASM), "LD  ") == 0);
    processTest(t + offset + 33,"getInstructionASM(0xFB55) = LD  ", strcmp(getInstructionASM(0xFB55, masque, id, instructionASM), "LD  ") == 0);
    processTest(t + offset + 34,"getInstructionASM(0xFB65) = LD  ", strcmp(getInstructionASM(0xFB65, masque, id, instructionASM), "LD  ") == 0);

    return NBRTESTGETINSTRUCTIONASM;
}

