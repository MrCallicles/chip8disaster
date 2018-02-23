#ifndef FORMAT_H
#define FORMAT_H
#include "stack.h"
#include <stdlib.h>

#define formatStack_auto() formatStack(rom, stack);
#define fomatOpcode_auto() formatOpcode(stackOpcode[STACK/2], size);

void formatStack(FILE *stream, uint8_t stack[STACK]);
void formatOpcode(uint16_t stackOpcode[STACK/2], uint32_t size);
void formatASM(uint16_t stackOpcode[STACK/2],
               uint16_t instructionStack[STACK/2],
               uint16_t masque[NBRINSTRUCTION],
               uint16_t id[NBRINSTRUCTION],
               char* instructionASM[NBRINSTRUCTION],
               uint32_t size);

#endif
