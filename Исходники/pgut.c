/*
 * Parse string as uint64
 * valid range: 0 ~ (2^64-1)
 */
bool
parse_uint64(const char *value, uint64 *result)
{
	uint64	val;
	char   *endptr;

	if (strcmp(value, INFINITE_STR) == 0)
	{
#if defined(HAVE_LONG_INT_64)
		*result = ULONG_MAX;
#elif defined(HAVE_LONG_LONG_INT_64)
		*result = ULLONG_MAX;
#else
		*result = ULONG_MAX;
#endif
		return true;
	}

	errno = 0;
#ifdef WIN32
	val = _strtoui64(value, &endptr, 0);
#elif defined(HAVE_LONG_INT_64)
	val = strtoul(value, &endptr, 0);
#elif defined(HAVE_LONG_LONG_INT_64)
	val = strtoull(value, &endptr, 0);
#else
	val = strtoul(value, &endptr, 0);
#endif
	if (endptr == value || *endptr)
		return false;

	if (errno == ERANGE)
		return false;

	*result = val;

	return true;
}