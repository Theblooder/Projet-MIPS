#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "instructionsConvertBinHexa.h"
#include "memory.h"


int main(int argc, char * argv[])
{
	// memory RAM = NULL; /* RAM size is 4GB */

	// int binaire3[32] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1};
	// int binaire4[32] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0};
	// for(int i=0; i<32; i++) {
	// 	printf("[%d] ", binaire3[i]);
	// }

	// printf("\n");

	// for(int i=0; i<32; i++) {
	// 	printf("[%d] ", binaire4[i]);
	// }
	// printf("\n");


	// // writeFourOctetsInMemory(binaire2, 50, &RAM);
	// // writeFourOctetsInMemory(binaire7, 130, &RAM);
	
	// // int binaire3[32];
	// // int binaire4[32];

	// // readFourOctetsInMemory(binaire3, 50, &RAM);
	// // for(int i=0; i<32; i++) {
	// // 	printf("[%d] ", binaire3[i]);
	// // }

	// // printf("\n\n						+\n\n");

	// // readFourOctetsInMemory(binaire4, 130, &RAM);
	// // for(int i=0; i<32; i++) {
	// // 	printf("[%d] ", binaire4[i]);
	// // }

	// // printf("\n\n						=\n\n");

	// int binaire5[32];
	// // int binaire6[32];

	// if(addTwoBinaryRegister(binaire3,binaire4,binaire5)) printf("overflowed\n");
	// for(int i=0; i<32; i++) {
	// 	printf("[%d] ", binaire5[i]);
	// }
	// printf("\n");

	// // printf("\n\n\n");

	// // readFourOctetsInMemory(binaire5, 90, &RAM);
	// // for(int i=0; i<32; i++) {
	// // 	printf("[%d] ", binaire5[i]);
	// // }

	// // printf("\n\n						-\n\n");

	// // int binaire8[32];
	// // int binaire9[32];

	// // readFourOctetsInMemory(binaire8, 130, &RAM);
	// // for(int i=0; i<32; i++) {
	// // 	printf("[%d] ", binaire8[i]);
	// // }

	// // printf("\n\n						=\n\n");

	// // subTwoBinaryRegister(binaire5,binaire8,binaire9);
	// // writeFourOctetsInMemory(binaire9, 160, &RAM);

	// // int binaire10[32];

	// // readFourOctetsInMemory(binaire10, 160, &RAM);
	// // for(int i=0; i<32; i++) {
	// // 	printf("[%d] ", binaire10[i]);
	// // }

	// // printf("\n");





	memory RAM = NULL;
	Register tableRegister[32] = {0} ;
	
	int value = 30;
	int i;

	for(i=0; value>0; i++) {
        tableRegister[4].registre[i] = value % 2;  
        value = value / 2;  
    }
	value = 40;
	for(i=0; value>0; i++) {
        tableRegister[0].registre[i] = value % 2;  
        value = value / 2;  
    }
	
	int binaireInstruction2[32] = {0};
	int binaire3[32] = {0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0};
	writeFourOctetsInMemory(binaire3, 0, &RAM);
	readAndDecodeInstruction(0,binaireInstruction2, tableRegister, &RAM);






	// if(argc <= 2) {
	// 	printf("Erreur : veuillez rentrer un fichier d'entrée et de sortie\n");
	// 	exit(0);
	// }

	// FILE *inputFile;	
	// char inputFilename[32];
	// char *PathTests = "tests/";
	// strcpy(inputFilename, PathTests);
	// strcat(inputFilename, argv[1]);

	// inputFile = fopen(inputFilename, "r");
	// if(inputFile == NULL) {
	// 	perror("Probleme ouverture du fichier test");
	// 	exit(0);
	// }

	// FILE *outputFile;
	// char outputFilename[32];
	// char *PathHexified = "hexified/";
	// strcpy(outputFilename, PathHexified);
	// strcat(outputFilename, argv[2]);

	// outputFile = fopen(outputFilename, "w");
	// if(outputFile == NULL) {
	// 	perror("Probleme ouverture du fichier hexified");
	// 	exit(0);
	// }

	// char charInstruction;
	// char instruction[64];

	// char registres[32] = {0};

	// int cmptChar = 0;
	// int isOneSpaceChar = 0;
	// int insNotBegin = 1;
	// int numberOfRow = 1;

	// while(!feof(inputFile)) {
	// 	fscanf(inputFile, "%c", &charInstruction);
	
	// 	if(charInstruction == '\n' || feof(inputFile)) {
	// 		instruction[cmptChar] = '\0';
	// 		cmptChar = 0;

	// 		if(!isStringFullOfSpaces(instruction) && !isBeginWithCommentCharBeforeAnyCharOtherThanSpace(instruction)) {
	// 			int binaireInstruction[32] = {0};
	// 			int hexadecimalInstruction[8] = {0};
	// 			char operation[10];
	// 			int values[3];

	// 			instructionValue(instruction, values, operation);
	// 			// printf("%s\n", operation);
	// 			// printf("%d\n", values[0]);
	// 			// printf("%d\n", values[1]);
	// 			// printf("%d\n", values[2]);

	// 			if(!createBinaryInstruction(operation, values, binaireInstruction)) {
	// 				convertBinaireIntoHex(binaireInstruction, hexadecimalInstruction);
		
	// 				//displayBinary(binaireInstruction);
			
	// 				displayHexadecimal(hexadecimalInstruction);
	// 				printf(" : {%s}\n", instruction);

	// 				/* writing exa in output file */
	// 				for(int i=0; i<8; i++) {
	// 					fprintf(outputFile, "%x", hexadecimalInstruction[i]);
	// 				}
	// 				fputc('\n', outputFile);
	// 			}
	// 			else {
	// 				printf("Erreur de syntaxe ligne : %d\n", numberOfRow);
	// 				break;
	// 			}
	// 		}
	// 		numberOfRow++;
	// 	}
	// 	else if(charInstruction == ' ' && (isOneSpaceChar || insNotBegin)){
	// 		1 == 1;
	// 	}
	// 	else if(cmptChar <= 62){
	// 		instruction[cmptChar++] = charInstruction;
	// 		insNotBegin = 0;
	// 	}

	// 	if(charInstruction == ' ') {
	// 		isOneSpaceChar = 1;
	// 	}
	// 	else {isOneSpaceChar = 0;}

	// }

	// fclose(inputFile);
	// fclose(outputFile);

	return 0;
}
