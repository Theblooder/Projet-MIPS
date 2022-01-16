#ifndef __INSTRUCTIONFROMFILE__H_
#define __INSTRUCTIONFROMFILE__H_

#include "memory.h"
/* Prototype */

int _main_(char *instruction, char *cleanInstruction, int *values, int *operation, int numberOfRow);
int openFilesAndReadArguments(char *inputFilename, char *outputHexaFilename, char *outputRegisterFilename, int argc, char *argv[]);
void readFileAndPutIntoMemory(FILE *inputFile, FILE *outputFile, int *numberOfInsructionWritten, memory *RAM);
int cleanInstructionReturnLength(const char *instruction, char *clearInstruction);
int getOperation(const char *instruction, int *numberRegisterOffset, int *INToperation);
int isTexteEqual(char *operation, char *Texte);
int getRegisterOffset(char *instruction, int *currentPosition, int regValue, int *isError);
void interactifMode(int numberOfInsructionWritten, memory *RAM, Register *tableRegister);




#endif