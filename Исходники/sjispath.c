char sjis_getlastchar(char *s)
{
	if (!s || !*s) {
		return 0;
	}
	if (!_ismbstrail((const unsigned char *)s, s + strlen(s) - 1)) {
		return s[strlen(s) - 1];
	}
	return 0;
}