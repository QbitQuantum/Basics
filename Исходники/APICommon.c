void CCALL	WriteReport_Alert (const char* format, ...)
{
	char		buffer [512];
	va_list		argList;

	va_start (argList, format);
#if defined (macintosh)
	vsnprintf (buffer, sizeof (buffer), format, argList);
#else
	vsnprintf_s (buffer, sizeof (buffer), _TRUNCATE, format, argList);
#endif

	ACAPI_WriteReport (buffer, true);

	return;
}		// WriteReport_Alert