#include "instructionsConvertBinHexa.h"
#include <math.h>
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




int convertBinaireIntoHex(const char *binnaire, char *hex)
{

}


int convertIntoBinaireADD(char *binnaire, int *tabValue)
{
    int rs, rt, rd;

    int i;
}