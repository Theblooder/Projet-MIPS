#ifndef __MEMORY__H_
#define __MEMORY__H_

typedef struct element element;

struct element {
	int valeur[8];/* valeur de l’élément */
	int adress;
	int type; //Text or data (instruction or data) 0:data   1:instruction
	element *suivant;/* adresse du successeur */
};
typedef element* memory;

// typedef struct Register Register;

// struct Register {
// 	int registre[32];
// };
// typedef Register* tableRegister[32];
typedef struct Register Register;

struct Register {
	int registre[32];
};




void readMemory(memory *memory);

void insertInMemory(int *value8bits, int adresse, int type, memory *m);

void getValueFromMemory(int *value8bits, int adresse, memory *memory);

void writeFourOctetsInMemory(int *value32bits, int startAddress, int type, memory *memory);

void readFourOctetsInMemory(int *value32bits, int startAddress, memory *memory);

#endif