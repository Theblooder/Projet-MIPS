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
	
	unsigned long long int value = 30;
	int i;						   
								   
	for(i=0; value>0; i++) {
        tableRegister[1].registre[i] = value % 2;  
        value = value / 2;  
    }
	value = 51;
	for(i=0; value>0; i++) {
        tableRegister[2].registre[i] = value % 2;  
        value = value / 2;  
    }

	value = 69;
	for(i=0; value>0; i++) {
        tableRegister[4].registre[i] = value % 2;  
        value = value / 2;  
    }

	// int valueTest[32] = {1,1,1,1,1,1,1,0,1,0,0,0,1,1,1,1,1,0,1,0,1,1,0,0,1,0,1,0,1,1,1,0};
    // int test[32] = {0};

	// writeFourOctetsInMemory(valueTest, 51, &RAM);
	// readInstructionInMemory(51,test,&RAM);
	// int k;
	// for(k=31;k>=0;k--)
	// {
	// 	printf("%d",test[k]);
	// }
	// printf("\n");

	// value = 658;
	// for(i=0; value>0; i++) {
    //     tableRegister[26].registre[i] = value % 2;  
    //     value = value / 2;  
    // }

	// value = 96325;
	// for(i=0; value>0; i++) {
    //     tableRegister[27].registre[i] = value % 2;  
    //     value = value / 2;  
    // }

	// i = 0;
	// while (tableRegister[2].registre[i] != 1)
	// {
	// 	i++;
	// }
	
	// for(i=i+1; i<32; i++)  
    // {	
    //     if (tableRegister[2].registre[i] == 0)
    //     	tableRegister[2].registre[i] = 1;
    // 	else tableRegister[2].registre[i] = 0;
    // }
	
	int binaireInstruction2[32] = {0};

	//int binaire3[32] = {0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0}; 	//	ADD  R01 + R02 --> R04
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
	//int binaire3[32] = {0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1};		// JAL 12
	//int binaire3[32] = {0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0};		// JR R2
	int binaire3[32] = {0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0};

	writeFourOctetsInMemory(binaire3, 0, &RAM);
	readAndDecodeInstruction(0,binaireInstruction2, tableRegister, &RAM);


	int k;
	for(k=31;k>=0;k--)
	{
		printf("%d",tableRegister[29].registre[k]);
	}
	printf("\n");

	// for(k=31;k>=0;k--)
	// {
	// 	printf("%d",tableRegister[31].registre[k]);
	// }
	// printf("\n");

	// readInstructionInMemory(69,test,&RAM);
	// int k;
	// for(k=31;k>=0;k--)
	// {
	// 	printf("%d",test[k]);
	// }
	// printf("\n");


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
