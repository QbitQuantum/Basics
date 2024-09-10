void
wordcount(FILE_TYPE file, long *result)
{
	int c;
	long linec, wordc, charc;
	int inword = 0;

	linec = wordc = charc = 0;

	while ((c = GETC(file)) != EOF) {
		charc++;
		if (c == '\n')
			linec++;
		if (isspace(c)) {
			if (inword)
				inword = 0;
		} else {
			if (!inword) {
				inword = 1;
				wordc++;
			}
		}
	}
	result[0] = linec;
	result[1] = wordc;
	result[2] = charc;
}