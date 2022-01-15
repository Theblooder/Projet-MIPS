#ifndef _PRINTTERMINAL_H_
#define _PRINTTERMINAL_H_


void presentationMipsEmulator(char *inputFilename,char *outputFilename, char *outputRegFilename);

void showRegister (Register *tableRegister);

void showMemory(memory *ram);

int getch(void);



#endif