void udi_debug_printf( const char *format, ... )
{
	va_list	args;
	va_start(args, format);
	LogF("udi_debug_printf: ");
	LogFV(format, args);
	va_end(args);
}