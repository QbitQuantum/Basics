int hv_snprintf(char* str, hv_size_t size, const char* format, ...) {
  // http://stackoverflow.com/questions/2915672/snprintf-and-visual-studio-2010
	int count = -1;
	va_list ap;
	va_start(ap, format);

	if (size != 0) {
		count = _vsnprintf_s(str, size, _TRUNCATE, format, ap);
	}
	if (count == -1) {
		count = _vscprintf(format, ap);
	}
	va_end(ap);
	return count;
}