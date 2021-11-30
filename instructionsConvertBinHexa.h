#ifndef __INSTRUCTIONSCONVERTBINHEXA__H_
#define __INSTRUCTIONSCONVERTBINHEXA__H_


/* Prototypes */



/**
 * @brief To get the values and the operation of an instruction
 * 
 * @param instruction
 * @param tabValues 
 * @param operation 
 * @return int
 */

#include <stdlib.h>

int instructionValue(const char *instruction, int *tabValues, char *operation);

int isStringFullOfSpaces(const char *string);

int isBeginWithCommentCharBeforeAnyCharOtherThanSpace(char *string);

int convertBinaireIntoHex(int *binaireInstruction, int *hexadecimalInstruction);


int testTexte(char *operation, char *Texte);

int createBinaryInstruction(char *operation, int *tabValue, int *binaireInstruction);

int putToZero(int *binaireInstruction, int start, int end);

int putToValue(int *binaireInstruction, int start, int value);

int displayBinary(int *binaireInstruction);

int binaryADD(int *tabValue, int *binaireInstruction);

int binaryADDI(int *tabValue, int *binaireInstruction);

int binaryAND(int *tabValue, int *binaireInstruction);

int binaryBEQ(int *tabValue, int *binaireInstruction);

int binaryBGTZ(int *tabValue, int *binaireInstruction);

int binaryBLEZ(int *tabValue, int *binaireInstruction);

int binaryBNE(int *tabValue, int *binaireInstruction);

int binaryDIV(int *tabValue, int *binaireInstruction);

int binaryJ(int *tabValue, int *binaireInstruction);

int binaryJAL(int *tabValue, int *binaireInstruction);

int binaryJR(int *tabValue, int *binaireInstruction);

int binaryLUI(int *tabValue, int *binaireInstruction);

int binaryLW(int *tabValue, int *binaireInstruction);

int binaryMFHI(int *tabValue, int *binaireInstruction);

int binaryMFLO(int *tabValue, int *binaireInstruction);

int binaryMULT(int *tabValue, int *binaireInstruction);

int binaryNOP(int *tabValue, int *binaireInstruction);

int binaryOR(int *tabValue, int *binaireInstruction);

int binaryROTR(int *tabValue, int *binaireInstruction);

int binarySLL(int *tabValue, int *binaireInstruction);

int binarySLT(int *tabValue, int *binaireInstruction);

int binarySRL(int *tabValue, int *binaireInstruction);

int binarySUB(int *tabValue, int *binaireInstruction);

int binarySW(int *tabValue, int *binaireInstruction);

int binarySYSCALL(int *tabValue, int *binaireInstruction);

int binaryXOR(int *tabValue, int *binaireInstruction);

int displayHexadecimal(int *hexadecimalInstruction);

#endif