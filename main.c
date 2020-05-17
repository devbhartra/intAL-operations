#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "intal.h"

// Returns the sum of two intals.
char *intal_add(const char *intal1, const char *intal2)
{
    /*['2','1'] + ['1','2','3'] = ['1','2','4']
    Need to convert the ascii to integer (Subtract - '0')
    */
    int size1 = strlen(intal1);
    int size2 = strlen(intal2);
    char *s1;
    char *s2;
    s1 = (char *)malloc(size1 * sizeof(char));
    s2 = (char *)malloc(size2 * sizeof(char));

    // int greater;
    // (size1 > size2) ?  (greater = size1) : (greater = size2);
    for (int i = 0; i < strlen(intal1); i++)
    {
        strncat(s1, &intal1[i], 1);
    }
    for (int j = 0; j < strlen(intal2); j++)
    {
        strncat(s2, &intal2[j], 1);
    }
    int sum = atoi(s1) + atoi(s2);

    char *arr;
    arr = (char *)malloc((size1 + size2) * sizeof(char));

    // converting int to char array
    sprintf(arr, "%d", sum);
    // printf("%s", arr);
    return arr;
}

int intal_compare(const char *intal1, const char *intal2)
{
    int size1 = strlen(intal1);
    int size2 = strlen(intal2);
    char *s1;
    char *s2;
    s1 = (char *)malloc(size1 * sizeof(char));
    s2 = (char *)malloc(size2 * sizeof(char));

    // int greater;
    // (size1 > size2) ?  (greater = size1) : (greater = size2);
    for (int i = 0; i < strlen(intal1); i++)
    {
        strncat(s1, &intal1[i], 1);
    }
    for (int j = 0; j < strlen(intal2); j++)
    {
        strncat(s2, &intal2[j], 1);
    }

    int num1 = atoi(s1);
    int num2 = atoi(s2);

    if (num1 == num2)
    {
        return 0;
    }
    else if (num1 > num2)
    {
        return 1;
    }
    else
    {
        return -1;
    }

    // char *arr;
    // arr = (char *)malloc((size1 + size2) * sizeof(char));

    // // converting int to char array
    // sprintf(arr, "%d", comp);
    // // printf("%s", arr);
    // return arr;
}

// Returns the absolute difference of two intals.
char *intal_diff(const char *intal1, const char *intal2)
{
    /*['2','1'] + ['1','2','3'] = ['1','2','4']
    Need to convert the ascii to integer (Subtract - '0')
    */
    int size1 = strlen(intal1);
    int size2 = strlen(intal2);
    char *s1;
    char *s2;
    s1 = (char *)malloc(size1 * sizeof(char));
    s2 = (char *)malloc(size2 * sizeof(char));

    // int greater;
    // (size1 > size2) ?  (greater = size1) : (greater = size2);
    for (int i = 0; i < strlen(intal1); i++)
    {
        strncat(s1, &intal1[i], 1);
    }
    for (int j = 0; j < strlen(intal2); j++)
    {
        strncat(s2, &intal2[j], 1);
    }
    int diff = abs(atoi(s1) - atoi(s2));

    char *arr;
    arr = (char *)malloc((size1 + size2) * sizeof(char));

    // converting int to char array
    sprintf(arr, "%d", diff);
    // printf("%s", arr);
    return arr;
}

// return the product of 2 instals
char *intal_multiply(const char *intal1, const char *intal2)
{
    int size1 = strlen(intal1);
    int size2 = strlen(intal2);
    char *s1;
    char *s2;
    s1 = (char *)malloc(size1 * sizeof(char));
    s2 = (char *)malloc(size2 * sizeof(char));

    for (int i = 0; i < strlen(intal1); i++)
    {
        strncat(s1, &intal1[i], 1);
    }
    for (int j = 0; j < strlen(intal2); j++)
    {
        strncat(s2, &intal2[j], 1);
    }
    int product = atoi(s1) * atoi(s2);

    char *arr;
    arr = (char *)malloc((size1 + size2) * sizeof(char));

    // converting int to char array
    sprintf(arr, "%d", product);
    return arr;
}

// Driver to test the above functions, remove before submission!!
// int main()
// {
//     char intal1[] = {'1', '2', '\0'};
//     char intal2[] = {'3', '7', '4', '\0'};
//     char intal3[] = {'3', '5', '\0'};
//     char intal4[] = {'3', '5', '\0'};

//     char *temp1 = intal_add(intal1, intal2);
//     printf("%s", temp1);


//     // char *temp2 = intal_diff(intal3, intal4);
//     // printf("%s", temp2);

//     // int compare = intal_compare(intal1, intal4);
//     // printf("%d", compare);

//     // char *temp3 = intal_multiply(intal1, intal4);
//     // printf("%s", temp3);
//     return 0;
// }