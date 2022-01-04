#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "instructionsConvertBinHexa.h"
#include "instructionFromFile.h"
#include "memory.h"
#include <math.h>


int main(int argc, char * argv[])
{
	memory RAM = NULL;
	Register tableRegister[35] = {0} ;
	

	FILE *inputFile;
	FILE *outputFile;
	char inputFilename[32];
	char outputFilename[32];

	if(argc == 1) {
		printf("Erreur : veuillez rentrer un fichier d'entrée\n");
		exit(0);
	}
	else if(argc == 2) {
		char *PathTests = "tests/";	
		strcpy(inputFilename, PathTests);
		strcat(inputFilename, argv[1]);

		inputFile = fopen(inputFilename, "r");
		if(inputFile == NULL) {
			perror("Probleme ouverture du fichier test");
			exit(0);
		}

		strcpy(outputFilename, "hexified/");
		strcat(outputFilename, argv[1]);

		outputFile = fopen(outputFilename, "w");
		if(outputFile == NULL) {
			perror("Probleme ouverture du fichier hexified");
			exit(0);
		}
	}
	else {	
		char *PathTests = "tests/";	
		strcpy(inputFilename, PathTests);
		strcat(inputFilename, argv[1]);

		inputFile = fopen(inputFilename, "r");
		if(inputFile == NULL) {
			perror("Probleme ouverture du fichier test");
			exit(0);
		}
		if(argv[2][0] != '-') {
			char *PathHexified = "hexified/";
			strcpy(outputFilename, PathHexified);
			strcat(outputFilename, argv[2]);

			outputFile = fopen(outputFilename, "w");
			if(outputFile == NULL) {
				perror("Probleme ouverture du fichier hexified");
				exit(0);
			}
		}
		else {
			strcpy(outputFilename, "hexified/");
			strcat(outputFilename, argv[1]);

			outputFile = fopen(outputFilename, "w");
			if(outputFile == NULL) {
				perror("Probleme ouverture du fichier hexified");
				exit(0);
			}
		}
	}

	int isStepMode = 0;
	for(int j=1; j<argc; j++) {
		if(argv[j][0] == '-') {
			if(1==1) {
				isStepMode = 1;
			}
		}
	}

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


	char charInstruction;
	char instruction[1024];
	char cleanInstruction[1024];
	int cmptChar = 0;
	int numberOfRow = 0;
	int lengthInstruction = 0;
	int addressInstruction = 0;
	int numberOfInsructionWritten = 0;
	int PC = 0;

	while(!feof(inputFile)) {
		numberOfRow++;
		fscanf(inputFile, "%c", &charInstruction);
		while(charInstruction != '\n' && !feof(inputFile)) {
			if(cmptChar < 1022) {
				instruction[cmptChar++] = charInstruction;
			}
			else if(cmptChar == 1022) {
				printf("ERROR : row %d contain too much characters\n", numberOfRow);
				cmptChar++;
			}
			fscanf(inputFile, "%c", &charInstruction);
		}
		instruction[cmptChar] = '\0';
		cmptChar = 0;

		lengthInstruction = cleanInstructionReturnLength(instruction, cleanInstruction);
		// printf("ins:%s:\n", instruction);
		// printf("clean ins:%s:\n", cleanInstruction);
		// printf("%d\n", lengthInstruction);

		int nbrRegOff[2];
		int operation;
		int currentPosition;
		int isError = 0;

		currentPosition = getOperation(cleanInstruction, nbrRegOff, &operation);
		if(operation == 0) {
			if(strlen(cleanInstruction) != 0) {
				printf("ERROR : row %d : wrong argument\n", numberOfRow);
			}
			continue;
		}
		// printf("operation :%d:\n", operation);
		// printf("pos :%d\n", currentPosition);
		// printf("reg :%d\n", nbrRegOff[0]);
		// printf("off :%d\n", nbrRegOff[1]);

		int values[3] = {0};
		int number;

		if(operation == 13 || operation == 24) {
			if(currentPosition < lengthInstruction) {
				number = getRegisterOffset(cleanInstruction, &currentPosition, 1, &isError);
			}
			if(!isError) {
				values[0] = number;
			}
			if(currentPosition < lengthInstruction) {
				number = getRegisterOffset(cleanInstruction, &currentPosition, 0, &isError);
			}
			if(!isError) {
				values[1] = number;
			}
			if(currentPosition < lengthInstruction) {
				number = getRegisterOffset(cleanInstruction, &currentPosition, 1, &isError);
			}
			if(!isError) {
				values[2] = number;
			}
			if(isError) {
				printf("ERROR row %d: register or offset value is wrong or missing\n", numberOfRow);
			}
		}
		else {
			for(int k=0; k<nbrRegOff[0]; k++) {
				if(currentPosition < lengthInstruction) {
					number = getRegisterOffset(cleanInstruction, &currentPosition, 1, &isError);
				}
				else {
					printf("ERROR row %d: register value (n°%d) is missing\n", numberOfRow, k+1);
					isError = 1;
					break;
				}

				if(isError) {
					printf("ERROR row %d: wrong register value (n°%d)\n", numberOfRow, k+1);
					break;
				}
				else {
					values[k] = number;
				}
			}
			for(int k=0; k<nbrRegOff[1]; k++) {
				if(currentPosition < lengthInstruction) {
					number = getRegisterOffset(cleanInstruction, &currentPosition, 0, &isError);
				}
				else {
					printf("ERROR row %d: offset value (n°%d) is missing\n", numberOfRow, k+1);
					isError = 1;
					break;
				}

				if(isError) {
					printf("ERROR row %d: wrong offset value (n°%d)\n", numberOfRow, k+1);
					break;
				}
				else {
					values[nbrRegOff[0]+k] = number;
				}
			}
		}

		// printf("%d\n", values[0]);
		// printf("%d\n", values[1]);
		// printf("%d\n", values[2]);

		if(!isError) {
			int binaireInstruction[32] = {0};
			int hexadecimalInstruction[8] = {0};

			createBinaryInstruction(operation, values, binaireInstruction);
			convertBinaireIntoHex(binaireInstruction, hexadecimalInstruction);

			writeFourOctetsInMemory(binaireInstruction, addressInstruction, 1, &RAM);
			numberOfInsructionWritten++;
			addressInstruction += 4;

			int i;

			for(i=0; i<8-log10(addressInstruction-3); i++) {
				printf("0");
			}
			printf("%d", addressInstruction-4);
			displayHexadecimal(hexadecimalInstruction);
			printf(" : {%s}\n", cleanInstruction);

			/* writing exa in output file */
			for(i=0; i<8; i++) {
				fprintf(outputFile, "%x", hexadecimalInstruction[i]);
			}
			fputc('\n', outputFile);
		}
	}

	while(getchar() != '\n');

	int i;
	int tempPC = 0;
	int moreInstruction = 1;

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
				while(getchar() != '\n');

				printf("Execution of :\n");
			}
			readAndDecodeInstruction(PC, tableRegister, &RAM);
			// printf("\n");
		}
		else {
			moreInstruction = 0;
		}
	}

	fclose(inputFile);
	fclose(outputFile);

	return 0;
}
