#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "intal.h"

#define MAX(x, y) ((x > y) ? x : y)
#define MAXIMUM 1001

static int getMin(unsigned int a, unsigned int b)
{
    return (a >= b) ? b : a;
}

void swap(char *a, char *b)
{

    char *temp = malloc(10000);
    strcpy(temp, a);
    strcpy(a, b);
    strcpy(b, temp);
}

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
    sumArr = (int *)calloc((greater + 1), sizeof(int));

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
    // for (int i = 0; i < greater + 1; i++)
    // {
    //     printf("%d", sumArr[i]);
    // }

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
    int len = size1 + size2;
    int *arr = (int *)malloc(sizeof(int) * len); //the number of digits of the result - len is the top;
    memset(arr, 0, sizeof(int) * len);
    for (int i = size1 - 1; i > -1; i--)
        for (int j = size2 - 1; j > -1; j--)
            arr[i + j + 1] += (intal1[i] - '0') * (intal2[j] - '0'); //collect result of each position;
    for (int i = len - 1; i > 0; i--)                                //restore the carry for each position and get the final result;
    {
        arr[i - 1] += arr[i] / 10;
        arr[i] %= 10;
    }
    char *s = (char *)malloc(sizeof(char) * (len + 1)); //converting the digits result to string;
    int index = 0;
    int i = 0;
    if (arr[i] == 0)
        i++; //in case the zero position has no carry, if it does, ignore it;
    while (i < len)
        s[index++] = arr[i++] + '0';
    s[index] = '\0';
    return s;
}

char *intal_pow(const char *intal1, unsigned int n)
{
    if (n == 0)
    {
        char *resArr = (char *)malloc(1 * sizeof(char));
        strcpy(resArr, "1");
        return resArr;
    }
    char *temp, *resArr;
    temp = intal_pow(intal1, n / 2);
    if (n % 2 == 0)
    {
        resArr = intal_multiply(temp, temp);
        strcpy(temp, resArr);
        // free(temp);
        return temp;
    }
    else
    {
        temp = intal_multiply(temp, temp);
        resArr = intal_multiply(intal1, temp);
        strcpy(temp, resArr);
        // free(temp);
        free(resArr);
        return temp;
    }
}

/*
char *intal_fibonacci(unsigned int n)
{
    char *prev_2, *prev_1, *res, *t;
    
    prev_2 = (char*)malloc(sizeof(char)*2);
    prev_2[0] = '0';
    prev_2[1] = '\0';

    if(n==0)
        return prev_2;


    prev_1 = (char*)malloc(sizeof(char)*2);
    prev_1[0] = '1';
    prev_1[1] = '\0';

    if(n==1)
        return prev_1;

    int i = 2;
    while(i<=n){
        res = intal_add(prev_2,prev_1);
        t = prev_2;
        prev_2 = prev_1;
        prev_1 = res;
        free(t);
        i+=1;
    }

    //free up any extra allocated memory
    free(prev_2);
    //cant free prev1 becuase it points to res

    return res;
}

char* intal_mod(const char* intal1, const char* intal2){

}

char* intal_gcd(const char* intal1, const char* intal2){
    // if both are 0, return 0
    if(strcmp(intal1, "0") && strcmp(intal2, "0")){
        char* temp = (char*)malloc(1 * sizeof(char));
        strcpy(temp, "0");
        return(temp);
    }

}
*/

char *intal_factorial(unsigned int n)
{
    if (n == 0 || n == 1)
    {
        char *res = (char *)malloc(1 * sizeof(char));
        strcpy(res, "1");
        return res;
    }
    int i = 2;
    char *t1, *t2, *res, *add_one, *next_num;

    //a constant '1' to add to the previous number, to obtain next intal number
    add_one = (char *)malloc(sizeof(char) * 2);
    strcpy(add_one, "1\0");

    //the next number to be multiplied in to the resulting factorial
    next_num = (char *)malloc(sizeof(char) * 2);
    strcpy(next_num, "1\0");

    //actual factorial result over the n iterations
    res = (char *)malloc(sizeof(char) * 2);
    strcpy(res, "1\0");

    while (i <= n)
    {
        t1 = intal_add(next_num, add_one);
        t2 = next_num;
        next_num = t1;

        t1 = intal_multiply(res, next_num);
        t2 = res;
        res = t1;

        i += 1;
    }

    return res;
}

char *intal_bincoeff(unsigned int n, unsigned int k)
{
    char **array = (char **)malloc(sizeof(char *) * (k + 1));
    //array of size k, initally all values 0
    for (int i = 0; i <= k; i++)
    {
        array[i] = (char *)malloc(sizeof(char *) * MAXIMUM);
        strcpy(array[i], "0");
    }
    strcpy(array[0], "1"); //C(n,0) = 1

    char *t, *res;

    for (int i = 1; i <= n; i++)
    {
        for (int j = getMin(i, k); j > 0; j--)
        {
            t = intal_add(array[j], array[j - 1]);
            strcpy(array[j], t);
        }
    }

    res = strdup(array[k]);
    for (int i = 0; i <= k; i++)
    {
        free(array[i]);
    }
    free(array);
    return res;
}

int intal_max(char **arr, int n)
{
    char *max = (char *)malloc(MAXIMUM * sizeof(char));
    // assuming the 1st intal to be the max
    strcpy(max, arr[0]);
    int pos = 0;
    // start loop from next element
    for (int i = 1; i < n; i++)
    {
        if (intal_compare(arr[i], max) == 1){
            strcpy(max, arr[i]);
            pos = i;
        } // the number is greater, need to swap
    }
    return pos;
}

int intal_min(char **arr, int n){
    char *min = (char *)malloc(MAXIMUM * sizeof(char));
    // assuming the 1st intal to be the max
    strcpy(min, arr[0]);
    int pos = 0;
    // start loop from next element
    for (int i = 1; i < n; i++)
    {
        if (intal_compare(arr[i], min) == -1){
            strcpy(min, arr[i]);
            pos = i;
        } // the number is greater, need to swap
    }
    return pos;
}

int intal_search(char **arr, int n, const char* key){
    int pos = -1;
    char *intalKey = (char *)malloc(MAXIMUM * sizeof(char));
    strcpy(intalKey, key);
    for(int i = 0; i < n; i++){
        if(intal_compare(intalKey,arr[i]) == 0){
            pos = i;
            break;
        }
    }
    return pos;

}