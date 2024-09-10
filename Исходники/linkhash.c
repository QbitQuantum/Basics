void lh_abort(const wchar_t *msg, ...)
{
	va_list ap;
	va_start(ap, msg);
	vwprintf(msg, ap);
	va_end(ap);
	exit(1);
}