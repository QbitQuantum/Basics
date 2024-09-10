int main()	{
	char str[]="-This, is a sample string.";
	char *pch;
	printf("Splitting string \"%s\" into tokens:\n",str);
	pch = Strtok (str," ,.-");
	while (pch != NULL)	{
        printf ("%s\n",pch);
	pch = Strtok (NULL, " ,.-");
	}

	return 0;
}