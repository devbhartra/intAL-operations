char *intal_mod(const char *intal1, const char *intal2)
{
	char *divident, *divisor, *t1, *t2;
	divident = strdup(intal1);

	int iter = 0; //value varies between 0 and 1

	//run loop till divident is greater than divisor
	while (intal_compare(divident, intal2) != -1)
	{

		divisor = strdup(intal2);
		//run loop till divisor is smaller than divident
		while (intal_compare(divident, divisor) == 1)
		{
			t1 = intal_multiply(divisor, "2");
			// printf("%s", t1);
			t2 = divisor;
			divisor = t1;
			free(t2);
		}
		t1 = intal_diff(divisor, divident);
		t2 = divident;
		divident = t1;
		// free(t2);

		//if intal1 is a factor of intal2
		if (intal_compare(divident, "0") == 0)
		{
			free(divident);
			free(divisor);
			char *res = (char *)malloc(sizeof(char) * 2);
			res[0] = '0';
			res[1] = '\0';
			return res;
		}

		iter += 1;
		iter %= 2;
	}

	if (iter == 1)
	{
		t1 = intal_diff(intal2, divident);
		t2 = divident;
		divident = t1;
		// free(t2);
	}

	t1 = stripZeros(divident);
	t2 = divident;
	divident = t1;
	// free(t2);

	// free(divisor);

	return divident;
}