LPSTR UnicodeStr4CodeToUTF8Str(LPSTR in)
{
	LPSTR temp;
	unsigned int code, help;
	CHAR utf8[5];
	size_t length;
	while(temp = StrChrA(in, '\\'), temp != NULL)
	{
		if((temp[1] == 'u')||(temp[1] == 'U'))
		{
			temp[0] = '\0';
			StringCchLengthA(in, STRSAFE_MAX_CCH, &length);
			CHAR A[length+1];
			StringCchCopyA(A, length+1, in);
			StringCchLengthA(temp+6, STRSAFE_MAX_CCH, &length);
			CHAR B[length+1];
			StringCchCopyA(B, length+1, temp+6);
			temp[6] = '\0';
			CHAR hex_code[7];
			StringCchCopyA(hex_code, 7, "0x");
			CharLowerA(temp+2);
			StringCchCatA(hex_code, 7, temp+2);
			if(StrToIntExA(hex_code, STIF_SUPPORT_HEX, (int *)&code) == TRUE)
			{
				help = code;
				if(code <= 0x007F)
				{
					utf8[0] = code;
					utf8[1] = '\0';
				}
				else if(code <= 0x07FF)
				{
					utf8[0] = 0xC0+(help >> 6);
					utf8[1] = 0x80+(code&0x3F);
					utf8[2] = '\0';
				}
				else if(code <= 0xFFFF)