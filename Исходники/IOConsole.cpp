void IOConsole::Error(const char *formatString, ...)
{
	va_list ap;
	va_start(ap, formatString);

	char buffer[MAX_STRING_LENGTH];
	vsnprintf_s(buffer, MAX_STRING_LENGTH, MAX_STRING_LENGTH-1, formatString, ap);

	SetConsoleTextAttribute(m_hOutput, FOREGROUND_RED | FOREGROUND_INTENSITY);
	(*this) << buffer;
	SetConsoleTextAttribute(m_hOutput, FOREGROUND_RED | FOREGROUND_BLUE 
		| FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	va_end(ap);
	//		assert(0);
}