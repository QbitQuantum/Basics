int interleaved_two_of_five(struct zint_symbol *symbol, unsigned char source[], int length)
{ /* Code 2 of 5 Interleaved */

	int i, j, k, error_number;
	char bars[7], spaces[7], mixed[14], dest[1000];
#ifndef _MSC_VER
	unsigned char temp[length + 2];
#else
	unsigned char* temp = (unsigned char *)_alloca((length + 2) * sizeof(unsigned char));
#endif

	error_number = 0;
	
	if(length > 89) {
		strcpy(symbol->errtxt, "Input too long");
		return ERROR_TOO_LONG;
	}
	error_number = is_sane(NEON, source, length);
    if (error_number == ERROR_INVALID_DATA1) {
		strcpy(symbol->errtxt, "Invalid characters in data");
		return error_number;
	}
	
	ustrcpy(temp, (unsigned char *) "");
	/* Input must be an even number of characters for Interlaced 2 of 5 to work:
	   if an odd number of characters has been entered then add a leading zero */
	if (length & 1)
	{
		ustrcpy(temp, (unsigned char *) "0");
		length++;
	}
	uconcat(temp, source);

	/* start character */
	strcpy(dest, "1111");

	for(i = 0; i < length; i+=2 )
	{
		/* look up the bars and the spaces and put them in two strings */
		strcpy(bars, "");
		lookup(NEON, C25InterTable, temp[i], bars);
		strcpy(spaces, "");
		lookup(NEON, C25InterTable, temp[i + 1], spaces);

		/* then merge (interlace) the strings together */
		k = 0;
		for(j = 0; j <= 4; j++)
		{
			mixed[k] = bars[j]; k++;
			mixed[k] = spaces[j]; k++;
		}
		mixed[k] = '\0';
		concat (dest, mixed);
	}

	/* Stop character */
	concat (dest, "311");
	
	expand(symbol, dest);
	ustrcpy(symbol->text, temp);
	return error_number;

}