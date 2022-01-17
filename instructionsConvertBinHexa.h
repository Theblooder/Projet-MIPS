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


int convertBinaireIntoHexAndDisplay(int *binaireInstruction, int *hexadecimalInstruction);

int createBinaryInstruction(int operation, int *tabValue, int *binaireInstruction);

int putToZero(int *binaireInstruction, int start, int end);

int putToValue(int *binaireInstruction, int start, int value);

int displayBinary(int *binaireInstruction);

void binaryADD(int *tabValue, int *binaireInstruction);

void binaryADDI(int *tabValue, int *binaireInstruction);

void binaryAND(int *tabValue, int *binaireInstruction);

void binaryBEQ(int *tabValue, int *binaireInstruction);

void binaryBGTZ(int *tabValue, int *binaireInstruction);

void binaryBLEZ(int *tabValue, int *binaireInstruction);

void binaryBNE(int *tabValue, int *binaireInstruction);

void binaryDIV(int *tabValue, int *binaireInstruction);

void binaryJ(int *tabValue, int *binaireInstruction);

void binaryJAL(int *tabValue, int *binaireInstruction);

void binaryJR(int *tabValue, int *binaireInstruction);

void binaryLUI(int *tabValue, int *binaireInstruction);

void binaryLW(int *tabValue, int *binaireInstruction);

void binaryMFHI(int *tabValue, int *binaireInstruction);

void binaryMFLO(int *tabValue, int *binaireInstruction);

void binaryMULT(int *tabValue, int *binaireInstruction);

void binaryNOP(int *tabValue, int *binaireInstruction);

void binaryOR(int *tabValue, int *binaireInstruction);

void binaryROTR(int *tabValue, int *binaireInstruction);

void binarySLL(int *tabValue, int *binaireInstruction);

void binarySLT(int *tabValue, int *binaireInstruction);

void binarySRL(int *tabValue, int *binaireInstruction);

void binarySUB(int *tabValue, int *binaireInstruction);

void binarySW(int *tabValue, int *binaireInstruction);

void binarySYSCALL(int *tabValue, int *binaireInstruction);

void binaryXOR(int *tabValue, int *binaireInstruction);

int displayHexadecimal(int *hexadecimalInstruction);

#endif