/* ------------------ L2str ------------------- */
void __CDECL
L2str( const PLstr s )
{
	if (LTYPE(*s)==LINTEGER_TY) {
#if defined(WCE) || defined(__BORLANDC__)
		LTOA(LINT(*s),LSTR(*s),10);
#else
		sprintf(LSTR(*s), "%ld", LINT(*s));
#endif
		LLEN(*s) = STRLEN(LSTR(*s));
	} else {	/* LREAL_TY */
		/* There is a problem with the Windows CE */
		char	str[50];
		size_t	len;

		snprintf(str, sizeof(str), "%.*g", lNumericDigits, LREAL(*s));
		/* --- remove the last dot from the number --- */
		len = STRLEN(str);
#ifdef WCE
		if (str[len-1] == '.') len--;
#endif
		if (len>=LMAXLEN(*s)) Lfx(s,len);
		MEMCPY(LSTR(*s),str,len);
		LLEN(*s) = len;
	}
	LTYPE(*s) = LSTRING_TY;
} /* L2str */