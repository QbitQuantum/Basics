int scanf(const char * fmt, ...) {
	va_list args;
	int read;

	va_start(args, fmt);
	read = vscanf(fmt, args);
	va_end(args);
	
	return read;
}