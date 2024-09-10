extern int
_stdvsscanf(char* s, const char* fmt, va_list args)
{
	return vsscanf(s, fmt, args);
}