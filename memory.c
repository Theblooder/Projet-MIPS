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

void getValueFromMemory(int *value8bits, int adresse, liste *memory)
{
	element *actuel = *memory;
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
	printf("Cette adresse de la mémoire ne contient pas de valeur\n");
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

void readFourOctetsInMemory(int *value32bits, int startAddress, liste *memory)
{
	int i; int j;

	int value8bits[8];

	for(i=0; i<4; i++) {
		getValueFromMemory(value8bits, startAddress+i, memory);
		for(j=0; j<8; j++) {
			value32bits[8*i + j] = value8bits[j];
		}
	}
}


//Ne fonctionne pas avec des chiffres négatifs, je me pose la question si ADD à le droit d'avoir des chiffres négatif, ADDI oui mais juste pour le immediate j'ai l'impression
//alors que je crois me rappeler qu'on a toujours eu le droit d'avoir des registres avec des chiffres négatifs...
//Faut qu'on regarde, puis je ferais les modifs en conséquence

int addTwoBinaryRegister(int *register1, int *register2, int *destinationRegister)
{
	int i;
	int carry = 0;
	int overflowed = 0;
	for(i=31;i>=0;i--)
	{
		destinationRegister[i] = register1[i] + register2[i] + carry;
		carry = 0;
		if(destinationRegister[i] == 2)
		{
			destinationRegister[i] = 0;
			carry = 1;
		}
		else if(destinationRegister[i] == 3)
		{
			destinationRegister[i] = 1;
			carry = 1;
		}
	}
	if(carry == 1)	overflowed = 1;
	
	return overflowed;
}

int subTwoBinaryRegister(int *register1, int *register2, int *destinationRegister)
{
	int i = 31;
	int carry = 0;
	int overflowed = 0;
	while (register2[i] != 1)
	{
		i--;
	}
	
	for(i=i-1; i>=0; i--)  
    {	
        if (register2[i] == 0)
            register2[i] = 1;
        else register2[i] = 0;
    }

	for(i=31;i>=0;i--)
	{
		destinationRegister[i] = register1[i] + register2[i] + carry;
		carry = 0;
		if(destinationRegister[i] == 2)
		{
			destinationRegister[i] = 0;
			carry = 1;
		}
		else if(destinationRegister[i] == 3)
		{
			destinationRegister[i] = 1;
			carry = 1;
		}
	}
	if(carry == 1)	overflowed = 1;
	
	return overflowed;

	/*
	int tempRegister[32] = {0};

	for(i=15; i>=0; i--)  
    {	
        tempRegister[i] = register2[i];
    }

	i = 31;

	while (tempRegister[i] != 1)
	{
		i--;
	}
	
	for(i=i-1; i>=0; i--)  
    {	
        if (tempRegister[i] == 0)
            tempRegister[i] = 1;
        else tempRegister[i] = 0;
    }

	for(i=31;i>=0;i--)
	{
		destinationRegister[i] = register1[i] + register2[i] + carry;
		carry = 0;
		if(destinationRegister[i] == 2)
		{
			destinationRegister[i] = 0;
			carry = 1;
		}
		else if(destinationRegister[i] == 3)
		{
			destinationRegister[i] = 1;
			carry = 1;
		}
	}
	if(carry == 1)	overflowed = 1;
	
	return overflowed;

	*/
}