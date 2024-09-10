int GTextUtils::Gisalpha(const gint c)
{
#ifdef USE_WIDE_CHARS
	return  iswalpha(c);
#else
	return  isalpha(c);
#endif
}