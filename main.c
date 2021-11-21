#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "instructionsConvertBinHexa.h"

int main(int argc, char * argv[])
{
	//	FILE *fic;

	// char filename[32];
	// char* PathTests = "tests/";
	// strcpy(filename, PathTests);
	// strcat(filename, argv[1]);

	// fic = fopen(filename, "r");
	// if(fic == NULL) {
	// 	perror("Probleme ouverture du fichier");
	// 	exit(0);
	// }
	
	// char instruction[20];

	// while(!feof(fic)) {
	// 	fscanf(fic, "%s", instruction);
	// 	printf("Valeur lue = %s\n", instruction);
	// }

	// fclose(fic);


	char instruction[32] = "ADD $3 $2 $3";
	//char instruction[32] = "ADDI $3 $2 32700";
	int binaireInstruction[32] = {0};
	int hexadecimalInstruction[8]= {0};
	char operation[5];
	int values[3];

	instructionValue(instruction, values, operation);
	printf("%s\n", operation);
	printf("%d\n", values[0]);
	printf("%d\n", values[1]);
	printf("%d\n", values[2]);
	
	//printf("%ld\n", strlen(operation));	//Erreur

	FunctionChoice(operation, values, binaireInstruction, hexadecimalInstruction);

	

	//convertIntoBinaireADD(instruction, binaireInstruction);

	//printf("%s\n", binaireInstruction);

	return 0;
}
