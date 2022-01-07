#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "instructionsConvertBinHexa.h"
#include "instructionFromFile.h"
#include "memory.h"
#include "executeInstruction.h"
#include "printTerminal.h"
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

	presentationMipsEmulator(inputFilename,outputFilename);
	

	char charInstruction;
	char instruction[1024];
	char cleanInstruction[1024];
	int cmptChar = 0;
	int numberOfRow = 0;
	int addressInstruction = 0;
	int numberOfInsructionWritten = 0;
	int isError = 0;

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

		int values[3] = {0};
		int operation;

		isError = _main_(instruction, cleanInstruction, values, &operation, numberOfRow);

		if(!isError) {
			int binaireInstruction[32] = {0};
			int hexadecimalInstruction[8] = {0};

			createBinaryInstruction(operation, values, binaireInstruction);

			writeFourOctetsInMemory(binaireInstruction, addressInstruction, 1, &RAM);
			numberOfInsructionWritten++;
			addressInstruction += 4;

			int i;

			for(i=0; i<8-log10(addressInstruction-3); i++) {
				printf("0");
			}
			printf("%d", addressInstruction-4);
			convertBinaireIntoHexAndDisplay(binaireInstruction, hexadecimalInstruction);
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
	int PC = 0;
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
			}
			readAndDecodeInstruction(PC, tableRegister, &RAM);
		}
		else {
			moreInstruction = 0;
		}
	}

	showRegister(tableRegister);
	
	fclose(inputFile);
	fclose(outputFile);

	

	return 0;
}
