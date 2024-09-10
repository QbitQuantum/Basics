void LocalConsole::Write(const char * Format, ...)
{
	va_list ap;
	va_start(ap, Format);
	vprintf(Format, ap);
}