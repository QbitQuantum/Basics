FILE *openLog(const char *func, const char *file, int line) {
	char timestamp[TIMESTAMP_BUFFER_LEN];
#ifdef _WIN32
	char delimiter = '\\';
	SYSTEMTIME now;
	FILE *log;
	GetLocalTime(&now);
	sprintf_s(timestamp, TIMESTAMP_BUFFER_LEN, "%d-%02d-%02d %02d:%02d:%02d.%03d", now.wYear, now.wMonth, now.wDay, now.wHour, now.wMinute, now.wSecond, now.wMilliseconds);
#else
	char delimiter = '/';
	struct timeval tv;
	time_t curtime;
	gettimeofday(&tv, NULL);
	curtime = tv.tv_sec;
	strftime(timestamp, 30, "%Y-%m-%d %T", localtime(&curtime));
#ifdef __APPLE__
	sprintf(timestamp + strlen(timestamp), ".%03i ", tv.tv_usec / 1000);
#else
	sprintf(timestamp + strlen(timestamp), ".%03li ", tv.tv_usec / 1000);
#endif
#endif
#ifndef _WIN32
	FILE *log = fopen(getLogFilename(), "a");
#else
	log = _fsopen(getLogFilename(), "a", _SH_DENYNO);
#endif
	fprintf(log, "%s ", timestamp);
	if (file) {
		char *f = strrchr((char *)file, delimiter);
		if (!f) f = (char *)file;
		else f++;
		fprintf(log, "%s() [%s:%i] ", func, f, line);
	}
	return log;
}