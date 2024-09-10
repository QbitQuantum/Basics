int gtm_snprintf(char *str, size_t size, const char *format, ...)
{ /* hack for VMS, ignore size argument and call sprintf. When snprintf becomes available on VMS, nix this file and define SNPRINTF
   * in gtm_stdio.h to snprintf */

	va_list	printargs;
	int	retval, rc;

	va_start(printargs, format);
	retval = VSPRINTF(str, format, printargs, rc);
	va_end(printargs);
	return retval;
}