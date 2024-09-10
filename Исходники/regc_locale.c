static int
pg_wc_islower(pg_wchar c)
{
#ifdef USE_WIDE_UPPER_LOWER
	if (GetDatabaseEncoding() == PG_UTF8)
	{
		if (sizeof(wchar_t) >= 4 || c <= (pg_wchar) 0xFFFF)
			return iswlower((wint_t) c);
	}
#endif
	return (c <= (pg_wchar) UCHAR_MAX && islower((unsigned char) c));
}