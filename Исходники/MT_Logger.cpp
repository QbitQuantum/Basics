void MT_Logger::Log(char *format, ...)
{
	va_list args;
	va_start(args, format);

	char buffer[512];
	vsprintf_s(buffer, sizeof(buffer), format, args);
	OutputDebugStringA(buffer);

	va_end(args);
}