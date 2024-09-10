void wdbg_printf(const wchar_t* fmt, ...)
{
	wchar_t buf[1024+1];	// wvsprintfW will truncate to this size
	va_list ap;
	va_start(ap, fmt);
	wvsprintfW(buf, fmt, ap);	// (return value doesn't indicate whether truncation occurred)
	va_end(ap);

	OutputDebugStringW(buf);
}