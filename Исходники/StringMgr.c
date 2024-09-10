/***********************************************************************
 *
 * FUNCTION:	StrChr
 *
 * DESCRIPTION: This routine looks for a character within a string. It
 *		behaves the same as the standard C library function strchr, except
 *		that it works correctly with multi-byte character encodings.
 *
 * PARAMETERS:
 *		str  - string to search
 *		chr  - the character to search for
 *
 * RETURNED:	pointer to the first occurance of character in str, or NULL
 *		if not found.
 *
 * HISTORY:
 *		08/18/95	ron	Created by Ron Marianetti
 *		05/07/96	rsf	Fixed to MemHandle searching for '\0'
 *		10/24/96	rsf	Check chr
 *		08/12/97	ADH	Revised Algorithm
 *		08/26/98	kwk	Changed chr param from Int16 to WChar. Fixed up
 *							sign extension problem.
 *		05/13/00	kwk	Made it work for all char encodings, not just Latin.
 *
 ***********************************************************************/
Char* StrChr(const Char* str, WChar chr)
{
	Char c = (Char)chr;
	register const Char* srcP = str;
	
	ErrNonFatalDisplayIf(str == NULL, "NULL string passed");

	// Correct for sign extension. This will happen if the caller passes
	// a single byte >= 0x80, which the compiler will sign extend.
	if (chr >= 0xFF80)
	{
		ErrNonFatalDisplay("Sign extended character passed to StrChr");
		chr = chr & 0x00FF;
	}
	
	// See if we need to do the slower (multi-byte) search case.
	if (chr > kTxtMaxAlwaysSingleByte)
	{
		Char buffer[maxCharBytes + 1];
		UInt16 len = TxtSetNextChar(buffer, 0, chr);
		if (len > 1)
		{
			buffer[len] = '\0';
			return(StrStr(str, buffer));
		}
	}
	
	// Be sure to handle chr == '\0' correctly
	do
	{
		if (*srcP == c)
		{
			// If the character we're searching for could be part of a
			// multi-byte character, then we need to do an extra check
			// to make sure we didn't find part of a multi-byte character.
			// Since most people use StrChr to search for tabs, returns,
			// etc. this typically never gets executed.
			if (chr > kTxtMaxNeverMultiByte)
			{
				UInt32 charStart, charEnd;
				UInt32 charOffset = srcP - str;
				TxtCharBounds(str, charOffset, &charStart, &charEnd);
				if (charStart == charOffset)
				{
					return((Char*)srcP);
				}
			}
			else
			{
				return((Char*)srcP);
			}
		}
	} while (*srcP++ != 0);
	
	return(NULL);
} // StrChr