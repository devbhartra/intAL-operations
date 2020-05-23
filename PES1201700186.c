#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "intal.h"

#define MAX(x, y) ((x > y) ? x : y)
#define MIN(x, y) ((x < y) ? x : y)
#define MAXIMUM 1001
#define ISEVEN(n) ((n % 2 == 0) ? 1 : 0)
// #define ISODD(n) ((n % 2 != 0) ? 1 : 0)

static int min(unsigned int a, unsigned int b)
{
	return (a < b) ? a : b;
}

// pads extra 0s and converts to int
static int *char2int(const char *arr, int greater, int size)
{
	int *intArr;
	intArr = (int *)calloc(greater + 1, sizeof(int *));
	// printf(" ");
	int start = greater - size;
	int j = 0;
	for (int i = start; i < greater; i++)
	{
		intArr[i] = arr[j] - '0';
		j++;
	}
	return intArr; // returns padded array in int form
}

static char *coinHelper(char **inputArr, char **tableArr, int n)
{
	char *temporary, *currentNumber, *prevNum;
	if (n < 0)
		return "0";
	else if (n == 0)
	{
		tableArr[0] = inputArr[0];
		return tableArr[0];
	}
	temporary = coinHelper(inputArr, tableArr, n - 2);
	currentNumber = intal_add(temporary, inputArr[n]);
	prevNum = coinHelper(inputArr, tableArr, n - 1);

	int result = intal_compare(currentNumber, prevNum);
	if (result >= 0)
	{
		tableArr[n] = currentNumber;
	}
	else
	{
		tableArr[n] = prevNum;
	}
	return tableArr[n];
}

static char *int2char(int *arr, int size)
{
	char *charArr;
	charArr = (char *)malloc((size + 1) * sizeof(char *));
	for (int i = 0; i < size; i++)
	{
		charArr[i] = arr[i] + '0';
	}
	charArr[size] = '\0';
	return charArr;
}

// needed for factorial
static int product(int x, int *resultant, int size)
{
	int carry = 0;
	for (int i = 0; i < size; i++)
	{
		int prod = (resultant[i] * x);
		int digit = prod + carry;
		resultant[i] = digit % 10;
		carry = digit / 10;
	}

	while (carry > 0)
	{
		resultant[size] = carry % 10;
		carry = carry / 10;
		size++;
	}

	return size;
}

// needed for intal sort
static int partition(char **arr, int l, int r)
{
	char *midElement = malloc(10001);
	strcpy(midElement, arr[r]);
	int i = l - 1;
	for (int j = l; j <= r - 1; j++)
	{
		if (intal_compare(arr[j], midElement) == -1)
		{
			i = i + 1;
			char *temp = malloc(10001);

			strcpy(temp, arr[i]);
			strcpy(arr[i], arr[j]);
			strcpy(arr[j], temp);
			free(temp);
		}
	}
	char *temp2 = malloc(10001);

	strcpy(temp2, arr[i + 1]);
	strcpy(arr[i + 1], arr[r]);
	strcpy(arr[r], temp2);

	i++;
	free(midElement);
	free(temp2);
	return (i);
}

// needed for intal sort
static void qSorting(char **arr, int l, int r)
{
	if (l < r)
	{
		int partitioning = partition(arr, l, r);
		qSorting(arr, l, partitioning - 1);
		qSorting(arr, partitioning + 1, r);
	}
}

char *intal_add(const char *intal1, const char *intal2)
{

	int size1 = strlen(intal1);
	int size2 = strlen(intal2);

	int greater = MAX(size1, size2);

	int *intArr1;
	intArr1 = char2int(intal1, greater, size1);
	int *intArr2;
	intArr2 = char2int(intal2, greater, size2);

	// both char intals are now int arrays

	int *sumArr;
	sumArr = (int *)calloc((greater + 1), sizeof(int *));

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

	char *charArr = (char *)malloc(greater * sizeof(char *));
	charArr = int2char(sumArr, greater + 1);
	if (charArr[0] == '0')
	{
		charArr += 1;
	}

	char *result = (char *)malloc((greater + 1) * sizeof(char *));
	strcpy(result, charArr);

	free(intArr1);
	free(intArr2);
	return result;
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
	free(intArr1);
	free(intArr2);
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

	char *charArr = (char *)malloc((greater) * sizeof(char));
	charArr = int2char(diffArr, greater);
	// free(diffArr);
	int count = 0;
	for (int i = 0; i < strlen(charArr); i++)
	{
		if (charArr[i] == '0')
		{
			count += 1;
		}
		else
			break;
	}
	if (count == strlen(charArr))
	{
		strcpy(charArr, "0");
	}
	else
	{
		charArr += count;
	}
	// free(intArr2);
	// free(intArr1);
	// free(diffArr);
	// charArr[greater] = '\0';
	return charArr;
}

char *intal_multiply(const char *intal1, const char *intal2)
{
	if (strcmp("0", intal2) == 0 || strcmp("0", intal1) == 0)
	{
		char *result = (char *)malloc(sizeof(char) * 2);
		strcpy(result, "0\0");
		return result;
	}
	int size1 = strlen(intal1);
	int size2 = strlen(intal2);
	int len = size1 + size2;
	int *arr = (int *)malloc(sizeof(int) * len); 
	memset(arr, 0, sizeof(int) * len);
	for (int i = size1 - 1; i > -1; i--)
		for (int j = size2 - 1; j > -1; j--)
			arr[i + j + 1] += (intal1[i] - '0') * (intal2[j] - '0'); 
	for (int i = len - 1; i > 0; i--)								
	{
		arr[i - 1] += arr[i] / 10;
		arr[i] %= 10;
	}
	char *s = (char *)malloc(sizeof(char) * (len + 1));
	int index = 0;
	int i = 0;
	if (arr[i] == 0)
		i++; 
	while (i < len)
		s[index++] = arr[i++] + '0';
	s[index] = '\0';

	free(arr);
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

int intal_max(char **arr, int n)
{
	char *max = (char *)malloc(MAXIMUM * sizeof(char));
	// assuming the 1st intal to be the max
	strcpy(max, arr[0]);
	int pos = 0;
	// start loop from next element
	for (int i = 1; i < n; i++)
	{
		if (intal_compare(arr[i], max) == 1)
		{
			strcpy(max, arr[i]);
			pos = i;
		} // the number is greater, need to swap
	}
	return pos;
}

int intal_min(char **arr, int n)
{
	char *min = (char *)malloc(MAXIMUM * sizeof(char));
	// assuming the 1st intal to be the max
	strcpy(min, arr[0]);
	int pos = 0;
	// start loop from next element
	for (int i = 1; i < n; i++)
	{
		if (intal_compare(arr[i], min) == -1)
		{
			strcpy(min, arr[i]);
			pos = i;
		} // the number is greater, need to swap
	}
	return pos;
}

int intal_search(char **arr, int n, const char *key)
{
	int pos = -1;
	char *intalKey = (char *)malloc(MAXIMUM * sizeof(char));
	strcpy(intalKey, key);
	for (int i = 0; i < n; i++)
	{
		if (intal_compare(intalKey, arr[i]) == 0)
		{
			pos = i;
			break;
		}
	}
	free(intalKey);
	return pos;
}

char *intal_factorial(unsigned int n)
{
	if (n == 0 || n == 1)
	{
		char *temp = (char *)calloc(sizeof(char), 1);
		strcpy(temp, "1");
		return temp;
	}
	int *tempArr = malloc(100000);
	tempArr[0] = 1;
	int size = 1;

	for (int i = 2; i <= n; i++)
		size = product(i, tempArr, size);
	//printf("%d\n", size);
	int count = 0;
	char *result = malloc(100000);
	for (int i = size - 1; i >= 0; i--)
	{
		result[count] = tempArr[i] + '0';
		count++;
	}

	free(tempArr);
	return result;
}

static int binSearchHelp(char **arr, int l, int r, char *key)
{
	int temp = r - l + 1;
	if (temp < 1)
	{
		return -1;
	}
	int midElement = (l + r) / 2;

	if (intal_compare(key, arr[midElement]) == 0)
		return midElement;

	else if (intal_compare(key, arr[midElement]) == -1)
		return binSearchHelp(arr, l, midElement - 1, key);

	else
		return binSearchHelp(arr, midElement + 1, r, key);
}

int intal_binsearch(char **arr, int n, const char *key)
{
	char *charArr = (char *)malloc(sizeof(char) * 1001);
	strcpy(charArr, key);
	int result = -1;
	result = binSearchHelp(arr, 0, n, charArr);
	free(charArr);
	return result;
}

void intal_sort(char **arr, int n)
{
	qSorting(arr, 0, n - 1);
}


char *coin_row_problem(char **arr, int n)
{
	char **tableArr = (char **)malloc(sizeof(char *) * n);
	for (int i = 0; i < n; i++)
	{
		tableArr[i] = (char *)malloc(sizeof(char) * MAXIMUM);
		strcpy(tableArr[i], "0");
	}
	char *res = (char *)malloc(sizeof(char) * MAXIMUM);
	strcpy(res, coinHelper(arr, tableArr, n - 1));
	return res;
}

void swap(char *a, char *b)
{

	char *temp = malloc(1000 * sizeof(char));
	strcpy(temp, a);
	strcpy(a, b);
	strcpy(b, temp);
}

char *intal_fibonacci(unsigned int n)
{
	char *a = (char *)malloc(sizeof(char) * 2);
	strcpy(a, "0");

	if (n == 0)
		return a;

	char *b = (char *)malloc(sizeof(char) * 2);
	strcpy(b, "1");
	if (n == 1)
		return b;
	char *res, *temp;
	int i = 2;
	while (i <= n)
	{

		res = intal_add(a, b);
		// printf("%s<------res\n", res);
		temp = a;
		a = b;
		b = res;
		free(temp);
		i++;
	}
	// free(a);
	return res;
}

static char *removePreZeroes(const char *tempArr)
{
	char *charArr = (char *)malloc(sizeof(char) * 1001);
	strcpy(charArr, tempArr);
	int count = 0;
	for (int i = 0; i < strlen(charArr); i++)
	{
		if (charArr[i] == '0')
		{
			count += 1;
		}
		else
			break;
	}
	if (count == strlen(charArr))
	{
		strcpy(charArr, "0");
	}
	else
	{
		charArr += count;
	}

	return charArr;
}

char *intal_mod(const char *intal1, const char *intal2)
{
	char *numer, *denom;
	// numer -> dividend
	// denom -> denominator
	char *temp1, *temp2;
	numer = strdup(intal1);
	int count = 0; //keep track of iterations
	// while (denom < intal2)
	while (intal_compare(numer, intal2) != -1)
	{
		denom = strdup(intal2);
		// numer > denom: compare == 1
		// till numerator > denominator
		while (intal_compare(numer, denom) == 1)
		{
			temp1 = intal_multiply("2", denom);
			temp2 = denom;
			denom = temp1;
			// free(temp2);
		}
		temp1 = intal_diff(denom, numer);
		temp2 = numer;
		numer = temp1;
		if (intal_compare(numer, "0") == 0)
		{
			free(numer);
			free(denom);
			char *result = (char *)malloc(sizeof(char) * 2);
			strcpy(result, "0\0");
			return result;
		}
		count++;
	}
	int status = ISEVEN(count); // status 1 -> even iterations
	if (status == 0)
	{
		temp1 = intal_diff(intal2, numer);
		temp2 = numer;
		numer = temp1;
	}
	temp1 = removePreZeroes(numer);
	temp2 = numer;
	numer = temp1;
	return numer;
}

static char *gcdHelper(char *temp1, char *temp2)
{
	if (strcmp(temp2, "0") == 0)
	{
		char *result = strdup(temp1);
		return result;
	}
	char *mod, *temp;
	mod = intal_mod(temp1, temp2);
	temp = gcdHelper(temp2, mod);
	return temp;
}
char *intal_gcd(const char *intal1, const char *intal2)
{
	if (strcmp("0", intal1) == 0 && strcmp("0", intal2) == 0)
	{
		char *result = (char *)malloc(sizeof(char) * 2);
		strcpy(result, "0");
		return (result);
	}

	else
	{
		char *temp1, *temp2, *result;
		// strcpy(temp1, intal1);
		// strcpy(temp2, intal2);
		temp1 = strdup(intal1);
		temp2 = strdup(intal2);
		result = gcdHelper(temp1, temp2);
		free(temp1);
		free(temp2);
		return result;
	}
}

char *intal_bincoeff(unsigned int n, unsigned int k)
{
	// reducing complexity using a standard identity
	if (k > n / 2)
		k = n - k;

	char **table = (char **)malloc(sizeof(char *) * (k + 1));
	// memsetting all values to 0
	for (int i = 0; i <= k; i++)
	{
		table[i] = (char *)malloc(sizeof(char *) * 1001);
		strcpy(table[i], "0");
		// memset(table[i],"0", sizeof(table[i]));
	}
	strcpy(table[0], "1");

	char *result;

	for (int i = 1; i <= n; i++)
	{
		for (int j = MIN(i, k); j > 0; j--)
		{
			// Pascals Identity
			table[j] = intal_add(table[j], table[j - 1]);
		}
	}

	result = strdup(table[k]);
	for (int i = 0; i <= k; i++)
	{
		free(table[i]);
	}
	free(table);
	return result;
}
