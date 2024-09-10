extern void DBG(const char *format, ...)
{
#if DEBUG
	va_list ap;
	char msg[256];
	va_start(ap, format);
	_vsprintf_p(msg, 256, format, ap);
	va_end(ap);
	elog(NOTICE, msg);
#endif
}