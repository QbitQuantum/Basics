int main()
{
	char line[1000];
	printf("enter a list of integers separated by a space bar: ");
	readline(line, 1000);
	printf("you entered: %s\n", line);
	char * toks[200];

	int ne = strTok(line, ' ', toks, 200);
	int * ints = new int[ne];
	for(int i = 0; i < ne; i++)
	{
		int n = atoi(toks[i]);
		ints[i] = n;
	}

	qsort((void*) ints, ne, sizeof(int), &intCmpA);
	printf("values:");
	int sum = 0;
	for(int i = 0; i < ne; i++)
	{
		printf("% i +", ints[i]);
		sum += ints[i];
	}
	printf("\b = %i\n", sum);
	delete [] ints;
	return 0;
}