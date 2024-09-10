int vwprintf(const wchar_t *format, va_list args)
{
	wchar_t buf[1024];
	int ret = wvsprintfW(buf, format, args);

	char ansibuf[1024];
	WideCharToMultiByte(CP_ACP, 0, buf, -1, ansibuf, sizeof(ansibuf), 0, 0);
	fwrite(ansibuf, ret, 1, stdout);

	return ret;
}