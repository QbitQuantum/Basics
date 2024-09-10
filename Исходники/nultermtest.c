main()
{
	char str[6];
	
	printf ("Type in a string.\n");
	gets(str);
	
	nulterm(6, str);
	
	if(str[5]=='\0')
	{
		printf ("\nstr is null terminated");
	}
	else
	{
		printf ("\nstr is not null terminated");
	}
	
	flushall();
	getchar();
}