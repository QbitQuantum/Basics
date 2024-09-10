/*
 * On Windows, use CP<code page number> instead of the nl_langinfo() result
 *
 * Visual Studio 2012 expanded the set of valid LC_CTYPE values, so have its
 * locale machinery determine the code page.  See comments at IsoLocaleName().
 * For other compilers, follow the locale's predictable format.
 *
 * Visual Studio 2015 should still be able to do the same, but the declaration
 * of lc_codepage is missing in _locale_t, causing this code compilation to
 * fail, hence this falls back instead on GetLocaleInfoEx. VS 2015 may be an
 * exception and post-VS2015 versions should be able to handle properly the
 * codepage number using _create_locale(). So, instead of the same logic as
 * VS 2012 and VS 2013, this routine uses GetLocaleInfoEx to parse short
 * locale names like "de-DE", "fr-FR", etc. If those cannot be parsed correctly
 * process falls back to the pre-VS-2010 manual parsing done with
 * using <Language>_<Country>.<CodePage> as a base.
 *
 * Returns a malloc()'d string for the caller to free.
 */
static char *
win32_langinfo(const char *ctype)
{
	char	   *r = NULL;

#if (_MSC_VER >= 1700) && (_MSC_VER < 1900)
	_locale_t	loct = NULL;

	loct = _create_locale(LC_CTYPE, ctype);
	if (loct != NULL)
	{
		r = malloc(16);			/* excess */
		if (r != NULL)
			sprintf(r, "CP%u", loct->locinfo->lc_codepage);
		_free_locale(loct);
	}
#else
	char	   *codepage;

#if (_MSC_VER >= 1900)
	uint32		cp;
	WCHAR		wctype[LOCALE_NAME_MAX_LENGTH];

	memset(wctype, 0, sizeof(wctype));
	MultiByteToWideChar(CP_ACP, 0, ctype, -1, wctype, LOCALE_NAME_MAX_LENGTH);

	if (GetLocaleInfoEx(wctype,
						LOCALE_IDEFAULTANSICODEPAGE | LOCALE_RETURN_NUMBER,
						(LPWSTR) &cp, sizeof(cp) / sizeof(WCHAR)) > 0)
	{
		r = malloc(16);			/* excess */
		if (r != NULL)
			sprintf(r, "CP%u", cp);
	}
	else
#endif
	{
		/*
		 * Locale format on Win32 is <Language>_<Country>.<CodePage> . For
		 * example, English_United States.1252.
		 */
		codepage = strrchr(ctype, '.');
		if (codepage != NULL)
		{
			int			ln;

			codepage++;
			ln = strlen(codepage);
			r = malloc(ln + 3);
			if (r != NULL)
				sprintf(r, "CP%s", codepage);
		}

	}
#endif

	return r;
}