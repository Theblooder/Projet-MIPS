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


	char instruction[32] = "ADD $3 $34";
	char binaireInstruction[33];
	int values[3];

	instructionValue(instruction, values);

	printf("%d\n", values[0]);
	printf("%d\n", values[1]);
	printf("%d\n", values[2]);

	//convertIntoBinaireADD(instruction, binaireInstruction);

	//printf("%s\n", binaireInstruction);

	return 0;
}
