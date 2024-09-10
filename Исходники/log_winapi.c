void log_handler_platform(LogCategory category, LogLevel level,
                          const char *file, int line,
                          const char *function, const char *format,
                          va_list arguments) {
	WORD type;
	DWORD event_id;
	char message[512 + 1] = "<unknown>";
	LPCSTR insert_strings[1];

	(void)category;
	(void)file;
	(void)line;
	(void)function;

	if (_event_log == NULL) {
		return;
	}

	switch (level) {
	case LOG_LEVEL_ERROR:
		type = EVENTLOG_ERROR_TYPE;
		event_id = BRICKD_GENERIC_ERROR;
		break;

	case LOG_LEVEL_WARN:
		type = EVENTLOG_WARNING_TYPE;
		event_id = BRICKD_GENERIC_WARNING;
		break;

	default:
		// ignore all other log levels
		return;
	}

#ifdef _MSC_VER
	_vsnprintf_s(message, sizeof(message), sizeof(message) - 1, format, arguments);
#else
	vsnprintf(message, sizeof(message), format, arguments);
#endif

	insert_strings[0] = message;

	ReportEvent(_event_log, type, 0, event_id, NULL, 1, 0, insert_strings, NULL);
}