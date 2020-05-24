// Dev Bhartra
// APSSSE Mini Project
// PES1201700186
// PES University

// C Library to perform operations on integers of Arbitrary length

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "intal.h"

#define MAX(x, y) ((x > y) ? x : y)
#define MIN(x, y) ((x < y) ? x : y)
#define MAXIMUM 1001
#define ISEVEN(n) ((n % 2 == 0) ? 1 : 0)

// helper function two swap the values of 2 intals
// static void swap(char *a, char *b)
// {
// 	char *temp = malloc(1000 * sizeof(char));
// 	strcpy(temp, a);
// 	strcpy(a, b);
// 	strcpy(b, temp);
// }

// pads extra 0s if required and converts to character array to integer array
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

// Convert the integer array to character array, in intal form
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

// helper function to remove preceeding 0s
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

// helper function to help with GCD
// Implements Euclidean Algorithm for GCD
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

// helper function to help with binary search
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

// static function to help with the Coin Row problem
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
	// free(temporary);
	// free(currentNumber);
	// free(prevNum);
	return tableArr[n];
}

// helper function needed for factorial
static int product(int num, int *resultant, int size)
{
	int carryOver = 0;
	for (int i = 0; i < size; i++)
	{
		int prod = (resultant[i] * num);
		int digit = prod + carryOver;
		resultant[i] = digit % 10;
		carryOver = digit / 10;
		// free(digit)
		// free(carryOver);
	}
	// if leftover Carry is still present:
	while (carryOver > 0)
	{
		resultant[size] = carryOver % 10;
		carryOver = carryOver / 10;
		size++;
	}
	return size;
}

// helper function needed for intal sort, implements the logic of finding the partitioning element in quickSort
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
			// free(temp);
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

// helper function needed for intal sort, implements the recursive quickSort logic
static void qSorting(char **arr, int l, int r)
{
	if (l < r)
	{
		int partitioning = partition(arr, l, r);
		qSorting(arr, l, partitioning - 1);
		qSorting(arr, partitioning + 1, r);
	}
}

// main function, to add two intals
// returns a char array
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

	// array to store the final  sum
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
	// removing the extra preceeding 0s
	if (charArr[0] == '0')
	{
		charArr += 1;
	}

	char *result = (char *)malloc((greater + 1) * sizeof(char *));
	strcpy(result, charArr);
	// free charArr
	free(intArr1);
	free(intArr2);
	free(sumArr);
	return result;
}

// main function, to compare two input intal values.
// returns, -1, +1 or zero
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
			continue; // both current values in the numbers are equal
		}
		else if (intArr1[i] > intArr2[i])
		{
			flag = 1; // intal1 > intal2
			break;
		}
		else
		{
			flag = -1; // intal2 > intal1
			break;
		}
	}
	free(intArr1);
	free(intArr2);
	return flag;
}

// main function to find the difference between two intals
// returns a character array
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

	// temp array to store the difference
	int *diffArr;
	diffArr = (int *)calloc((greater), sizeof(int)); // need to strip

	// main difference logic
	int diff = 0;

	// find bigger number:
	int comp = intal_compare(intal1, intal2);
	// intal1 > intal2
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

	// removing extra 0s from the front
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

	// move char pointer up by thre number of 0s present in the front
	else
	{
		charArr += count;
	}
	free(diffArr);
	// free(intArr2);
	// free(intArr1);
	// charArr[greater] = '\0';
	return charArr;
}

// main function to multiply 2 intals
// returns a char array
char *intal_multiply(const char *intal1, const char *intal2)
{
	// if any of the inputs is a 0, return 0
	if (strcmp("0", intal2) == 0 || strcmp("0", intal1) == 0)
	{
		char *result = (char *)malloc(sizeof(char) * 2);
		strcpy(result, "0\0");
		return result;
	}
	int size1 = strlen(intal1);
	int size2 = strlen(intal2);

	// max possible length of the product
	int len = size1 + size2;

	// temporary array to store the product
	int *arr = (int *)malloc(sizeof(int) * len);
	// int *arr = (int *)calloc(sizeof(int) , len);
	memset(arr, 0, sizeof(int) * len);

	for (int i = size1 - 1; i > -1; i--)
	{
		for (int j = size2 - 1; j > -1; j--)
		{
			// actual number by number multiplication
			arr[i + j + 1] += (intal1[i] - '0') * (intal2[j] - '0');
		}
	}
	for (int i = len - 1; i > 0; i--)
	{
		arr[i - 1] += arr[i] / 10;
		arr[i] %= 10;
	}
	char *s = (char *)malloc(sizeof(char) * (len + 1));
	int index = 0;
	int i = 0;
	if (arr[i] == 0)
	{
		i++;
	}
	while (i < len)
	{
		s[index++] = arr[i++] + '0';
	}
	s[index] = '\0';

	free(arr);
	return s;
}

// main function to calculate intal1^intal2
char *intal_pow(const char *intal1, unsigned int n)
{
	// anything to the power 0 = 1
	if (n == 0)
	{
		char *resArr = (char *)malloc(1 * sizeof(char));
		strcpy(resArr, "1");
		return resArr;
	}
	char *temp, *resArr;

	// recursive algorithm
	temp = intal_pow(intal1, n / 2);
	if (n % 2 == 0)
	{
		resArr = intal_multiply(temp, temp);
		strcpy(temp, resArr);
		free(resArr);
		return temp;
	}
	else
	{
		temp = intal_multiply(temp, temp);
		resArr = intal_multiply(intal1, temp);
		strcpy(temp, resArr);
		free(resArr);
		return temp;
	}
}

// main function to find offset of max intal in an array of intals
// returns an int index value
int intal_max(char **arr, int n)
{
	char *max = (char *)malloc(MAXIMUM * sizeof(char));
	// assuming the 1st intal to be the max
	strcpy(max, arr[0]);
	int pos = 0;
	// start loop from next element
	for (int i = 1; i < n; i++)
	{
		// the number is greater, need to swap
		if (intal_compare(arr[i], max) == 1)
		{
			strcpy(max, arr[i]);
			pos = i;
		}
	}
	free(max);
	return pos;
}

// main funtion to find offset of min intal in an array of intals
// returns an int index value
int intal_min(char **arr, int n)
{
	char *min = (char *)malloc(MAXIMUM * sizeof(char));
	// assuming the 1st intal to be the max
	strcpy(min, arr[0]);
	int pos = 0;
	// start loop from next element
	for (int i = 1; i < n; i++)
	{
		// the number is lesser, need to swap
		if (intal_compare(arr[i], min) == -1)
		{
			strcpy(min, arr[i]);
			pos = i;
		}
	}
	free(min);
	return pos;
}

// main function to search for intal in an array. Implements linear  search
int intal_search(char **arr, int n, const char *key)
{
	int pos = -1;
	char *intalKey = (char *)malloc(MAXIMUM * sizeof(char));
	strcpy(intalKey, key);
	for (int i = 0; i < n; i++)
	{
		// element found
		if (intal_compare(intalKey, arr[i]) == 0)
		{
			pos = i;
			break;
		}
	}
	free(intalKey);
	return pos;
}

// main function to calculate factorial of a number. Can calculate uptil values exceeding 7000, in miliseconds
char *intal_factorial(unsigned int n)
{
	// base case, 0! and 1! = 1
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

// main function to perform binary search. Returns -1 or 1 if not found or found, respectively
int intal_binsearch(char **arr, int n, const char *key)
{
	if (n == 1)
	{
		if (intal_compare(arr[0], key) == 0)
		{
			return 1;
		}
		else
		{
			return -1;
		}
	}
	char *charArr = (char *)malloc(sizeof(char) * 1001);
	strcpy(charArr, key);
	int result = -1;
	result = binSearchHelp(arr, 0, n, charArr);
	free(charArr);
	return result;
}

// main function to perform quickSort on an array of intals
void intal_sort(char **arr, int n)
{
	qSorting(arr, 0, n - 1);
}

// main function to solve the coin row problem, in a n array of intals
// The goal is to pick up the maximum amount of money subject to the constraint that no two coins adjacent in the initial row can be picked up.
char *coin_row_problem(char **arr, int n)
{
	if (n == 1)
	{
		char *temp = (char *)malloc(sizeof(char) * 1);
		strcpy(temp, arr[0]);
		return temp;
	}
	if (n == 2)
	{
		char *temp = (char *)malloc(sizeof(char) * 1);
		int status = intal_compare(arr[0], arr[1]);
		if (status == 1 || status == 0)
		{
			strcpy(temp, arr[0]);
			return temp;
		}
		else
		{
			strcpy(temp, arr[1]);
			return temp;
		}
	}
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

// main function to calculate the nth fiboncacci number. Faster than brute force. Store only the n-1th and n-2nd values in each iteration for space efficiency
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

// main function to calculate intal1 mod intal2
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
			// free(numer);
			// free(denom);
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

// main function to calculate gcd of 2 intals. Applies the euclidean logic of recursion
char *intal_gcd(const char *intal1, const char *intal2)
{
	// border case when both intals are 0
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

// main function to calculate the binomial coefficient for nCk
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
	// 1st value in each row of Pascals triangle is 1
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