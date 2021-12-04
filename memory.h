#ifndef __MEMORY__H_
#define __MEMORY__H_

typedef struct element element;

struct element {
	int valeur[8];/* valeur de l’élément */
	int adress;
	element *suivant;/* adresse du successeur */
};
typedef element* liste;


void readMemory(liste *memory);

void insertInMemory(int *value8bits, int adresse, liste *memory);

void getValueFromMemory(int *value8bits, int adresse, liste *memory);

void writeFourOctetsInMemory(int *value32bits, int startAddress, liste *memory);

void readFourOctetsInMemory(int *value32bits, int startAddress, liste *memory);

int addTwoBinaryRegister(int *register1, int *register2, int *destinationRegister);

int subTwoBinaryRegister(int *register1, int *register2, int *destinationRegister);

#endif