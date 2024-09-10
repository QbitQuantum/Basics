int   ftk_vsnprintf(char *str, size_t size, const char *format, va_list ap)
{
	return _vsnprintf(str, size-1, format, ap);
}