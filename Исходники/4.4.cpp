int _tmain(int argc, _TCHAR* argv[])
{
	char st[100];
	printf("Input: ");
    gets_s(st);
	int *a = new int[strlen(st)];
	for (int i = 0; i < strlen(st); i++)
	{
		a[i] = st[i] - '0';
	}
	hs(a, strlen(st));
	if (a[0] == 0) 
	{
	for (int i = 1; i<strlen(st);i++)
	{
		if (a[i] != 0)
		{
			a[0] = a[i];
			a[i] = 0;
			break;
		}
	}
	}
	for (int i = 0; i<strlen(st);i++)
	{
		printf("%d", a[i]);
	}
	return 0;
}