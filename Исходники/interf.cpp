void vmprintf(const WCHAR *fmt,...)
{
	va_list argptr;
	va_start(argptr,fmt);
	WCHAR OutStr[2048];
	_vsnwprintf(OutStr,ARRAYSIZE(OutStr)-1,fmt,argptr);
	VText(OutStr);
	va_end(argptr);
}