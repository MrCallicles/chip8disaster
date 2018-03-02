#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "cpu.h"
#include "stack.h"
#include "define.h"
#include "init.h"
#include "format.h"
#include "test.h"

#define DISPLAY_PASSED 1
#define DISPLAY_NOT_PASSED 2
#define DISPLAY_STATISTICS 4

void formatTest(Test t[BUFFERTEST],bool passed, bool not_passed, uint32_t size)
{
    /*
     * Flag
     * Constante qui peut être égale à
     * DISPLAY_PASSED --> affiche les tests réussi
     * DISPLAY_NOT_PASSED --> affiche les tests ratés
     * DISPLAY_STATISTICS --> affiche des statistiques sur les test
     *
     */
    uint32_t nPassed = 0;
    uint32_t nNotPassed = 0;
    for(uint8_t i = 0; i < size; i++)
    {
        t[i].pass ? ++nPassed : ++nNotPassed;

        if(t[i].pass && passed)
        {
             printf("\x1B[32m"
                    "PASSED %d : "
                    "%s"
                    "\x1B[0m"
                    "\n",
                    i,
                    t[i].strCondition);
        }
        if(!t[i].pass && not_passed)
        {
             printf("\x1B[31m"
                    "NOT PASSED %d : "
                    "%s"
                    "\x1B[0m"
                    "\n",
                    i,
                    t[i].strCondition);
        }
    }
            printf("%d test(s) passed\n"
                   "%d test(s) not passed\n",
                   nPassed, nNotPassed);
}

void processTest(Test *t, char* strCond, bool condition)
{
    t->pass = condition;
    if(strlen(strCond) > 128) strncpy(t->strCondition, strCond, 128);
    else strcpy(t->strCondition, strCond);
}

int main(void)
{
    Test t[BUFFERTEST];
    /* test stack.c */
    //initialiseMask_Id_ASM();
    //storeOpcode();
    //storeInstruction();
    //sizeRom();


    /* test cpu.c */
    Cpu *cpuInitCPU = malloc(sizeof(Cpu));
    initCPU(cpuInitCPU);
    //initCPU
    processTest(&t[0], "initCPU() -> V[0] == 0", cpuInitCPU->V[0] == 0);
    processTest(&t[1], "initCPU() -> V[1] == 0", cpuInitCPU->V[1] == 0);
    processTest(&t[2], "initCPU() -> V[2] == 0", cpuInitCPU->V[2] == 0);
    processTest(&t[3], "initCPU() -> V[3] == 0", cpuInitCPU->V[3] == 0);
    processTest(&t[4], "initCPU() -> V[4] == 0", cpuInitCPU->V[4] == 0);
    processTest(&t[5], "initCPU() -> V[5] == 0", cpuInitCPU->V[5] == 0);
    processTest(&t[6], "initCPU() -> V[6] == 0", cpuInitCPU->V[6] == 0);
    processTest(&t[7], "initCPU() -> V[7] == 0", cpuInitCPU->V[7] == 0);
    processTest(&t[8], "initCPU() -> V[8] == 0", cpuInitCPU->V[8] == 0);
    processTest(&t[9], "initCPU() -> V[9] == 0", cpuInitCPU->V[9] == 0);
    processTest(&t[10], "initCPU() -> V[0xA] == 0", cpuInitCPU->V[0xA] == 0);
    processTest(&t[11], "initCPU() -> V[0xB] == 0", cpuInitCPU->V[0xB] == 0);
    processTest(&t[12], "initCPU() -> V[0xC] == 0", cpuInitCPU->V[0xC] == 0);
    processTest(&t[13], "initCPU() -> V[0xD] == 0", cpuInitCPU->V[0xD] == 0);
    processTest(&t[14], "initCPU() -> V[0xE] == 0", cpuInitCPU->V[0xE] == 0);
    processTest(&t[15], "initCPU() -> V[0xF] == 0", cpuInitCPU->V[0xF] == 0);
    processTest(&t[16], "initCPU() -> I == 0", cpuInitCPU->I == 0);
    processTest(&t[17], "initCPU() -> DT == 0", cpuInitCPU->DT == 0);
    processTest(&t[18], "initCPU() -> ST == 0", cpuInitCPU->ST == 0);
    processTest(&t[19], "initCPU() -> PC == 0x200", cpuInitCPU->PC == 0x200);
    free(cpuInitCPU);

    //decrementDelaySound//
    Cpu *cpuDecrement = malloc(sizeof(Cpu));
    initCPU(cpuDecrement);
    cpuDecrement->DT = 2;
    cpuDecrement->ST = 2;
    decrementDelaySound(cpuDecrement);
    processTest(&t[20], "decrementDelaySound where DT & ST = 2", cpuDecrement->DT == 1 && cpuDecrement->ST == 1);
    decrementDelaySound(cpuDecrement);
    processTest(&t[21], "decrementDelaySound where DT & ST = 1", cpuDecrement->DT == 0 && cpuDecrement->ST == 0);
    decrementDelaySound(cpuDecrement);
    processTest(&t[22], "decrementDelaySound where DT & ST = 0", cpuDecrement->DT == 0 && cpuDecrement->ST == 0);
    free(cpuDecrement);

    /*test init.c */
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
    processTest(&t[23],"getInstruction(0x0444) = 0", getInstruction(0x0444, masque, id) == 0);
    processTest(&t[24],"getInstruction(0x00E0) = 0x00E0", getInstruction(0x00E0, masque, id) == 0x00E0);
    processTest(&t[25],"getInstruction(0x00EE) = 0x00EE", getInstruction(0x00EE, masque, id) == 0x00EE);
    processTest(&t[26],"getInstruction(0x1222) = 0x1000", getInstruction(0x1222, masque, id) == 0x1000);
    processTest(&t[27],"getInstruction(0x2222) = 0x2000", getInstruction(0x2222, masque, id) == 0x2000);
    processTest(&t[28],"getInstruction(0x3222) = 0x3000", getInstruction(0x3222, masque, id) == 0x3000);
    processTest(&t[29],"getInstruction(0x4222) = 0x4000", getInstruction(0x4222, masque, id) == 0x4000);
    processTest(&t[30],"getInstruction(0x5220) = 0x5000", getInstruction(0x5222, masque, id) == 0x5000);
    processTest(&t[31],"getInstruction(0x6222) = 0x6000", getInstruction(0x6222, masque, id) == 0x6000);
    processTest(&t[32],"getInstruction(0x7222) = 0x7000", getInstruction(0x7222, masque, id) == 0x7000);
    processTest(&t[33],"getInstruction(0x8220) = 0x8000", getInstruction(0x8220, masque, id) == 0x8000);
    processTest(&t[34],"getInstruction(0x8221) = 0x8001", getInstruction(0x8221, masque, id) == 0x8001);
    processTest(&t[34],"getInstruction(0x8222) = 0x8002", getInstruction(0x8222, masque, id) == 0x8002);
    processTest(&t[35],"getInstruction(0x8223) = 0x8003", getInstruction(0x8223, masque, id) == 0x8003);
    processTest(&t[36],"getInstruction(0x8224) = 0x8004", getInstruction(0x8224, masque, id) == 0x8004);
    processTest(&t[37],"getInstruction(0x8225) = 0x8005", getInstruction(0x8225, masque, id) == 0x8005);
    processTest(&t[38],"getInstruction(0x8226) = 0x8006", getInstruction(0x8226, masque, id) == 0x8006);
    processTest(&t[39],"getInstruction(0x8227) = 0x8007", getInstruction(0x8227, masque, id) == 0x8007);
    processTest(&t[40],"getInstruction(0x822E) = 0x800E", getInstruction(0x822E, masque, id) == 0x800E);
    processTest(&t[41],"getInstruction(0x9D00) = 0x9000", getInstruction(0x9D00, masque, id) == 0x9000);
    processTest(&t[42],"getInstruction(0xAD00) = 0xA000", getInstruction(0xAD00, masque, id) == 0xA000);
    processTest(&t[43],"getInstruction(0xBD00) = 0xB000", getInstruction(0xBD00, masque, id) == 0xB000);
    processTest(&t[44],"getInstruction(0xCD00) = 0xC000", getInstruction(0xCD00, masque, id) == 0xC000);
    processTest(&t[45],"getInstruction(0xDD00) = 0xD000", getInstruction(0xDD00, masque, id) == 0xD000);
    processTest(&t[46],"getInstruction(0xEB9E) = 0xE09E", getInstruction(0xEB9E, masque, id) == 0xE09E);
    processTest(&t[47],"getInstruction(0xEBA1) = 0xE0A1", getInstruction(0xEBA1, masque, id) == 0xE0A1);
    processTest(&t[48],"getInstruction(0xFB07) = 0xF007", getInstruction(0xFB07, masque, id) == 0xF007);
    processTest(&t[49],"getInstruction(0xFB0A) = 0xF00A", getInstruction(0xFB0A, masque, id) == 0xF00A);
    processTest(&t[50],"getInstruction(0xFB15) = 0xF015", getInstruction(0xFB15, masque, id) == 0xF015);
    processTest(&t[51],"getInstruction(0xFB18) = 0xF018", getInstruction(0xFB18, masque, id) == 0xF018);
    processTest(&t[52],"getInstruction(0xFB1E) = 0xF01E", getInstruction(0xFB1E, masque, id) == 0xF01E);
    processTest(&t[53],"getInstruction(0xFB29) = 0xF029", getInstruction(0xFB29, masque, id) == 0xF029);
    processTest(&t[54],"getInstruction(0xFB33) = 0xF033", getInstruction(0xFB33, masque, id) == 0xF033);
    processTest(&t[55],"getInstruction(0xFB55) = 0xF055", getInstruction(0xFB55, masque, id) == 0xF055);
    processTest(&t[56],"getInstruction(0xFB65) = 0xF065", getInstruction(0xFB65, masque, id) == 0xF065);

    //getInstructionID
    processTest(&t[57],"getInstructionID(0x0444) = 2",  getInstructionID(0x0444, masque, id) == 2);
    processTest(&t[58],"getInstructionID(0x00E0) = 0",  getInstructionID(0x00E0, masque, id) == 0);
    processTest(&t[59],"getInstructionID(0x00EE) = 1",  getInstructionID(0x00EE, masque, id) == 1);
    processTest(&t[60],"getInstructionID(0x1222) = 3",  getInstructionID(0x1222, masque, id) == 3);
    processTest(&t[61],"getInstructionID(0x2222) = 4",  getInstructionID(0x2222, masque, id) == 4);
    processTest(&t[62],"getInstructionID(0x3222) = 5",  getInstructionID(0x3222, masque, id) == 5);
    processTest(&t[63],"getInstructionID(0x4222) = 6",  getInstructionID(0x4222, masque, id) == 6);
    processTest(&t[64],"getInstructionID(0x5220) = 7",  getInstructionID(0x5222, masque, id) == 7);
    processTest(&t[65],"getInstructionID(0x6222) = 8",  getInstructionID(0x6222, masque, id) == 8);
    processTest(&t[66],"getInstructionID(0x7222) = 9",  getInstructionID(0x7222, masque, id) == 9);
    processTest(&t[67],"getInstructionID(0x8220) = 10", getInstructionID(0x8220, masque, id) == 10);
    processTest(&t[68],"getInstructionID(0x8221) = 11", getInstructionID(0x8221, masque, id) == 11);
    processTest(&t[69],"getInstructionID(0x8222) = 12", getInstructionID(0x8222, masque, id) == 12);
    processTest(&t[70],"getInstructionID(0x8223) = 13", getInstructionID(0x8223, masque, id) == 13);
    processTest(&t[71],"getInstructionID(0x8224) = 14", getInstructionID(0x8224, masque, id) == 14);
    processTest(&t[72],"getInstructionID(0x8225) = 15", getInstructionID(0x8225, masque, id) == 15);
    processTest(&t[73],"getInstructionID(0x8226) = 16", getInstructionID(0x8226, masque, id) == 16);
    processTest(&t[74],"getInstructionID(0x8227) = 17", getInstructionID(0x8227, masque, id) == 17);
    processTest(&t[75],"getInstructionID(0x822E) = 18", getInstructionID(0x822E, masque, id) == 18);
    processTest(&t[76],"getInstructionID(0x9D00) = 19", getInstructionID(0x9D00, masque, id) == 19);
    processTest(&t[77],"getInstructionID(0xAD00) = 20", getInstructionID(0xAD00, masque, id) == 20);
    processTest(&t[78],"getInstructionID(0xBD00) = 21", getInstructionID(0xBD00, masque, id) == 21);
    processTest(&t[79],"getInstructionID(0xCD00) = 22", getInstructionID(0xCD00, masque, id) == 22);
    processTest(&t[80],"getInstructionID(0xDD00) = 23", getInstructionID(0xDD00, masque, id) == 23);
    processTest(&t[81],"getInstructionID(0xEB9E) = 24", getInstructionID(0xEB9E, masque, id) == 24);
    processTest(&t[82],"getInstructionID(0xEBA1) = 25", getInstructionID(0xEBA1, masque, id) == 25);
    processTest(&t[83],"getInstructionID(0xFB07) = 26", getInstructionID(0xFB07, masque, id) == 26);
    processTest(&t[84],"getInstructionID(0xFB0A) = 27", getInstructionID(0xFB0A, masque, id) == 27);
    processTest(&t[85],"getInstructionID(0xFB15) = 28", getInstructionID(0xFB15, masque, id) == 28);
    processTest(&t[86],"getInstructionID(0xFB18) = 29", getInstructionID(0xFB18, masque, id) == 29);
    processTest(&t[87],"getInstructionID(0xFB1E) = 30", getInstructionID(0xFB1E, masque, id) == 30);
    processTest(&t[88],"getInstructionID(0xFB29) = 31", getInstructionID(0xFB29, masque, id) == 31);
    processTest(&t[89],"getInstructionID(0xFB33) = 32", getInstructionID(0xFB33, masque, id) == 32);
    processTest(&t[90],"getInstructionID(0xFB55) = 33", getInstructionID(0xFB55, masque, id) == 33);
    processTest(&t[91],"getInstructionID(0xFB65) = 34", getInstructionID(0xFB65, masque, id) == 34);

    //getInstructionASM
    processTest(&t[92] ,"getInstructionASM(0x0444) = SYS ", strcmp(getInstructionASM(0x0444, masque, id, instructionASM), "SYS ") == 0);
    processTest(&t[93] ,"getInstructionASM(0x00E0) = CLS ", strcmp(getInstructionASM(0x00E0, masque, id, instructionASM), "CLS ") == 0);
    processTest(&t[94] ,"getInstructionASM(0x00EE) = RET ", strcmp(getInstructionASM(0x00EE, masque, id, instructionASM), "RET ") == 0);
    processTest(&t[94] ,"getInstructionASM(0x1222) = JP  ", strcmp(getInstructionASM(0x1222, masque, id, instructionASM), "JP  ") == 0);
    processTest(&t[95] ,"getInstructionASM(0x2222) = CALL", strcmp(getInstructionASM(0x2222, masque, id, instructionASM), "CALL") == 0);
    processTest(&t[96] ,"getInstructionASM(0x3222) = SE  ", strcmp(getInstructionASM(0x3222, masque, id, instructionASM), "SE  ") == 0);
    processTest(&t[97] ,"getInstructionASM(0x4222) = SNE ", strcmp(getInstructionASM(0x4222, masque, id, instructionASM), "SNE ") == 0);
    processTest(&t[98] ,"getInstructionASM(0x5220) = SE  ", strcmp(getInstructionASM(0x5222, masque, id, instructionASM), "SE  ") == 0);
    processTest(&t[99] ,"getInstructionASM(0x6222) = LD  ", strcmp(getInstructionASM(0x6222, masque, id, instructionASM), "LD  ") == 0);
    processTest(&t[100],"getInstructionASM(0x7222) = ADD ", strcmp(getInstructionASM(0x7222, masque, id, instructionASM), "ADD ") == 0);
    processTest(&t[101],"getInstructionASM(0x8220) = LD  ", strcmp(getInstructionASM(0x8220, masque, id, instructionASM), "LD  ") == 0);
    processTest(&t[102],"getInstructionASM(0x8221) = OR  ", strcmp(getInstructionASM(0x8221, masque, id, instructionASM), "OR  ") == 0);
    processTest(&t[103],"getInstructionASM(0x8222) = AND ", strcmp(getInstructionASM(0x8222, masque, id, instructionASM), "AND ") == 0);
    processTest(&t[104],"getInstructionASM(0x8223) = XOR ", strcmp(getInstructionASM(0x8223, masque, id, instructionASM), "XOR ") == 0);
    processTest(&t[105],"getInstructionASM(0x8224) = ADD ", strcmp(getInstructionASM(0x8224, masque, id, instructionASM), "ADD ") == 0);
    processTest(&t[106],"getInstructionASM(0x8225) = SUB ", strcmp(getInstructionASM(0x8225, masque, id, instructionASM), "SUB ") == 0);
    processTest(&t[107],"getInstructionASM(0x8226) = SHR ", strcmp(getInstructionASM(0x8226, masque, id, instructionASM), "SHR ") == 0);
    processTest(&t[108],"getInstructionASM(0x8227) = SUBN", strcmp(getInstructionASM(0x8227, masque, id, instructionASM), "SUBN") == 0);
    processTest(&t[109],"getInstructionASM(0x822E) = SHL ", strcmp(getInstructionASM(0x822E, masque, id, instructionASM), "SHL ") == 0);
    processTest(&t[110],"getInstructionASM(0x9D00) = SNE ", strcmp(getInstructionASM(0x9D00, masque, id, instructionASM), "SNE ") == 0);
    processTest(&t[111],"getInstructionASM(0xAD00) = LD  ", strcmp(getInstructionASM(0xAD00, masque, id, instructionASM), "LD  ") == 0);
    processTest(&t[112],"getInstructionASM(0xBD00) = JP  ", strcmp(getInstructionASM(0xBD00, masque, id, instructionASM), "JP  ") == 0);
    processTest(&t[113],"getInstructionASM(0xCD00) = RND ", strcmp(getInstructionASM(0xCD00, masque, id, instructionASM), "RND ") == 0);
    processTest(&t[114],"getInstructionASM(0xDD00) = DRW ", strcmp(getInstructionASM(0xDD00, masque, id, instructionASM), "DRW ") == 0);
    processTest(&t[115],"getInstructionASM(0xEB9E) = SKP ", strcmp(getInstructionASM(0xEB9E, masque, id, instructionASM), "SKP ") == 0);
    processTest(&t[116],"getInstructionASM(0xEBA1) = SKNP", strcmp(getInstructionASM(0xEBA1, masque, id, instructionASM), "SKNP") == 0);
    processTest(&t[117],"getInstructionASM(0xFB07) = LD  ", strcmp(getInstructionASM(0xFB07, masque, id, instructionASM), "LD  ") == 0);
    processTest(&t[118],"getInstructionASM(0xFB0A) = LD  ", strcmp(getInstructionASM(0xFB0A, masque, id, instructionASM), "LD  ") == 0);
    processTest(&t[119],"getInstructionASM(0xFB15) = LD  ", strcmp(getInstructionASM(0xFB15, masque, id, instructionASM), "LD  ") == 0);
    processTest(&t[120],"getInstructionASM(0xFB18) = LD  ", strcmp(getInstructionASM(0xFB18, masque, id, instructionASM), "LD  ") == 0);
    processTest(&t[121],"getInstructionASM(0xFB1E) = ADD ", strcmp(getInstructionASM(0xFB1E, masque, id, instructionASM), "ADD ") == 0);
    processTest(&t[122],"getInstructionASM(0xFB29) = LD  ", strcmp(getInstructionASM(0xFB29, masque, id, instructionASM), "LD  ") == 0);
    processTest(&t[123],"getInstructionASM(0xFB33) = LD  ", strcmp(getInstructionASM(0xFB33, masque, id, instructionASM), "LD  ") == 0);
    processTest(&t[124],"getInstructionASM(0xFB55) = LD  ", strcmp(getInstructionASM(0xFB55, masque, id, instructionASM), "LD  ") == 0);
    processTest(&t[125],"getInstructionASM(0xFB65) = LD  ", strcmp(getInstructionASM(0xFB65, masque, id, instructionASM), "LD  ") == 0);

    //getOpOneValue
    processTest(&t[126],"getOpOneValue(0x0111) = 0x111", getOpOneValue(0x0111, masque, id) == 0x111);
    processTest(&t[127],"getOpOneValue(0x00E0) = 0x0", getOpOneValue(0x00E0, masque, id) == 0x0);
    processTest(&t[128],"getOpOneValue(0x00EE) = 0x0", getOpOneValue(0x00EE, masque, id) == 0x0);
    processTest(&t[129],"getOpOneValue(0x1222) = 0x222", getOpOneValue(0x1222, masque, id) == 0x222);
    processTest(&t[130],"getOpOneValue(0x2222) = 0x222", getOpOneValue(0x2222, masque, id) == 0x222);
    processTest(&t[131],"getOpOneValue(0x3A55) = 0xA", getOpOneValue(0x3A55, masque, id) == 0xA);
    processTest(&t[132],"getOpOneValue(0x4A55) = 0xA", getOpOneValue(0x4A55, masque, id) == 0xA);
    processTest(&t[133],"getOpOneValue(0x5A50) = 0xA", getOpOneValue(0x5A50, masque, id) == 0xA);
    processTest(&t[134],"getOpOneValue(0x6A50) = 0xA", getOpOneValue(0x6A50, masque, id) == 0xA);
    processTest(&t[135],"getOpOneValue(0x7B44) = 0xB", getOpOneValue(0x7B44, masque, id) == 0xB);
    processTest(&t[136],"getOpOneValue(0x8CA0) = 0xC", getOpOneValue(0x8CA0, masque, id) == 0xC);
    processTest(&t[137],"getOpOneValue(0x89A1) = 0x9", getOpOneValue(0x89A1, masque, id) == 0x9);
    processTest(&t[138],"getOpOneValue(0x89A2) = 0x9", getOpOneValue(0x89A2, masque, id) == 0x9);
    processTest(&t[139],"getOpOneValue(0x89A3) = 0x9", getOpOneValue(0x89A3, masque, id) == 0x9);
    processTest(&t[140],"getOpOneValue(0x89A4) = 0x9", getOpOneValue(0x89A4, masque, id) == 0x9);
    processTest(&t[141],"getOpOneValue(0x89A5) = 0x9", getOpOneValue(0x89A5, masque, id) == 0x9);
    processTest(&t[142],"getOpOneValue(0x89A6) = 0x9", getOpOneValue(0x89A6, masque, id) == 0x9);
    processTest(&t[143],"getOpOneValue(0x89A7) = 0x9", getOpOneValue(0x89A7, masque, id) == 0x9);
    processTest(&t[144],"getOpOneValue(0x89AE) = 0x9", getOpOneValue(0x89AE, masque, id) == 0x9);
    processTest(&t[145],"getOpOneValue(0x95F0) = 0x5", getOpOneValue(0x95F0, masque, id) == 0x5);
    processTest(&t[146],"getOpOneValue(0xA555) = 0x555", getOpOneValue(0xA555, masque, id) == 0x555);
    processTest(&t[147],"getOpOneValue(0xB555) = 0x555", getOpOneValue(0xB555, masque, id) == 0x555);
    processTest(&t[148],"getOpOneValue(0xCB77) = 0xB", getOpOneValue(0xCB77, masque, id) == 0xB);
    processTest(&t[149],"getOpOneValue(0xD347) = 0x3", getOpOneValue(0xD347, masque, id) == 0x3);
    processTest(&t[150],"getOpOneValue(0xEA9E) = 0xA", getOpOneValue(0xEA9E, masque, id) == 0xA);
    processTest(&t[151],"getOpOneValue(0xEAA1) = 0xA", getOpOneValue(0xEAA1, masque, id) == 0xA);
    processTest(&t[152],"getOpOneValue(0xF107) = 0x1", getOpOneValue(0xF107, masque, id) == 0x1);
    processTest(&t[153],"getOpOneValue(0xF20A) = 0x2", getOpOneValue(0xF20A, masque, id) == 0x2);
    processTest(&t[154],"getOpOneValue(0xF515) = 0x5", getOpOneValue(0xF515, masque, id) == 0x5);
    processTest(&t[155],"getOpOneValue(0xF818) = 0x8", getOpOneValue(0xF818, masque, id) == 0x8);
    processTest(&t[156],"getOpOneValue(0xFC1E) = 0xC", getOpOneValue(0xFC1E, masque, id) == 0xC);
    processTest(&t[157],"getOpOneValue(0xFD29) = 0xD", getOpOneValue(0xFD29, masque, id) == 0xD);
    processTest(&t[158],"getOpOneValue(0xFE33) = 0xE", getOpOneValue(0xFE33, masque, id) == 0xE);
    processTest(&t[159],"getOpOneValue(0xFA55) = 0xA", getOpOneValue(0xfA55, masque, id) == 0xA);
    processTest(&t[160],"getOpOneValue(0xF965) = 0x9", getOpOneValue(0xf965, masque, id) == 0x9);

    //getOpTwoValue
    processTest(&t[161],"getOpTwoValue(0x0111) = 0x111", getOpTwoValue(0x0111, masque, id) == 0x111);
    processTest(&t[162],"getOpTwoValue(0x00E0) = 0x0",   getOpTwoValue(0x00E0, masque, id) == 0x0);
    processTest(&t[163],"getOpTwoValue(0x00EE) = 0x0",   getOpTwoValue(0x00EE, masque, id) == 0x0);
    processTest(&t[164],"getOpTwoValue(0x1222) = 0x222", getOpTwoValue(0x1222, masque, id) == 0x222);
    processTest(&t[165],"getOpTwoValue(0x2222) = 0x222", getOpTwoValue(0x2222, masque, id) == 0x222);
    processTest(&t[166],"getOpTwoValue(0x3A55) = 0x55",  getOpTwoValue(0x3A55, masque, id) == 0x55);
    processTest(&t[167],"getOpTwoValue(0x4A55) = 0x55",  getOpTwoValue(0x4A55, masque, id) == 0x55);
    processTest(&t[168],"getOpTwoValue(0x5A50) = 0x5",   getOpTwoValue(0x5A50, masque, id) == 0x5);
    processTest(&t[169],"getOpTwoValue(0x6A50) = 0x50",  getOpTwoValue(0x6A50, masque, id) == 0x50);
    processTest(&t[170],"getOpTwoValue(0x7B44) = 0x44",  getOpTwoValue(0x7B44, masque, id) == 0x44);
    processTest(&t[171],"getOpTwoValue(0x8CA0) = 0xA",   getOpTwoValue(0x8CA0, masque, id) == 0xA);
    processTest(&t[172],"getOpTwoValue(0x89A1) = 0xA",   getOpTwoValue(0x89A1, masque, id) == 0xA);
    processTest(&t[173],"getOpTwoValue(0x89A2) = 0xA",   getOpTwoValue(0x89A2, masque, id) == 0xA);
    processTest(&t[174],"getOpTwoValue(0x89A3) = 0xA",   getOpTwoValue(0x89A3, masque, id) == 0xA);
    processTest(&t[175],"getOpTwoValue(0x89A4) = 0xA",   getOpTwoValue(0x89A4, masque, id) == 0xA);
    processTest(&t[176],"getOpTwoValue(0x89A5) = 0xA",   getOpTwoValue(0x89A5, masque, id) == 0xA);
    processTest(&t[177],"getOpTwoValue(0x89A6) = 0xA",   getOpTwoValue(0x89A6, masque, id) == 0xA);
    processTest(&t[178],"getOpTwoValue(0x89A7) = 0xA",   getOpTwoValue(0x89A7, masque, id) == 0xA);
    processTest(&t[179],"getOpTwoValue(0x89AE) = 0xA",   getOpTwoValue(0x89AE, masque, id) == 0xA);
    processTest(&t[180],"getOpTwoValue(0x95F0) = 0xF",   getOpTwoValue(0x95F0, masque, id) == 0xF);
    processTest(&t[181],"getOpTwoValue(0xA555) = 0x555", getOpTwoValue(0xA555, masque, id) == 0x555);
    processTest(&t[182],"getOpTwoValue(0xB555) = 0x555", getOpTwoValue(0xB555, masque, id) == 0x555);
    processTest(&t[183],"getOpTwoValue(0xCB77) = 0x77",  getOpTwoValue(0xCB77, masque, id) == 0x77);
    processTest(&t[184],"getOpTwoValue(0xD347) = 0x47",  getOpTwoValue(0xD347, masque, id) == 0x47);
    processTest(&t[185],"getOpTwoValue(0xEA9E) = 0x0",   getOpTwoValue(0xEA9E, masque, id) == 0x0);
    processTest(&t[186],"getOpTwoValue(0xEAA1) = 0x0",   getOpTwoValue(0xEAA1, masque, id) == 0x0);
    processTest(&t[187],"getOpTwoValue(0xF107) = 0x1",   getOpTwoValue(0xF107, masque, id) == 0x1);
    processTest(&t[188],"getOpTwoValue(0xF20A) = 0x2",   getOpTwoValue(0xF20A, masque, id) == 0x2);
    processTest(&t[189],"getOpTwoValue(0xF515) = 0x5",   getOpTwoValue(0xF515, masque, id) == 0x5);
    processTest(&t[190],"getOpTwoValue(0xF818) = 0x8",   getOpTwoValue(0xF818, masque, id) == 0x8);
    processTest(&t[191],"getOpTwoValue(0xFC1E) = 0xC",   getOpTwoValue(0xFC1E, masque, id) == 0xC);
    processTest(&t[192],"getOpTwoValue(0xFD29) = 0xD",   getOpTwoValue(0xFD29, masque, id) == 0xD);
    processTest(&t[193],"getOpTwoValue(0xFE33) = 0xE",   getOpTwoValue(0xFE33, masque, id) == 0xE);
    processTest(&t[194],"getOpTwoValue(0xFA55) = 0xA",   getOpTwoValue(0xfA55, masque, id) == 0xA);
    processTest(&t[195],"getOpTwoValue(0xF965) = 0x0",   getOpTwoValue(0xf965, masque, id) == 0x0);

    //
    Cpu *cpuExecOpCode = malloc(sizeof(Cpu));

    initCPU(cpuExecOpCode);
    execOpCodeCPU(cpuExecOpCode, 0, 0x0, 0x0);
    processTest(&t[196], "execOpCodeCPU(0, 0x111, 0x111) (CLS)",false);

    initCPU(cpuExecOpCode);
    cpuExecOpCode->stack[0] = 0x200;
    cpuExecOpCode->SP = 1;
    execOpCodeCPU(cpuExecOpCode, 1, 0x0, 0x0);
    //RET
    processTest(&t[197], "execOpCodeCPU(1, 0x0, 0x0) (RET)", cpuExecOpCode->PC == 0x200 && cpuExecOpCode->SP == 0);

    initCPU(cpuExecOpCode);
    execOpCodeCPU(cpuExecOpCode, 2, 0x0, 0x0);
    //not implemented SYS
    processTest(&t[198], "execOpCodeCPU(2, 0x0, 0x0) (SYS)", true);


    initCPU(cpuExecOpCode);
    execOpCodeCPU(cpuExecOpCode, 3, 0x200, 0x200);
    processTest(&t[199], "execOpCodeCPU(3, 0x200, 0x200) (JMP)",
                cpuExecOpCode->PC == 0x200);

    initCPU(cpuExecOpCode);
    execOpCodeCPU(cpuExecOpCode, 4, 0x400, 0x400);
    processTest(&t[200], "execOpCodeCPU(0x2000, 0x150, 0x150) (CALL)",
                cpuExecOpCode->stack[0] == 0 ||
                cpuExecOpCode->PC == 0x400 ||
                cpuExecOpCode->SP == 1
            );

    initCPU(cpuExecOpCode);
    cpuExecOpCode->V[1] = 0xF0;
    execOpCodeCPU(cpuExecOpCode, 5, 1, 0xF0);
    processTest(&t[201], "execOpCodeCPU(5, V[1], 0xF0) (SE egal)", cpuExecOpCode->PC == 0x202);

    initCPU(cpuExecOpCode);
    cpuExecOpCode->V[1] = 0xF0;
    execOpCodeCPU(cpuExecOpCode, 5, 1, 0xF0);
    execOpCodeCPU(cpuExecOpCode, 5, 1, 0xF0);
    processTest(&t[202], "execOpCodeCPU(5, V[1], 0xF0) (SE egal)", cpuExecOpCode->PC == 0x204);

    initCPU(cpuExecOpCode);
    cpuExecOpCode->V[1] = 0xF0;
    execOpCodeCPU(cpuExecOpCode, 5, 1, 0xC0);
    processTest(&t[203], "execOpCodeCPU(5, V[1], 0xC0) (SE not egal)", cpuExecOpCode->PC == 0x200);

    initCPU(cpuExecOpCode);
    cpuExecOpCode->V[1] = 0xF0;
    execOpCodeCPU(cpuExecOpCode, 6, 1, 0xF0);
    processTest(&t[204], "execOpCodeCPU(6, V[1], 0xC0) (SNE egal)", cpuExecOpCode->PC == 0x200);

    initCPU(cpuExecOpCode);
    cpuExecOpCode->V[1] = 0xF0;
    execOpCodeCPU(cpuExecOpCode, 6, 1, 0xD0);
    processTest(&t[205], "execOpCodeCPU(6, V[1], 0xC0) (SNE not egal)", cpuExecOpCode->PC == 0x202);

    initCPU(cpuExecOpCode);
    cpuExecOpCode->V[1] = 0xF0;
    cpuExecOpCode->V[0xB] = 0xF0;
    execOpCodeCPU(cpuExecOpCode, 7, 1, 0xb);
    processTest(&t[206], "execOpCodeCPU(7, V[1], V[B]) (SE Vx,Vy egal)", cpuExecOpCode->PC == 0x202);

    initCPU(cpuExecOpCode);
    cpuExecOpCode->V[1] = 0xF0;
    cpuExecOpCode->V[0xB] = 0xD0;
    execOpCodeCPU(cpuExecOpCode, 7, 1, 0xb);
    processTest(&t[207], "execOpCodeCPU(7, V[1], V[1]) (SE Vx,Vy not egal)", cpuExecOpCode->PC == 0x200);

    initCPU(cpuExecOpCode);
    cpuExecOpCode->V[1] = 0xF0;
    cpuExecOpCode->V[0xB] = 0xD0;
    execOpCodeCPU(cpuExecOpCode, 7, 1, 0xb);
    processTest(&t[208], "execOpCodeCPU(7, V[1], V[B]) (SE Vx,Vy not egal)", cpuExecOpCode->PC == 0x200);

    initCPU(cpuExecOpCode);
    execOpCodeCPU(cpuExecOpCode, 8, 1, 0xFF);
    processTest(&t[209], "execOpCodeCPU(8, V[1], 0xFF) (LD Vx,NN)", cpuExecOpCode->V[1] == 0xFF);

    initCPU(cpuExecOpCode);
    cpuExecOpCode->V[1] = 0x5;
    execOpCodeCPU(cpuExecOpCode, 9, 1, 0x5);
    processTest(&t[210], "execOpCodeCPU(9, V[1], 0xFF) (ADD Vx,NN)", cpuExecOpCode->V[1] == (0x5 + 0x5));

    initCPU(cpuExecOpCode);
    cpuExecOpCode->V[3] = 0x5;
    cpuExecOpCode->V[5] = 0xD0;
    execOpCodeCPU(cpuExecOpCode, 10, 3, 5);
    processTest(&t[211], "execOpCodeCPU(10, V[3], V[5]) (LD Vx,Vy)", cpuExecOpCode->V[3] == 0xD0);

    initCPU(cpuExecOpCode);
    cpuExecOpCode->V[3] = 0xEA;
    cpuExecOpCode->V[5] = 0xD0;
    execOpCodeCPU(cpuExecOpCode, 11, 3, 5);
    processTest(&t[212], "execOpCodeCPU(11, V[3], V[5]) (OR Vx, Vy)", (cpuExecOpCode->V[3] == 0xEA) |
           (cpuExecOpCode->V[5] == 0xD0));

    initCPU(cpuExecOpCode);
    cpuExecOpCode->V[3] = 0xEA;
    cpuExecOpCode->V[5] = 0xD0;
    execOpCodeCPU(cpuExecOpCode, 12, 3, 5);
    processTest(&t[213], "execOpCodeCPU(12, V[3], V[5]) (AND Vx, Vy)",
                (cpuExecOpCode->V[3] == (0xEA & 0xD0)));

    initCPU(cpuExecOpCode);
    cpuExecOpCode->V[3] = 0xEA;
    cpuExecOpCode->V[5] = 0xD0;
    execOpCodeCPU(cpuExecOpCode, 13, 3, 5);
    processTest(&t[214], "execOpCodeCPU(13, V[3], V[5]) (XOR Vx, Vy)", cpuExecOpCode->V[3] == (0xEA ^ 0xD0));

    initCPU(cpuExecOpCode);
    cpuExecOpCode->V[3] = 0x0A;
    cpuExecOpCode->V[5] = 0xD0;
    execOpCodeCPU(cpuExecOpCode, 14, 3, 5);
    processTest(&t[215],
                "execOpCodeCPU(14 , V[3], V[5]) (ADD Vx, Vy with carry)",
                (cpuExecOpCode->V[3] == (0x0A + 0xD0)) && (cpuExecOpCode->V[0xF] == 0));


    initCPU(cpuExecOpCode);
    cpuExecOpCode->V[3] = 0xFF;
    cpuExecOpCode->V[5] = 0x05;
    execOpCodeCPU(cpuExecOpCode, 14, 3, 5);
    processTest(&t[216],
                "execOpCodeCPU(14 , V[3], V[5]) (ADD Vx, Vy with carry)",
                (cpuExecOpCode->V[3] == 0x04) && (cpuExecOpCode->V[0xF] == 1));

    initCPU(cpuExecOpCode);
    cpuExecOpCode->V[3] = 0xF0;
    cpuExecOpCode->V[5] = 0x0F;
    execOpCodeCPU(cpuExecOpCode, 14, 3, 5);
    processTest(&t[217],
                "execOpCodeCPU(14 , V[3], V[5]) (ADD Vx, Vy with carry)",
                (cpuExecOpCode->V[3] == 0xFF) && (cpuExecOpCode->V[0xF] == 0));

    initCPU(cpuExecOpCode);
    cpuExecOpCode->V[3] = 0xF0;
    cpuExecOpCode->V[5] = 0x0F;
    execOpCodeCPU(cpuExecOpCode, 14, 3, 5);
    processTest(&t[218],
                "execOpCodeCPU(14 , V[3], V[5]) (ADD Vx, Vy with carry)",
                (cpuExecOpCode->V[3] == 0xFF) && (cpuExecOpCode->V[0xF] == 0));

    initCPU(cpuExecOpCode);
    cpuExecOpCode->V[3] = 0xF0;
    cpuExecOpCode->V[5] = 0x0F;
    execOpCodeCPU(cpuExecOpCode, 15, 3, 5);
    processTest(&t[219],
                "execOpCodeCPU(15 , V[3], V[5]) (SUB Vx, Vy with carry)",
                (cpuExecOpCode->V[3] == (0xF0 - 0x0F)) && (cpuExecOpCode->V[0xF] == 0));

    initCPU(cpuExecOpCode);
    cpuExecOpCode->V[3] = 0xA;
    cpuExecOpCode->V[5] = 0xF;
    execOpCodeCPU(cpuExecOpCode, 15, 3, 5);
    processTest(&t[220],
                "execOpCodeCPU(15 , V[3], V[5]) (SUB Vx, Vy with carry)",
                (cpuExecOpCode->V[3] == (0xA - 0xF)) && (cpuExecOpCode->V[0xF] == 1));

    //loadRomCPU
    formatTest(t,false,true, 221);
    exit(EXIT_SUCCESS);
}
