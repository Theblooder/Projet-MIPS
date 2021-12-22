#include "instructionsConvertBinHexa.h"
#include <math.h>
#include <string.h>
#include <stdio.h>


int instructionValue(const char *instruction, int *tabValues, char *operation)
{
    int i = 0; int j; int indiceValue = 0; int lengthValue = 1; int k; ; int negativeValue; int numberOfValues = 3; /*Pour limiter l'écriture de seulement 3 valeurs max dans le tableau de value */
    int getInstructionBool = 0;
    int indiceStartInstruction = 0; int indiceEndInstruction = 0;

    while(instruction[i] != '\0' && instruction[i] != '#' && numberOfValues != 0) {
        if((instruction[i] == ' ' || instruction[i] == ',' || instruction[i] == '(') && indiceEndInstruction != 0) {
            getInstructionBool = 1;
            operation[indiceEndInstruction] = '\0';
            /* To remove the '$' from the number */
            if(instruction[i+1] == ' ') {
                if(instruction[i+2] == '$') {
                    j = i+3;
                }
                else {
                    j = i+2;
                }
            }
            else {
                if(instruction[i+1] == '$') {
                    j = i+2;
                }
                else {
                    j = i+1;
                }
            }
            
            int temp = j;

            /* If there is a negative value I just go 1 char after and remember it */
            if(instruction[temp] == '-') {
                temp++;   /*When we count the length of the number */
                j++;     /* When we will convert the char into int */
                negativeValue = 1;
            }
            else {
                negativeValue = 0;
            }
            /* Get the length if the value */
            while(instruction[temp+1] != ',' && instruction[temp+1] != '(' && instruction[temp+1] != ')' && instruction[temp+1] != ' ' && instruction[temp+1] != '#' && instruction[temp+1] != '\0') {
                lengthValue += 1;
                temp++;
            }
            /*We can go throw all the part of the instruction */
            if(instruction[temp+1] == ' ' && instruction[temp+2] == ',') {
                i = temp + 1;
            }
            else {
                i = temp;
            }

            /* Add the value to the list */
            tabValues[indiceValue] = 0;
            for(k=lengthValue; k>0; k--) {
                tabValues[indiceValue] += (int) (instruction[j]-48) * pow(10, k-1);
                j++;
            }
            if(negativeValue) {
                tabValues[indiceValue] *= -1;
            }
            numberOfValues--;
            indiceValue++;
            lengthValue = 1;
        }
        /* Get the operation of the instruction */
        if(!getInstructionBool && instruction[i] != ' ') {
            operation[indiceStartInstruction++] = instruction[i];
            indiceEndInstruction = i+1;
        }
        /* For NOP operation */
        if(instruction[i+1] == '\0') {
            operation[indiceEndInstruction] = '\0';
        }
        i++;
    }
    return 0;
}

int isStringFullOfSpaces(const char *string)
{
    int i = 0;
    int isFullOfSpaces = 1;

    while(string[i] != '\0' && isFullOfSpaces) {
        if(string[i++] != ' ') {
            isFullOfSpaces = 0;
        }
    }
    return isFullOfSpaces;
}

int isBeginWithCommentCharBeforeAnyCharOtherThanSpace(char *string)
{   
    int i = 0;
    int isCommentLine = 0;

    while(string[i] != '\0' && (string[i] == ' ' || string[i] == '#')) {
        if(string[i++] == '#') {
            isCommentLine = 1;
        }
    }
    return isCommentLine;
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

    if(testTexte(operation, "ADD"))           binaryADD(tabValue, binaireInstruction);
    else if(testTexte(operation, "ADDI"))     binaryADDI(tabValue, binaireInstruction);
    else if(testTexte(operation, "AND"))      binaryAND(tabValue, binaireInstruction);
    else if(testTexte(operation, "BEQ"))      binaryBEQ(tabValue, binaireInstruction);
    else if(testTexte(operation, "BGTZ"))     binaryBGTZ(tabValue, binaireInstruction);
    else if(testTexte(operation, "BLEZ"))     binaryBLEZ(tabValue, binaireInstruction);
    else if(testTexte(operation, "BNE"))      binaryBNE(tabValue, binaireInstruction);
    else if(testTexte(operation, "DIV"))      binaryDIV(tabValue, binaireInstruction);
    else if(testTexte(operation, "J"))        binaryJ(tabValue, binaireInstruction);
    else if(testTexte(operation, "JAL"))      binaryJAL(tabValue, binaireInstruction);
    else if(testTexte(operation, "JR"))       binaryJR(tabValue, binaireInstruction);
    else if(testTexte(operation, "LUI"))      binaryLUI(tabValue, binaireInstruction);
    else if(testTexte(operation, "LW"))       binaryLW(tabValue, binaireInstruction);
    else if(testTexte(operation, "MFHI"))     binaryMFHI(tabValue, binaireInstruction);
    else if(testTexte(operation, "MFLO"))     binaryMFLO(tabValue, binaireInstruction);
    else if(testTexte(operation, "MULT"))     binaryMULT(tabValue, binaireInstruction);
    else if(testTexte(operation, "NOP"))      binaryNOP(tabValue, binaireInstruction);
    else if(testTexte(operation, "OR"))       binaryOR(tabValue, binaireInstruction);
    else if(testTexte(operation, "ROTR"))     binaryROTR(tabValue, binaireInstruction);
    else if(testTexte(operation, "SLL"))      binarySLL(tabValue, binaireInstruction);
    else if(testTexte(operation, "SLT"))      binarySLT(tabValue, binaireInstruction);
    else if(testTexte(operation, "SRL"))      binarySRL(tabValue, binaireInstruction);
    else if(testTexte(operation, "SUB"))      binarySUB(tabValue, binaireInstruction);
    else if(testTexte(operation, "SW"))       binarySW(tabValue, binaireInstruction);
    else if(testTexte(operation, "SYSCALL"))  binarySYSCALL(tabValue, binaireInstruction);
    else if(testTexte(operation, "XOR"))      binaryXOR(tabValue, binaireInstruction);
    else {
        //printf("Opération non reconnu\n");
        return 1;
    }

    return 0;
}

int putToZero(int *binaireInstruction, int start, int end)
{
    int i;
    for(i=start; i<=end; i++)
    {
        binaireInstruction[i] = 0;
    }
    
    return 0;
}

int putToValue(int *binaireInstruction, int start, int value)
{
    int i;
    int isSigned = 0;

    if(value < 0) {
        isSigned = 1;
        value *= -1;
    }

    for(i=start; value>0; i++) {
        binaireInstruction[i] = value % 2;  
        value = value / 2;  
    }
    if(isSigned)
    {
        for(i=start; i<start+16; i++)  /* 16 is the number of bits for the immediates values */
        {
            binaireInstruction[i] ^= 1;
        }
        /* complement to 2 */
        i = 0;
        while(binaireInstruction[i] != 0) {
            binaireInstruction[i] = 0;
            i++;
        }
        binaireInstruction[i] = 1;
    }
    
    return 0;
}

int displayBinary(int *binaireInstruction)
{
    int i;
    printf("Binary :");
    for(i=1; i<32; i++)  
    {  
        if(i%4 == 0) printf(" ");
        printf("%d", binaireInstruction[i-1]);  
    }

    printf("\n");

    return 0;
}

int displayHexadecimal(int *hexadecimalInstruction)
{
    int i;
    //printf("Hexadecimal :");
    for(i=0; i<=7; i++)  
    {  
        if(i%2 == 0) printf(" ");
        printf("%x", hexadecimalInstruction[i]);  
    }
    //printf("\n");

    return 0;
}

int binaryADD(int *tabValue, int *binaireInstruction)
{ 
    putToValue(binaireInstruction,0,32);
    putToZero(binaireInstruction,6,10);
    putToValue(binaireInstruction,11,tabValue[0]);
    putToValue(binaireInstruction,16,tabValue[2]);
    putToValue(binaireInstruction,21,tabValue[1]);   
    putToZero(binaireInstruction,26,31);
}

int binaryADDI(int *tabValue, int *binaireInstruction)
{ 
    putToValue(binaireInstruction,0,tabValue[2]);
    putToZero(binaireInstruction,16,31);
    putToValue(binaireInstruction,16,tabValue[0]);
    putToValue(binaireInstruction,21,tabValue[1]);
    putToValue(binaireInstruction,26,8);
}

int binaryAND(int *tabValue, int *binaireInstruction)
{ 
    putToValue(binaireInstruction,0,36);
    putToValue(binaireInstruction,6,0);
    putToValue(binaireInstruction,11,tabValue[0]);
    putToValue(binaireInstruction,16,tabValue[2]);
    putToValue(binaireInstruction,21,tabValue[1]);
    putToValue(binaireInstruction,26,0);
}

int binaryBEQ(int *tabValue, int *binaireInstruction)
{ 
    putToValue(binaireInstruction,0,tabValue[2]);
    putToZero(binaireInstruction,16,31);
    putToValue(binaireInstruction,16,tabValue[1]);
    putToValue(binaireInstruction,21,tabValue[0]);
    putToValue(binaireInstruction,26,4);
}

int binaryBGTZ(int *tabValue, int *binaireInstruction)
{ 
    putToValue(binaireInstruction,0,tabValue[1]);
    putToZero(binaireInstruction,16,31);
    putToValue(binaireInstruction,16,0);
    putToValue(binaireInstruction,21,tabValue[0]);
    putToValue(binaireInstruction,26,7);
}

int binaryBLEZ(int *tabValue, int *binaireInstruction)
{ 
    putToValue(binaireInstruction,0,tabValue[1]);
    putToZero(binaireInstruction,16,31);
    putToValue(binaireInstruction,16,0);
    putToValue(binaireInstruction,21,tabValue[0]);
    putToValue(binaireInstruction,26,6);
}

int binaryBNE(int *tabValue, int *binaireInstruction)
{ 
    putToValue(binaireInstruction,0,tabValue[2]);
    putToZero(binaireInstruction,16,31);
    putToValue(binaireInstruction,16,tabValue[1]);
    putToValue(binaireInstruction,21,tabValue[0]);
    putToValue(binaireInstruction,26,5);
}

int binaryDIV(int *tabValue, int *binaireInstruction)
{ 
    putToValue(binaireInstruction,0,26);
    putToValue(binaireInstruction,6,0);
    putToValue(binaireInstruction,16,tabValue[1]);
    putToValue(binaireInstruction,21,tabValue[0]);
    putToValue(binaireInstruction,26,0);
}

int binaryJ(int *tabValue, int *binaireInstruction)
{ 
    putToValue(binaireInstruction,0,tabValue[0]>>2);
    putToZero(binaireInstruction,26,31);
    putToValue(binaireInstruction,26,2);
}

int binaryJAL(int *tabValue, int *binaireInstruction)
{
    putToValue(binaireInstruction,0,tabValue[0]>>2);
    putToZero(binaireInstruction,26,31);
    putToValue(binaireInstruction,26,3);
}

int binaryJR(int *tabValue, int *binaireInstruction)
{ 
    putToValue(binaireInstruction,0,8);
    putToValue(binaireInstruction,6,0);
    putToValue(binaireInstruction,11,0);
    putToValue(binaireInstruction,21,tabValue[0]);
    putToValue(binaireInstruction,26,0);
}

int binaryLUI(int *tabValue, int *binaireInstruction)
{ 
    putToValue(binaireInstruction,0,tabValue[1]);
    putToZero(binaireInstruction,16,31);
    putToValue(binaireInstruction,16,tabValue[0]);
    putToValue(binaireInstruction,21,0);
    putToValue(binaireInstruction,26,15);
}

int binaryLW(int *tabValue, int *binaireInstruction)
{ 
    putToValue(binaireInstruction,0,tabValue[1]);
    putToZero(binaireInstruction,16,31);
    putToValue(binaireInstruction,16,tabValue[0]);
    putToValue(binaireInstruction,21,tabValue[2]);
    putToValue(binaireInstruction,26,35);
}

int binaryMFHI(int *tabValue, int *binaireInstruction)
{ 
    putToValue(binaireInstruction,0,16);
    putToValue(binaireInstruction,6,0);
    putToValue(binaireInstruction,11,tabValue[0]);
    putToValue(binaireInstruction,16,0);
    putToValue(binaireInstruction,26,0);
}

int binaryMFLO(int *tabValue, int *binaireInstruction)
{ 
    putToValue(binaireInstruction,0,18);
    putToValue(binaireInstruction,6,0);
    putToValue(binaireInstruction,11,tabValue[0]);
    putToValue(binaireInstruction,16,0);
    putToValue(binaireInstruction,26,0);
}

int binaryMULT(int *tabValue, int *binaireInstruction)
{ 
    putToValue(binaireInstruction,0,24);
    putToValue(binaireInstruction,6,0);
    putToValue(binaireInstruction,16,tabValue[1]);
    putToValue(binaireInstruction,21,tabValue[0]);
    putToValue(binaireInstruction,26,0);
}

int binaryNOP(int *tabValue, int *binaireInstruction)
{ 
    putToValue(binaireInstruction,0,0);
}

int binaryOR(int *tabValue, int *binaireInstruction)
{ 
    putToValue(binaireInstruction,0,37);
    putToValue(binaireInstruction,6,0);
    putToValue(binaireInstruction,11,tabValue[0]);
    putToValue(binaireInstruction,16,tabValue[2]);
    putToValue(binaireInstruction,21,tabValue[1]);
    putToValue(binaireInstruction,26,0);
}

int binaryROTR(int *tabValue, int *binaireInstruction)
{ 
    putToValue(binaireInstruction,0,2);
    putToValue(binaireInstruction,6,tabValue[2]);
    putToValue(binaireInstruction,11,tabValue[0]);
    putToValue(binaireInstruction,16,tabValue[1]);
    putToValue(binaireInstruction,21,1);
    putToValue(binaireInstruction,22,0);
    putToValue(binaireInstruction,26,0);
}

int binarySLL(int *tabValue, int *binaireInstruction)
{ 
    putToValue(binaireInstruction,0,0);
    putToValue(binaireInstruction,6,tabValue[2]);
    putToValue(binaireInstruction,11,tabValue[0]);
    putToValue(binaireInstruction,16,tabValue[1]);
    putToValue(binaireInstruction,21,0);
    putToValue(binaireInstruction,26,0);
}

int binarySLT(int *tabValue, int *binaireInstruction)
{ 
    putToValue(binaireInstruction,0,42);
    putToValue(binaireInstruction,6,0);
    putToValue(binaireInstruction,11,tabValue[0]);
    putToValue(binaireInstruction,16,tabValue[2]);
    putToValue(binaireInstruction,21,tabValue[1]);
    putToValue(binaireInstruction,26,0);
}

int binarySRL(int *tabValue, int *binaireInstruction)
{ 
    putToValue(binaireInstruction,0,2);
    putToValue(binaireInstruction,6,tabValue[2]);
    putToValue(binaireInstruction,11,tabValue[0]);
    putToValue(binaireInstruction,16,tabValue[1]);
    putToValue(binaireInstruction,21,0);
    putToValue(binaireInstruction,22,0);
    putToValue(binaireInstruction,26,0);
}   

int binarySUB(int *tabValue, int *binaireInstruction)
{ 
    putToValue(binaireInstruction,0,34);
    putToValue(binaireInstruction,6,0);
    putToValue(binaireInstruction,11,tabValue[0]);
    putToValue(binaireInstruction,16,tabValue[2]);
    putToValue(binaireInstruction,21,tabValue[1]);
    putToValue(binaireInstruction,26,0);
}

int binarySW(int *tabValue, int *binaireInstruction)
{ 
    putToValue(binaireInstruction,0,tabValue[1]);
    putToZero(binaireInstruction,16,31);
    putToValue(binaireInstruction,16,tabValue[0]);
    putToValue(binaireInstruction,21,tabValue[2]);
    putToValue(binaireInstruction,26,43);
}

int binarySYSCALL(int *tabValue, int *binaireInstruction)
{
    putToValue(binaireInstruction,0,12);
    putToValue(binaireInstruction,6,0);
    putToValue(binaireInstruction,26,0);
}

int binaryXOR(int *tabValue, int *binaireInstruction)
{
    putToValue(binaireInstruction,0,38);
    putToValue(binaireInstruction,6,0);
    putToValue(binaireInstruction,11,tabValue[0]);
    putToValue(binaireInstruction,16,tabValue[2]);
    putToValue(binaireInstruction,21,tabValue[1]);
    putToValue(binaireInstruction,26,0);
}

int convertBinaireIntoHex(int *binaireInstruction, int *hexadecimalInstruction)
{
    int i, j, n = 31;
    for(i=7; i>=0; i--)
    {
        for(j=0; j<=3; j++)
        {
            hexadecimalInstruction[i] += (int) (pow(2, j) * binaireInstruction[n]);
            n--;
        }
    }
    return 0;
}


