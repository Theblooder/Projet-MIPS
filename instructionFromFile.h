#ifndef __INSTRUCTIONFROMFILE__H_
#define __INSTRUCTIONFROMFILE__H_

/* Prototype */

int _main_(char *instruction, char *cleanInstruction, int *values, int *operation, int numberOfRow);
int cleanInstructionReturnLength(const char *instruction, char *clearInstruction);
int getOperation(const char *instruction, int *numberRegisterOffset, int *INToperation);
int isTexteEqual(char *operation, char *Texte);
int getRegisterOffset(char *instruction, int *currentPosition, int regValue, int *isError);




#endif