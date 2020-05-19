#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "intal.h"

#define MAX(x, y) ((x > y) ? x : y)

// pads extra 0s and converts to int
static int *char2int(const char *arr, int greater, int size)
{
    int *intArr;
    intArr = (int *)calloc(greater, sizeof(int));
    // printf(" ");
    int start = greater - size;
    int j = 0;
    for (int i = start; i <= greater; i++)
    {
        intArr[i] = arr[j] - '0';
        j++;
    }
    return intArr; // returns padded array in int form
}

static char *int2char(int *arr, int size)
{
    char *charArr;
    charArr = (char *)malloc(size * sizeof(char));
    for (int i = 0; i < size; i++)
    {
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

    int greater = MAX(size1, size2);

    int *intArr1;
    intArr1 = char2int(intal1, greater, size1);
    int *intArr2;
    intArr2 = char2int(intal2, greater, size2);

    // both char intals are now int arrays

    int *sumArr;
    sumArr = (int *)calloc((greater + 1), sizeof(int)); /// need to strip
    printf("Sumarray: ");
    for (int i = 0; i < greater + 1; i++)
    {
        printf("%d", sumArr[i]);
    }
    printf("\n");
    for (int i = 0; i < greater; i++)
    {
        printf("%d", intArr1[i]);
    }
    printf("\n");
    for (int i = 0; i < greater; i++)
    {
        printf("%d", intArr2[i]);
    }
    printf("\n");

    // main adding logic
    int carry = 0;
    int sum = 0;
    int j = greater;
    for (int i = greater - 1; i >= 0; i--)
    {
        sum = (intArr1[i]) + (intArr2[i]) + carry;
        sumArr[j] = sum % 10;
        carry = sum / 10;
        j--;
    }
    if (carry > 0)
    {
        sumArr[0] = carry;
    }
    for (int i = 0; i < greater + 1; i++)
    {
        printf("%d", sumArr[i]);
    }

    char *charArr = (char *)malloc(greater * sizeof(char));
    charArr = int2char(sumArr, greater + 1);
    if (charArr[0] == '0')
    {
        charArr += 1;
    }
    return charArr;
}

int intal_compare(const char *intal1, const char *intal2)
{
    int size1 = strlen(intal1);
    int size2 = strlen(intal2);

    int greater = MAX(size1, size2);

    int *intArr1;
    intArr1 = char2int(intal1, greater, size1);
    int *intArr2;
    intArr2 = char2int(intal2, greater, size2);
    // both char intals are now int arrays
    int flag = 0;
    for (int i = 0; i < greater; i++)
    {
        if (intArr1[i] == intArr2[i])
        {
            continue;
        }
        else if (intArr1[i] > intArr2[i])
        {
            flag = 1;
            break;
        }
        else
        {
            flag = -1;
            break;
        }
    }
    return flag;
}

char *intal_diff(const char *intal1, const char *intal2)
{
    int size1 = strlen(intal1);
    int size2 = strlen(intal2);

    int greater = MAX(size1, size2);
    int *intArr1;
    intArr1 = char2int(intal1, greater, size1);
    int *intArr2;
    intArr2 = char2int(intal2, greater, size2);

    // both char intals are now int arrays

    int *diffArr;
    diffArr = (int *)calloc((greater), sizeof(int)); // need to strip
    printf("Diffarray: ");
    for (int i = 0; i < greater; i++)
    {
        printf("%d", diffArr[i]);
    }
    printf("\n");
    for (int i = 0; i < greater; i++)
    {
        printf("%d", intArr1[i]);
    }
    printf("\n");
    for (int i = 0; i < greater; i++)
    {
        printf("%d", intArr2[i]);
    }
    printf("\n");

    // main difference logic
    int diff = 0;

    // find bigger number:
    int comp = intal_compare(intal1, intal2);

    if (comp == 1)
    {
        for (int i = greater - 1; i >= 0; i--)
        {
            diff = intArr1[i] - intArr2[i];
            if (diff < 0)
            {
                intArr1[i] += 10;
                intArr1[i - 1] -= 1;
                diff = intArr1[i] - intArr2[i];
            }
            diffArr[i] = diff;
        }
    }
    // both are equal
    else if (comp == 0)
    {
        diffArr[0] = 0;
    }
    // intal2 is greater
    else
    {
        for (int i = greater - 1; i >= 0; i--)
        {
            diff = intArr2[i] - intArr1[i];
            if (diff < 0)
            {
                intArr2[i] += 10;
                intArr2[i - 1] -= 1;
                diff = intArr2[i] - intArr1[i];
            }
            diffArr[i] = diff;
        }
    }
    for (int i = 0; i < greater + 1; i++)
    {
        printf("%d", diffArr[i]);
    }

    char *charArr = (char *)malloc(greater * sizeof(char));
    charArr = int2char(diffArr, greater);
    if (strlen(charArr) > 0 && charArr[0] == '0')
    {
        charArr += 1;
    }
    return charArr;
    // return diffArr;
}

/*
char *intal_multiply(const char *intal1, const char *intal2)
{
    int size1 = strlen(intal1);
    int size2 = strlen(intal2);

    int greater = MAX(size1, size2);

    int *intArr1;
    intArr1 = char2int(intal1, greater, size1);
    int *intArr2;
    intArr2 = char2int(intal2, greater, size2);

    // printf("Num1--->  ");
    // for (int i = 0; i < greater; i++)
    // {
    //     printf("%d ", intArr1[i]);
    // }
    // printf("\n");

    // printf("Num2--->  ");
    // for (int i = 0; i < greater; i++)
    // {
    //     printf("%d ", intArr2[i]);
    // }
    // printf("\n");

    int total = size2 + size1;
    // printf("Total num --> %d \n", total);
    int *prodArr;
    prodArr = (int *)malloc((total) * sizeof(int)); // need to strip

    printf("prodArr elements--->  ");
    for (int i = greater - 1; i >= 0; i--) // the number below (intArr2)
    {
        for (int j = greater - 1; j >= 0; j--)
        { // the number on top (intArr1)
            prodArr[i + j] = prodArr[i + j] + (intArr2[i] * intArr1[j]);
            printf("%d ", prodArr[i+j]);
        }
    }
    printf("\n");
    printf("Final prodarray--->   ");
    for (int i = total - 1; i >= 0; i--)
    {
        printf("%d ", prodArr[i]);
    }
    printf("\n");

    int carry = 0;
    int *resArray = (int *)malloc(total * sizeof(int));
    for (int i = total-1; i >= 0; i--)
    {
        int prod = (prodArr[i] + carry) % 10;
        carry = prodArr[i] / 10;
        resArray[i] = prod;
    }

    printf("\n");
    printf("Resarr--->  ");
    for (int i = 0; i <= total; i++)
    {
        printf("%d ", resArray[i]);
    }
    printf("\n");

    char *charArr = (char *)malloc(total * sizeof(char));
    charArr = int2char(resArray, greater);
    // if (strlen(charArr) > 0 && charArr[0] == '0')
    // {
    //     charArr += 1;
    // }
    return charArr;
}
*/

char *intal_multiply(const char *intal1, const char *intal2){

    int len1 = strlen(intal1);
    int len2 = strlen(intal2);
    int len  = len1 + len2;
    int *arr = (int*)malloc(sizeof(int)*len); //the number of digits of the result - len is the top;
    memset(arr, 0, sizeof(int)*len); //this is critical;
    for(int i=len1-1; i > -1; i--)
        for(int j=len2-1; j > -1; j--)
            arr[i+j+1] += (intal1[i]-'0')*(intal2[j]-'0'); //collect result of each position;
    for(int i=len-1; i > 0; i--) //restore the carry for each position and get the final result;
    {
        arr[i-1] += arr[i]/10;
        arr[i] %= 10;
    }
    char *s = (char*)malloc(sizeof(char)*(len+1)); //converting the digits result to string;
    int index = 0;
    int i = 0;
    if(arr[i]==0) i++; //in case the zero position has no carry, if it does, ignore it;
    while(i < len)
        s[index++] = arr[i++]+'0';
    s[index] = '\0';
    return s;

}