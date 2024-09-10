/*
 * On win32, strftime() returns the encoding in CP_ACP, which is likely
 * different from SERVER_ENCODING. This is especially important in Japanese
 * versions of Windows which will use SJIS encoding, which we don't support
 * as a server encoding.
 *
 * Replace strftime() with a version that gets the string in UTF16 and then
 * converts it to the appropriate encoding as necessary.
 *
 * Note that this only affects the calls to strftime() in this file, which are
 * used to get the locale-aware strings. Other parts of the backend use
 * pg_strftime(), which isn't locale-aware and does not need to be replaced.
 */
static size_t
strftime_win32(char *dst, size_t dstlen, const wchar_t *format, const struct tm *tm)
{
	size_t	len;
	wchar_t	wbuf[MAX_L10N_DATA];
	int		encoding;

	encoding = GetDatabaseEncoding();

	len = wcsftime(wbuf, MAX_L10N_DATA, format, tm);
	if (len == 0)
		/* strftime call failed - return 0 with the contents of dst unspecified */
		return 0;

	len = WideCharToMultiByte(CP_UTF8, 0, wbuf, len, dst, dstlen, NULL, NULL);
	if (len == 0)
		elog(ERROR,
			"could not convert string to UTF-8:error %lu", GetLastError());

	dst[len] = '\0';
	if (encoding != PG_UTF8)
	{
		char *convstr = pg_do_encoding_conversion(dst, len, PG_UTF8, encoding);
		if (dst != convstr)
		{
			strlcpy(dst, convstr, dstlen);
			len = strlen(dst);
		}
	}

	return len;
}