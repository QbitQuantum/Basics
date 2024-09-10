ev_int64_t
evutil_strtoll(const char *s, char **endptr, int base)
{
#ifdef HAVE_STRTOLL
	return (ev_int64_t)strtoll(s, endptr, base);
#elif SIZEOF_LONG == 8
	return (ev_int64_t)strtol(s, endptr, base);
#elif defined(WIN32) && defined(_MSC_VER) && _MSC_VER < 1300
	/* XXXX on old versions of MS APIs, we only support base
	 * 10. */
	ev_int64_t r;
	if (base != 10)
		return 0;
	r = (ev_int64_t) _atoi64(s);
	while (isspace(*s))
		++s;
	while (isdigit(*s))
		++s;
	if (endptr)
		*endptr = (char*) s;
	return r;
#elif defined(WIN32)
	return (ev_int64_t) _strtoi64(s, endptr, base);
#else
#error "I don't know how to parse 64-bit integers."
#endif
}