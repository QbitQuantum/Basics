int japan_post(struct zint_symbol *symbol, unsigned char source[], int length)
{ /* Japanese Postal Code (Kasutama Barcode) */
	int error_number, h;
	char pattern[69];
	int writer, loopey, inter_posn, i, sum, check;
	char check_char;
	char inter[23];

#ifndef _MSC_VER
        char local_source[length + 1];
#else
        char* local_source = (char*)_alloca(length + 1);
#endif
	
	inter_posn = 0;
	error_number = 0;

	strcpy(local_source, (char*)source);
	for(i = 0; i < length; i++) {
		local_source[i] = source[i];
	}
	to_upper((unsigned char*)local_source);
	error_number = is_sane(SHKASUTSET, (unsigned char*)local_source, length);

	if(error_number == ERROR_INVALID_DATA) {
		strcpy(symbol->errtxt, "Invalid characters in data");
		return error_number;
	}
	memset(inter, 'd', 20);/* Pad character CC4 */
	inter[20] = '\0';

	i = 0;
	inter_posn = 0;
	do {
		if(((local_source[i] >= '0') && (local_source[i] <= '9')) || (local_source[i] == '-')) {
			inter[inter_posn] = local_source[i];
			inter_posn++;
		} else {
			if((local_source[i] >= 'A') && (local_source[i] <= 'J')) {
				inter[inter_posn] = 'a';
				inter[inter_posn + 1] = local_source[i] - 'A' + '0';
				inter_posn += 2;
			}
			if((local_source[i] >= 'K') && (local_source[i] <= 'T')) {
				inter[inter_posn] = 'b';
				inter[inter_posn + 1] = local_source[i] - 'K' + '0';
				inter_posn += 2;
			}
			if((local_source[i] >= 'U') && (local_source[i] <= 'Z')) {
				inter[inter_posn] = 'c';
				inter[inter_posn + 1] = local_source[i] - 'U' + '0';
				inter_posn += 2;
			}
		}
		i++;
	}while((i < length) && (inter_posn < 20));
	inter[20] = '\0';

	strcpy(pattern, "13"); /* Start */

	sum = 0;
	for(i = 0; i < 20; i++) {
		concat(pattern, JapanTable[posn(KASUTSET, inter[i])]);
		sum += posn(CHKASUTSET, inter[i]);
		/* printf("%c (%d)\n", inter[i], posn(CHKASUTSET, inter[i])); */
	}

	/* Calculate check digit */
	check = 19 - (sum % 19);
	if(check == 19) { check = 0; }
	if(check <= 9) { check_char = check + '0'; }
	if(check == 10) { check_char = '-'; }
	if(check >= 11) { check_char = (check - 11) + 'a'; }
	concat(pattern, JapanTable[posn(KASUTSET, check_char)]);
	/* printf("check %c (%d)\n", check_char, check); */

	concat(pattern, "31"); /* Stop */

	/* Resolve pattern to 4-state symbols */
	writer = 0;
	h = strlen(pattern);
	for(loopey = 0; loopey < h; loopey++)
	{
		if((pattern[loopey] == '2') || (pattern[loopey] == '1'))
		{
			set_module(symbol, 0, writer);
		}
		set_module(symbol, 1, writer);
		if((pattern[loopey] == '3') || (pattern[loopey] == '1'))
		{
			set_module(symbol, 2, writer);
		}
		writer += 2;
	}

	symbol->row_height[0] = 3;
	symbol->row_height[1] = 2;
	symbol->row_height[2] = 3;
	symbol->rows = 3;
	symbol->width = writer - 1;

	return error_number;
}