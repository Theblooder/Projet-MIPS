#include "instructionsConvertBinHexa.h"
#include <math.h>
#include "stdio.h"

int instructionValue(const char *instruction, int *tabValues)
{
    int i = 0; int j; int indiceValue = 0; int lengthValue = 1; int k; int numberOfValues = 3;/*Pour limiter l'écriture de seulement 3 valeurs max dans le tableau de value */

    while(instruction[i] != '\0' && numberOfValues != 0) {
        if(instruction[i] == ' ') {
            if(instruction[i+1] == '$') {
                j = i+2;
            }
            else {
                j = i+1;
            }
            int temp = j;
            while(instruction[temp+1] != ' ' && instruction[temp+1] != '\0') {
                lengthValue += 1;
                temp++;
            }
            tabValues[indiceValue] = 0;
            for(k=lengthValue; k>0; k--) {
                tabValues[indiceValue] += (int) (instruction[j]-48) * pow(10, k-1);
                j++;
            }
            numberOfValues--;
            indiceValue++;
            lengthValue = 1;
        }
        i++;
    }
    return 0;
}



int convertIntoBinaireADD(const char *instruction, char *binnaire)
{
    int rs, rt, rd;

    int i;
}