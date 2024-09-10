static int printf_wrapper(FILE *f, const char *fmt, ...)
{
	va_list argptr;
	int count;

	va_start(argptr, fmt);
	if (f == NULL)
	{
		count = VPrintf(PRINT_HIGH, fmt, argptr);
	}
	else
	{
		count = vfprintf(f, fmt, argptr);
	}
	va_end(argptr);
	return count;
}