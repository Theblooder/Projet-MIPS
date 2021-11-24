#ifndef __INSTRUCTIONSCONVERTBINHEXA__H_
#define __INSTRUCTIONSCONVERTBINHEXA__H_


/* Prototypes */




int instructionValue(const char *instruction, int *tabValues, char *operation);

int convertBinaireIntoHex(int *binaireInstruction, int *hexadecimalInstruction);


int testTexte(char *operation, char *Texte);

int createBinaryInstruction(char *operation, int *tabValue, int *binaireInstruction);

int putToZero(int *binaireInstruction, int start, int end);

int putToValue(int *binaireInstruction, int start, int value);

int displayBinary(int *binaireInstruction);

int binaryADD(char *operation, int *tabValue, int *binaireInstruction);

int binaryADDI(char *operation, int *tabValue, int *binaireInstruction);

int binaryAND(char *operation, int *tabValue, int *binaireInstruction);

int binaryOR(char *operation, int *tabValue, int *binaireInstruction);

int displayHexadecimal(int *hexadecimalInstruction);

#endif