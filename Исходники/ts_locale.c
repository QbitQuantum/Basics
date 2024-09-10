/*
 * lowerstr_with_len --- fold string to lower case
 *
 * Input string need not be null-terminated.
 *
 * Returned string is palloc'd
 */
char *
lowerstr_with_len(const char *str, int len)
{
	char	   *out;

#ifdef USE_WIDE_UPPER_LOWER
	Oid			collation = DEFAULT_COLLATION_OID;		/* TODO */
	pg_locale_t	mylocale = 0;	/* TODO */
#endif

	if (len == 0)
		return pstrdup("");

#ifdef USE_WIDE_UPPER_LOWER

	/*
	 * Use wide char code only when max encoding length > 1 and ctype != C.
	 * Some operating systems fail with multi-byte encodings and a C locale.
	 * Also, for a C locale there is no need to process as multibyte. From
	 * backend/utils/adt/oracle_compat.c Teodor
	 */
	if (pg_database_encoding_max_length() > 1 && !lc_ctype_is_c(collation))
	{
		wchar_t    *wstr,
				   *wptr;
		int			wlen;

		/*
		 * alloc number of wchar_t for worst case, len contains number of
		 * bytes >= number of characters and alloc 1 wchar_t for 0, because
		 * wchar2char wants zero-terminated string
		 */
		wptr = wstr = (wchar_t *) palloc(sizeof(wchar_t) * (len + 1));

		wlen = char2wchar(wstr, len + 1, str, len, mylocale);
		Assert(wlen <= len);

		while (*wptr)
		{
			*wptr = towlower((wint_t) *wptr);
			wptr++;
		}

		/*
		 * Alloc result string for worst case + '\0'
		 */
		len = pg_database_encoding_max_length() * wlen + 1;
		out = (char *) palloc(len);

		wlen = wchar2char(out, wstr, len, mylocale);

		pfree(wstr);

		if (wlen < 0)
			ereport(ERROR,
					(errcode(ERRCODE_CHARACTER_NOT_IN_REPERTOIRE),
			errmsg("conversion from wchar_t to server encoding failed: %m")));
		Assert(wlen < len);
	}
	else
#endif   /* USE_WIDE_UPPER_LOWER */
	{
		const char *ptr = str;
		char	   *outptr;

		outptr = out = (char *) palloc(sizeof(char) * (len + 1));
		while ((ptr - str) < len && *ptr)
		{
			*outptr++ = tolower(TOUCHAR(ptr));
			ptr++;
		}
		*outptr = '\0';
	}

	return out;
}