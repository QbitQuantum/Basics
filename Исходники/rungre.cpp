int vprintf(const char* format, va_list args){
	char buffer[4096];
	int r=vsprintf(buffer, format, args);
	gre_write(STDOUT_FILENO, buffer, r);
	return r;
}