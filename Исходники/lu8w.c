int u8fprintf(FILE *file, const char *format, ...)
{
	int ret = 0;
	va_list argptr;
	char *buf;
	int buflen;
	wchar_t *wbuf;

	va_start(argptr, format);

	buflen = _vscprintf(format, argptr) + 1;
	if(buflen <= 0) {
		return -1;
	}

	buf = (char *)calloc(buflen, sizeof(char));
	if(buf == NULL) {
		return -1;
	}

	vsnprintf(buf, buflen, format, argptr);

	va_end(argptr);

	if(file == stdout || file == stderr) {
		wbuf = u8stows(buf);
		if(wbuf) {
			ret = fwprintf(file, L"%s", wbuf);
			free(wbuf);
		}
	}
	else {
		ret = fprintf(file, "%s", buf);
	}

	free(buf);

	return ret;
}