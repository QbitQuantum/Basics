static int
pg_wc_islower(pg_wchar c)
{
	switch (pg_regex_strategy)
	{
		case PG_REGEX_LOCALE_C:
			return (c <= (pg_wchar) 127 &&
					(pg_char_properties[c] & PG_ISLOWER));
		case PG_REGEX_LOCALE_WIDE:
#ifdef USE_WIDE_UPPER_LOWER
			if (sizeof(wchar_t) >= 4 || c <= (pg_wchar) 0xFFFF)
				return iswlower((wint_t) c);
#endif
			/* FALL THRU */
		case PG_REGEX_LOCALE_1BYTE:
			return (c <= (pg_wchar) UCHAR_MAX &&
					islower((unsigned char) c));
		case PG_REGEX_LOCALE_WIDE_L:
#if defined(HAVE_LOCALE_T) && defined(USE_WIDE_UPPER_LOWER)
			if (sizeof(wchar_t) >= 4 || c <= (pg_wchar) 0xFFFF)
				return iswlower_l((wint_t) c, pg_regex_locale);
#endif
			/* FALL THRU */
		case PG_REGEX_LOCALE_1BYTE_L:
#ifdef HAVE_LOCALE_T
			return (c <= (pg_wchar) UCHAR_MAX &&
					islower_l((unsigned char) c, pg_regex_locale));
#endif
			break;
	}
	return 0;					/* can't get here, but keep compiler quiet */
}