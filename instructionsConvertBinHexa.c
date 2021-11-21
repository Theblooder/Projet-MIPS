#include "instructionsConvertBinHexa.h"
#include <math.h>
#include <string.h>
#include "stdio.h"


int instructionValue(const char *instruction, int *tabValues, char *operation)
{
    int i = 0; int j; int indiceValue = 0; int lengthValue = 1; int k; int numberOfValues = 3; /*Pour limiter l'écriture de seulement 3 valeurs max dans le tableau de value */
    int getInstructionBool = 0;

    while(instruction[i] != '\0' && numberOfValues != 0) {
        if(instruction[i] == ' ') {
            /* To end the string */ 
            getInstructionBool = i;
            operation[getInstructionBool] = '\0';
            /* To remove the '$' from the number */
            if(instruction[i+1] == '$') {
                j = i+2;
            }
            else {
                j = i+1;
            }
            /* Get the length if the value */
            int temp = j;
            while(instruction[temp+1] != ' ' && instruction[temp+1] != '\0') {
                lengthValue += 1;
                temp++;
            }
            /* Add the value to the list */
            tabValues[indiceValue] = 0;
            for(k=lengthValue; k>0; k--) {
                tabValues[indiceValue] += (int) (instruction[j]-48) * pow(10, k-1);
                j++;
            }
            numberOfValues--;
            indiceValue++;
            lengthValue = 1;
        }
        /* Get the operation of the instruction */
        if(!getInstructionBool) {
            operation[i] = instruction[i];
        }
        i++;
    }
    return 0;
}

int TestTexte(char *operation, char *Texte)
{
    int i = 0;
    int value = 1;
    int tailleOp = strlen(operation);
    int tailleTe = strlen(Texte);
    if(tailleOp != tailleTe)
    {
        value = 0;
    }
    while (operation[i] != '\0' && value == 1)
    {
        if(operation[i]!=Texte[i])
        {
            value = 0;
        }
        i++;
    }
    return value;
}

int createBinaryInstruction(char *operation, int *tabValue, int *binaireInstruction, int *hexadecimalInstruction)
{
    if(TestTexte(operation,"ADD"))           BinaryADD(operation, tabValue, binaireInstruction, hexadecimalInstruction);
    else if(TestTexte(operation,"ADDI"))     BinaryADDI(operation, tabValue, binaireInstruction, hexadecimalInstruction);
    else if(TestTexte(operation,"AND"))      BinaryAND(operation, tabValue, binaireInstruction, hexadecimalInstruction);
    else if(TestTexte(operation,"BEQ"));
    else if(TestTexte(operation,"BGTZ"));
    else if(TestTexte(operation,"BLEZ"));
    else if(TestTexte(operation,"BNE"));
    else if(TestTexte(operation,"DIV"));
    else if(TestTexte(operation,"J"));
    else if(TestTexte(operation,"JAL"));
    else if(TestTexte(operation,"JR"));
    else if(TestTexte(operation,"LUI"));
    else if(TestTexte(operation,"LW"));
    else if(TestTexte(operation,"MFHI"));
    else if(TestTexte(operation,"MLFO"));
    else if(TestTexte(operation,"MULT"));
    else if(TestTexte(operation,"NOP"));
    else if(TestTexte(operation,"OR"))       BinaryOR(operation, tabValue, binaireInstruction, hexadecimalInstruction);
    else if(TestTexte(operation,"ROTR"));
    else if(TestTexte(operation,"SLL"));
    else if(TestTexte(operation,"SLT"));
    else if(TestTexte(operation,"SRL"));
    else if(TestTexte(operation,"SUB"));
    else if(TestTexte(operation,"SW"));
    else if(TestTexte(operation,"SYSCALL"));
    else if(TestTexte(operation,"XOR"));

    return 1;
}

int putToZero(int *binaireInstruction, int start, int end)
{
    int i;
    for(i = start;i <= end; i++)
    {
        binaireInstruction[i] = 0;
    }
    
    return 1;
}

int putToValue(int *binaireInstruction, int start, int value)
{
    int i;
    for(i = start; value > 0; i++)  
    {  
        binaireInstruction[i] = value%2;  
        value = value/2;  
    }
    return 1;
}

int DisplayBinary(int *binaireInstruction)
{
    int i;
    printf("Binary :");
    for(i=32; i > 0; i--)  
    {  
        if(i%4 == 0) printf(" ");
        printf("%d",binaireInstruction[i-1]);  
    }

    printf("\n");

    return 1;
}

int DisplayHexadecimal(int *hexadecimalInstruction)
{
    int i;
    printf("Hexadecimal :");
    for(i=0; i <= 7; i++)  
    {  
        if(i%2 == 0) printf(" ");
        printf("%x",hexadecimalInstruction[i]);  
    }

    printf("\n");

    return 1;
}

int BinaryADD(char *operation, int *tabValue, int *binaireInstruction, int *hexadecimalInstruction)
{ 
    putToValue(binaireInstruction,0,32);
    putToZero(binaireInstruction,6,10);
    putToValue(binaireInstruction,11,tabValue[0]);
    putToValue(binaireInstruction,16,tabValue[2]);
    putToValue(binaireInstruction,21,tabValue[1]);   
    putToZero(binaireInstruction,26,31); 
    DisplayBinary(binaireInstruction);
    convertBinaireIntoHex(binaireInstruction, hexadecimalInstruction);
}

int BinaryADDI(char *operation, int *tabValue, int *binaireInstruction, int *hexadecimalInstruction)
{ 
    putToValue(binaireInstruction,5,8);
    putToValue(binaireInstruction,10,tabValue[1]);
    putToValue(binaireInstruction,15,tabValue[0]);
    putToValue(binaireInstruction,31,tabValue[2]);  
    DisplayBinary(binaireInstruction);
    convertBinaireIntoHex(binaireInstruction, hexadecimalInstruction);
}

int BinaryAND(char *operation, int *tabValue, int *binaireInstruction, int *hexadecimalInstruction)
{ 
    putToZero(binaireInstruction,0,5);
    putToValue(binaireInstruction,10,tabValue[1]);
    putToValue(binaireInstruction,15,tabValue[2]);
    putToValue(binaireInstruction,20,tabValue[0]);
    putToZero(binaireInstruction,21,25);
    putToValue(binaireInstruction,31,36);   
    DisplayBinary(binaireInstruction);
    convertBinaireIntoHex(binaireInstruction, hexadecimalInstruction);
}

int BinaryOR(char *operation, int *tabValue, int *binaireInstruction, int *hexadecimalInstruction)
{ 
    putToZero(binaireInstruction,0,5);
    putToValue(binaireInstruction,10,tabValue[1]);
    putToValue(binaireInstruction,15,tabValue[2]);
    putToValue(binaireInstruction,20,tabValue[0]);
    putToZero(binaireInstruction,21,25);
    putToValue(binaireInstruction,31,37);   
    DisplayBinary(binaireInstruction);
    convertBinaireIntoHex(binaireInstruction, hexadecimalInstruction);
}



int convertBinaireIntoHex(int *binaireInstruction, int *hexadecimalInstruction)
{
    int i,j,n = 0;
    for(i=7;i>=0;i--)
    {
        for(j = 0;j <=3; j++)
        {
            hexadecimalInstruction[i] = hexadecimalInstruction[i] +  (int)pow(2, j)*binaireInstruction[n];
            n++;
        }
    }

    DisplayHexadecimal(hexadecimalInstruction);

    return 1;
}