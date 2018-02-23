#ifndef INIT_H
#define INIT_H

#define STACK_INIT 1000
#define NBRINSTRUCTION_INIT 35

void init(uint8_t stack[STACK_INIT],
          uint16_t stackOpcode[STACK_INIT/2],
          uint16_t instructionStack[STACK_INIT/2],
          uint16_t masque[NBRINSTRUCTION_INIT],
          uint16_t id[NBRINSTRUCTION_INIT],
          char* instructionASM[NBRINSTRUCTION_INIT],
          char* pathRom,
          FILE *rom,
          uint32_t *size);

#endif
