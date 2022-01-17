#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "instructionsConvertBinHexa.h"
#include "memory.h"
#include "instructionFromFile.h"
#include "executeInstruction.h"
#include "printTerminal.h"
#include <math.h>

int main(int argc, char * argv[])
{
	memory RAM = NULL;
	Register tableRegister[35] = {0};
	
	FILE *inputFile;
	FILE *outputHexaFile;
	FILE *outputRegisterFile;
	char inputFilename[32];
	char outputHexaFilename[32];
	char outputRegisterFilename[32];

	int modeType;
	modeType = openFilesAndReadArguments(inputFilename, outputHexaFilename, outputRegisterFilename, argc, argv);

	if(modeType != 2) {
		inputFile = fopen(inputFilename, "r");
			if(inputFile == NULL) {
				perror("Problem opening the test file");
				exit(0);
			}
		outputHexaFile = fopen(outputHexaFilename, "w");
			if(outputHexaFile == NULL) {
				perror("Problem opening the hexified file");
				exit(0);
			}
		if(outputRegisterFilename[0] != '\0') {
			outputRegisterFile = fopen(outputRegisterFilename, "w");
				if(outputRegisterFile == NULL) {
					perror("Problem opening the registry file");
					exit(0);
				}
		}
	}

	presentationMipsEmulator(inputFilename, outputHexaFilename, outputRegisterFilename);
	
	int numberOfInsructionWritten = 0;

	if(modeType == 2)
	{
		interactifMode(numberOfInsructionWritten, &RAM, tableRegister);
	}
	else
	{
		readFileAndPutIntoMemory(inputFile, outputHexaFile, &numberOfInsructionWritten, &RAM);

		while(getchar() != '\n');

		int i;
		int PC = 0;
		int tempPC = 0;
		int moreInstruction = 1;
		unsigned char choice = 0;

		while(moreInstruction)
		{
			i = 0; tempPC = 0;

			for(i=31;i>=0;i--)
			{
				tempPC += (unsigned long long int) (pow(2, i) * tableRegister[32].registre[i]);
			}
			PC = tempPC;

			if(PC < 4*numberOfInsructionWritten) {
				readAndDecodeInstruction(PC, tableRegister, &RAM);
				if(modeType == 1)
				{
					printf("[1 or enter] Continue	 [2] Show registers 	[3] Show memory\n\n");
				
					while (choice = getch(),(choice != '\n') || (choice != 0x32) || (choice != 0x33) || (choice != 0x31))
					{
						if((choice == '\n')||(choice == 0x31)) break;
						if(choice == 0x32)
						{
							showRegister(tableRegister);
							printf("[1 or enter] Continue	 [2] Show registers 	[3] Show memory\n\n");
						}
						if(choice == 0x33) 
						{
							showMemory(&RAM);
							printf("[1 or enter] Continue	 [2] Show registers 	[3] Show memory\n\n");
						}
					}	
				}	
			}
			else {
				moreInstruction = 0;
			}	
		}
	}
	
	showRegister(tableRegister);
	showMemory(&RAM);
	
	if(outputRegisterFilename[0] != '\0')
	{
		putRegisterInFile(tableRegister, outputRegisterFile);
		fclose(outputRegisterFile);
	}
	
	if(modeType != 2) {
		fclose(inputFile);
		fclose(outputHexaFile);
	}
	

	return 0;
}
