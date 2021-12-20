#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "instructionsConvertBinHexa.h"
#include "memory.h"
#include <math.h>


int main(int argc, char * argv[])
{

	memory RAM = NULL;
	Register tableRegister[32] = {0} ;
	
	unsigned long long int value = 4147483649;                          /* 2147483647 max value for 32 bits and -2147483648 min value for 32 bits */
	int i;						   
								   
	for(i=0; value>0; i++) {
        tableRegister[1].registre[i] = value % 2;  
        value = value / 2;
    }
	value = 4147483649;
	for(i=0; value>0; i++) {
        tableRegister[2].registre[i] = value % 2;  
        value = value / 2;  
    }

	value = 0;
	for(i=0; value>0; i++) {
        tableRegister[4].registre[i] = value % 2;  
        value = value / 2;  
    }
	
	int binaireInstruction2[32] = {0};

	int binaire3[32] = {0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0}; 	//	ADD  R01 + R02 --> R04
	//int binaire3[32] = {0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0};		//	ADDI 17412 + R02 --> R04
	//int binaire3[32] = {0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0}; 	//	SUB  R01 - R02 --> R04
	//int binaire3[32] = {0,0,1,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0}; 	//	AND  R01 & R02 --> R04
	//int binaire3[32] = {1,0,1,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0};   	//	OR   R01 | R02 --> R04
	//int binaire3[32] = {0,0,0,0,0,0,0,0,1,1,1,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; 	//	SLL  R02 << 28 --> R04
	//int binaire3[32] = {0,1,0,1,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0};		//	SLT  R02 < R01 ? --> R04
	//int binaire3[32] = {0,1,1,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0};		//	XOR  R01 XOR R02 --> R04
	//int binaire3[32] = {0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; 	//	SRL  R02 >> 2 --> R04
	//int binaire3[32] = {0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0}; 	//	ROTR R02 >> 2 --> R04
	//int binaire3[32] = {0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0};		//	MULT R02 * 30 --> R26/27
	//int binaire3[32] = {0,1,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};		//	MFLO R8 <-- R26
	//int binaire3[32] = {0,0,0,0,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};	    //	MFHI R12 <-- R27
	//int binaire3[32] = {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,1,1};		//	LW   R4 <-- 2(R2)
	//int binaire3[32] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,1,0,1,1};		//	SW 	 R2 --> 0(R4)			
	//int binaire3[32] = {0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1};		//  LUI R2 = 12 || 0^16
	//int binaire3[32] = {0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1};		//  JAL 12
	//int binaire3[32] = {0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0};		//  JR R2
	//int binaire3[32] = {0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0};		//  J 12
	//int binaire3[32] = {0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,1,0,1};		//  BNE R4 != R2 ? --> PC  + 12
	//int binaire3[32] = {0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,1,1};		//	BGTZ R2 > 0 ? --> PC  + 12
	//int binaire3[32] = {0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,1,0};		//  BLEZ R2 <= 0 ? --> PC  + 12
	//int binaire3[32] = {0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,1,0,0};		//	BEQ R8 = R2 ? --> PC  + 12
	//int binaire3[32] = {0,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0};		//	DIV R2/R4 --> R26/27	

	writeFourOctetsInMemory(binaire3, 0, 0, &RAM);
    readAndDecodeInstruction(0, tableRegister, &RAM);


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

	// int PC = 0;
	// int addressInstruction = 0;
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
	// 				//convertBinaireIntoHex(binaireInstruction, hexadecimalInstruction);
	// 				int i;
	// 				for(i=31;i>=0;i--)
	// 				{
	// 					printf("%d",binaireInstruction[i]);
	// 				}
	// 				printf("\n");

	// 				writeFourOctetsInMemory(binaireInstruction, addressInstruction, 1, &RAM);
	// 				//printf("dd\n");
	// 				addressInstruction += 4;

	// 				// displayHexadecimal(hexadecimalInstruction);
	// 				// printf(" : {%s}\n", instruction);

	// 				// /* writing exa in output file */
	// 				// for(int i=0; i<8; i++) {
	// 				// 	fprintf(outputFile, "%x", hexadecimalInstruction[i]);
	// 				// }
	// 				// fputc('\n', outputFile);
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
	
	// while(PC<8)
	// {

	// 	for(i=31;i>=0;i--)
	// 	{
	// 		PC += (unsigned long long int) (pow(2, i) * tableRegister[32].registre[i]);
	// 	}
	// 	readAndDecodeInstruction(PC,binaireInstruction2, tableRegister, &RAM);
	// 	printf("\n");
	// }


	// fclose(inputFile);
	// fclose(outputFile);

	return 0;
}
