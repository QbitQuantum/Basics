/**
 * mono_log_write_syslog
 * 	
 * 	Write data to the syslog file.
 *
 * 	@domain - Identifier string
 * 	@level - Logging level flags
 * 	@format - Printf format string
 * 	@vargs - Variable argument list
 */
void
mono_log_write_syslog(const char *domain, GLogLevelFlags level, mono_bool hdr, const char *format, va_list args)
{
	time_t t;
	struct tm *tod;
	char logTime[80],
	      logMessage[512];
	pid_t pid;
	int iLog = 0;
	size_t nLog;

	if (logFile == NULL)
		mono_log_open_syslog(NULL, NULL);

	time(&t);
	tod = localtime(&t);
	pid = _getpid();
	strftime(logTime, sizeof(logTime), "%Y-%m-%d %H:%M:%S", tod);
	iLog = sprintf(logMessage, "%s level[%c] mono[%d]: ",
		       logTime,mapLogFileLevel(level),pid);
	nLog = sizeof(logMessage) - iLog - 2;
	vsnprintf(logMessage+iLog, nLog, format, args);
	iLog = strlen(logMessage);
	logMessage[iLog++] = '\n';
	logMessage[iLog++] = 0;
	fputs(logMessage, logFile);
	fflush(logFile);

	if (level == G_LOG_FLAG_FATAL)
		abort();
}