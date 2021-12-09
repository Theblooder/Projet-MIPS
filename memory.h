#ifndef __MEMORY__H_
#define __MEMORY__H_

typedef struct element element;

struct element {
	int valeur[8];/* valeur de l’élément */
	int adress;
	element *suivant;/* adresse du successeur */
};
typedef element* memory;


void readMemory(memory *memory);

void insertInMemory(int *value8bits, int adresse, memory *memory);

void getValueFromMemory(int *value8bits, int adresse, memory *memory);

void writeFourOctetsInMemory(int *value32bits, int startAddress, memory *memory);

void readFourOctetsInMemory(int *value32bits, int startAddress, memory *memory);

int addTwoBinaryRegister(int *register1, int *register2, int *destinationRegister);

int subTwoBinaryRegister(int *register1, int *register2, int *destinationRegister);

#endif