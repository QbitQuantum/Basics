static UINT SIOFmtPut(LPCSTR Fmt, ...)
{
	UINT cch;
	char buf[150]; // Plenty for our simple strings
	va_list val;
	va_start(val, Fmt);
	cch = wvsprintfA(buf, Fmt, val);
	cch = SIOPut(buf, cch);
	va_end(val);
	return cch;
}