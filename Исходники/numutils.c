/*
 * pg_strtouint64
 *		Converts 'str' into an unsigned 64-bit integer.
 *
 * This has the identical API to strtoul(3), except that it will handle
 * 64-bit ints even where "long" is narrower than that.
 *
 * For the moment it seems sufficient to assume that the platform has
 * such a function somewhere; let's not roll our own.
 */
uint64
pg_strtouint64(const char *str, char **endptr, int base)
{
#ifdef _MSC_VER					/* MSVC only */
	return _strtoui64(str, endptr, base);
#elif defined(HAVE_STRTOULL) && SIZEOF_LONG < 8
	return strtoull(str, endptr, base);
#else
	return strtoul(str, endptr, base);
#endif
}