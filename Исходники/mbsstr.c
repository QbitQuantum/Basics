unsigned char * __cdecl _mbsstr(
    const unsigned char *str1,
    const unsigned char *str2
    )
{
	unsigned char *cp, *s1, *s2, *endp;

        if (0 == __mbcodepage)
            return strstr(str1, str2);

	cp = (unsigned char *) str1;
	endp = (unsigned PCHAR) (str1 + (_BYTELEN(str1) - _BYTELEN(str2)));

	while (*cp && (cp <= endp))
	{
		s1 = cp;
		s2 = (PCHAR) str2;

		/*
		 * MBCS: ok to ++ since doing equality comparison.
		 * [This depends on MBCS strings being "legal".]
		 */

		while ( *s1 && *s2 && (*s1 == *s2) )
			s1++, s2++;

		if (!(*s2))
			return(cp);	/* success! */

		/*
		 * bump pointer to next char
		 */

		cp = _MBSINC(cp);

	}

	return(NULL);

}