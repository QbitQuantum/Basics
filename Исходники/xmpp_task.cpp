void Task::debug(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	QString str;
	str.vsprintf(fmt, ap);
	va_end(ap);
	debug(str);
}