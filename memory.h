#ifndef __MEMORY__H_
#define __MEMORY__H_

typedef struct element element;

struct element {
	int valeur[8];/* valeur de l’élément */
	int adress;
	int type; //Text or data (instruction or data)
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

void convertInToBinnary(int value, int *destinationRegister);

void readAndDecodeInstruction(int Sp,int *binaireInstruction, Register *tableRegister, memory *m);

void readInstructionInMemory(int Sp,int *binaireInstruction,memory *memory);

int decodeInstruction(int *binaireInstruction);

int executeTheGoodOperation(int Operation, int *binaireInstruction, Register *tableRegister,  memory *m);

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

void MFHI_Operation(int *binaireInstruction,Register *tableRegister);

void MFLO_Operation(int *binaireInstruction,Register *tableRegister);

void SW_Operation(int *binaireInstruction,Register *tableRegister, memory *m);

void LW_Operation(int *binaireInstruction,Register *tableRegister, memory *m);

void LUI_Operation(int *binaireInstruction,Register *tableRegister);

void JAL_Operation(int *binaireInstruction,Register *tableRegister);

void JR_Operation(int *binaireInstruction,Register *tableRegister);

void J_Operation(int *binaireInstruction,Register *tableRegister);

void BNE_Operation(int *binaireInstruction,Register *tableRegister);

void BGTZ_Operation(int *binaireInstruction,Register *tableRegister);

void BLEZ_Operation(int *binaireInstruction,Register *tableRegister);

void BEQ_Operation(int *binaireInstruction,Register *tableRegister);

void DIV_Operation(int *binaireInstruction,Register *tableRegister);

int addTwoBinaryRegister(int *register1, int *register2, int *destinationRegister);

int subTwoBinaryRegister(int *register1, int *register2, int *destinationRegister);

void andTwoBinaryRegister(int *register1, int *register2, int *destinationRegister);

void orTwoBinaryRegister(int *register1, int *register2, int *destinationRegister);

void sllTwoBinaryRegister(int *register1, int deplacement, int *destinationRegister);

void sltTwoBinaryRegister(int *register1, int *register2, int *destinationRegister);

void xorTwoBinaryRegister(int *register1, int *register2, int *destinationRegister);

void srlTwoBinaryRegister(int *register1, int deplacement, int *destinationRegister);

void rotrTwoBinaryRegister(int *register1, int deplacement, int *destinationRegister);

void multTwoBinaryRegister(int *register1, int multiplication,Register *tableRegister);

void mfhiTwoBinaryRegister(int *destinationRegister, Register *tableRegister);

void mfloTwoBinaryRegister(int *destinationRegister, Register *tableRegister);

void swTwoBinaryRegister(int *register1, int register2, int *destinationRegister,  memory *m);

void ldTwoBinaryRegister(int *register1, int register2, int *destinationRegister,  memory *m);

void luiTwoBinaryRegister(int register1, int *destinationRegister);

void jalTwoBinaryRegister(int register1,Register *tableRegister);

void jrTwoBinaryRegister(int *register1,Register *tableRegister);

void jTwoBinaryRegister(int register1,Register *tableRegister);

void bneTwoBinaryRegister(int *register1, int *register2, int offset,  Register *tableRegister);

void blezTwoBinaryRegister(int *register1, int offset,  Register *tableRegister);

void bgtzTwoBinaryRegister(int *register1, int offset,  Register *tableRegister);

void beqTwoBinaryRegister(int *register1, int *register2, int offset,  Register *tableRegister);

void divTwoBinaryRegister(int *register1, int *register2,Register *tableRegister);

#endif