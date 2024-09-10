void config_printf_noskip (const char *fmt, ...)
{
	va_list arg; va_start(arg, fmt);
	vfprintf (config_file_out, fmt, arg);
	fputc('\n', config_file_out);
}