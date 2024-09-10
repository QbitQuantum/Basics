/* EXTPROTO */
char*
rxvt_wcstombs (const wchar_t* str, int len)
{
	mbstate_t	mbs;
	char*	r;
	char*	dst;

	if (len < 0)
		len = wcslen (str);

	memset (&mbs, 0, sizeof (mbs));
	r = (char *)rxvt_malloc (len * MB_CUR_MAX + 1);
	dst = r;

	while (len--) {
		int l = wcrtomb (dst, *str++, &mbs);
		if (l < 0)
			*dst++ = '?';
		else
			dst += l;
	}

	*dst++ = 0;

	return r;
}