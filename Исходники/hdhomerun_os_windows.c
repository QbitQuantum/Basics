/*
 * The console output format should be set to UTF-8, however in XP and Vista this breaks batch file processing.
 * Attempting to restore on exit fails to restore if the program is terminated by the user.
 * Solution - set the output format each printf.
 */
void console_vprintf(const char *fmt, va_list ap)
{
	UINT cp = GetConsoleOutputCP();
	SetConsoleOutputCP(CP_UTF8);
	vprintf(fmt, ap);
	SetConsoleOutputCP(cp);
}