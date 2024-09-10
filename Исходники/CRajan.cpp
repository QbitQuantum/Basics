inline void __cdecl DebugPrintA(char *format, ...)
{
	static char buff[4096];
	static HANDLE outh = GetStdHandle(STD_OUTPUT_HANDLE);
	static DWORD written;
	va_list va;
	va_start(va, format);
	vsprintf_s(buff, format, va);
	WriteFile(outh, buff, strlen(buff), &written, NULL);
	va_end(va);
}