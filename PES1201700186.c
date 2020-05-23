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

	while (carry)
	{
		resultant[size] = carry % 10;
		carry = carry / 10;
		size++;
	}

	return size;
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
	int *arr = (int *)malloc(sizeof(int) * len); //the number of digits of the result - len is the top;
	memset(arr, 0, sizeof(int) * len);
	for (int i = size1 - 1; i > -1; i--)
		for (int j = size2 - 1; j > -1; j--)
			arr[i + j + 1] += (intal1[i] - '0') * (intal2[j] - '0'); //collect result of each position;
	for (int i = len - 1; i > 0; i--)								 //restore the carry for each position and get the final result;
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
	if(n == 0 || n == 1){
		char *temp = (char*)calloc(sizeof(char), 1);
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

int intal_binsearch(char **arr, int n, const char *key)
{
	char *k = (char *)malloc(sizeof(char) * MAXIMUM);
	strcpy(k, key);
	int res;
	res = custom_binSearch(arr, 0, n, k);
	free(k);
	return res;
}

//binary search helper function, actual binary search logic
int custom_binSearch(char **arr, int l, int r, char *key)
{
	if (r - l + 1 < 1)
	{
		return -1;
	}
	int m = (l + r) / 2;

	if (intal_compare(key, arr[m]) == 0)
		return m;

	else if (intal_compare(key, arr[m]) == -1)
		return custom_binSearch(arr, l, m - 1, key);

	else
		return custom_binSearch(arr, m + 1, r, key);
}

int partition(char **arr, int low, int high)
{
	char *pivot = malloc(10000);
	strcpy(pivot, arr[high]);
	//printf("%s\n", pivot);
	int i = low - 1;

	for (int j = low; j <= high - 1; j++)
	{
		//printf("%d\n", intal_compare(arr[j],pivot));
		if (intal_compare(arr[j], pivot) == -1)
		{
			i = i + 1;
			//printf("%s\n", arr[i]);
			char *temp = malloc(10000);
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;

			//swap(arr[i],arr[j]);
			//printf("%s\n", arr[j]);
		}
	}
	char *temp2 = malloc(10000);
	//char *temp = malloc(1000);
	temp2 = arr[i + 1];
	arr[i + 1] = arr[high];
	arr[high] = temp2;
	//swap(arr[i+1],arr[high]);
	return (i + 1);
}

void quick_sort(char **arr, int low, int high)
{
	if (low < high)
	{
		int pi = partition(arr, low, high);
		quick_sort(arr, low, pi - 1);
		quick_sort(arr, pi + 1, high);
	}
}

void intal_sort(char **arr, int n)
{
	quick_sort(arr, 0, n - 1);
}

// no need to sort
char *coin_row_problem(char **arr, int n)
{
	// array to store the DP 'array(table)'
	char **tableArr = (char **)malloc((n + 1) * sizeof(char)); // extra 1 to account for 0 in the beginning
	if (n == 1)
	{
		return arr[0];
	}
	if (n == 2)
	{
		// return MAX(arr[0], arr[1]);
		int flag = intal_compare(arr[0], arr[1]);
		if (flag == 1 || flag == 0)
			return arr[0];
		else
			return arr[1];
	}
	// for more than 3 values:
	tableArr[0] = "0";
	// strcpy(tableArr[0], "0");
	// printf("%s <-----\n", tableArr[0]);

	tableArr[1] = arr[0];
	// printf("%s <-----\n", tableArr[1]);

	// strcpy(tableArr[1], arr[0]);
	for (int i = 1; i < n; i++)
	{
		char *sum;
		sum = intal_add(arr[i], tableArr[i - 1]);
		int flag = intal_compare(sum, tableArr[i]);
		// printf("%d", flag);
		if (flag == 1 || flag == 0)
		{
			tableArr[i + 1] = sum;
			// strcpy(tableArr[i + 1], sum);
		}
		else
			tableArr[i + 1] = tableArr[i];
		// free(sum);
	}

	char *result = (char *)malloc(sizeof(char) * 1001);
	strcpy(result, tableArr[n]);
	free(tableArr);
	return result;
	// return "0";
}

void swap(char *a, char *b)
{

	char *temp = malloc(1000 * sizeof(char));
	strcpy(temp, a);
	strcpy(a, b);
	strcpy(b, temp);
}

char *reverse(char *a)
{
	int x = strlen(a);
	char *final_result = malloc(10000);
	int k = 0;
	for (int i = x - 1; i >= 0; i--)
	{
		final_result[k] = a[i];
		//printf("%c\n", a[i]);
		k = k + 1;
	}

	//printf("%s\n", final_result);

	return final_result;
}

char *tempadd(const char *intal1, const char *intal2)
{

	char *temp1 = malloc(10000);
	char *temp2 = malloc(10000);

	strcpy(temp1, intal1);
	strcpy(temp2, intal2);

	char *result = malloc(10000);

	if (strlen(temp1) > strlen(temp2))
		swap(temp1, temp2);
	int n1 = strlen(temp1);
	int n2 = strlen(temp2);

	char *actual1 = malloc(10000);
	char *actual2 = malloc(10000);

	strcpy(actual1, reverse(temp1));
	strcpy(actual2, reverse(temp2));

	int carry = 0;
	int count = 0;
	for (int i = 0; i < n1; i++)
	{
		int sum = (actual1[i] - '0') + (actual2[i] - '0') + carry;
		result[count] = sum % 10 + '0';
		count = count + 1;
		carry = sum / 10;
	}

	for (int i = n1; i < n2; i++)
	{
		int sum = (actual2[i] - '0') + carry;
		result[count] = sum % 10 + '0';
		count = count + 1;
		carry = sum / 10;
	}

	if (carry)
	{
		result[count] = carry + '0';
		count = count + 1;
	}

	//printf("%s\n", result);
	char *final_result = malloc(10000);
	strcpy(final_result, reverse(result));
	//printf("%s\n", final_result);
	return final_result;
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

		res = tempadd(a, b);
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
