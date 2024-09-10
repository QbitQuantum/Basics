static char *
readpassphrase(const char *prompt, char *buf, size_t bufsiz, int flags)
{
	HANDLE hStdin, hStdout;
	DWORD mode, rbytes;
	BOOL success;

	(void)flags;

	hStdin = GetStdHandle(STD_INPUT_HANDLE);
	if (hStdin == INVALID_HANDLE_VALUE)
		return (NULL);
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdout == INVALID_HANDLE_VALUE)
		return (NULL);

	success = GetConsoleMode(hStdin, &mode);
	if (!success)
		return (NULL);
	mode &= ~ENABLE_ECHO_INPUT;
	mode |= ENABLE_LINE_INPUT | ENABLE_PROCESSED_INPUT;
	success = SetConsoleMode(hStdin, mode);
	if (!success)
		return (NULL);

	success = WriteFile(hStdout, prompt, (DWORD)strlen(prompt),
		NULL, NULL);
	if (!success)
		return (NULL);
	success = ReadFile(hStdin, buf, (DWORD)bufsiz - 1, &rbytes, NULL);
	if (!success)
		return (NULL);
	WriteFile(hStdout, "\r\n", 2, NULL, NULL);
	buf[rbytes] = '\0';
	/* Remove trailing carriage return(s). */
	if (rbytes > 2 && buf[rbytes - 2] == '\r' && buf[rbytes - 1] == '\n')
		buf[rbytes - 2] = '\0';

	return (buf);
}