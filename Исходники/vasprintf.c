int
vasprintf(char **ret, const char *fmt, va_list ap)
{
#if HAVE_VSNPRINTF
	int chunks;
	size_t buflen;
	char *buf;
	int len;

	chunks = ((strlen(fmt) + 1) / CHUNKSIZE) + 1;
	buflen = chunks * CHUNKSIZE;
	for (;;) {
		if ((buf = malloc(buflen)) == NULL) {
			*ret = NULL;
			return -1;
		}
		len = vsnprintf(buf, buflen, fmt, ap);
		if (len >= 0 && len < (buflen - 1)) {
			break;
		}
		free(buf);
		buflen = (++chunks) * CHUNKSIZE;
		if (len >= 0 && len >= buflen) {
			buflen = len + 1;
		}
	}
	*ret = buf;
	return len;
#else /* HAVE_VSNPRINTF */
#ifdef _REENTRANT
	FILE *fp;
#else /* !_REENTRANT */
	static FILE *fp = NULL;
#endif /* !_REENTRANT */
	int len;
	char *buf;

	*ret = NULL;

#ifdef _REENTRANT

# ifdef WIN32
#  error Win32 do not have /dev/null, should use vsnprintf version
# endif

	if ((fp = fopen(_PATH_DEVNULL, "w")) == NULL)
		return -1;
#else /* !_REENTRANT */
	if ((fp == NULL) && ((fp = fopen(_PATH_DEVNULL, "w")) == NULL))
		return -1;
#endif /* !_REENTRANT */

	len = vfprintf(fp, fmt, ap);

#ifdef _REENTRANT
	if (fclose(fp) != 0)
		return -1;
#endif /* _REENTRANT */

	if (len < 0)
		return len;
	if ((buf = malloc(len + 1)) == NULL)
		return -1;
	if (vsprintf(buf, fmt, ap) != len)
		return -1;
	*ret = buf;
	return len;
#endif /* HAVE_VSNPRINTF */
}