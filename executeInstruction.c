#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "memory.h"
#include "executeInstruction.h"
#include "instructionsConvertBinHexa.h"



void convertInToBinnary(int value, int *destinationRegister)
{
	int isSigned = 0;

    if(value < 0) {
        isSigned = 1;
        value *= -1;
    }

	int i;
	for(i=0; value>0; i++) {
        destinationRegister[i] = value % 2;  
        value = value / 2;  
    }

	if(isSigned) {
        for(i=0; i<32; i++) {
            destinationRegister[i] ^= 1;
        }
        /* complement to 2 */
        i = 0;
        while(destinationRegister[i] != 0) {
            destinationRegister[i] = 0;
            i++;
        }
        destinationRegister[i] = 1;
    }
}

void readAndDecodeInstruction(int address, Register *tableRegister, memory *m)
{
	int binaireInstruction[32] = {0};
	readInstructionInMemory(address, binaireInstruction, m);

	/* PC += 4 */
	// printf("\n");
	int nextPcAdress[32] = {0};
	// printf("PC + 4\n");
	convertInToBinnary(4, nextPcAdress);
	addTwoBinaryRegister(tableRegister[32].registre, nextPcAdress, tableRegister[32].registre);
	

	executeTheGoodOperation(decodeInstruction(binaireInstruction), binaireInstruction, tableRegister, m);


}

void readInstructionInMemory(int address, int *binaireInstruction, memory *m)
{
	readFourOctetsInMemory(binaireInstruction, address, m);
}

int decodeInstruction(int *binaireInstruction)
{
	int Operation = 0;
	int i;
	int null = 1;

	for(i=5; i>=0; i--)
	{
		Operation = Operation + ((int) pow(2, 5-i) * binaireInstruction[31-i]);
	}

	if (Operation != 0) null = 0;

	if(null == 1)
	{
		Operation = 0;
		for(i=5;i>=0;i--)
		{
			Operation = Operation + ((int) pow(2, i) * binaireInstruction[i]);
		}
		Operation *= -1;
	}

	if(Operation == -2)
	{
		if(binaireInstruction[21] == 1) Operation = 1000;
	}

	else if(Operation == 0)
	{
		for(i=31; i>=0 && null == 1; i--)
		{
			if(binaireInstruction[i]!=0)
			{
				null = 0;
				Operation = 2000;
			}
		}
	}
	// printf("opération = %d\n",Operation);
	return Operation;
}

int executeTheGoodOperation(int Operation, int *binaireInstruction, Register *tableRegister, memory *m)
{
	if(Operation == -32)          	ADD_Operation(binaireInstruction, tableRegister); 		//ADD
    else if(Operation == 8)     	ADDI_Operation(binaireInstruction, tableRegister); 		//ADDI
    else if(Operation == -36)		AND_Operation(binaireInstruction, tableRegister);	 	//AND
    else if(Operation == 4)			BEQ_Operation(binaireInstruction, tableRegister); 		//BEQ
    else if(Operation == 7)			BGTZ_Operation(binaireInstruction, tableRegister);	 	//BGTZ
	else if(Operation == 6)			BLEZ_Operation(binaireInstruction, tableRegister);	 	//BLEZ
	else if(Operation == 5)			BNE_Operation(binaireInstruction, tableRegister);	 	//BNE
	else if(Operation == -26)		DIV_Operation(binaireInstruction, tableRegister); 		//DIV
	else if(Operation == 2)			J_Operation(binaireInstruction, tableRegister); 		//J
	else if(Operation == 3)			JAL_Operation(binaireInstruction, tableRegister); 		//JAL
	else if(Operation == -8)		JR_Operation(binaireInstruction, tableRegister);	 	//JR
	else if(Operation == 15)		LUI_Operation(binaireInstruction, tableRegister); 		//LUI
	else if(Operation == 35)		LW_Operation(binaireInstruction, tableRegister, m); 	//LW
	else if(Operation == -16)		MFHI_Operation(binaireInstruction, tableRegister);		//MFHI
	else if(Operation == -18)		MFLO_Operation(binaireInstruction, tableRegister);	 	//MFLO
	else if(Operation == -24)		MULT_Operation(binaireInstruction, tableRegister); 		//MULT
	else if(Operation == 0)			NOP_Operation(binaireInstruction, tableRegister);		//NOP	
	else if(Operation == -37)		OR_Operation(binaireInstruction, tableRegister); 		//OR
	else if(Operation == 1000)		ROTR_Operation(binaireInstruction, tableRegister); 		//ROTR 	
	else if(Operation == 2000)		SLL_Operation(binaireInstruction, tableRegister);	 	//SLL	
	else if(Operation == -42)		SLT_Operation(binaireInstruction, tableRegister);	 	//SLT
	else if(Operation == -2)		SRL_Operation(binaireInstruction, tableRegister);	 	//SRL	
	else if(Operation == -34)		SUB_Operation(binaireInstruction, tableRegister);	 	//SUB
	else if(Operation == 43)		SW_Operation(binaireInstruction, tableRegister, m);		//SW
	// else if(Operation == -12)	SYSCALL_Operation(binaireInstruction, tableRegister); 	//SYSCALL
	else if(Operation == -38)		XOR_Operation(binaireInstruction, tableRegister); 		//XOR
    else {	
        printf("Opération non reconnu dans le décodage pas la lecture fichier\n");
        return 1;
    }
}

int returnArgument(int *binaireInstruction, int start, int end)
{
	int i;
	int j = 0;
	int argument = 0;
	for(i=start; i<end; i++)
	{
		argument += (int) (pow(2, j) * binaireInstruction[i]); 
		j++;
	}
	return argument;
}

void printRegister(int *registre)
{
	// int i;
	// for(i=31; i>=0; i--) {
	// 	printf("%d", registre[i]);
	// }
	// printf("\n");
}

void ADD_Operation(int *binaireInstruction, Register *tableRegister)
{
	int rd = returnArgument(binaireInstruction, 11, 16);
	int rt = returnArgument(binaireInstruction, 16, 21);
	int rs = returnArgument(binaireInstruction, 21, 26);
	
	printf("Processing instruction: ");
	printf("ADD $%d, $%d, $%d\n\n",rd,rs,rt);

	addTwoBinaryRegister(tableRegister[rs].registre, tableRegister[rt].registre, tableRegister[rd].registre);
		
	// printf("R%d + R%d --> R%d\n", rs, rt, rd);

	printRegister(tableRegister[rd].registre);

}

void ADDI_Operation(int *binaireInstruction, Register *tableRegister)
{
	int rt = returnArgument(binaireInstruction, 16, 21);
	int rs = returnArgument(binaireInstruction, 21, 26);

	int i;
	int immediateValue[32] = {0};

	for(i=0; i<16; i++) {
		immediateValue[i] = binaireInstruction[i];
	}
	if(binaireInstruction[15] == 1) {
		for(i=16; i<32; i++) {
			immediateValue[i] = 1;
		}
	}

	printf("Processing instruction: ");
	printf("ADDI $%d, $%d, %d\n\n",rt,rs,returnArgument(immediateValue, 0, 32));

	addTwoBinaryRegister(tableRegister[rs].registre, immediateValue, tableRegister[rt].registre);

	// printf(" %d + R%d --> R%d\n", returnArgument(immediateValue, 0, 32), rs, rt);
	
	printRegister(tableRegister[rt].registre);
}

void AND_Operation(int *binaireInstruction, Register *tableRegister)
{
	int rd = returnArgument(binaireInstruction, 11, 16);
	int rt = returnArgument(binaireInstruction, 16, 21);
	int rs = returnArgument(binaireInstruction, 21, 26);

	printf("Processing instruction: ");
	printf("AND $%d, $%d, $%d\n\n",rd,rs,rt);

	andTwoBinaryRegister(tableRegister[rs].registre, tableRegister[rt].registre, tableRegister[rd].registre);

	// printf("R%d AND R%d --> R%d\n", rd, rs, rt);
	
	printRegister(tableRegister[rd].registre);
}

void BEQ_Operation(int *binaireInstruction, Register *tableRegister)
{
	int rt = returnArgument(binaireInstruction, 16, 21);
	int rs = returnArgument(binaireInstruction, 21, 26);

	int i;
	int sl_offset = 2;
	int offset[32] = {0};

	for(i=0; i<16; i++) {
		offset[sl_offset++] = binaireInstruction[i];
	}
	if(binaireInstruction[15] == 1) {
		for(i=18; i<32; i++) {
			offset[i] = 1;
		}
	}

	printf("Processing instruction: ");
	printf("BEQ $%d, $%d, %d\n\n",rs,rt,returnArgument(offset, 0, 32));

	beqTwoBinaryRegister(tableRegister[rt].registre, tableRegister[rs].registre, offset, tableRegister);

	// printf("BEQ R%d = R%d ? --> PC  + %d\n", rt, rs, returnArgument(offset, 0, 32));
	
	printRegister(tableRegister[32].registre);
}

void BGTZ_Operation(int *binaireInstruction, Register *tableRegister)
{
	int rs = returnArgument(binaireInstruction, 21, 26);

	int i;
	int sl_offset = 2;
	int offset[32] = {0};

	for(i=0; i<16; i++) {
		offset[sl_offset++] = binaireInstruction[i];
	}
	if(binaireInstruction[15] == 1) {
		for(i=18; i<32; i++) {
			offset[i] = 1;
		}
	}

	printf("Processing instruction: ");
	printf("BGTZ $%d, %d\n\n",rs,returnArgument(offset, 0, 32));

	bgtzOneBinaryRegister(tableRegister[rs].registre, offset, tableRegister);

	// printf("BGTZ R%d > 0 ? --> PC + %d\n", rs, returnArgument(offset, 0, 32));
	
	printRegister(tableRegister[32].registre);
}

void BLEZ_Operation(int *binaireInstruction, Register *tableRegister)
{
	int rs = returnArgument(binaireInstruction, 21, 26);

	int i;
	int sl_offset = 2;
	int offset[32] = {0};

	for(i=0; i<16; i++) {
		offset[sl_offset++] = binaireInstruction[i];
	}
	if(binaireInstruction[15] == 1) {
		for(i=18; i<32; i++) {
			offset[i] = 1;
		}
	}

	printf("Processing instruction: ");
	printf("BLEZ $%d, %d\n\n",rs,returnArgument(offset, 0, 32));

	blezOneBinaryRegister(tableRegister[rs].registre, offset, tableRegister);

	// printf("BLEZ R%d <= 0 ? --> PC  + %d\n", rs, returnArgument(offset, 0, 32));
	
	printRegister(tableRegister[32].registre);
}

void BNE_Operation(int *binaireInstruction, Register *tableRegister)
{
	int rt = returnArgument(binaireInstruction,16,21);
	int rs = returnArgument(binaireInstruction,21,26);

	int i;
	int sl_offset = 2;
	int offset[32] = {0};

	for(i=0; i<16; i++) {
		offset[sl_offset++] = binaireInstruction[i];
	}
	if(binaireInstruction[15] == 1) {
		for(i=18; i<32; i++) {
			offset[i] = 1;
		}
	}

	printf("Processing instruction: ");
	printf("BNE $%d, $%d, %d\n\n",rs,rt,returnArgument(offset, 0, 32));

	bneTwoBinaryRegister(tableRegister[rt].registre, tableRegister[rs].registre, offset, tableRegister);

	// printf("BNE R%d != R%d ? --> PC  + %d\n", rt, rs, returnArgument(offset, 0, 32));
	
	printRegister(tableRegister[32].registre);
}

void DIV_Operation(int *binaireInstruction, Register *tableRegister)
{
	int rt = returnArgument(binaireInstruction, 16, 21);
	int rs = returnArgument(binaireInstruction, 21, 26);

	printf("Processing instruction: ");
	printf("DIV $%d, %d\n\n",rs,rt);

	divTwoBinaryRegister(tableRegister[rs].registre, tableRegister[rt].registre, tableRegister);

	printRegister(tableRegister[33].registre);
	printRegister(tableRegister[34].registre);
}

void J_Operation(int *binaireInstruction, Register *tableRegister)
{
	int i;
	int sl_offset = 2;
	int offset[32] = {0};

	for(i=0; i<26; i++) {
		offset[sl_offset++] = binaireInstruction[i];
	}

	printf("Processing instruction: ");
	printf("J %d\n\n",returnArgument(offset, 0, 32));

	jTwoBinaryRegister(offset, tableRegister);

	// printf("J %d\n", returnArgument(offset, 0, 32));
	
	printRegister(tableRegister[32].registre);
}

void JAL_Operation(int *binaireInstruction, Register *tableRegister)
{
	int i;
	int sl_offset = 2;
	int offset[32] = {0};

	for(i=0; i<26; i++) {
		offset[sl_offset++] = binaireInstruction[i];
	}

	printf("Processing instruction: ");
	printf("JAL %d\n\n",returnArgument(offset, 0, 32));

	jalTwoBinaryRegister(offset, tableRegister);
	
	// printf("JAL %d\n", returnArgument(offset, 0, 32));

	// printf("ra : ");
	printRegister(tableRegister[31].registre);
	// printf("PC : ");
	printRegister(tableRegister[32].registre);
}	

void JR_Operation(int *binaireInstruction, Register *tableRegister)
{
	int rs = returnArgument(binaireInstruction, 21, 26);

	printf("Processing instruction: ");
	printf("JR $%d\n\n",rs);

	jrTwoBinaryRegister(tableRegister[rs].registre, tableRegister);

	// printf("Jr R%d\n", rs);
	
	printRegister(tableRegister[32].registre);
}

void LUI_Operation(int *binaireInstruction, Register *tableRegister)
{
	int rt = returnArgument(binaireInstruction, 16, 21);

	int i;
	int immediateValue[32] = {0};

	for(i=0; i<16; i++) {
		immediateValue[i] = binaireInstruction[i];
	}
	if(binaireInstruction[15] == 1) {
		for(i=16; i<32; i++) {
			immediateValue[i] = 1;
		}
	}

	printf("Processing instruction: ");
	printf("LUI $%d, %d\n\n",rt,returnArgument(immediateValue, 0, 32));

	luiTwoBinaryRegister(immediateValue, tableRegister[rt].registre);

	// printf("LUI R%d = %d || 0^16\n", rt, returnArgument(immediateValue, 0, 32));
	
	printRegister(tableRegister[rt].registre);
}

void LW_Operation(int *binaireInstruction, Register *tableRegister, memory *m)
{	
	int rt = returnArgument(binaireInstruction, 16, 21);
	int base = returnArgument(binaireInstruction, 21, 26);

	int i;
	int immediateValue[32] = {0};

	for(i=0; i<16; i++) {
		immediateValue[i] = binaireInstruction[i];
	}
	if(binaireInstruction[15] == 1) {
		for(i=16; i<32; i++) {
			immediateValue[i] = 1;
		}
	}

	printf("Processing instruction: ");
	printf("LW $%d, %d(%d)\n\n",rt,returnArgument(immediateValue, 0, 32),base);

	ldTwoBinaryRegister(tableRegister[base].registre, immediateValue, tableRegister[rt].registre, m);

	// printf("LW R%d <-- %d(R%d)\n", rt, returnArgument(immediateValue, 0, 32), base);

	printRegister(tableRegister[rt].registre);
}

void MFHI_Operation(int *binaireInstruction, Register *tableRegister)
{
	int rd = returnArgument(binaireInstruction, 11, 16);

	printf("Processing instruction: ");
	printf("MFHI $%d\n\n",rd);

	mfhiTwoBinaryRegister(tableRegister[rd].registre, tableRegister);

	// printf("R%d <-- R34\n", rd);

	printRegister(tableRegister[rd].registre);
}

void MFLO_Operation(int *binaireInstruction, Register *tableRegister)
{
	int rd = returnArgument(binaireInstruction, 11, 16);

	printf("Processing instruction: ");
	printf("MFLO $%d\n\n",rd);

	mfloTwoBinaryRegister(tableRegister[rd].registre, tableRegister);

	// printf("R%d <-- R33\n", rd);

	printRegister(tableRegister[rd].registre);
}

void MULT_Operation(int *binaireInstruction, Register *tableRegister)
{
	int rt = returnArgument(binaireInstruction, 16, 21);
	int rs = returnArgument(binaireInstruction, 21, 26);

	printf("Processing instruction: ");
	printf("MULT $%d, $%d\n\n",rs,rt);

	multTwoBinaryRegister(tableRegister[rs].registre, tableRegister[rt].registre, tableRegister);

 	// printf("R%d * %d --> R33/34\n", registre2, registre1);
	
	printRegister(tableRegister[33].registre);
	printRegister(tableRegister[34].registre);
}

void NOP_Operation(int *binaireInstruction, Register *tableRegister)
{
	printf("Processing instruction: ");
	printf("NOP\n\n");

	sllTwoBinaryRegister(tableRegister[0].registre, 0, tableRegister[0].registre);
	// printf("NOP\n");
}

void OR_Operation(int *binaireInstruction, Register *tableRegister)
{
	int rd = returnArgument(binaireInstruction, 11, 16);
	int rt = returnArgument(binaireInstruction, 16, 21);
	int rs = returnArgument(binaireInstruction, 21, 26);

	printf("Processing instruction: ");
	printf("OR $%d, $%d, $%d\n\n",rd,rs,rt);

	orTwoBinaryRegister(tableRegister[rs].registre, tableRegister[rt].registre, tableRegister[rd].registre);

	// printf("R%d OR R%d --> R%d\n", rd, rs, rt);

	printRegister(tableRegister[rd].registre);
}

void ROTR_Operation(int *binaireInstruction, Register *tableRegister)
{
	int sa = returnArgument(binaireInstruction, 6, 11);
	int rd = returnArgument(binaireInstruction, 11, 16);
	int rt = returnArgument(binaireInstruction, 16, 21);

	printf("Processing instruction: ");
	printf("ROTR $%d, $%d, $%d\n\n",rd,rt,sa);

	rotrTwoBinaryRegister(tableRegister[rt].registre, sa, tableRegister[rd].registre);

	// printf("R%d ROTR %d --> R%d\n", rd, sa, rd);
	
	printRegister(tableRegister[rd].registre);
}

void SLL_Operation(int *binaireInstruction, Register *tableRegister)
{
	int sa = returnArgument(binaireInstruction, 6, 11);
	int rd = returnArgument(binaireInstruction, 11, 16);
	int rt = returnArgument(binaireInstruction, 16, 21);

	printf("Processing instruction: ");
	printf("SLL $%d, $%d, $%d\n\n",rd,rt,sa);

	sllTwoBinaryRegister(tableRegister[rt].registre, sa, tableRegister[rd].registre);

	// printf("R%d << %d --> R%d\n", rt, sa, rd);
	
	printRegister(tableRegister[rd].registre);
}

void SLT_Operation(int *binaireInstruction, Register *tableRegister)
{
	int rd = returnArgument(binaireInstruction, 11, 16);
	int rt = returnArgument(binaireInstruction, 16, 21);
	int rs = returnArgument(binaireInstruction, 21, 26);

	printf("Processing instruction: ");
	printf("SLT $%d, $%d, $%d\n\n",rd,rs,rt);

	sltTwoBinaryRegister(tableRegister[rt].registre, tableRegister[rs].registre, tableRegister[rd].registre);

	// printf("R%d < R%d ? --> R%d\n", rs, rt, rd);

	printRegister(tableRegister[rd].registre);
}

void SRL_Operation(int *binaireInstruction, Register *tableRegister)
{
	int sa = returnArgument(binaireInstruction, 6, 11);
	int rd = returnArgument(binaireInstruction, 11, 16);
	int rt = returnArgument(binaireInstruction, 16, 21);

	printf("Processing instruction: ");
	printf("SRL $%d, $%d, $%d\n\n",rd,rt,sa);

	srlTwoBinaryRegister(tableRegister[rt].registre, sa, tableRegister[rd].registre);

	// printf("R%d >> %d --> R%d\n", rt, sa, rd);
	
	printRegister(tableRegister[rd].registre);
}

void SUB_Operation(int *binaireInstruction, Register *tableRegister)
{
	int rd = returnArgument(binaireInstruction, 11, 16);
	int rt = returnArgument(binaireInstruction, 16, 21);
	int rs = returnArgument(binaireInstruction, 21, 26);

	printf("Processing instruction: ");
	printf("SUB $%d, $%d, $%d\n\n",rd,rs,rt);

	subTwoBinaryRegister(tableRegister[rs].registre, tableRegister[rt].registre, tableRegister[rd].registre);

	// printf("R%d - R%d --> R%d\n", rs, rt, rd);

	printRegister(tableRegister[rd].registre);
}

void SW_Operation(int *binaireInstruction,Register *tableRegister,  memory *m)
{
	int rt = returnArgument(binaireInstruction, 16, 21);
	int base = returnArgument(binaireInstruction, 21, 26);

	int i;
	int immediateValue[32] = {0};

	for(i=0; i<16; i++) {
		immediateValue[i] = binaireInstruction[i];
	}
	if(binaireInstruction[15] == 1) {
		for(i=16; i<32; i++) {
			immediateValue[i] = 1;
		}
	}

	printf("Processing instruction: ");
	printf("SW $%d, %d($%d)\n\n",rt,returnArgument(immediateValue, 0, 32),base);

	swTwoBinaryRegister(tableRegister[base].registre, immediateValue, tableRegister[rt].registre, m);

	// printf("SW R%d --> %d(R%d)\n", rt, returnArgument(immediateValue, 0, 32), base);

	printRegister(tableRegister[rt].registre);
}

// void SYSCALL_Operation(int *binaireInstruction,Register *tableRegister)
// {

// }

void XOR_Operation(int *binaireInstruction, Register *tableRegister)
{
	int rd = returnArgument(binaireInstruction, 11, 16);
	int rt = returnArgument(binaireInstruction, 16, 21);
	int rs = returnArgument(binaireInstruction, 21, 26);

	printf("Processing instruction: ");
	printf("XOR $%d, $%d, $%d\n\n",rd,rs,rt);

	xorTwoBinaryRegister(tableRegister[rs].registre, tableRegister[rt].registre, tableRegister[rd].registre);

	// printf("R%d XOR R%d --> R%d\n", rs, rt, rd);

	printRegister(tableRegister[rd].registre);
}



//Ne fonctionne pas avec des chiffres négatifs, je me pose la question si ADD à le droit d'avoir des chiffres négatif, ADDI oui mais juste pour le immediate j'ai l'impression
//alors que je crois me rappeler qu'on a toujours eu le droit d'avoir des registres avec des chiffres négatifs...
//Faut qu'on regarde, puis je ferais les modifs en conséquence

int addTwoBinaryRegister(int *register1, int *register2, int *destinationRegister)
{

	printRegister(register1);
	printRegister(register2);

	int i;
	int carry = 0;
	int overflowed = 0;
	int tempRegister[32] = {0};

	for(i=0;i<32;i++)
	{
		tempRegister[i] = register1[i] + register2[i] + carry;
		carry = 0;
		if(tempRegister[i] == 2)
		{
			tempRegister[i] = 0;
			carry = 1;
		}
		else if(tempRegister[i] == 3)
		{
			tempRegister[i] = 1;
			carry = 1;
		}
	}
	/* To check if overflow */
	if(register1[31] != register2[31]) {
		overflowed = 0;
	}
	else if(register1[31] != tempRegister[31]) {
		overflowed = 1;
	}
	else {overflowed = 0;}
	
	if(overflowed == 0)
	{
		for(i=0;i<32;i++)
		{
			destinationRegister[i] = tempRegister[i];
		}
	
	}
	else {
		printf("overflowed\n");
	}
	return overflowed;
}

int subTwoBinaryRegister(int *register1, int *register2, int *destinationRegister)
{
	int i;
	int carry = 0;
	int overflowed = 0;
	int tempRegister[32];

	printRegister(register1);
	printRegister(register2);

	for(i=0; i<32; i++) {
		tempRegister[i] = register2[i];
	}

	i = 0;
	while (tempRegister[i] != 1) {
		i++;
	}
	
	for(i=i+1; i<32; i++) {	
        if (tempRegister[i] == 0)
            tempRegister[i] = 1;
        else tempRegister[i] = 0;
    }

	addTwoBinaryRegister(register1, tempRegister, destinationRegister);

}

void andTwoBinaryRegister(int *register1, int *register2, int *destinationRegister)
{
	int i;

	printRegister(register1);
	printRegister(register2);

	for(i=31; i>=0; i--)
	{
		destinationRegister[i] = register1[i] & register2[i];
	}
}

void orTwoBinaryRegister(int *register1, int *register2, int *destinationRegister)
{
	int i;

	printRegister(register1);
	printRegister(register2);

	for(i=31; i>=0; i--)
	{
		destinationRegister[i] = register1[i] | register2[i];
	}
}

void sllTwoBinaryRegister(int *register1, int deplacement, int *destinationRegister)
{
	int i;
	int j = 31;

	printRegister(register1);

	for(i=31-deplacement; i>=0; i--) {
		destinationRegister[j] = register1[i];
		j--;
	}
	for(i=j; i>=0; i--) {
		destinationRegister[i] = 0;
	}
}

void sltTwoBinaryRegister(int *register1, int *register2, int *destinationRegister)
{
	int i;
	int isEqual0 = 1;
	
	printRegister(register1);
	printRegister(register2);

	subTwoBinaryRegister(register1, register2, destinationRegister);

	for(i=0; i<32; i++) {
		if(destinationRegister[i] == 1) {
			isEqual0 = 0;
		}
	}

	if(destinationRegister[31] == 1 || isEqual0) {
		for(i=0; i<32; i++) {
			destinationRegister[i] = 0;
		}
	}
	else {
		for(i=1; i<32; i++) {
			destinationRegister[i] = 0;
		}
		destinationRegister[0] = 1;
	}
}

void xorTwoBinaryRegister(int *register1, int *register2, int *destinationRegister)
{
	int i = 0;

	printRegister(register1);
	printRegister(register2);

	for(i=31; i>=0; i--) {
		destinationRegister[i] = register1[i] ^ register2[i];
	}
}

void srlTwoBinaryRegister(int *register1, int deplacement, int *destinationRegister)
{
	int i;
	int j = 0;
	
	printRegister(register1);

	for(i=deplacement; i<32; i++) {
		destinationRegister[j] = register1[i];
		j++;
	}
	for(i=j; i<32; i++) {
		destinationRegister[i] = 0;
	}
}

void rotrTwoBinaryRegister(int *register1, int deplacement, int *destinationRegister)
{
	printRegister(register1);

	int i;

	for(i=0; i<deplacement; i++)
	{
		destinationRegister[32-deplacement+i] = register1[i];
	}
	for(i=0; i<32-deplacement; i++)
	{
		destinationRegister[i] = register1[i+deplacement];
	}
}

void multTwoBinaryRegister(int *register1, int *multiplication, Register *tableRegister)
{
	int i;
	int k;
	unsigned long long int tempValueRegistre1 = 0;
	unsigned long long int tempValueRegistre2 = 0;

	printRegister(register1);
	printRegister(multiplication);
	
	if(register1[31] == 1)
	{
		i = 0;
		while (register1[i] != 1) {
			i++;
		}
	
		for(i=i+1; i<32; i++) {	
        	if (register1[i] == 0)
            	register1[i] = 1;
       		else register1[i] = 0;
    	}

		for(i=30;i>=0;i--)
		{
			tempValueRegistre1 += (unsigned long long int) (pow(2, i) * register1[i]);
		}

		tempValueRegistre1*= -1;
	}
	else
	{
		for(i=30;i>=0;i--)
		{
			tempValueRegistre1 += (unsigned long long int) (pow(2, i) * register1[i]);
		}
	}

	if(multiplication[31] == 1)
	{
		i = 0;
		while (multiplication[i] != 1) {
			i++;
		}
	
		for(i=i+1; i<32; i++) {	
        	if (multiplication[i] == 0)
            	multiplication[i] = 1;
       		else multiplication[i] = 0;
    	}

		for(i=30;i>=0;i--)
		{
			tempValueRegistre2 += (unsigned long long int) (pow(2, i) * multiplication[i]);
		}

		tempValueRegistre2*= -1;
	}
	else
	{
		for(i=30;i>=0;i--)
		{
			tempValueRegistre2 += (unsigned long long int) (pow(2, i) * multiplication[i]);
		}
	}
	
	

	// printf("%lld\n",tempValueRegistre1);
	// printf("%lld\n",tempValueRegistre2);

	tempValueRegistre1 *= tempValueRegistre2;

	// printf("%lld\n",tempValueRegistre1);
	
	for(i=0; tempValueRegistre1>0 && i<32; i++) {
        tableRegister[33].registre[i] = tempValueRegistre1 % 2;  
        tempValueRegistre1 = tempValueRegistre1 / 2;  
    }

	convertInToBinnary(tempValueRegistre1,tableRegister[34].registre);
}

void mfloTwoBinaryRegister(int *destinationRegister, Register *tableRegister)
{
	int i;

	for(i=0; i<32; i++) {
		destinationRegister[i] = tableRegister[33].registre[i];
	}
}

void mfhiTwoBinaryRegister(int *destinationRegister, Register *tableRegister)
{
	int i;

	for(i=0; i<32; i++) {
		destinationRegister[i] = tableRegister[34].registre[i];
	}
}

void swTwoBinaryRegister(int *register1, int *register2, int *destinationRegister, memory *m)
{
	int offset[32] = {0};

	addTwoBinaryRegister(register1, register2, offset);

	int i;
	unsigned int jump = 0;

	if(offset[31] == 1 || (offset[0] != 0 || offset[1] != 0)) {
		printf("ERROR : Address pointé invalide\n");
		return;
	}
	else {
		for(i=31; i>=0; i--) {
			jump += (pow(2, i) * offset[i]);
		}

		// printf("address :%d\n", jump);

		writeFourOctetsInMemory(destinationRegister, jump, 0, m);
	}
}	

void ldTwoBinaryRegister(int *register1, int *register2, int *destinationRegister, memory *m)
{
	int offset[32] = {0};

	addTwoBinaryRegister(register1, register2, offset);

	int i;
	unsigned int jump = 0;

	if(offset[31] == 1 || (offset[0] != 0 && offset[1] != 0)) {
		printf("ERROR : Address pointé invalide\n");
		return;
	}
	else {
		for(i=31; i>=0; i--) {
			jump += (pow(2, i) * offset[i]);
		}

		// printf("address :%d\n", jump);

		readInstructionInMemory(jump, destinationRegister, m);
	}	
}	

void luiTwoBinaryRegister(int *register1, int *destinationRegister)
{
	int i;

	printRegister(register1);

	for(i=31; i>=16; i--)
	{
		destinationRegister[i] = register1[i-16];
	}

	for(i=15; i>=0; i--)
	{
		destinationRegister[i] = 0;
	}
	
}	

void jalTwoBinaryRegister(int *index_jump, Register *tableRegister)
{
	int i;

	for(i=0; i<32; i++) {
		tableRegister[31].registre[i] = tableRegister[32].registre[i];
	}

	for(i=0; i<28; i++) {
		tableRegister[32].registre[i] = index_jump[i];
	}
}

void jrTwoBinaryRegister(int *register1, Register *tableRegister)
{
	int i;

	for(i=31; i>=0; i--) {
		tableRegister[32].registre[i] = register1[i];	
	}
}

void jTwoBinaryRegister(int *index_jump, Register *tableRegister)
{
	int i;

	for(i=0; i<28; i++) {
		tableRegister[32].registre[i] = index_jump[i];
	}
}

void bneTwoBinaryRegister(int *register1, int *register2, int *offset,  Register *tableRegister)
{
	int i;
	int isEqual = 1;

	printRegister(register1);
	printRegister(register2);
	
	for(i=31; i>=0; i--) {
		if(register1[i] != register2[i]) {
			isEqual = 0;
		}
	}

	if(!isEqual)
	{
		addTwoBinaryRegister(tableRegister[32].registre, offset, tableRegister[32].registre);
	}
	
}	

void bgtzOneBinaryRegister(int *register1, int *offset, Register *tableRegister)
{
	int isGreaterThan0 = 1;

	printRegister(register1);
	
	if(register1[31] == 1 || returnArgument(register1, 0, 32) == 0) {
		isGreaterThan0 = 0;
	}

	if(isGreaterThan0) {
		addTwoBinaryRegister(tableRegister[32].registre, offset, tableRegister[32].registre);
	}
}	

void blezOneBinaryRegister(int *register1, int *offset, Register *tableRegister)
{
	int isLessOrEqualThan0 = 0;

	printRegister(register1);
	
	if(register1[31] == 1 || returnArgument(register1, 0, 32) == 0) {
		isLessOrEqualThan0 = 1;
	}

	if(isLessOrEqualThan0) {
		addTwoBinaryRegister(tableRegister[32].registre, offset, tableRegister[32].registre);
	}
}	

void beqTwoBinaryRegister(int *register1, int *register2, int *offset, Register *tableRegister)
{
	int i;
	int isEqual = 1;

	printRegister(register1);
	printRegister(register2);
	
	for(i=31; i>=0; i--) {
		if(register1[i] != register2[i]) {
			isEqual = 0;
		}
	}

	if(isEqual)
	{
		addTwoBinaryRegister(tableRegister[32].registre, offset, tableRegister[32].registre);
	}
}	

void divTwoBinaryRegister(int *register1, int *register2, Register *tableRegister)
{
	int i;
	int tempValueRegistre1 = 0;
	int tempValueRegistre2 = 0;
	unsigned int quotient;
	int remainder;
	unsigned int resultValue;

	printRegister(register1);
	printRegister(register2);
	

	if(register1[31] == 1)
	{
		i = 0;
		while (register1[i] != 1) {
			i++;
		}
	
		for(i=i+1; i<32; i++) {	
        	if (register1[i] == 0)
            	register1[i] = 1;
       		else register1[i] = 0;
    	}

		for(i=30;i>=0;i--)
		{
			tempValueRegistre1 += (unsigned long long int) (pow(2, i) * register1[i]);
		}

		tempValueRegistre1*= -1;
	}
	else
	{
		for(i=30;i>=0;i--)
		{
			tempValueRegistre1 += (unsigned long long int) (pow(2, i) * register1[i]);
		}
	}

	if(register2[31] == 1)
	{
		i = 0;
		while (register2[i] != 1) {
			i++;
		}
	
		for(i=i+1; i<32; i++) {	
        	if (register2[i] == 0)
            	register2[i] = 1;
       		else register2[i] = 0;
    	}

		for(i=30;i>=0;i--)
		{
			tempValueRegistre2 += (unsigned long long int) (pow(2, i) * register2[i]);
		}

		tempValueRegistre2*= -1;
	}
	else
	{
		for(i=30;i>=0;i--)
		{
			tempValueRegistre2 += (unsigned long long int) (pow(2, i) * register2[i]);
		}
	}
	// printf("%d\n",tempValueRegistre1);
	// printf("%d\n",tempValueRegistre2);

	resultValue = tempValueRegistre1 / tempValueRegistre2;
	quotient = (int) resultValue;
	remainder = tempValueRegistre1 % tempValueRegistre2;
	// printf("%d\n",quotient);
	// printf("%d\n",remainder);
	
	
	for(i=0; quotient>0 && i<32; i++) {
        tableRegister[33].registre[i] = quotient % 2;  
        quotient = quotient / 2;  
    }

	convertInToBinnary(remainder,tableRegister[34].registre);
}