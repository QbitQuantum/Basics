/*--------------------------------------------------------------------------*/
char *getlongpathname(char *shortpathname,BOOL *convertok)
{
	char *LongName = NULL;
	wchar_t *wcshortpathname = to_wide_string(shortpathname);
	if (wcshortpathname)
	{
		wchar_t *wcLongName = getlongpathnameW(wcshortpathname, convertok);
		if (wcLongName)
		{
			LongName = wide_string_to_UTF8(wcLongName);
			FREE(wcLongName); wcLongName = NULL;
		}
		else
		{
			LongName = strdup(shortpathname);
			*convertok = FALSE;
		}
	}
	else
	{
		LongName = strdup(shortpathname);
		*convertok = FALSE;
	}
	return LongName;
}