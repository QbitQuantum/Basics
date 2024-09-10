int main(void)	{
	int i, len;
	char str[20];

	scanf("%s", str);

	len = strlen(str);

	for (i = 0; i < len; i++)
		printf("..%c.", getC(i));
	printf(".\n");

	for (i = 0; i < len; i++)
		printf(".%c.%c", getC(i), getC(i));
	printf(".\n");

	printf("#");
	for (i = 0; i < len - 1; i++)
		printf(".%c.%c", str[i], i % 3 == 0 ? '#' : '*');
	printf(".%c.%c", str[i], i % 3 == 2 ? '*' : '#');
	printf("\n");

	for (i = 0; i < len; i++)
		printf(".%c.%c", getC(i), getC(i));
	printf(".\n");

	for (i = 0; i < len; i++)
		printf("..%c.", getC(i));
	printf(".\n");

	return 0;
}