int ConvSJIStoJIS(CODECONVINFO *cInfo)
{
	int Kcode;
	char *Str;
	char *Put;
	char *Limit;
	int Continue;

	cInfo->KanaProc = &ConvSJIStoJISkanaProc;

	Continue = NO;
	Str = cInfo->Str;
	Put = cInfo->Buf;
	Limit = cInfo->Buf + cInfo->BufSize - 5;

	for(; cInfo->StrLen > 0; cInfo->StrLen--)
	{
		if(Put >= Limit)
		{
			Continue = YES;
			break;
		}

		if(cInfo->KanjiFst == 0)
		{
			if((((uchar)*Str >= (uchar)0x81) && ((uchar)*Str <= (uchar)0x9F)) ||
			   ((uchar)*Str >= (uchar)0xE0))
			{
				Put = ConvSJIStoJISkanaProc(cInfo, 0, Put);
				cInfo->KanjiFst = *Str++;
			}
			else if(((uchar)*Str >= (uchar)0xA0) && ((uchar)*Str <= (uchar)0xDF))
			{
				Put = ConvSJIStoJISkanaProc(cInfo, *Str++, Put);
			}
			else
			{
				Put = ConvSJIStoJISkanaProc(cInfo, 0, Put);
				if(cInfo->KanjiMode != CONV_ASCII)
				{
					*Put++ = 0x1B;
					*Put++ = '(';
					*Put++ = 'B';
					cInfo->KanjiMode = CONV_ASCII;
				}
				*Put++ = *Str++;
			}
		}
		else
		{
			Put = ConvSJIStoJISkanaProc(cInfo, 0, Put);
			if((uchar)*Str >= (uchar)0x40)
			{
				if(cInfo->KanjiMode != CONV_KANJI)
				{
					*Put++ = 0x1B;
					*Put++ = '$';
					*Put++ = 'B';
					cInfo->KanjiMode = CONV_KANJI;
				}

				Kcode = ConvertIBMExtendedChar(((uchar)cInfo->KanjiFst * 0x100) + (uchar)*Str++);
				Kcode = _mbcjmstojis(Kcode);
				*Put++ = HIGH8(Kcode);
				*Put++ = LOW8(Kcode);
			}
			else
			{
				if(cInfo->KanjiMode != CONV_ASCII)
				{
					*Put++ = 0x1B;
					*Put++ = '(';
					*Put++ = 'B';
					cInfo->KanjiMode = CONV_ASCII;
				}
				*Put++ = cInfo->KanjiFst;
				*Put++ = *Str++;
			}
			cInfo->KanjiFst = 0;
		}
	}

	cInfo->Str = Str;
	cInfo->OutLen = Put - cInfo->Buf;

	return(Continue);
}