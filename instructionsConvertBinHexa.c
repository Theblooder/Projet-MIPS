#include "instructionsConvertBinHexa.h"
#include <math.h>
#include <string.h>
#include <stdio.h>



int createBinaryInstruction(int operation, int *tabValue, int *binaireInstruction)
{

    if(operation == 1)           binaryADD(tabValue, binaireInstruction);
    else if(operation == 2)     binaryADDI(tabValue, binaireInstruction);
    else if(operation == 3)      binaryAND(tabValue, binaireInstruction);
    else if(operation == 4)      binaryBEQ(tabValue, binaireInstruction);
    else if(operation == 5)     binaryBGTZ(tabValue, binaireInstruction);
    else if(operation == 6)     binaryBLEZ(tabValue, binaireInstruction);
    else if(operation == 7)      binaryBNE(tabValue, binaireInstruction);
    else if(operation == 8)      binaryDIV(tabValue, binaireInstruction);
    else if(operation == 9)        binaryJ(tabValue, binaireInstruction);
    else if(operation == 10)      binaryJAL(tabValue, binaireInstruction);
    else if(operation == 11)       binaryJR(tabValue, binaireInstruction);
    else if(operation == 12)      binaryLUI(tabValue, binaireInstruction);
    else if(operation == 13)       binaryLW(tabValue, binaireInstruction);
    else if(operation == 14)     binaryMFHI(tabValue, binaireInstruction);
    else if(operation == 15)     binaryMFLO(tabValue, binaireInstruction);
    else if(operation == 16)     binaryMULT(tabValue, binaireInstruction);
    else if(operation == 17)      binaryNOP(tabValue, binaireInstruction);
    else if(operation == 18)       binaryOR(tabValue, binaireInstruction);
    else if(operation == 19)     binaryROTR(tabValue, binaireInstruction);
    else if(operation == 20)      binarySLL(tabValue, binaireInstruction);
    else if(operation == 21)      binarySLT(tabValue, binaireInstruction);
    else if(operation == 22)      binarySRL(tabValue, binaireInstruction);
    else if(operation == 23)      binarySUB(tabValue, binaireInstruction);
    else if(operation == 24)       binarySW(tabValue, binaireInstruction);
    else if(operation == 25)  binarySYSCALL(tabValue, binaireInstruction);
    else if(operation == 26)      binaryXOR(tabValue, binaireInstruction);

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
        i = start;
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
    for(i=31; i>=0; i--)  
    {  
        if(i%4 == 0) printf(" ");
        printf("%d", binaireInstruction[i]);  
    }

    printf("\n");

    return 0;
}

int displayHexadecimal(int *hexadecimalInstruction)
{
    int i;
    //printf("Hexadecimal :");
    for(i=8; i>=1; i--)  
    {  
        if(i%2 == 0) printf(" ");
        printf("%x", hexadecimalInstruction[i-1]);  
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
    putToZero(binaireInstruction,11,31);
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
    putToZero(binaireInstruction,11,31);
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
    putToZero(binaireInstruction,11,31);
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
    int i, j, n = 0;
    for(i=0; i<8; i++)
    {
        for(j=0; j<=3; j++)
        {
            hexadecimalInstruction[i] += (int) (pow(2, j) * binaireInstruction[n]);
            n++;
        }
    }
    return 0;
}


