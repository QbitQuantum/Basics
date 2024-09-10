/* For reading in resource names and types.  */
int GetNameOrd()

{
    PWCHAR pch;
    int	fString;

    /* get space delimited string */
    if (!GetGenText())
        return FALSE;

    /* convert to upper case */
    _wcsupr(tokenbuf);

    /* is it a string or number */
    for (pch=tokenbuf,fString=0 ; *pch ; pch++ )
	if (!iswdigit(*pch))
	    fString = 1;

    /* determine if ordinal */
    if (tokenbuf[0] == L'0' && tokenbuf[1] == L'X') {
	int         HexNum;
	int         inc;
	USHORT      wCount;
	PWCHAR      s;

	HexNum = 0;
	s = &tokenbuf[2];
	for (wCount = 4 ; wCount && iswxdigit(*s) ; --wCount)  {
	    if (*s >= L'A')
		inc = *s - L'A' + 10;
	    else
		inc = *s - L'0';
	    HexNum = HexNum * 16 + inc;
	    s++;
	}
	token.val = (USHORT)HexNum;
    }
    else if (fString) {
        token.val = 0;
    }
    else {
	token.val = (USHORT)wcsatoi(tokenbuf);
    }

    return TRUE;
}