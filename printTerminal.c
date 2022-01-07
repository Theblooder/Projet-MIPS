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
    int length = 0;

    // for(i=0;i<35;i++)
    // {
    //     if(i<10)
    //     {
    //         printf("0%d: %d",i,returnArgument(tableRegister[i].registre,0,32));
    //         if(returnArgument(tableRegister[i].registre,0,32) == 0)
    //         {
    //             length = 1;
    //         }
    //         else
    //         {
    //             length = log10(returnArgument(tableRegister[i].registre,0,32));
    //         }
    //         for(k=length+4;k<20;k++)
    //         {
    //             printf(" ");
    //         }

    //         printf("0%d: %d",i,returnArgument(tableRegister[i].registre,0,32));
    //         if(returnArgument(tableRegister[i].registre,0,32) == 0)
    //         {
    //             length = 1;
    //         }
    //         else
    //         {
    //             length = log10(returnArgument(tableRegister[i].registre,0,32));
    //         }
    //         for(k=length+4;k<40;k++)
    //         {
    //             printf(" ");
    //         }

    //         printf("0%d: %d",i,returnArgument(tableRegister[i].registre,0,32));
    //     }
    //     else
    //     {
    //         printf("%d: %d",i,returnArgument(tableRegister[i].registre,0,32));
    //         if(returnArgument(tableRegister[i].registre,0,32) == 0)
    //         {
    //             length = 1;
    //         }
    //         else
    //         {
    //             length = log10(returnArgument(tableRegister[i].registre,0,32));
    //         }
    //         for(k=length+3;k<20;k++)
    //         {
    //             printf(" ");
    //         }

    //         printf("%d: %d",i,returnArgument(tableRegister[i].registre,0,32));
    //         if(returnArgument(tableRegister[i].registre,0,32) == 0)
    //         {
    //             length = 1;
    //         }
    //         else
    //         {
    //             length = log10(returnArgument(tableRegister[i].registre,0,32));
    //         }
    //         for(k=length+3;k<40;k++)
    //         {
    //             printf(" ");
    //         }

    //         printf("%d: %d",i,returnArgument(tableRegister[i].registre,0,32));
    //     }
    //     printf("\n");
    //}
}

