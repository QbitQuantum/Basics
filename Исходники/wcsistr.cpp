wchar_t* _wsetlocale_map(int category, const wchar_t *locale)
{
	wchar_t *ret = _wsetlocale(category, locale);

	for (wchar_t c = 0; c < 256; ++c)
	{
		g_mapToLower[c] = towlower(c);
		g_mapToUpper[c] = towupper(c);
	}
	
	return ret;
}