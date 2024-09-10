/*
 * Format the given arguments and append the resulting string to an sbuf.
 */
int
sbuf_printf(struct sbuf *s, const char *fmt, ...)
{
	__va_list ap;
	int result;

	__va_start(ap, fmt);
	result = sbuf_vprintf(s, fmt, ap);
	__va_end(ap);
	return (result);
}