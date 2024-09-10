/* Wrapper for sscanf() */
int	gtm_sscanf(char *str, const char *format, ...)
{
	va_list		scanargs;
	int		retval;

	va_start(scanargs, format);
	VSSCANF(str, format, scanargs, retval);
	va_end(scanargs);
	return retval;
}