long s_conv(char nome[])
{
	FILE *fp;

	char conv[15], riga[150]; int base; long sum=0; char *rem;

	int cont = 0;

	if((fp = fopen(nome,"r")) == NULL)
	{
		printf("File non trovato\n");

		return EXIT_FAILURE;
	}

	while(fgets(riga, 150, fp) != NULL)
	{
		sscanf(riga, "%*c%s%*c%d", conv, &base);
		printf("%s %d\n", conv, base);
		cont = strtol(conv, NULL, base);
		printf("%d\n",cont);
		sum += cont; 
	}

	fcloseall();

	return sum;
}