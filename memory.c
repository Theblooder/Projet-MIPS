#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "memory.h"
#include "executeInstruction.h"

void readMemory(memory *m)
{
	element *actuel = *m;

	int Value32Bits[32] = {0};
	int finalValue = 0;
	int i = 0;
	int j = 0;
	int address = 0;
	int type = 0;
	int noData = 0;

	while (actuel != NULL)
	{
		for(i=0; i<4; i++) {
		
			for(j=0; j<8; j++) {
				Value32Bits[8*i + j] = actuel->valeur[j];
			}
			address = actuel->adress;
			type = actuel->type;
			actuel = actuel->suivant;
			if(type == 0) noData = 1;
		}
		if(type == 0) {
			printf("%d : ", address - 1000);
			finalValue = returnArgument(Value32Bits,0,32);
			printf("%d\n\n",finalValue);
		}
	}	

	if(noData == 0) printf("There is no DATA in memory\n\n");
	
	return;
}

void readFourOctets(int *value32bits, int startAddress, memory *m)
{
	int i; int j;

	int value8bits[8];

	for(i=0; i<4; i++) {
		getValueFromMemory(value8bits, startAddress+(3-i), m);
		for(j=0; j<8; j++) {
			value32bits[8*i + j] = value8bits[j];
		}
	}
}

void getValueFromMemory(int *value8bits, int adresse, memory *m)
{
	element *actuel = *m;
	element *precedent = NULL;
	int i;

	while(actuel != NULL) {
		if(actuel->adress == adresse) {
            for(i=0; i<8; i++) {
				value8bits[i] = actuel->valeur[i];
			}
			return;
		}
		precedent = actuel;
		actuel = actuel->suivant;
	}
	printf("This memory address does not contain a value\n");
	for(i=0; i<8; i++) 
	{
		value8bits[i] = 0;
	}
}

void insertInMemory(int *value8bits, int adresse, int type, memory *m)
{
	element *actuel = *m;
	element *precedent = NULL;
	int i;

	while(actuel != NULL) {
		if(actuel->adress == adresse) {
			if(actuel->type == type) {
				for(i=0; i<8; i++) {
					actuel->valeur[i] = value8bits[i];
				}
			}
			else {
				printf("You can't edit data on an instruction\n");
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
	e->type = type;

	if(precedent == NULL) {
		*m = e;
		e->suivant = actuel;
	}
	else {
		e->suivant = actuel;

		precedent->suivant = e;
	}
}

void writeFourOctetsInMemory(int *value32bits, int startAddress, int type, memory *m)
{
	int i; int j;
	int value8bits[8];

	for(i=0; i<4; i++) {
		for(j=0; j<8; j++) {
			value8bits[j] = value32bits[8*i + j];
		}
		insertInMemory(value8bits, startAddress+(3-i), type, m);
	}
}

void readFourOctetsInMemory(int *value32bits, int startAddress, memory *m)
{
	int i; int j;

	int value8bits[8];

	for(i=0; i<4; i++) {
		getValueFromMemory(value8bits, startAddress+(3-i), m);
		for(j=0; j<8; j++) {
			value32bits[8*i + j] = value8bits[j];
		}
	}
}

