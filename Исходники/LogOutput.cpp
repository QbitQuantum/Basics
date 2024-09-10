void CLogOutput::Print(const char *fmt, ...)
{
	char text[bufferSize];
	va_list	ap;	

	va_start(ap, fmt);
	VSNPRINTF(text, sizeof(text), fmt, ap);
	va_end(ap);

	Output(0, text);
}