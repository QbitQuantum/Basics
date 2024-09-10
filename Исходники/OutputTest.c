static int TEST_vprintf(const char *fmt, va_list ap)
{
	return vfprintf(GetLogFile(), fmt, ap);
}