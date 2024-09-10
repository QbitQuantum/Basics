static wchar_t *
towcs(const char *s)
{
	wchar_t *wcs;
	size_t n;

	if ((n = mbsrtowcs(NULL, &s, 0, NULL)) == (size_t)-1)
		return (NULL);
	if ((wcs = malloc((n + 1) * sizeof(*wcs))) == NULL)
		return (NULL);
	mbsrtowcs(wcs, &s, n + 1, NULL);
	return (wcs);
}