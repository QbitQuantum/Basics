static void log_v(int priority, const char *fullPath, int line, const char *message, va_list ap)
{
	static int using_terminal = -1;
	if (using_terminal == -1) {
#if defined HAVE_VSYSLOG
#if defined HAVE_VFPRINTF && defined HAVE_ISATTY
		using_terminal = isatty(fileno(stderr));
#else
		using_terminal = 0;
#endif
#elif defined HAVE_VFPRINTF
		using_terminal = 1;
#else
		using_terminal = 0;
#endif
	}

#define LOG_PREAMBLE "%s PJSON %s:%d :: "

	char *pathCopy = strdup(fullPath);
	char *path = strstr(pathCopy, "src/pjson_c");
	if (!path)
		path = pathCopy;
	// TODO: memoize the program name string length
	size_t messageLen = strlen(message) + strlen(path) + 4 /* line number */ + 100 /* chars for message */;
	const char *programNameToPrint = getConsumerName_internal();
	size_t formatLen = messageLen + sizeof(LOG_PREAMBLE) + (using_terminal ? 1 : 0) + strlen(programNameToPrint);
	char *format = alloca(formatLen);
	snprintf(format, formatLen, LOG_PREAMBLE "%s%s", programNameToPrint, path, line, message, using_terminal ? "\n" : "");

#if HAVE_VSYSLOG
	if (LIKELY(!using_terminal)) {
		vsyslog(priority, format, ap);
	} else {
		VFPRINTF(priority, stderr, format, ap);
	}
#elif HAVE_VFPRINTF
	VFPRINTF(priority, stderr, format, ap);
#else
#error Logging mechanism not implemented
#endif

	free(pathCopy);
}