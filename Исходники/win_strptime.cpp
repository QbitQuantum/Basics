static const u_char *
find_string(const u_char *bp, int *tgt, const char * const *n1,
		const char * const *n2, int c)
{
	int i;
	unsigned int len;

	/* check full name - then abbreviated ones */
	for (; n1 != NULL; n1 = n2, n2 = NULL) {
		for (i = 0; i < c; i++, n1++) {
			len = strlen(*n1);
//			if (strncasecmp(*n1, (const char *)bp, len) == 0) {
			if (CompareStringA(LOCALE_SYSTEM_DEFAULT, NORM_IGNORECASE, *n1, -1, (const char *)bp, len) == CSTR_EQUAL) {
				*tgt = i;
				return bp + len;
			}
		}
	}

	/* Nothing matched */
	return NULL;
}