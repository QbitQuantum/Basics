char	*
tstostr(char *to, tchar *from)
{
	tchar	*ptc;
	wchar_t	wc;
	char	*pmb;
	int	len;

	if (to == (char *)NULL) {	/* Need to xalloc(). */
		int	i;
		int	i1;
		char	junk[MB_LEN_MAX];

		/* Get sum of byte counts for each char in from. */
		i = 0;
		ptc = from;
		while (wc = (wchar_t)((*ptc++)&TRIM)) {
			if ((i1 = wctomb(junk, wc)) <= 0) {
				i1 = 1;
			}
			i += i1;
		}

		/* Allocate that much. */
		to = (char *)xalloc(i + 1);
	}

	ptc = from;
	pmb = to;
	while (wc = (wchar_t)((*ptc++)&TRIM)) {
		if ((len = wctomb(pmb, wc)) <= 0) {
			*pmb = (unsigned char)wc;
			len = 1;
		}
		pmb += len;
	}
	*pmb = (char)0;
	return (to);
}