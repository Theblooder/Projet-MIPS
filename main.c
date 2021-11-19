#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * argv[])
{
	FILE *fic;

	char filename[32];
	char* PathTests = "tests/";
	strcpy(filename, PathTests);
	strcat(filename, argv[1]);

	fic = fopen(filename, "r");
	if(fic == NULL) {
		perror("Probleme ouverture du fichier");
		exit(0);
	}
	
	
	char instruction[20];

	while(!feof(fic)) {
		fscanf(fic, "%s", instruction);
		printf("Valeur lue = %s\n", instruction);
	}

	fclose(fic);

	return 0;
}
