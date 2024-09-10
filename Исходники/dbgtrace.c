LIBUTILS_API int debug_printfW(const wchar_t * s,...)
{
	wchar_t ss[MAX_LINE_LENGTH];
	int  len;
	va_list arg;
	va_start(arg,s);
	len=wvsprintfW(ss,s,arg);
	va_end(arg);
	OutputDebugStringW(ss);
	return len;
}