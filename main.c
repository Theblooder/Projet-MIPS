#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "instructionsConvertBinHexa.h"
#include "memory.h"


typedef struct element element;

struct element {
	int valeur;/* valeur de l’élément */
	int adress;
	element *suivant;/* adresse du successeur */
};
typedef element* liste;

void afficherListe(liste *l);
void insererElement(int x, int adresse, liste *l);


int main(void)
{
	liste L = NULL;


	insererElement(2, 1, &L);
	insererElement(3, 1, &L);

	afficherListe(&L);

	return 0;
}

void afficherListe(liste *l)
{
	element *actuel = *l;

	while(actuel != NULL)
	{
		printf("value : %d\n", actuel->valeur);
		printf("adresse : %d\n", actuel->adress);
		actuel = actuel->suivant;
	}	
	return;
}

void insererElement(int x, int adresse, liste *l)
{
	element *actuel = *l;
	element *precedent = NULL;
	

	while(actuel != NULL) {
		if(actuel->adress == adresse) {
			actuel->valeur = x;
			return;
		}
		precedent = actuel;
		actuel = actuel->suivant;
	}

	element *e = (element*) malloc(sizeof(element));
	e->valeur = x;
	e->adress = adresse;

	if(precedent == NULL) {
		*l = e;
		e->suivant = actuel;
	}
	else {
		e->suivant = actuel;

		precedent->suivant = e;
	}
}

// int main(int argc, char * argv[])
// {
// 	FILE *fic;
// 	char filename[32] = "tests/in1.txt";
// 	// char *PathTests = "tests/";
// 	// strcpy(filename, PathTests);
// 	// strcat(filename, argv[1]);

// 	fic = fopen(filename, "r");
// 	if(fic == NULL) {
// 		perror("Probleme ouverture du fichier");
// 		exit(0);
// 	}

	
// 	char charInstruction;
// 	char instruction[32];

// 	int cmptChar = 0;

// 	while(!feof(fic)) {
// 		fscanf(fic, "%c", &charInstruction);
// 		if(charInstruction == '\n') {
// 			instruction[cmptChar] = '\0';
// 			cmptChar = 0;

// 			if(!isStringFullOfSpaces(instruction) && !isBeginWithCommentCharBeforeAnyCharOtherThanSpace(instruction)) {
// 				int binaireInstruction[32] = {0};
// 				int hexadecimalInstruction[8]= {0};
// 				char operation[5];
// 				int values[3];

// 				instructionValue(instruction, values, operation);
// 				printf("%s\n", operation);
// 				printf("%d\n", values[0]);
// 				printf("%d\n", values[1]);
// 				printf("%d\n", values[2]);

// 				createBinaryInstruction(operation, values, binaireInstruction);

// 				convertBinaireIntoHex(binaireInstruction, hexadecimalInstruction);
		
// 				//displayBinary(binaireInstruction);

// 				displayHexadecimal(hexadecimalInstruction);
// 			}

// 		}
// 		else {
// 			instruction[cmptChar++] = charInstruction;
// 		}

// 	}

// 	fclose(fic);

// 	return 0;
// }
