void printStr(FILE* fout, char* string)
{
	int num = 0;
	bool is_text = false;

	for (int i = 0; string[i] != '\r'; i++)
	if (!IsPunct(string, i))
		is_text = true;

	if (is_text)
	while (string[num] != '\0')
	{

		assert(string[num]);
		if (!string[num])
			Nerror = STRPOSERR;
		if (string[num] != '\r')
		{
			fprintf(fout, "%c", string[num]);
			num += 1;
		}
		else if (string[num]>0 && string[num] < 255)
		{
			fprintf(fout, "\n");
			break;
		}
		else
		{
			printf("What the %*&#!?");
		}
	}
}