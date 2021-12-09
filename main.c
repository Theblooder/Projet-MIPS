#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "instructionsConvertBinHexa.h"
#include "memory.h"


int main(int argc, char * argv[])
{
	memory RAM = NULL; /* RAM size is 4GB */

	int binaire2[32] = {0,0,1,1,0,1,0,1,0,0,0,0,1,1,1,1,1,0,0,0,0,1,1,1,1,0,0,1,0,1,0,1};
	int binaire7[32] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,1,0,0,0,1,1,0,1,0,1,0};


	writeFourOctetsInMemory(binaire2, 50, &memory);
	writeFourOctetsInMemory(binaire7, 130, &memory);
	
	int binaire3[32];
	int binaire4[32];

	readFourOctetsInMemory(binaire3, 12, &memory);
	for(int i=0; i<32; i++) {
		printf("[%d] ", binaire3[i]);
	}

	printf("\n\n						+\n\n");

	readFourOctetsInMemory(binaire4, 50, &memory);
	for(int i=0; i<32; i++) {
		printf("[%d] ", binaire4[i]);
	}

	printf("\n\n						=\n\n");

	int binaire5[32];
	int binaire6[32];

	if(addTwoBinaryRegister(binaire3,binaire4,binaire5)) printf("overflowed\n");
	writeFourOctetsInMemory(binaire5, 90, &memory);
	readFourOctetsInMemory(binaire5, 90, &memory);
	for(int i=0; i<32; i++) {
		printf("[%d] ", binaire5[i]);
	}

	printf("\n\n\n");

	readFourOctetsInMemory(binaire5, 90, &memory);
	for(int i=0; i<32; i++) {
		printf("[%d] ", binaire5[i]);
	}

	printf("\n\n						-\n\n");

	int binaire8[32];
	int binaire9[32];

	readFourOctetsInMemory(binaire8, 130, &memory);
	for(int i=0; i<32; i++) {
		printf("[%d] ", binaire8[i]);
	}

	printf("\n\n						=\n\n");

	subTwoBinaryRegister(binaire5,binaire8,binaire9);
	writeFourOctetsInMemory(binaire9, 160, &memory);

	int binaire10[32];

	readFourOctetsInMemory(binaire10, 160, &memory);
	for(int i=0; i<32; i++) {
		printf("[%d] ", binaire10[i]);
	}

	printf("\n");

	// FILE *fic;
	// char filename[32] = "tests/in1.txt";
	// // char *PathTests = "tests/";
	// // strcpy(filename, PathTests);
	// // strcat(filename, argv[1]);

	// fic = fopen(filename, "r");
	// if(fic == NULL) {
	// 	perror("Probleme ouverture du fichier");
	// 	exit(0);
	// }

	
	// char charInstruction;
	// char instruction[32];

	// int cmptChar = 0;

	// while(!feof(fic)) {
	// 	fscanf(fic, "%c", &charInstruction);
	// 	if(charInstruction == '\n') {
	// 		instruction[cmptChar] = '\0';
	// 		cmptChar = 0;

	// 		if(!isStringFullOfSpaces(instruction) && !isBeginWithCommentCharBeforeAnyCharOtherThanSpace(instruction)) {
	// 			int binaireInstruction[32] = {0};
	// 			int hexadecimalInstruction[8]= {0};
	// 			char operation[5];
	// 			int values[3];

	// 			instructionValue(instruction, values, operation);
	// 			// printf("%s\n", operation);
	// 			// printf("%d\n", values[0]);
	// 			// printf("%d\n", values[1]);
	// 			// printf("%d\n", values[2]);

	// 			createBinaryInstruction(operation, values, binaireInstruction);

	// 			convertBinaireIntoHex(binaireInstruction, hexadecimalInstruction);
		
	// 			//displayBinary(binaireInstruction);

	// 			displayHexadecimal(hexadecimalInstruction);
	// 		}

	// 	}
	// 	else {
	// 		instruction[cmptChar++] = charInstruction;
	// 	}

	// }

	// fclose(fic);

	return 0;
}
