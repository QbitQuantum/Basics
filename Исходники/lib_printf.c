static int
do_printf (const char *format, va_list ap, int (*func)(int c, void *data),
	   void *data)
{
	char c;
	int n, f;
	int width, precision;

	n = 0;
	while ((c = *format++) != '\0') {
		if (c == '%') {
			f = parse_format (&format, &width, &precision);
			if (f & LENGTH_INTMAX)
				f |= LENGTH_LONGLONG;
			else if (f & LENGTH_SIZE)
				f |= LENGTH_LONG;
			else if (f & LENGTH_PTRDIFF)
				f |= LENGTH_LONG;
			if (f == END_STRING) {
				break;
			} else if (f & CONVERSION_NONE) {
				PUTCHAR ('%');
			} else if (f & CONVERSION_INT) {
				long long intval;
				unsigned long long uintval;

				if (f & LENGTH_CHAR)
					intval = (long long)va_arg (ap, int);
				else if (f & LENGTH_SHORT)
					intval = (long long)va_arg (ap, int);
				else if (f & LENGTH_LONGLONG)