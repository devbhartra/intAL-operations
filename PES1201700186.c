#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "intal.h"

// pads extra 0s and converts to int
static int *char2int(const char *arr, int greater, int size)
{
    int *intArr;
    intArr = (int *)calloc(greater+1, sizeof(int));
    // printf(" ");
    int start = greater - size;
    int j = 0;
    for(int i = start; i <= greater; i++){
        intArr[i] = arr[j] - '0';
        j++;
    }
    return intArr; // returns padded array in int form
}

static char *int2char(int *arr, int size){
    char *charArr;
    charArr = (char *)malloc(size*sizeof(char));
    for(int i = 0; i < size; i++){
        charArr[i] = arr[i] + '0';
    }
    return charArr;
}

char *intal_add(const char *intal1, const char *intal2)
{
    /*['2','1'] + ['1','2','3'] = ['1','2','4']
    Need to convert the ascii to integer (Subtract - '0')
    */
    int size1 = strlen(intal1);
    int size2 = strlen(intal2);

    // make these a macro ->
    int greater = (size1 > size2) ? size1 : size2;

    // int diff = greater - smaller; // Append these many 0s to smaller number

    int *intArr1;
    intArr1 = char2int(intal1, greater, size1);
    int *intArr2;
    intArr2 = char2int(intal2, greater, size2);

    // both char intals are now int arrays

    int *sumArr;
    sumArr = (int *)calloc((greater + 1), sizeof(int)); // need to strip
    for(int i = 0; i < greater+1; i++){
        printf("%d", sumArr[i]);
    }
    printf("\n");
    for(int i = 0; i < greater; i++){
        printf("%d", intArr1[i]);
    }
    printf("\n");
    for(int i = 0; i < greater; i++){
        printf("%d", intArr2[i]);
    }
    printf("\n");

    // main adding logic
    int carry = 0;
    int sum;
    for(int i = greater; i >= 0; i--)
    {
        sum = (intArr1[i]) + (intArr2[i]) + carry;
        sumArr[i] = sum % 10;
        carry = sumArr[i] / 10;
    }
    for(int i = 0; i < greater; i++){
        printf("%d", sumArr[i]);
    }

    char *charArr = (char*)malloc(greater*sizeof(char));
    charArr = int2char(sumArr, greater);
    return charArr;
}
