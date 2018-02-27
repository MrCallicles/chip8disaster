#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "stack.h"
#include "format.h"
#include "init.h"

uint32_t sizeRom(FILE *stream)
{
    /*
     * Renvoi la taille de la rom
     */
    rewind(stream);
    for(uint16_t i = 0; i < STACK; i++)
    {
        if(getc(stream) == EOF)
        {
            rewind(stream);
            return i;
        }
    }
    rewind(stream);
    return -1;
}

uint16_t getOpcode(uint8_t part1, uint8_t part2)
{
    /*
     * Prend deux valeurs uint8_t et le place dans un
     * uint16_t par décalage à gauche
     * Permet d'obtenir les opcode à partir
     * du fichier
     *
     */
    return (part1 << 8) + part2;
}

void storeOpcode(uint8_t stack[STACK], uint16_t stackOpcode[STACK/2], uint32_t sizeRom)
{
    /*
     * Prend une stack uint8_t et la met dans une uint16_t en utilisant getOpcode
     */
    for(uint16_t i = 0, j = 0; i < sizeRom/2; i++, j += 2)
    {
        stackOpcode[i] = getOpcode(stack[j], stack[j+1]);
    }
}

void initialiseMask_Id_ASM(uint16_t masque[NBRINSTRUCTION], uint16_t id[NBRINSTRUCTION],
                           char* instructionASM[NBRINSTRUCTION])
{
    //initialise Masque et id
    //ne le fait que si init = 0
    static bool init = false;
    if(init == false){
        masque[0]= 0xFFFF;  id[0]=0x00E0;  instructionASM[0] = "CLS ";/* 00E0 */
        masque[1]= 0xFFFF;  id[1]=0x00EE;  instructionASM[1] = "RET ";/* 00EE */
        masque[2]= 0xF000;  id[2]=0x0000;  instructionASM[2] = "SYS ";/* 0NNN */
        masque[3]= 0xF000;  id[3]=0x1000;  instructionASM[3] = "JP  ";/* 1NNN */
        masque[4]= 0xF000;  id[4]=0x2000;  instructionASM[4] = "CALL";/* 2NNN */
        masque[5]= 0xF000;  id[5]=0x3000;  instructionASM[5] = "SE  ";/* 3XNN */
        masque[6]= 0xF000;  id[6]=0x4000;  instructionASM[6] = "SNE ";/* 4XNN */
        masque[7]= 0xF000;  id[7]=0x5000;  instructionASM[7] = "SE  ";/* 5XY0 */
        masque[8]= 0xF000;  id[8]=0x6000;  instructionASM[8] = "LD  ";/* 6XNN */
        masque[9]= 0xF000;  id[9]=0x7000;  instructionASM[9] = "ADD ";/* 7XNN */
        masque[10]= 0xF00F; id[10]=0x8000; instructionASM[10] = "LD  "; /* 8XY0 */
        masque[11]= 0xF00F; id[11]=0x8001; instructionASM[11] = "OR  "; /* 8XY1 */
        masque[12]= 0xF00F; id[12]=0x8002; instructionASM[12] = "AND "; /* 8XY2 */
        masque[13]= 0xF00F; id[13]=0x8003; instructionASM[13] = "XOR "; /* BXY3 */
        masque[14]= 0xF00F; id[14]=0x8004; instructionASM[14] = "ADD "; /* 8XY4 */
        masque[15]= 0xF00F; id[15]=0x8005; instructionASM[15] = "SUB "; /* 8XY5 */
        masque[16]= 0xF00F; id[16]=0x8006; instructionASM[16] = "SHR "; /* 8XY6 */
        masque[17]= 0xF00F; id[17]=0x8007; instructionASM[17] = "SUBN"; /* 8XY7 */
        masque[18]= 0xF00F; id[18]=0x800E; instructionASM[18] = "SHL "; /* 8XYE */
        masque[19]= 0xF00F; id[19]=0x9000; instructionASM[19] = "SNE "; /* 9XY0 */
        masque[20]= 0xF000; id[20]=0xA000; instructionASM[20] = "LD  "; /* ANNN */
        masque[21]= 0xF000; id[21]=0xB000; instructionASM[21] = "JP  "; /* BNNN */
        masque[22]= 0xF000; id[22]=0xC000; instructionASM[22] = "RND "; /* CXNN */
        masque[23]= 0xF000; id[23]=0xD000; instructionASM[23] = "DRW "; /* DXYN */
        masque[24]= 0xF0FF; id[24]=0xE09E; instructionASM[24] = "SKP "; /* EX9E */
        masque[25]= 0xF0FF; id[25]=0xE0A1; instructionASM[25] = "SKNP"; /* EXA1 */
        masque[26]= 0xF0FF; id[26]=0xF007; instructionASM[26] = "LD  "; /* FX07 */
        masque[27]= 0xF0FF; id[27]=0xF00A; instructionASM[27] = "LD  "; /* FX0A */
        masque[28]= 0xF0FF; id[28]=0xF015; instructionASM[28] = "LD  "; /* FX15 */
        masque[29]= 0xF0FF; id[29]=0xF018; instructionASM[29] = "LD  "; /* FX18 */
        masque[30]= 0xF0FF; id[30]=0xF01E; instructionASM[30] = "ADD "; /* FX1E */
        masque[31]= 0xF0FF; id[31]=0xF029; instructionASM[31] = "LD  "; /* FX29 */
        masque[32]= 0xF0FF; id[32]=0xF033; instructionASM[32] = "LD  "; /* FX33 */
        masque[33]= 0xF0FF; id[33]=0xF055; instructionASM[33] = "LD  "; /* FX55 */
        masque[34]= 0xF0FF; id[34]=0xF065; instructionASM[34] = "LD  "; /* FX65 */
        init = true;
    }
}

/*
 * A remplacer par getInstructionID
 * qui renvoi i au lieu de str...
 */
uint16_t getInstruction(uint16_t opcode,
                    uint16_t masque[NBRINSTRUCTION],
                    uint16_t id[NBRINSTRUCTION])
{
    uint16_t tmp = 0;
    for(uint8_t i = 0; i < NBRINSTRUCTION; i++)
    {
        tmp = opcode & masque[i];
        if(tmp == id[i]){
            break;
        }
    }
    return tmp;
}

uint8_t getInstructionID(uint16_t opcode,
                    uint16_t masque[NBRINSTRUCTION],
                    uint16_t id[NBRINSTRUCTION])
{
    uint16_t tmp = 0;
    for(uint8_t i = 0; i < NBRINSTRUCTION; i++)
    {
        tmp = opcode & masque[i];
        if(tmp == id[i]) return i;

    }
    return 0;
}

char* getInstructionASM(uint16_t opcode,
                        uint16_t masque[NBRINSTRUCTION],
                        uint16_t id[NBRINSTRUCTION],
                        char* instructionASM[NBRINSTRUCTION])
{
    uint16_t tmp;
    char* str;
    for(uint8_t i = 0; i < NBRINSTRUCTION; i++)
    {
        tmp = opcode & masque[i];
        str = instructionASM[i];
        if(tmp == id[i]) break;
    }
    return str;
}

void storeInstruction(uint16_t stackOpcode[STACK/2],
                      uint16_t instructionStack[STACK/2],
                      uint16_t masque[NBRINSTRUCTION],
                      uint16_t id[NBRINSTRUCTION],
                      uint32_t size)
{
    for(uint16_t i = 0; i < size/2; i++)
    {
        instructionStack[i] = getInstruction(stackOpcode[i], masque, id);
    }
}

void getOpOne(uint16_t opcode,
              uint16_t masque[NBRINSTRUCTION],
              uint16_t id[NBRINSTRUCTION],
              char* str)
{
    uint16_t op = getInstruction(opcode, masque, id);
    switch(op)
    {
        case 0x0000: sprintf(str, "0x%x", (opcode & 0x0FFF)); break; //SYS addr
        case 0x00E0: sprintf(str, " "); break; //CLS
        case 0x00EE: sprintf(str, " "); break; //RET
        case 0x1000: sprintf(str, "0x%x", (opcode & 0x0FFF)); break; //JMP addr
        case 0x2000: sprintf(str, "0x%x", (opcode & 0x0FFF)); break;//CALL addr
        case 0x3000: sprintf(str, "V%x", (opcode & 0x0F00) >> 8); break;//SE Vx,kk
        case 0x4000: sprintf(str, "V%x", (opcode & 0x0F00) >> 8); break;//SNE Vx,kk
        case 0x5000: sprintf(str, "V%x", (opcode & 0x0F00) >> 8); break;//SE Vx,Vy
        case 0x6000: sprintf(str, "V%x", (opcode & 0x0F00) >> 8); break;//SE Vx,Vy
        case 0x7000: sprintf(str, "V%x", (opcode & 0x0F00) >> 8); break;//ADD Vx,kk
        case 0x8000: sprintf(str, "V%x", (opcode & 0x0F00) >> 8); break;//LD Vx,Vy
        case 0x8001: sprintf(str, "V%x", (opcode & 0x0F00) >> 8); break;//OR Vx,Vy
        case 0x8002: sprintf(str, "V%x", (opcode & 0x0F00) >> 8); break;//AND Vx,Vy
        case 0x8003: sprintf(str, "V%x", (opcode & 0x0F00) >> 8); break;//XOR Vx,Vy
        case 0x8004: sprintf(str, "V%x", (opcode & 0x0F00) >> 8); break;//ADD Vx,Vy
        case 0x8005: sprintf(str, "V%x", (opcode & 0x0F00) >> 8); break;//SUB Vx,Vy
        case 0x8006: sprintf(str, "V%x", (opcode & 0x0F00) >> 8); break;//SHR Vx {,Vy}
        case 0x8007: sprintf(str, "V%x", (opcode & 0x0F00) >> 8); break;//SUBN Vx,Vy
        case 0x800E: sprintf(str, "V%x", (opcode & 0x0F00) >> 8); break;//SHL Vx {,Vy}
        case 0x9000: sprintf(str, "V%x", (opcode & 0x0F00) >> 8); break;//SNE Vx,Vy
        case 0xA000: sprintf(str,"I"); break; //LD I, addr
        case 0xB000: sprintf(str,"V0"); break;
        case 0xC000: sprintf(str, "V%x", (opcode & 0x0F00) >> 8); break;//RND Vx, byte
        case 0xD000: sprintf(str, "V%x", (opcode & 0x0F00) >> 8); break;//DRW Vx,Vy, nibble
        case 0xE09E: sprintf(str, "V%x", (opcode & 0x0F00) >> 8); break;//SKP Vx
        case 0xE0A1: sprintf(str, "V%x", (opcode & 0x0F00) >> 8); break;//SKNP Vx
        case 0xF007: sprintf(str, "V%x", (opcode & 0x0F00) >> 8); break;//LD Vx, DT
        case 0xF00A: sprintf(str, "V%x", (opcode & 0x0F00) >> 8); break;//LD Vx, K
        case 0xF015: sprintf(str, "DT"); //LD DT, Vx
        case 0xF018: sprintf(str, "V%x", (opcode & 0x0F00) >> 8); break;//LD Vx, K
        case 0xF01E: sprintf(str, "I"); break; //ADD I,Vx
        case 0xF029: sprintf(str,"F"); break;//LD F, Vx
        case 0xF033: sprintf(str,"B"); break;//LD B,Vx
        case 0xF055: sprintf(str,"[I]"); break;//LD [I], Vx
        case 0xF065: sprintf(str, "V%x", (opcode & 0x0F00) >> 8); break;//LD Vx, [I]
        default: sprintf(str, "RMAC"); break;
    }
}
void getOpTwo(uint16_t opcode,
              uint16_t masque[NBRINSTRUCTION],
              uint16_t id[NBRINSTRUCTION],
              char* str)
{
    uint16_t op = getInstruction(opcode, masque, id);
    switch(op)
    {
        case 0x0000: sprintf(str, " "); break; //SYS addr
        case 0x00E0: sprintf(str, " "); break; //CLS
        case 0x00EE: sprintf(str, " "); break; //RET
        case 0x1000: sprintf(str, " "); break; //JMP addr
        case 0x2000: sprintf(str, " "); break;//CALL addr
        case 0x3000: sprintf(str, "0x%x", (opcode & 0x00FF)); break;//SE Vx,kk
        case 0x4000: sprintf(str, "0x%x", (opcode & 0x00FF)); break;//SNE Vx,kk
        case 0x5000: sprintf(str, "V%x", (opcode & 0x00F0) >> 4); break;//SE Vx,Vy
        case 0x6000: sprintf(str, "0x%x", (opcode & 0x00FF)); break;//LD Vx,kk
        case 0x7000: sprintf(str, "0x%x", (opcode & 0x00FF)); break;//ADD Vx,kk
        case 0x8000: sprintf(str, "V%x", (opcode & 0x00F0) >> 4); break;//LD Vx,Vy
        case 0x8001: sprintf(str, "V%x", (opcode & 0x00F0) >> 4); break;//OR Vx,Vy
        case 0x8002: sprintf(str, "V%x", (opcode & 0x00F0) >> 4); break;//AND Vx,Vy
        case 0x8003: sprintf(str, "V%x", (opcode & 0x00F0) >> 4); break;//XOR Vx,Vy
        case 0x8004: sprintf(str, "V%x", (opcode & 0x00F0) >> 4); break;//ADD Vx,Vy
        case 0x8005: sprintf(str, "V%x", (opcode & 0x00F0) >> 4); break;//SUB Vx,Vy
        case 0x8006: sprintf(str, "{V%x}", (opcode & 0x00F0) >> 4); break;//SHR Vx {,Vy}
        case 0x8007: sprintf(str, "V%x", (opcode & 0x00F0) >> 4); break;//SUBN Vx,Vy
        case 0x800E: sprintf(str, "{V%x}", (opcode & 0x00F0) >> 4); break;//SHL Vx {,Vy}
        case 0x9000: sprintf(str, "V%x", (opcode & 0x00F0) >> 4); break;//SNE Vx,Vy
        case 0xA000: sprintf(str, "0x%x", (opcode & 0x0FFF)); break; //LD I, addr
        case 0xB000: sprintf(str, "0x%x", (opcode & 0x0FFF)); break;
        case 0xC000: sprintf(str, "0x%x", (opcode & 0x00FF)); break;//RND Vx, byte
        case 0xD000: sprintf(str, "V%x, %x", (opcode & 0x00F0) >> 4, (opcode & 0x000F)); break;//DRW Vx,Vy, nibble
        case 0xE09E: sprintf(str, " "); break;//SKP Vx
        case 0xE0A1: sprintf(str, " "); break;//SKNP Vx
        case 0xF007: sprintf(str, "DT"); break;//LD Vx, DT
        case 0xF00A: sprintf(str, "K"); break;//LD Vx, K
        case 0xF015: sprintf(str, "V%x", (opcode & 0x0F00) >> 8); break;//LD DT, Vx
        case 0xF018: sprintf(str, "K"); break;//LD Vx, K
        case 0xF01E: sprintf(str,"V%x", (opcode & 0x0F00) >> 8); break; //ADD I,Vx
        case 0xF029: sprintf(str,"V%x", (opcode & 0x0F00) >> 8); break;//LD F, Vx
        case 0xF033: sprintf(str,"V%x", (opcode & 0x0F00) >> 8); break;//LD B,Vx
        case 0xF055: sprintf(str,"V%x", (opcode & 0x0F00) >> 8); break;//LD [I], Vx
        case 0xF065: sprintf(str, "[I]"); break;//LD Vx, [I]
        default: sprintf(str, "RMAC"); break;
    }
}

uint16_t getOpOneValue(uint16_t opcode,
              uint16_t masque[NBRINSTRUCTION],
              uint16_t id[NBRINSTRUCTION])
{
    uint16_t op = getInstruction(opcode, masque, id);
    switch(op)
    {
        case 0x0000: return (opcode & 0xFFFF); //SYS Addr
        case 0x00E0: return 0; //CLS
        case 0x00EE: return 0; //RET
        case 0x1000: return (opcode & 0x0FFF); //JMP addr
        case 0x2000: return (opcode & 0x0FFF); //CALL addr
        case 0x3000: return ((opcode & 0x0F00) >> 8); //SE Vx,kk
        case 0x4000: return ((opcode & 0x0F00) >> 8); //SNE Vx,kk
        case 0x5000: return ((opcode & 0x0F00) >> 8); //SE Vx,Vy
        case 0x6000: return ((opcode & 0x0F00) >> 8); //SE Vx,Vy
        case 0x7000: return ((opcode & 0x0F00) >> 8); //ADD Vx,kk
        case 0x8000: return ((opcode & 0x0F00) >> 8); //LD Vx,Vy
        case 0x8001: return ((opcode & 0x0F00) >> 8); //OR Vx,Vy
        case 0x8002: return ((opcode & 0x0F00) >> 8); //AND Vx,Vy
        case 0x8003: return ((opcode & 0x0F00) >> 8); //XOR Vx,Vy
        case 0x8004: return ((opcode & 0x0F00) >> 8); //ADD Vx,Vy
        case 0x8005: return ((opcode & 0x0F00) >> 8); //SUB Vx,Vy
        case 0x8006: return ((opcode & 0x0F00) >> 8); //SHR Vx {,Vy}
        case 0x8007: return ((opcode & 0x0F00) >> 8); //SUBN Vx,Vy
        case 0x800E: return ((opcode & 0x0F00) >> 8); //SHL Vx {,Vy}
        case 0x9000: return ((opcode & 0x0F00) >> 8); //SNE Vx,Vy
        case 0xA000: return ((opcode & 0x0FFF)); //LD I, addr
        case 0xB000: return ((opcode & 0x0FFF)); //JP V0, addr
        case 0xC000: return ((opcode & 0x0F00) >> 8); //RND Vx, byte
        case 0xD000: return ((opcode & 0x0F00) >> 8); //DRW Vx,Vy, nibble
        case 0xE09E: return ((opcode & 0x0F00) >> 8); //SKP Vx
        case 0xE0A1: return ((opcode & 0x0F00) >> 8); //SKNP Vx
        case 0xF007: return ((opcode & 0x0F00) >> 8); //LD Vx, DT
        case 0xF00A: return ((opcode & 0x0F00) >> 8); //LD Vx, K
        case 0xF015: return ((opcode & 0x0F00) >> 8); //LD DT, Vx
        case 0xF018: return ((opcode & 0x0F00) >> 8); //LD Vx, K
        case 0xF01E: return ((opcode & 0x0F00) >> 8); //ADD I,Vx
        case 0xF029: return ((opcode & 0x0F00) >> 8); //LD F, Vx
        case 0xF033: return ((opcode & 0x0F00) >> 8); //LD B,Vx
        case 0xF055: return ((opcode & 0x0F00) >> 8); //LD [I], Vx
        case 0xF065: return ((opcode & 0x0F00) >> 8); //LD Vx, [I]
        default: return -1 ;
    }
}

uint16_t getOpTwoValue(uint16_t opcode,
              uint16_t masque[NBRINSTRUCTION],
              uint16_t id[NBRINSTRUCTION])
{
    uint16_t op = getInstruction(opcode, masque, id);
    switch(op)
    {
        case 0x0000: return (opcode & 0xFFFF); //SYS Addr
        case 0x00E0: return 0; //CLS
        case 0x00EE: return 0; //RET
        case 0x1000: return (opcode & 0x0FFF); //JMP addr
        case 0x2000: return (opcode & 0x0FFF); //CALL addr
        case 0x3000: return (opcode & 0x00FF); //SE Vx,kk
        case 0x4000: return (opcode & 0x00FF); //SNE Vx,kk
        case 0x5000: return ((opcode & 0x00F0) >> 4); //SE Vx,Vy
        case 0x6000: return (opcode & 0x00FF); //LD Vx,kk
        case 0x7000: return (opcode & 0x00FF); //ADD Vx,kk
        case 0x8000: return ((opcode & 0x00F0) >> 4); //LD Vx,Vy
        case 0x8001: return ((opcode & 0x00F0) >> 4); //OR Vx,Vy
        case 0x8002: return ((opcode & 0x00F0) >> 4); //AND Vx,Vy
        case 0x8003: return ((opcode & 0x00F0) >> 4); //XOR Vx,Vy
        case 0x8004: return ((opcode & 0x00F0) >> 4); //ADD Vx,Vy
        case 0x8005: return ((opcode & 0x00F0) >> 4); //SUB Vx,Vy
        case 0x8006: return ((opcode & 0x00F0) >> 4); //SHR Vx {,Vy}
        case 0x8007: return ((opcode & 0x00F0) >> 4); //SUBN Vx,Vy
        case 0x800E: return ((opcode & 0x00F0) >> 4); //SHL Vx {,Vy}
        case 0x9000: return ((opcode & 0x00F0) >> 4); //SNE Vx,Vy
        case 0xA000: return (opcode & 0x0FFF); //LD I, addr
        case 0xB000: return (opcode & 0x0FFF);
        case 0xC000: return (opcode & 0x00FF); //RND Vx, byte
        case 0xD000: return (opcode & 0x00FF); //DRW Vx,Vy, nibble
        case 0xE09E: return 0; //SKP Vx
        case 0xE0A1: return 0; //SKNP Vx
        case 0xF007: return ((opcode & 0x0F00) >> 8); //LD Vx, DT
        case 0xF00A: return ((opcode & 0x0F00) >> 8); //LD Vx, K
        case 0xF015: return ((opcode & 0x0F00) >> 8); //LD DT, Vx
        case 0xF018: return ((opcode & 0x0F00) >> 8);//LD Vx, K
        case 0xF01E: return ((opcode & 0x0F00) >> 8); //ADD I,Vx
        case 0xF029: return ((opcode & 0x0F00) >> 8); //LD F, Vx
        case 0xF033: return ((opcode & 0x0F00) >> 8); //LD B,Vx
        case 0xF055: return ((opcode & 0x0F00) >> 8); //LD [I], Vx
        case 0xF065: return 0;//LD Vx, [I]
        default: return -1;
    }
}
