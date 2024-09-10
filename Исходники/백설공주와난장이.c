int main()
{
	FILE *f;
	freopen_s(&f, "input.txt", "r", stdin);
	freopen_s(&f, "output.txt", "w", stdout);

	int tall[7];

	for (int i = 0; i < 7; i++)
		scanf_s("%d", &tall[i]);

	qsort(tall, sizeof(tall) / sizeof(int), sizeof(int), compare);

	for(int i =6;i>=5;i--)
		printf("%d\n", tall[i]);

	return 0;
}