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
    sprintf(arr, "%ld", sum);
    // printf("%s", arr);
    return arr;
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
    sprintf(arr, "%ld", diff);
    // printf("%s", arr);
    return arr;
}

int main()
{
    char intal1[] = {'1', '2', '\0'};
    char intal2[] = {'3', '7', '4', '\0'};
    char intal3[] = {'3', '5', '\0'};
    char intal4[] = {'3', '5', '\0'};

    // char *temp1 = intal_add(intal1, intal2);
    // printf("%s", temp1);
    // printf("%d", sum);

    char *temp2 = intal_diff(intal3, intal4);
    printf("%s", temp2);
    return 0;
}