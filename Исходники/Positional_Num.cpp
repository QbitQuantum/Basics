int main()
{
	unsigned int N;
	
	printf("Input any number : ");
	scanf_s("%u", &N);

	do
	{
		N = AddPosi(N);
		printf("%u\n", N);
	} while (N >= 10);


	return 0;
}