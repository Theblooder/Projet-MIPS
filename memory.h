#ifndef __MEMORY__H_
#define __MEMORY__H_

typedef struct element element;

struct element {
	int valeur[8];/* valeur de l’élément */
	int adress;
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

void insertInMemory(int *value8bits, int adresse, memory *memory);

void getValueFromMemory(int *value8bits, int adresse, memory *memory);

void writeFourOctetsInMemory(int *value32bits, int startAddress, memory *memory);

void readFourOctetsInMemory(int *value32bits, int startAddress, memory *memory);

int addTwoBinaryRegister(int *register1, int *register2, int *destinationRegister);

int subTwoBinaryRegister(int *register1, int *register2, int *destinationRegister);

void readAndDecodeInstruction(int Sp,int *binaireInstruction, Register *tableRegister, memory *m);

void readInstructionInMemory(int Sp,int *binaireInstruction,memory *memory);

int decodeInstruction(int *binaireInstruction);

int executeTheGoodOperation(int Operation, int *binaireInstruction, Register *tableRegister);

int returnArgument(int *binaireInstruction, int start, int end);

void ADD_Operation(int *binaireInstruction, Register *tableRegister);

void ADDI_Operation(int *binaireInstruction,Register *tableRegistesr);

void SUB_Operation(int *binaireInstruction,Register *tableRegister);

void AND_Operation(int *binaireInstruction,Register *tableRegister);

void OR_Operation(int *binaireInstruction,Register *tableRegister);

void SLL_Operation(int *binaireInstruction,Register *tableRegister);

void SLT_Operation(int *binaireInstruction,Register *tableRegister);

void XOR_Operation(int *binaireInstruction,Register *tableRegister); 

void SRL_Operation(int *binaireInstruction,Register *tableRegister);

void ROTR_Operation(int *binaireInstruction,Register *tableRegister);

void NOP_Operation(int *binaireInstruction,Register *tableRegister);

void MULT_Operation(int *binaireInstruction,Register *tableRegister);

void andTwoBinaryRegister(int *register1, int *register2, int *destinationRegister);

void orTwoBinaryRegister(int *register1, int *register2, int *destinationRegister);

void sllTwoBinaryRegister(int *register1, int deplacement, int *destinationRegister);

void sltTwoBinaryRegister(int *register1, int *register2, int *destinationRegister);

void xorTwoBinaryRegister(int *register1, int *register2, int *destinationRegister);

void srlTwoBinaryRegister(int *register1, int deplacement, int *destinationRegister);

void rotrTwoBinaryRegister(int *register1, int deplacement, int *destinationRegister);

void multTwoBinaryRegister(int *register1, int multiplication,Register *tableRegister);

#endif