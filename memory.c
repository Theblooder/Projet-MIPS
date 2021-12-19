#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "memory.h"

void readMemory(memory *m)
{
	element *actuel = *m;

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
	printf("Cette adresse de la mémoire ne contient pas de valeur\n");
	for(i=0; i<8; i++) 
	{
		value8bits[i] = 0;
	}
}

void insertInMemory(int *value8bits, int adresse, memory *m)
{
	element *actuel = *m;
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
		*m = e;
		e->suivant = actuel;
	}
	else {
		e->suivant = actuel;

		precedent->suivant = e;
	}
}

void writeFourOctetsInMemory(int *value32bits, int startAddress, memory *m)
{
	int i; int j;
	int value8bits[8];

	for(i=0; i<4; i++) {
		for(j=0; j<8; j++) {
			value8bits[j] = value32bits[8*i + j];
		}
		insertInMemory(value8bits, startAddress+i, m);
	}
}

void readFourOctetsInMemory(int *value32bits, int startAddress, memory *m)
{
	int i; int j;

	int value8bits[8];

	for(i=0; i<4; i++) {
		getValueFromMemory(value8bits, startAddress+i, m);
		for(j=0; j<8; j++) {
			value32bits[8*i + j] = value8bits[j];
		}
	}
}

void readAndDecodeInstruction(int Sp,int *binaireInstruction, Register *tableRegister, memory *m)
{
	readInstructionInMemory(Sp, binaireInstruction, m);
	executeTheGoodOperation(decodeInstruction(binaireInstruction),binaireInstruction, tableRegister, m);

}
void readInstructionInMemory(int Sp,int *binaireInstruction, memory *m)
{
	readFourOctetsInMemory(binaireInstruction,Sp,m);
}

int decodeInstruction(int *binaireInstruction)
{
	int Operation = 0;
	int i;
	int null = 1;

	for(i=5;i>=0;i--)
	{
		Operation = Operation + ((int) pow(2, i) * binaireInstruction[31-i]);
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
		for(i=31;i>=0 && null == 1;i--)
		{
			if(binaireInstruction[i]!=0)
			{
				null = 0;
				Operation = 2000;
			}
		}
	}
	printf("%d\n",Operation);
	return Operation;
}

int executeTheGoodOperation(int Operation, int *binaireInstruction, Register *tableRegister, memory *m)
{
	if(Operation == -32)          	ADD_Operation(binaireInstruction, tableRegister); 		//ADD
    else if(Operation == 8)     	ADDI_Operation(binaireInstruction, tableRegister); 		//ADDI
    else if(Operation == -36)		AND_Operation(binaireInstruction, tableRegister);	 	//AND
    // else if(Operation == 4)			BEQ_Operation(Operation, binaireInstruction); 		//BEQ
    // else if(Operation == 7)			BGTZ_Operation(Operation, binaireInstruction);	 	//BGTZ
	// else if(Operation == 6)			BLEZ_Operation(Operation, binaireInstruction);	 	//BLEZ
	// else if(Operation == 5)			BNE_Operation(Operation, binaireInstruction);	 	//BNE
	// else if(Operation == -26)		DIV_Operation(Operation, binaireInstruction); 		//DIV
	else if(Operation == 2)			J_Operation(binaireInstruction, tableRegister); 			//J
	else if(Operation == 3)			JAL_Operation(binaireInstruction, tableRegister); 		//JAL
	else if(Operation == -8)		JR_Operation(binaireInstruction, tableRegister);	 	//JR
	else if(Operation == 15)		LUI_Operation(binaireInstruction, tableRegister); 		//LUI
	else if(Operation == 35)		LW_Operation(binaireInstruction, tableRegister, m); 	//LW
	else if(Operation == -16)		MFHI_Operation(binaireInstruction, tableRegister);		//MFHI
	else if(Operation == -18)		MFLO_Operation(binaireInstruction, tableRegister);	 	//MFLO
	else if(Operation == -24)		MULT_Operation(binaireInstruction, tableRegister); 		//MULT
	else if(Operation == 0)			NOP_Operation(binaireInstruction, tableRegister);		//NOP	//Pareil
	else if(Operation == -37)		OR_Operation(binaireInstruction, tableRegister); 		//OR
	else if(Operation == 1000)		ROTR_Operation(binaireInstruction, tableRegister); 		//ROTR 	
	else if(Operation == 2000)		SLL_Operation(binaireInstruction, tableRegister);	 	//SLL	//Pareil
	else if(Operation == -42)		SLT_Operation(binaireInstruction, tableRegister);	 	//SLT
	else if(Operation == -2)		SRL_Operation(binaireInstruction, tableRegister);	 	//SRL	
	else if(Operation == -34)		SUB_Operation(binaireInstruction, tableRegister);	 	//SUB
	else if(Operation == 43)		SW_Operation(binaireInstruction, tableRegister, m);		//SW
	// else if(Operation == -12)	SYSCALL_Operation(binaireInstruction, tableRegister); 	//SYSCALL
	else if(Operation == -38)		XOR_Operation(binaireInstruction, tableRegister); 		//XOR
    else {	
        //printf("Opération non reconnu\n");
        return 1;
    }
}

int returnArgument(int *binaireInstruction, int start, int end)
{
	int i;
	int j = 0;
	int argument = 0;
	for(i=start;i<end;i++)
	{
		argument += ((int) pow(2, j) * binaireInstruction[i]); 
		j++;
	}
	return argument;
}

void ADD_Operation(int *binaireInstruction, Register *tableRegister)
{
	int registre1 = returnArgument(binaireInstruction,11,16);
	int registre2 = returnArgument(binaireInstruction,16,21);
	int registre3 = returnArgument(binaireInstruction,21,26);
	
	addTwoBinaryRegister(tableRegister[registre3].registre,tableRegister[registre2].registre,tableRegister[registre1].registre);
	
	
	printf("R%d + R%d --> R%d\n",registre3,registre2,registre1);
	int i;
	for(i=31;i>=0;i--)
	{
		printf("%d",tableRegister[registre1].registre[i]);
	}
	printf("\n");
}

void ADDI_Operation(int *binaireInstruction,Register *tableRegister)
{
	int registre1 = returnArgument(binaireInstruction,0,16);
	int registre2 = returnArgument(binaireInstruction,16,21);
	int registre3 = returnArgument(binaireInstruction,21,26);

	int binaryRegistre1[32]={0};
	int tempValue = registre1;

	int i;
	for(i=0; tempValue>0; i++) {
        binaryRegistre1[i] = tempValue % 2;  
        tempValue = tempValue / 2;  
    }

	addTwoBinaryRegister(tableRegister[registre3].registre,binaryRegistre1,tableRegister[registre2].registre);

	printf(" %d + R%d --> R%d\n",registre1,registre3,registre2);
	for(i=31;i>=0;i--)
	{
		printf("%d",tableRegister[registre2].registre[i]);
	}
	printf("\n");
}

void AND_Operation(int *binaireInstruction,Register *tableRegister)
{
	int registre1 = returnArgument(binaireInstruction,11,16);
	int registre2 = returnArgument(binaireInstruction,16,21);
	int registre3 = returnArgument(binaireInstruction,21,26);

	andTwoBinaryRegister(tableRegister[registre3].registre,tableRegister[registre2].registre,tableRegister[registre1].registre);

	int i;
	printf("R%d AND R%d --> R%d\n",registre1,registre3,registre2);
	for(i=31;i>=0;i--)
	{
		printf("%d",tableRegister[registre1].registre[i]);
	}
	printf("\n");
}

// void BEQ_Operation(int *binaireInstruction, tableRegister *tableRegister)
// {

// }

// void BGTZ_Operation(int *binaireInstruction, tableRegister *tableRegister)
// {

// }

// void BLEZ_Operation(int *binaireInstruction, tableRegister *tableRegister)
// {

// }

// void BNE_Operation(int *binaireInstruction, tableRegister *tableRegister)
// {

// }

// void DIV_Operation(int *binaireInstruction, tableRegister *tableRegister)
// {

// }

void J_Operation(int *binaireInstruction,Register *tableRegister)
{
	int registre1 = returnArgument(binaireInstruction,0,26);

	jTwoBinaryRegister(registre1,tableRegister);

	printf("J %d\n",registre1);
}

void JAL_Operation(int *binaireInstruction,Register *tableRegister)
{
	int registre1 = returnArgument(binaireInstruction,0,26);

	jalTwoBinaryRegister(registre1,tableRegister);

	printf("JAL %d\n",registre1);

}

void JR_Operation(int *binaireInstruction,Register *tableRegister)
{
	int registre1 = returnArgument(binaireInstruction,21,26);

	jrTwoBinaryRegister(tableRegister[registre1].registre,tableRegister);

	printf("Jr R%d\n",registre1);
}

void LUI_Operation(int *binaireInstruction,Register *tableRegister)
{
	int registre1 = returnArgument(binaireInstruction,0,16);
	int registre2 = returnArgument(binaireInstruction,16,21);

	luiTwoBinaryRegister(registre1,tableRegister[registre2].registre);

	int i;

	printf("LUI R%d = %d || 0^16\n",registre2,registre1);
	for(i=31;i>=0;i--)
	{
		printf("%d",tableRegister[registre2].registre[i]);
	}
	printf("\n");
}

void LW_Operation(int *binaireInstruction,Register *tableRegister, memory *m)
{	
	int registre1 = returnArgument(binaireInstruction,0,16);
	int registre2 = returnArgument(binaireInstruction,16,21);
	int registre3 = returnArgument(binaireInstruction,21,26);

	ldTwoBinaryRegister(tableRegister[registre2].registre,registre1,tableRegister[registre3].registre, m);

	int i;

	printf("LW R%d <-- %d(R%d)\n",registre3,registre1,registre2);
	for(i=31;i>=0;i--)
	{
		printf("%d",tableRegister[registre3].registre[i]);
	}
	printf("\n");
}

void MFHI_Operation(int *binaireInstruction,Register *tableRegister)
{
	int registre1 = returnArgument(binaireInstruction,11,16);

	mfhiTwoBinaryRegister(tableRegister[registre1].registre,tableRegister);

	int i;
	printf("R%d <-- R27\n",registre1);
	for(i=31;i>=0;i--)
	{
		printf("%d",tableRegister[registre1].registre[i]);
	}
	printf("\n");
}

void MFLO_Operation(int *binaireInstruction,Register *tableRegister)
{
	int registre1 = returnArgument(binaireInstruction,11,16);

	mfloTwoBinaryRegister(tableRegister[registre1].registre,tableRegister);

	int i;
	printf("R%d <-- R26\n",registre1);
	for(i=31;i>=0;i--)
	{
		printf("%d",tableRegister[registre1].registre[i]);
	}
	printf("\n");
}

void MULT_Operation(int *binaireInstruction,Register *tableRegister)
{
	int registre1 = returnArgument(binaireInstruction,16,21);
	int registre2 = returnArgument(binaireInstruction,21,26);

	multTwoBinaryRegister(tableRegister[registre2].registre,registre1,tableRegister);

	int k;
	printf("R%d * %d --> R26/27\n",registre2,registre1);
	for(k=31;k>=0;k--)
	{
		printf("%d",tableRegister[26].registre[k]);
	}
	printf("\n");

	for(k=31;k>=0;k--)
	{
		printf("%d",tableRegister[27].registre[k]);
	}
	printf("\n");
}

void NOP_Operation(int *binaireInstruction,Register *tableRegister)
{
	sllTwoBinaryRegister(tableRegister[0].registre,0,tableRegister[0].registre);
	printf("NOP\n");
}

void OR_Operation(int *binaireInstruction,Register *tableRegister)
{
	int registre1 = returnArgument(binaireInstruction,11,16);
	int registre2 = returnArgument(binaireInstruction,16,21);
	int registre3 = returnArgument(binaireInstruction,21,26);

	orTwoBinaryRegister(tableRegister[registre3].registre,tableRegister[registre2].registre,tableRegister[registre1].registre);

	int i;
	printf("R%d OR R%d --> R%d\n",registre1,registre3,registre2);
	for(i=31;i>=0;i--)
	{
		printf("%d",tableRegister[registre1].registre[i]);
	}
	printf("\n");
}

void ROTR_Operation(int *binaireInstruction,Register *tableRegister)
{
	int registre1 = returnArgument(binaireInstruction,6,11);
	int registre2 = returnArgument(binaireInstruction,11,16);
	int registre3 = returnArgument(binaireInstruction,16,21);

	rotrTwoBinaryRegister(tableRegister[registre3].registre,registre1,tableRegister[registre2].registre);

	int i;
	printf("R%d ROTR %d --> R%d\n",registre1,registre1,registre2);
	for(i=31;i>=0;i--)
	{
		printf("%d",tableRegister[registre2].registre[i]);
	}
	printf("\n");
}

void SLL_Operation(int *binaireInstruction,Register *tableRegister)
{
	int registre1 = returnArgument(binaireInstruction,6,11);
	int registre2 = returnArgument(binaireInstruction,11,16);
	int registre3 = returnArgument(binaireInstruction,16,21);

	sllTwoBinaryRegister(tableRegister[registre3].registre,registre1,tableRegister[registre2].registre);

	int i;
	printf("R%d << %d --> R%d\n",registre3,registre1,registre2);
	for(i=31;i>=0;i--)
	{
		printf("%d",tableRegister[registre2].registre[i]);
	}
	printf("\n");
}

void SLT_Operation(int *binaireInstruction,Register *tableRegister)
{
	int registre1 = returnArgument(binaireInstruction,11,16);
	int registre2 = returnArgument(binaireInstruction,16,21);
	int registre3 = returnArgument(binaireInstruction,21,26);

	sltTwoBinaryRegister(tableRegister[registre2].registre,tableRegister[registre3].registre,tableRegister[registre1].registre);

	int i;
	printf("R%d < R%d ? --> R%d\n",registre2,registre3,registre1);
	for(i=31;i>=0;i--)
	{
		printf("%d",tableRegister[registre1].registre[i]);
	}
	printf("\n");
}

void SRL_Operation(int *binaireInstruction,Register *tableRegister)
{
	int registre1 = returnArgument(binaireInstruction,6,11);
	int registre2 = returnArgument(binaireInstruction,11,16);
	int registre3 = returnArgument(binaireInstruction,16,21);

	srlTwoBinaryRegister(tableRegister[registre3].registre,registre1,tableRegister[registre2].registre);

	int i;
	printf("R%d >> %d --> R%d\n",registre3,registre1,registre2);
	for(i=31;i>=0;i--)
	{
		printf("%d",tableRegister[registre2].registre[i]);
	}
	printf("\n");
}

void SUB_Operation(int *binaireInstruction,Register *tableRegister)
{
	int registre1 = returnArgument(binaireInstruction,11,16);
	int registre2 = returnArgument(binaireInstruction,16,21);
	int registre3 = returnArgument(binaireInstruction,21,26);

	subTwoBinaryRegister(tableRegister[registre3].registre,tableRegister[registre2].registre,tableRegister[registre1].registre);

	int i;

	printf("R%d - R%d --> R%d\n",registre3,registre2,registre1);
	for(i=31;i>=0;i--)
	{
		printf("%d",tableRegister[registre1].registre[i]);
	}
	printf("\n");
}

void SW_Operation(int *binaireInstruction,Register *tableRegister,  memory *m)
{
	int registre1 = returnArgument(binaireInstruction,0,16);
	int registre2 = returnArgument(binaireInstruction,16,21);
	int registre3 = returnArgument(binaireInstruction,21,26);

	swTwoBinaryRegister(tableRegister[registre3].registre,registre1,tableRegister[registre2].registre, m);

	int i;

	printf("SW R%d --> %d(R%d)\n",registre2,registre1,registre3);
}

// void SYSCALL_Operation(int *binaireInstruction,Register *tableRegister)
// {

// }

void XOR_Operation(int *binaireInstruction,Register *tableRegister)
{
	int registre1 = returnArgument(binaireInstruction,11,16);
	int registre2 = returnArgument(binaireInstruction,16,21);
	int registre3 = returnArgument(binaireInstruction,21,26);

	xorTwoBinaryRegister(tableRegister[registre3].registre,tableRegister[registre2].registre,tableRegister[registre1].registre);

	int i;

	printf("R%d XOR R%d --> R%d\n",registre3,registre2,registre1);
	for(i=31;i>=0;i--)
	{
		printf("%d",tableRegister[registre1].registre[i]);
	}
	printf("\n");
}



//Ne fonctionne pas avec des chiffres négatifs, je me pose la question si ADD à le droit d'avoir des chiffres négatif, ADDI oui mais juste pour le immediate j'ai l'impression
//alors que je crois me rappeler qu'on a toujours eu le droit d'avoir des registres avec des chiffres négatifs...
//Faut qu'on regarde, puis je ferais les modifs en conséquence

int addTwoBinaryRegister(int *register1, int *register2, int *destinationRegister)
{

	int k;
	for(k=31;k>=0;k--)
	{
		printf("%d",register1[k]);
	}
	printf("\n");
	for(k=31;k>=0;k--)
	{
		printf("%d",register2[k]);
	}
	printf("\n");

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
	if(carry == 1)	overflowed = 1;
	
	if(overflowed == 0)
	{
		for(i=0;i<32;i++)
		{
			destinationRegister[i] = tempRegister[i];
		}
	
	}
	return overflowed;
}

int subTwoBinaryRegister(int *register1, int *register2, int *destinationRegister)
{
	int i = 0;
	int carry = 0;
	int overflowed = 0;

	int k;
	for(k=31;k>=0;k--)
	{
		printf("%d",register1[k]);
	}
	printf("\n");
	for(k=31;k>=0;k--)
	{
		printf("%d",register2[k]);
	}
	printf("\n");

	while (register2[i] != 1)
	{
		i++;
	}
	
	for(i=i+1; i<32; i++)  
    {	
        if (register2[i] == 0)
            register2[i] = 1;
        else register2[i] = 0;
    }

	for(k=31;k>=0;k--)
	{
		printf("%d",register2[k]);
	}
	printf("\n");

	for(i=0;i<32;i++)
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

void andTwoBinaryRegister(int *register1, int *register2, int *destinationRegister)
{
	int i = 0;

	int k;
	for(k=31;k>=0;k--)
	{
		printf("%d",register1[k]);
	}
	printf("\n");
	for(k=31;k>=0;k--)
	{
		printf("%d",register2[k]);
	}
	printf("\n");

	for(i=31;i>=0;i--)
	{
		destinationRegister[i] = register1[i] & register2[i];
	}
}

void orTwoBinaryRegister(int *register1, int *register2, int *destinationRegister)
{
	int i = 0;

	int k;
	for(k=31;k>=0;k--)
	{
		printf("%d",register1[k]);
	}
	printf("\n");
	for(k=31;k>=0;k--)
	{
		printf("%d",register2[k]);
	}
	printf("\n");

	for(i=31;i>=0;i--)
	{
		destinationRegister[i] = register1[i] | register2[i];
	}
}

void sllTwoBinaryRegister(int *register1, int deplacement, int *destinationRegister)
{
	int i;
	int j = 31;
	int k;
	for(k=31;k>=0;k--)
	{
		printf("%d",register1[k]);
	}
	printf("\n");

	for(i=31-deplacement;i>=0;i--)
	{
		destinationRegister[j] = register1[i];
		j--;
	}
	for(i=j;i>=0;i--)
	{
		destinationRegister[i] = 0;
	}
}

void sltTwoBinaryRegister(int *register1, int *register2, int *destinationRegister)
{
	int i;
	int k;
	int negatifRegistre1 = 0;
	int negatifRegistre2 = 0;
	int tempValueRegistre1 = 0;
	int tempValueRegistre2 = 0;
	
	for(k=31;k>=0;k--)
	{
		printf("%d",register1[k]);
	}
	printf("\n");

	for(k=31;k>=0;k--)
	{
		printf("%d",register2[k]);
	}
	printf("\n");

	if(register1[31] == 1)
	{
		i = 0;
		while (register1[i] != 1)
		{
			i++;
		}
	
		for(i=i+1; i<32; i++)  
    	{		
        	if (register1[i] == 0)
            	register1[i] = 1;
        	else register1[i] = 0;
    	}
		negatifRegistre1 = 1;
	}

	if(register1[31] == 1)
	{
		i = 0;
		while (register2[i] != 1)
		{
			i++;
		}
	
		for(i=i+1; i<32; i++)  
    	{	
        	if (register2[i] == 0)
            	register2[i] = 1;
        	else register2[i] = 0;
    	}
		negatifRegistre2 = 1;
	}

	for(i=30;i>=0;i--)
	{
		tempValueRegistre1 += (int) (pow(2, i) * register1[i]);
		tempValueRegistre2 += (int) (pow(2, i) * register2[i]);
	}
	
	if(negatifRegistre1 == 1) tempValueRegistre1 *= -1;
	if(negatifRegistre2 == 1) tempValueRegistre2 *= -1;
	
	if(tempValueRegistre1 < tempValueRegistre2) destinationRegister[0] = 1;
	else destinationRegister[0] = 0;
}

void xorTwoBinaryRegister(int *register1, int *register2, int *destinationRegister)
{
	int i = 0;

	int k;
	for(k=31;k>=0;k--)
	{
		printf("%d",register1[k]);
	}
	printf("\n");
	for(k=31;k>=0;k--)
	{
		printf("%d",register2[k]);
	}
	printf("\n");

	for(i=31;i>=0;i--)
	{
		if( (register1[i] == 1 && register2[i] == 0) || (register1[i] == 0 && register2[i] == 1) ) destinationRegister[i] = 1;
		else destinationRegister[i] = 0;
	}
}

void srlTwoBinaryRegister(int *register1, int deplacement, int *destinationRegister)
{
	int i;
	int j = 0;
	int k;
	for(k=31;k>=0;k--)
	{
		printf("%d",register1[k]);
	}
	printf("\n");

	for(i=deplacement;i<31;i++)
	{
		destinationRegister[j] = register1[i];
		j++;
	}
	for(i=j;i<31;i++)
	{
		destinationRegister[i] = 0;
	}
}

void rotrTwoBinaryRegister(int *register1, int deplacement, int *destinationRegister)
{
	int i;
	int k;

	for(k=31;k>=0;k--)
	{
		printf("%d",register1[k]);
	}
	printf("\n");

	for(i=0;i<=deplacement;i++)
	{
		destinationRegister[i] = register1[deplacement-i-1];
	}
	for(i=i;i<31;i++)
	{
		destinationRegister[i] = register1[i];
	}
}

void multTwoBinaryRegister(int *register1, int multiplication,Register *tableRegister)
{
	int i;
	int k;
	unsigned long long int tempValueRegistre1 = 0;
	for(k=31;k>=0;k--)
	{
		printf("%d",register1[k]);
	}
	printf("\n");
	
	for(i=31;i>=0;i--)
	{
		tempValueRegistre1 += (unsigned long long int) (pow(2, i) * register1[i]);
	}
	printf("%lld\n",tempValueRegistre1);

	tempValueRegistre1 *= multiplication;

	printf("%lld\n",tempValueRegistre1);
	
	for(i=0; tempValueRegistre1>0 && i<32; i++) {
        tableRegister[26].registre[i] = tempValueRegistre1 % 2;  
        tempValueRegistre1 = tempValueRegistre1 / 2;  
    }

	for(i=0; tempValueRegistre1>0; i++) {
     	tableRegister[27].registre[i] = tempValueRegistre1 % 2;  
    	tempValueRegistre1 = tempValueRegistre1 / 2;  
    }
}

void mfloTwoBinaryRegister(int *destinationRegister, Register *tableRegister)
{
	int i;

	for(i=0;i<31;i++)
	{
		destinationRegister[i] = tableRegister[26].registre[i];
	}
}

void mfhiTwoBinaryRegister(int *destinationRegister, Register *tableRegister)
{
	int i;

	for(i=0;i<31;i++)
	{
		destinationRegister[i] = tableRegister[27].registre[i];
	}
}

void swTwoBinaryRegister(int *register1, int register2, int *destinationRegister,  memory *m)
{
	int i;
	int valueSp = 0;

	for(i=31;i>=0;i--)
	{
		valueSp += (unsigned long long int) (pow(2, i) * register1[i]);
	}

	valueSp += register2;

	writeFourOctetsInMemory(destinationRegister, valueSp, m);
}	

void ldTwoBinaryRegister(int *register1, int register2, int *destinationRegister,  memory *m)
{
	int i;
	int valueSp = 0;
	
	for(i=31;i>=0;i--)
	{
		valueSp += (unsigned long long int) (pow(2, i) * register1[i]);
	}

	valueSp += register2;
	printf("%d\n",valueSp);

	readInstructionInMemory(valueSp, destinationRegister, m);
	
}	

void luiTwoBinaryRegister(int register1, int *destinationRegister)
{
	int i;
	
	int tempValueRegistre1[16] = {0};

	printf("%d\n",register1);

	for(i=0; register1>0; i++) {
        tempValueRegistre1[i] = register1 % 2;  
        register1 = register1 / 2;  
    }

	int k;

	for(k=15;k>=0;k--)
	{
		printf("%d",tempValueRegistre1[k]);
	}
	printf("\n");

	for(i=31;i>=16;i--)
	{
		destinationRegister[i] =  tempValueRegistre1[i-16];
	}

	for(i=15;i>=0;i--)
	{
		destinationRegister[i] = 0;
	}
	
}	

void jalTwoBinaryRegister(int register1,Register *tableRegister)
{
	int i;
	int tempValue = 8;
	int newSpRegister[32] = {0};
	for(i=0; tempValue>0; i++) {
        newSpRegister[i] = tempValue % 2;  
        tempValue = tempValue / 2;  
    }

	addTwoBinaryRegister(tableRegister[29].registre,newSpRegister,tableRegister[31].registre);

	tempValue = register1;

	for(i=0; tempValue>0; i++) {
        newSpRegister[i] = tempValue % 2;  
        tempValue = tempValue / 2;  
    }

	sllTwoBinaryRegister(newSpRegister,2,tableRegister[29].registre);
}

void jrTwoBinaryRegister(int *register1,Register *tableRegister)
{
	int i;
	for(i=31;i>=0;i--)
	{
		tableRegister[29].registre[i] = register1[i];	
	}
}

void jTwoBinaryRegister(int register1,Register *tableRegister)
{
	int i;
	int newSpRegister[32] = {0};

	for(i=0; register1>0; i++) {
        newSpRegister[i] = register1 % 2;  
        register1 = register1 / 2;  
    }

	sllTwoBinaryRegister(newSpRegister,2,tableRegister[29].registre);
}