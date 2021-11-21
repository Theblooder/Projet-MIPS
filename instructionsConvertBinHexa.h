#ifndef __INSTRUCTIONSCONVERTBINHEXA__H_
#define __INSTRUCTIONSCONVERTBINHEXA__H_


/* Prototypes */




int instructionValue(const char *instruction, int *tabValues, char *operation);

int convertBinaireIntoHex(int *binaireInstruction, int *hexadecimalInstruction);

int convertIntoBinaireADD(char *binnaire, int *tabValue);

int TestTexte(char *operation, char *Texte);

int FunctionChoice(char *operation, int *tabValue, int *binaireInstruction, int *hexadecimalInstruction);

int putToZero(int *binaireInstruction, int start, int end);

int putToValue(int *binaireInstruction, int start, int value);

int DisplayBinary(int *binaireInstruction);

int BinaryADD(char *operation, int *tabValue, int *binaireInstruction, int *hexadecimalInstruction);

int BinaryADDI(char *operation, int *tabValue, int *binaireInstruction, int *hexadecimalInstruction);

int BinaryAND(char *operation, int *tabValue, int *binaireInstruction, int *hexadecimalInstruction);

int BinaryOR(char *operation, int *tabValue, int *binaireInstruction, int *hexadecimalInstruction);

int DisplayHexadecimal(int *hexadecimalInstruction);

#endif