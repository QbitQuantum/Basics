main()
{
	char a1[] = "hello";
	char b1[] = "goodbye";

	e(a1,b1);

	printf("a1=%s.\n", a1);
	printf("b1=%s.\n", b1);

	char a2[] = "hello";
	char b2[] = "goodbye";

	strCpy(a2,b2);

	printf("a2=%s.\n", a2);
	printf("b2=%s.\n", b2);
}