int waeprintf (const char *fmt, ...)
{
	int result = 0;
	int strSize, param;
	char *strBuff, *s;
	va_list args;
	HANDLE hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE
	 || !GetConsoleScreenBufferInfo(hStdOut, &csbi))
	{
		/* Attempt fallback, fixes MSYS. */
		va_start (args, fmt);
		result = vprintf (fmt, args);
		va_end (args);
		fflush (stdout);
		return result;
	}

	/* Find out how much memory to allocate. */
	va_start(args, fmt);
	strSize = vsnprintf(NULL, 0, fmt, args);
	va_end(args);

	if (!(strBuff = malloc(strSize + 1)))
		return -1;

	va_start(args, fmt);
	result = vsnprintf(strBuff, strSize + 1, fmt, args);
	va_end(args);

	for (s = strBuff; *s;)
	{
		char *p, code, changed;

		if (*s != '\x1b')
		{
			putchar(*s++);
			continue;
		}
		if (*++s != '[')
		{
			putchar(*s++);
			continue;
		}
		p = ++s;
		while (*s && (*s < 64 || *s > 126))
			s++;
		if (!*s)
			break;

		/* We only care for colors so far. */
		if ((code = *s++) != 'm')
			continue;
		for (param = changed = 0; p < s; p++)
		{
			if (*p >= '0' && *p <= '9')
				param = param * 10 + *p - '0';
			else
			{
				changed |= waeprocess(&csbi, code, param);
				param = 0;
			}
		}
		if (changed)
			SetConsoleTextAttribute(hStdOut, csbi.wAttributes);
	}

	free(strBuff);
	return result;
}