#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "memory.h"
#include "executeInstruction.h"
#include "instructionsConvertBinHexa.h"
#include "printTerminal.h"

void presentationMipsEmulator(char *inputFilename,char *outputFilename)
{
    printf("                  ***** MIPS EMULATOR *****\n");
	printf("\n");
	printf("GILGER Rémi et LAGRANGE Damien\n");
	printf("\n");
	printf("Assembling file : %s\n", inputFilename);
	printf("Output will be written in : %s\n", outputFilename);
	printf("\n");
	printf("\n");
	printf("*** Text segment loaded - Ready to execute ***\n");
	printf("\n");

}

void showRegister (Register *tableRegister)
{
    int i = 0;
    int k = 0;
    int j = 0;
    int length = 0;
   
    while(i<32)
    {
        for(j=1;j<4;j++)
        {   
            if(i<32)
            {
                if(i<10)
                {
                    printf("0%d: %d",i,returnArgument(tableRegister[i].registre,0,32));
                    if(returnArgument(tableRegister[i].registre,0,32) == 0)
                    {
                        length = 0;
                    }
                    else
                    {
                        length = (int)log10(abs(returnArgument(tableRegister[i].registre,0,32)));
                        if(returnArgument(tableRegister[i].registre,0,32)< 0) length += 1;
                    }
                    for(k=length+4;k<20;k++)
                    {
                        printf(" ");
                    }
                    i++;
                }
                else
                {
                    printf("%d: %d",i,returnArgument(tableRegister[i].registre,0,32));
                    if(returnArgument(tableRegister[i].registre,0,32) == 0)
                    {
                        length = 0;
                    }
                    else
                    {
                        length = (int)log10(abs(returnArgument(tableRegister[i].registre,0,32)));
                        if(returnArgument(tableRegister[i].registre,0,32)< 0) length += 1;
                    }
                    for(k=length+4;k<20;k++)
                    {
                        printf(" ");
                    }
                    i++;
                }
            }  
        }      
        printf("\n");
    }
    printf("LO: %d",returnArgument(tableRegister[33].registre,0,32));
    if(returnArgument(tableRegister[33].registre,0,32) == 0)
    {
        length = 0;
    }
    else
    {
        length = (int)log10(abs(returnArgument(tableRegister[33].registre,0,32)));
        if(returnArgument(tableRegister[33].registre,0,32)< 0) length += 1;
    }
    for(k=length+4;k<20;k++)
    {
        printf(" ");
    }
    i++;
    printf("HI: %d",returnArgument(tableRegister[34].registre,0,32));
    if(returnArgument(tableRegister[34].registre,0,32) == 0)
    {
        length = 0;
    }
    else
    {
        length = (int)log10(abs(returnArgument(tableRegister[34].registre,0,32)));
        if(returnArgument(tableRegister[34].registre,0,32)< 0) length += 1;
    }
    for(k=length+4;k<20;k++)
    {
        printf(" ");
    }
    i++;
    printf("\n");
}

void showMemory(memory *ram)
{
    readMemory(ram);
}
