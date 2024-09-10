void main(void)
{
	FILE* in;
	int ch;
	static char string[2];
	if ((in = fopen("test.txt", "r")) != NULL)
	{
		while ((ch = getc(in)) != EOF)
		{
			*string = ch;
			CharToOemA(string, string);
			ch = *string;
			putc(ch, stdout);
		}
		fclose(in);
	}
	else
		printf("Нет возможности открыть файл. \n");
}