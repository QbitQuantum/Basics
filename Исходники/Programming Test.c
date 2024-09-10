int readInput(INTERVAL *arr1) // Read input from user
{

	int n = 0;
	char ch;

	while (1)
	{
		scanf_s("%d-%d", &arr1[n].min, &arr1[n].max);
		ch = getchar();
		n++;
		if (ch != ',')  break;
	}
	return n;
}