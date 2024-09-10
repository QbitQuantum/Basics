static int xstrcasecmp(const char *a, const char *b)
{
	if (a == NULL) {
		if (b == NULL)
			return 0;
		return -1;
	} else if (b == NULL) {
		return 1;
	}
	return u_strcasecmp(a, b);
}