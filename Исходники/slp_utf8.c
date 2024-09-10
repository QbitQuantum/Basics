/*
 * Same semantics as strchr.
 * Assumes that we start on a char boundry, and that c is a 7-bit
 * ASCII char.
 */
char *slp_utf_strchr(const char *s, char c) {
	int len;
	char *p;

	for (p = (char *)s; *p; p += len) {
		len = mblen(p, MB_CUR_MAX);
		if (len == 1 && *p == c)
			return (p);
	}
	return (NULL);
}