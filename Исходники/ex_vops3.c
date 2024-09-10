static void
cswitch(char *dst, int *dn, const char *src, int *sn)
{
	int	c;

#ifdef	MB
	if (mb_cur_max > 1) {
		nextc(c, src, *sn);
		if (c & INVBIT) {
			*dst = *src;
			*dn = *sn = 1;
		} else {
			if (iswupper(c))
				c = towlower(c);
			else if (iswlower(c))
				c = towupper(c);
			if ((*dn = wctomb(dst, c)) > *sn) {
				*dst = *src;
				*dn = *sn = 1;
			}
		}
	} else
#endif	/* MB */
	{
		c = *src & 0377;
		if (isupper(c))
			*dst = tolower(c);
		else if (islower(c))
			*dst = toupper(c);
		else
			*dst = c;
		*dn = *sn = 1;
	}
}