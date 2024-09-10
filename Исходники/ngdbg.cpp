VOID _cdecl EngPrint (char *fmt, ...)
{
	va_list va;
	va_start (va, fmt);

	EngDebugPrint ("", fmt, va);
}