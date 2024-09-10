int cprintf(const char *__format, ...)
{
	char buffer[MAX_BUFFER];
	int r;
	va_list ap;
	va_start(ap, __format);
	r = vsprintf_s(buffer, __format, ap);
	va_end(ap);
	cputs(buffer);
	return r;
}