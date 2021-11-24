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

int testTexte(char *operation, char *Texte)
{
    int i = 0;
    int isEqual = 1;
    int tailleOp = strlen(operation);
    int tailleTe = strlen(Texte);

    if(tailleOp != tailleTe)
    {
        isEqual = 0;
    }
    while(operation[i] != '\0' && isEqual == 1)
    {
        if(operation[i] != Texte[i])
        {
            isEqual = 0;
        }
        i++;
    }
    return isEqual;
}

int createBinaryInstruction(char *operation, int *tabValue, int *binaireInstruction)
{
    if(testTexte(operation, "ADD"))           binaryADD(operation, tabValue, binaireInstruction);
    else if(testTexte(operation, "ADDI"))     binaryADDI(operation, tabValue, binaireInstruction);
    else if(testTexte(operation, "AND"))      binaryAND(operation, tabValue, binaireInstruction);
    else if(testTexte(operation, "BEQ"));
    else if(testTexte(operation, "BGTZ"));
    else if(testTexte(operation, "BLEZ"));
    else if(testTexte(operation, "BNE"));
    else if(testTexte(operation, "DIV"));
    else if(testTexte(operation, "J"));
    else if(testTexte(operation, "JAL"));
    else if(testTexte(operation, "JR"));
    else if(testTexte(operation, "LUI"));
    else if(testTexte(operation, "LW"));
    else if(testTexte(operation, "MFHI"));
    else if(testTexte(operation, "MLFO"));
    else if(testTexte(operation, "MULT"));
    else if(testTexte(operation, "NOP"));
    else if(testTexte(operation, "OR"))       binaryOR(operation, tabValue, binaireInstruction);
    else if(testTexte(operation, "ROTR"));
    else if(testTexte(operation, "SLL"));
    else if(testTexte(operation, "SLT"));
    else if(testTexte(operation, "SRL"));
    else if(testTexte(operation, "SUB"));
    else if(testTexte(operation, "SW"));
    else if(testTexte(operation, "SYSCALL"));
    else if(testTexte(operation, "XOR"));

    return 1;
}

int putToZero(int *binaireInstruction, int start, int end)
{
    int i;
    for(i=start; i<=end; i++)
    {
        binaireInstruction[i] = 0;
    }
    
    return 1;
}

int putToValue(int *binaireInstruction, int start, int value)
{
    int i;
    for(i=start; value>0; i++)  
    {  
        binaireInstruction[i] = value % 2;  
        value = value / 2;  
    }
    return 1;
}

int displayBinary(int *binaireInstruction)
{
    int i;
    printf("Binary :");
    for(i=32; i>0; i--)  
    {  
        if(i%4 == 0) printf(" ");
        printf("%d", binaireInstruction[i-1]);  
    }

    printf("\n");

    return 1;
}

int displayHexadecimal(int *hexadecimalInstruction)
{
    int i;
    printf("Hexadecimal :");
    for(i=0; i<=7; i++)  
    {  
        if(i%2 == 0) printf(" ");
        printf("%x", hexadecimalInstruction[i]);  
    }
    printf("\n");

    return 1;
}

int binaryADD(char *operation, int *tabValue, int *binaireInstruction)
{ 
    putToValue(binaireInstruction,0,32);
    putToZero(binaireInstruction,6,10);
    putToValue(binaireInstruction,11,tabValue[0]);
    putToValue(binaireInstruction,16,tabValue[2]);
    putToValue(binaireInstruction,21,tabValue[1]);   
    putToZero(binaireInstruction,26,31);
}

int binaryADDI(char *operation, int *tabValue, int *binaireInstruction)
{ 
    putToValue(binaireInstruction,5,8);
    putToValue(binaireInstruction,10,tabValue[1]);
    putToValue(binaireInstruction,15,tabValue[0]);
    putToValue(binaireInstruction,31,tabValue[2]);
}

int binaryAND(char *operation, int *tabValue, int *binaireInstruction)
{ 
    putToZero(binaireInstruction,0,5);
    putToValue(binaireInstruction,10,tabValue[1]);
    putToValue(binaireInstruction,15,tabValue[2]);
    putToValue(binaireInstruction,20,tabValue[0]);
    putToZero(binaireInstruction,21,25);
    putToValue(binaireInstruction,31,36);
}

int binaryOR(char *operation, int *tabValue, int *binaireInstruction)
{ 
    putToZero(binaireInstruction,0,5);
    putToValue(binaireInstruction,10,tabValue[1]);
    putToValue(binaireInstruction,15,tabValue[2]);
    putToValue(binaireInstruction,20,tabValue[0]);
    putToZero(binaireInstruction,21,25);
    putToValue(binaireInstruction,31,37);
}



int convertBinaireIntoHex(int *binaireInstruction, int *hexadecimalInstruction)
{
    int i, j, n = 0;
    for(i=7; i>=0; i--)
    {
        for(j=0; j<=3; j++)
        {
            hexadecimalInstruction[i] += (int) (pow(2, j) * binaireInstruction[n]);
            n++;
        }
    }
    return 1;
}