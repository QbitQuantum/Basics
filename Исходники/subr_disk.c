static int
disk_debug(int level, char *fmt, ...)
{
	__va_list ap;

	__va_start(ap, fmt);
	if (level <= disk_debug_enable)
		kvprintf(fmt, ap);
	__va_end(ap);

	return 0;
}