/*
 *  stress_strxfrm()
 *	stress on strxfrm
 */
static void stress_strxfrm(
	const char *name,
	char *str1,
	const size_t len1,
	char *str2,
	const size_t len2)
{
	register size_t i;
	char buf[len1 + len2];

	for (i = 0; i < len1 - 1; i++) {
		*buf = '\0';
		STRCHK(name, 0 != strxfrm(buf, str1, sizeof(buf)));
		*buf = '\0';
		STRCHK(name, 0 != strxfrm(buf, str2, sizeof(buf)));
		*buf = '\0';
		STRCHK(name, 0 != strxfrm(buf, str1, sizeof(buf)));
		STRCHK(name, 0 != strxfrm(buf, str2, sizeof(buf)));
		*buf = '\0';
		STRCHK(name, 0 != strxfrm(buf, str2, sizeof(buf)));
		STRCHK(name, 0 != strxfrm(buf, str1, sizeof(buf)));
	}
}