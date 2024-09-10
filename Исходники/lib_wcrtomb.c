size_t wcrtomb(FAR char *s, wchar_t wc, FAR mbstate_t *ps)
{
	int retval = 0;
	char buf[10];

	if (s == NULL) {
		retval = wctomb((char *)buf, L'\0');
	} else {
		retval = wctomb(s, wc);
	}

	if (retval == -1) {
		return (size_t)(-1);
	} else {
		return (size_t) retval;
	}
}