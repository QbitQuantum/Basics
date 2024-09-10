int
swscanf(const wchar_t *wstr, const wchar_t *fmt, ...)
{
	int ret;
	va_list	ap;

	va_start(ap, fmt);
	ret = vswscanf(wstr, fmt, ap);
	va_end(ap);

	return (ret);
}