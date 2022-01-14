#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "instructionsConvertBinHexa.h"
#include "memory.h"
#include "instructionFromFile.h"
#include "executeInstruction.h"
#include "printTerminal.h"
#include <math.h>

#include <termios.h>
#include <unistd.h>

int getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}

int main(int argc, char * argv[])
{
	memory RAM = NULL;
	Register tableRegister[35] = {0} ;
	
	FILE *inputFile;
	FILE *outputFile;
	char inputFilename[32];
	char outputFilename[32];

	int isStepMode;
	isStepMode = openFilesAndReadArguments(inputFilename, outputFilename, argc, argv);

	inputFile = fopen(inputFilename, "r");
		if(inputFile == NULL) {
			perror("Probleme ouverture du fichier test");
			exit(0);
		}
	outputFile = fopen(outputFilename, "w");
		if(outputFile == NULL) {
			perror("Probleme ouverture du fichier hexified");
			exit(0);
		}

	presentationMipsEmulator(inputFilename, outputFilename);	
	
	int numberOfInsructionWritten = 0;
	readFileAndPutIntoMemory(inputFile, outputFile, &numberOfInsructionWritten, &RAM);

	
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
			if(isStepMode) {
				//while(getchar() != '\n');
			}
			readAndDecodeInstruction(PC, tableRegister, &RAM);
			if(isStepMode)
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
	
	
	
	fclose(inputFile);
	fclose(outputFile);

	

	return 0;
}
