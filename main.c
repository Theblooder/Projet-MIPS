#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "instructionsConvertBinHexa.h"
#include "memory.h"


int main(int argc, char * argv[])
{
	liste memory = NULL;

	int binaire[32] = {0,1,0,1,1,1,0,0,0,1,0,1,1,0,1,0,1,0,0,0,1,1,1,0,1,0,1,1,0,1,1,0};

	writeFourOctetsInMemory(binaire, 0, &memory);
	readMemory(&memory);

	int binaire2[32] = {1,1,0,1,1,1,0,0,0,1,0,1,1,0,1,0,1,0,0,0,1,1,1,0,1,0,1,1,0,1,1,1};

	writeFourOctetsInMemory(binaire2, 0, &memory);
	readMemory(&memory);


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
