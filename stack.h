#ifndef STACK_H
#define STACK_H

#define STACK 1000
#define NBRINSTRUCTION 35


uint32_t sizeRom(FILE *stream);
uint16_t getOpcode(uint8_t part1, uint8_t part2);
void storeOpcode(uint8_t stack[STACK],
                 uint16_t stackOpcode[STACK/2],
                uint32_t sizeRom);
void initialiseMask_Id_ASM(uint16_t masque[NBRINSTRUCTION],
                           uint16_t id[NBRINSTRUCTION],
                           char* instructionASM[NBRINSTRUCTION]);
uint16_t getInstruction(uint16_t opcode,
                        uint16_t masque[NBRINSTRUCTION],
                        uint16_t id[NBRINSTRUCTION]);
uint8_t getInstructionID(uint16_t opcode,
                         uint16_t masque[NBRINSTRUCTION],
                         uint16_t id[NBRINSTRUCTION]);
void storeInstruction(uint16_t stackOpcode[STACK/2],
                      uint16_t instructionStack[STACK/2],
                      uint16_t masque[NBRINSTRUCTION],
                      uint16_t id[NBRINSTRUCTION],
                      uint32_t size);
void getOpOne(uint16_t opcode,
              uint16_t masque[NBRINSTRUCTION],
              uint16_t id[NBRINSTRUCTION],
              char* str);
void getOpTwo(uint16_t opcode,
              uint16_t masque[NBRINSTRUCTION],
              uint16_t id[NBRINSTRUCTION],
              char* str);
uint16_t getOpOneValue(uint16_t opcode,
              uint16_t masque[NBRINSTRUCTION],
              uint16_t id[NBRINSTRUCTION]);
uint16_t getOpTwoValue(uint16_t opcode,
              uint16_t masque[NBRINSTRUCTION],
              uint16_t id[NBRINSTRUCTION]);
char* getInstructionASM(uint16_t opcode,
                        uint16_t masque[NBRINSTRUCTION],
                        uint16_t id[NBRINSTRUCTION],
                        char* instructionASM[NBRINSTRUCTION]);

#endif
