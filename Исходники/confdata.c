static void conf_default_message_callback(const char *fmt, va_list ap)
{
	printf("#\n# ");
	vprintf(fmt, ap);
	printf("\n#\n");
}