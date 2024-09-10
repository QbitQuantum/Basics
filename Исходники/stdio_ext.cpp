int wz_vsnprintf(char* str, size_t size, const char* format, va_list ap)
{
	int count;
	va_list aq;

	va_copy(aq, ap);

	// Find out how long the resulting string is
	count = _vscprintf(format, aq);
	va_end(aq);

	if (count >= 0
	 && str != NULL)
	{
		// Perfrom the actual string formatting
		_vsnprintf_s(str, size, _TRUNCATE, format, ap);
	}

	// Return the amount of characters that would be written if _no_ truncation occurred
	return count;
}