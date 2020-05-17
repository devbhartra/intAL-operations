#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// greater is max size, size is actual size
static int *conv2int(const char *arr, int greater, int size)
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

int main()
{
    char charArr[4] = {'1', '2', '3', '4'};
    int *intArr;
    intArr = conv2int(charArr,10,4);
    for(int i = 0; i < 10; i++){
        printf("%d", intArr[i]);
    }
}