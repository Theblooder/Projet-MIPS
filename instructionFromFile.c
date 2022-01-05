#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "instructionFromFile.h"

int _main_(char *instruction, char *cleanInstruction, int *values, int *operation, int numberOfRow)
{
    int lengthInstruction = 0;
    int nbrRegOff[2];
    int currentPosition;
    int isError = 0;

    lengthInstruction = cleanInstructionReturnLength(instruction, cleanInstruction);
    // printf("ins:%s:\n", instruction);
    // printf("clean ins:%s:\n", cleanInstruction);
    // printf("%d\n", lengthInstruction);

    
    currentPosition = getOperation(cleanInstruction, nbrRegOff, operation);
    if(*operation == 0) {
        if(strlen(cleanInstruction) != 0) {
            printf("ERROR : row %d : wrong argument\n", numberOfRow);
        }
        isError = 1;
    }
    // printf("operation :%d:\n", operation);
    // printf("pos :%d\n", currentPosition);
    // printf("reg :%d\n", nbrRegOff[0]);
    // printf("off :%d\n", nbrRegOff[1]);

    int number;

    if(*operation == 13 || *operation == 24) {
        if(currentPosition < lengthInstruction) {
            number = getRegisterOffset(cleanInstruction, &currentPosition, 1, &isError);
        }
        if(!isError) {
            values[0] = number;
        }
        if(currentPosition < lengthInstruction) {
            number = getRegisterOffset(cleanInstruction, &currentPosition, 0, &isError);
        }
        if(!isError) {
            values[1] = number;
        }
        if(currentPosition < lengthInstruction) {
            number = getRegisterOffset(cleanInstruction, &currentPosition, 1, &isError);
        }
        if(!isError) {
            values[2] = number;
        }
        if(isError) {
            printf("ERROR row %d: register or offset value is wrong or missing\n", numberOfRow);
        }
    }
    else {
        for(int k=0; k<nbrRegOff[0]; k++) {
            if(currentPosition < lengthInstruction) {
                number = getRegisterOffset(cleanInstruction, &currentPosition, 1, &isError);
            }
            else {
                printf("ERROR row %d: register value (n°%d) is missing\n", numberOfRow, k+1);
                isError = 1;
                break;
            }

            if(isError) {
                printf("ERROR row %d: wrong register value (n°%d)\n", numberOfRow, k+1);
                break;
            }
            else {
                values[k] = number;
            }
        }
        for(int k=0; k<nbrRegOff[1]; k++) {
            if(currentPosition < lengthInstruction) {
                number = getRegisterOffset(cleanInstruction, &currentPosition, 0, &isError);
            }
            else {
                printf("ERROR row %d: offset value (n°%d) is missing\n", numberOfRow, k+1);
                isError = 1;
                break;
            }

            if(isError) {
                printf("ERROR row %d: wrong offset value (n°%d)\n", numberOfRow, k+1);
                break;
            }
            else {
                values[nbrRegOff[0]+k] = number;
            }
        }
    }

    // printf("%d\n", values[0]);
    // printf("%d\n", values[1]);
    // printf("%d\n", values[2]);

    return isError;
}


int cleanInstructionReturnLength(const char *instruction, char *clearInstruction)
{
    int i = 0;  /*Index instruction*/
    int j = 0;  /*Index clearInstruction*/
    int insBegin = 0;
    int firstSpace = 1;

    while(instruction[i] != '\0' && instruction[i] != '#') {
        if(!insBegin) {
            if(instruction[i] != ' ') {
                insBegin = 1;
            }
        }
        if(insBegin) {
            if(instruction[i] != ' ') {
                clearInstruction[j++] = instruction[i];
            }
            else {
                if(firstSpace) {
                    clearInstruction[j++] = instruction[i];
                    firstSpace = 0;
                }
            }
        }
        i++;
    }
    clearInstruction[j] = '\0';
    
    return strlen(clearInstruction);
}

int isTexteEqual(char *operation, char *Texte)
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

int getOperation(const char *instruction, int *numberRegisterOffset, int *INToperation)
{
    int i = 0;
    char operation[10];

    while(instruction[i] != '\0' && instruction[i] != ' ' && i < 9) {
        operation[i] = instruction[i];
        i++;
    }
    operation[i] = '\0';

    if(isTexteEqual(operation, "ADD"))           {*INToperation = 1; numberRegisterOffset[0] = 3; numberRegisterOffset[1] = 0;}
    else if(isTexteEqual(operation, "ADDI"))     {*INToperation = 2; numberRegisterOffset[0] = 2; numberRegisterOffset[1] = 1;}
    else if(isTexteEqual(operation, "AND"))      {*INToperation = 3; numberRegisterOffset[0] = 3; numberRegisterOffset[1] = 0;}
    else if(isTexteEqual(operation, "BEQ"))      {*INToperation = 4; numberRegisterOffset[0] = 2; numberRegisterOffset[1] = 1;}
    else if(isTexteEqual(operation, "BGTZ"))     {*INToperation = 5; numberRegisterOffset[0] = 1; numberRegisterOffset[1] = 1;}
    else if(isTexteEqual(operation, "BLEZ"))     {*INToperation = 6; numberRegisterOffset[0] = 1; numberRegisterOffset[1] = 1;}
    else if(isTexteEqual(operation, "BNE"))      {*INToperation = 7; numberRegisterOffset[0] = 2; numberRegisterOffset[1] = 1;}
    else if(isTexteEqual(operation, "DIV"))      {*INToperation = 8; numberRegisterOffset[0] = 2; numberRegisterOffset[1] = 0;}
    else if(isTexteEqual(operation, "J"))        {*INToperation = 9; numberRegisterOffset[0] = 0; numberRegisterOffset[1] = 1;}
    else if(isTexteEqual(operation, "JAL"))      {*INToperation = 10; numberRegisterOffset[0] = 0; numberRegisterOffset[1] = 1;}
    else if(isTexteEqual(operation, "JR"))       {*INToperation = 11; numberRegisterOffset[0] = 1; numberRegisterOffset[1] = 0;}
    else if(isTexteEqual(operation, "LUI"))      {*INToperation = 12; numberRegisterOffset[0] = 1; numberRegisterOffset[1] = 1;}
    else if(isTexteEqual(operation, "LW"))       {*INToperation = 13; numberRegisterOffset[0] = 2; numberRegisterOffset[1] = 1;}
    else if(isTexteEqual(operation, "MFHI"))     {*INToperation = 14; numberRegisterOffset[0] = 1; numberRegisterOffset[1] = 0;}
    else if(isTexteEqual(operation, "MFLO"))     {*INToperation = 15; numberRegisterOffset[0] = 1; numberRegisterOffset[1] = 0;}
    else if(isTexteEqual(operation, "MULT"))     {*INToperation = 16; numberRegisterOffset[0] = 2; numberRegisterOffset[1] = 0;}
    else if(isTexteEqual(operation, "NOP"))      {*INToperation = 17; numberRegisterOffset[0] = 0; numberRegisterOffset[1] = 0;}
    else if(isTexteEqual(operation, "OR"))       {*INToperation = 18; numberRegisterOffset[0] = 3; numberRegisterOffset[1] = 0;}
    else if(isTexteEqual(operation, "ROTR"))     {*INToperation = 19; numberRegisterOffset[0] = 2; numberRegisterOffset[1] = 1;}
    else if(isTexteEqual(operation, "SLL"))      {*INToperation = 20; numberRegisterOffset[0] = 2; numberRegisterOffset[1] = 1;}
    else if(isTexteEqual(operation, "SLT"))      {*INToperation = 21; numberRegisterOffset[0] = 3; numberRegisterOffset[1] = 0;}
    else if(isTexteEqual(operation, "SRL"))      {*INToperation = 22; numberRegisterOffset[0] = 2; numberRegisterOffset[1] = 1;}
    else if(isTexteEqual(operation, "SUB"))      {*INToperation = 23; numberRegisterOffset[0] = 3; numberRegisterOffset[1] = 0;}
    else if(isTexteEqual(operation, "SW"))       {*INToperation = 24; numberRegisterOffset[0] = 2; numberRegisterOffset[1] = 1;}
    else if(isTexteEqual(operation, "SYSCALL"))  {*INToperation = 25; numberRegisterOffset[0] = 0; numberRegisterOffset[1] = 0;}
    else if(isTexteEqual(operation, "XOR"))      {*INToperation = 26; numberRegisterOffset[0] = 3; numberRegisterOffset[1] = 0;}
    else {
        //printf("Opération non reconnu\n");
        *INToperation = 0;
        i = 0;
    }
    return i;
}

int getRegisterOffset(char *instruction, int *currentPosition, int regValue, int *isError)
{
    int j;
    int number = 0;
    int isNegative = 0;

    if(regValue) {
        if(instruction[*currentPosition+1] == '$') {
            j = *currentPosition + 2;
        }
        else {
            *isError = 1;
            return -1;
        }
    }
    else {
        if(instruction[*currentPosition+1] == '-') {
            j = *currentPosition + 2;
            isNegative = 1;
        }
        else {
            j = *currentPosition + 1;
        }
    }

    for(; instruction[j] >= 48 && instruction[j] <= 57; j++) {
        number *= 10;
        number += instruction[j] - 48;
    }
    if(instruction[j] != ',' && instruction[j] != '\0' && instruction[j] != '(' && instruction[j] != ')') {
        *isError = 1;
        return -1;
    }
    else {
        *currentPosition = j;
    }

    if(isNegative) {
        number *= -1;
    }

    return number;
}