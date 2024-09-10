int main()
{
	char *p1, *p2;
	int n;
	printf("input two strings:\n");
	gets_s(p1, 50);
	gets_s(p2, 50);
	n=strcmp(p1, p2);
	printf("%d\n", n);
	system("pause");
}