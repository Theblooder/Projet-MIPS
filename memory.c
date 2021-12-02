#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "memory.h"

void readMemory(liste *memory)
{
	element *actuel = *memory;

	while(actuel != NULL)
	{
		printf("adresse : %d\n", actuel->adress);
		for(int i=0; i<8;i++) {
			printf("[%d] ", actuel->valeur[i]);
		}
		printf("\n");
		actuel = actuel->suivant;
	}	
	return;
}

void insertInMemory(int *value8bits, int adresse, liste *memory)
{
	element *actuel = *memory;
	element *precedent = NULL;
	int i;

	while(actuel != NULL) {
		if(actuel->adress == adresse) {
            for(i=0; i<8; i++) {
				actuel->valeur[i] = value8bits[i];
			}
			return;
		}
		precedent = actuel;
		actuel = actuel->suivant;
	}

	element *e = (element*) malloc(sizeof(element));
	for(i=0; i<8; i++) {
		e->valeur[i] = value8bits[i];
	}
	e->adress = adresse;

	if(precedent == NULL) {
		*memory = e;
		e->suivant = actuel;
	}
	else {
		e->suivant = actuel;

		precedent->suivant = e;
	}
}

void writeFourOctetsInMemory(int *value32bits, int startAddress, liste *memory)
{
	int i; int j;
	int value8bits[8];

	for(i=0; i<4; i++) {
		for(j=0; j<8; j++) {
			value8bits[j] = value32bits[8*i + j];
		}
		insertInMemory(value8bits, startAddress+i, memory);
	}
}