#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "intal.h"

#define MAX(x, y) ((x > y) ? x : y)

// pads extra 0s and converts to int
static int *char2int(const char *arr, int greater, int size)
{
    int *intArr;
    intArr = (int *)calloc(greater + 1, sizeof(int));
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

char *intal_multiply(const char *intal1, const char *intal2)
{

    int size1 = strlen(intal1);
    int size2 = strlen(intal2);

    int greater = MAX(size1, size2);

    int *intArr1;
    intArr1 = char2int(intal1, greater, size1);
    int *intArr2;
    intArr2 = char2int(intal2, greater, size2);

    int total = size2 + size1;
    int *prodArr;
    prodArr = (int *)malloc(total * sizeof(int)); // need to strip

    // both char intals are now int arrays
    int carry = 0;
    // int x = total - 1;
    // int shift = 0;
    // int prod;

    // intal1 is bigger
    // if (greater == size1)
    // {
    // int limit = greater - size2;
    for (int i = greater - 1; i >= 0; i--) // the number below (intArr2)
    {
        for (int j = greater - 1; j >= 0; j--)
        { // the number on top (intArr1)
            prodArr[i + j] = prodArr[i + j] + (intArr2[i] * intArr1[j]);
        }
    }
    // }
    for (int i = 0; i <= total; i++)
    {
        printf("%d ", prodArr[i]);
    }

    int *resArray = (int *)malloc(total * sizeof(int));
    for (int i = total; i >= 0; i--)
    {
        resArray[i] = (prodArr[i] % 10) + carry;
        carry = prodArr[i] / 10;
    }
    // for (int i = total; i >= 0; i--)
    // {
    //     int digit = prodArr[i] % 10;
    //     int carry = prodArr[i] / 10;
    //     if ((i + 1) < total)
    //     {
    //         prodArr[i + 1] += carry;
    //     }
    //     resArray[i] += digit;
    // }

    printf("\n");
    for (int i = 0; i <= total; i++)
    {
        printf("%d ", resArray[i]);
    }
    printf("\n");

    // char *charArr = (char *)malloc(greater * sizeof(char));
    // charArr = int2char(prodArr, greater);
    // if (strlen(charArr) > 0 && charArr[0] == '0')
    // {
    //     charArr += 1;
    // }
    return " ";
}