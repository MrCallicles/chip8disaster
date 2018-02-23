#include "define.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "init.h"
#include "format.h"
#include "stack.h"

void init(uint8_t stack[STACK_INIT],
          uint16_t stackOpCode[STACK_INIT/2],
          uint16_t instructionStack[STACK_INIT/2],
          uint16_t masque[NBRINSTRUCTION_INIT],
          uint16_t id[NBRINSTRUCTION_INIT],
          char* instructionASM[NBRINSTRUCTION_INIT],
          char* pathRom,
          FILE* rom,
          uint32_t* size){
    initialiseMask_Id_ASM(masque, id, instructionASM);
    rom = fopen(pathRom, "rb");
    if(rom == NULL)
    {
        fprintf(stderr, "impossible d'ouvrir la rom\n");
        exit(EXIT_FAILURE);
    }
    fread(&stack[0],sizeof(uint8_t)*(STACK_INIT), 1, rom);
    *size = sizeRom(rom);
    storeOpcode(stack, stackOpCode, *size);
    storeInstruction(stackOpCode, instructionStack, masque, id, *size);
    fclose(rom);
}

