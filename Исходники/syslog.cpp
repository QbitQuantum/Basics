/*
 * Log to the NT Event Log
 */
void
syslog(int priority, const char *message, ...) {
	va_list ap;
	char buf[1024];
	LPCSTR str[1];

	str[0] = buf;

	va_start(ap, message);
	vsprintf(buf, message, ap);
	va_end(ap);

	/* Make sure that the channel is open to write the event */
	if (hEventLog == NULL) {
		openlog("SoftHSM", 0, 0);
	}
	if (hEventLog != NULL) {
		switch (priority) {
		case LOG_INFO:
		case LOG_NOTICE:
		case LOG_DEBUG:
			ReportEventA(hEventLog, EVENTLOG_INFORMATION_TYPE, 0,
				     0x40000003, NULL, 1, 0, str, NULL);
			break;
		case LOG_WARNING:
			ReportEventA(hEventLog, EVENTLOG_WARNING_TYPE, 0,
				     0x80000002, NULL, 1, 0, str, NULL);
			break;
		default:
			ReportEventA(hEventLog, EVENTLOG_ERROR_TYPE, 0,
				     0xc0000001, NULL, 1, 0, str, NULL);
			break;
		}
	}
}