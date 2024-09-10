static __inline int
convert_wccl(FILE *fp, wchar_t *wcp, int width, const char *ccltab,
    locale_t locale)
{
	mbstate_t mbs;
	wint_t wi;
	int n, nread;

	mbs = initial_mbs;
	n = 0;
	if (wcp == SUPPRESS_PTR) {
		while ((wi = __fgetwc_mbs(fp, &mbs, &nread, locale)) != WEOF &&
		    width-- != 0 && ccltab[wctob(wi)])
			n += nread;
		if (wi != WEOF)
			__ungetwc(wi, fp, __get_locale());
	} else {
		while ((wi = __fgetwc_mbs(fp, &mbs, &nread, locale)) != WEOF &&
		    width-- != 0 && ccltab[wctob(wi)]) {
			*wcp++ = (wchar_t)wi;
			n += nread;
		}
		if (wi != WEOF)
			__ungetwc(wi, fp, __get_locale());
		if (n == 0)
			return (0);
		*wcp = 0;
	}
	return (n);
}