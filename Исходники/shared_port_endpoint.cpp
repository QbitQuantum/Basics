void ThreadSafeLogError(const char * msg, int err) {
	char buf[200];
	struct _timeb tv;
	struct tm tm;
	_ftime(&tv);
	_localtime64_s(&tm, &tv.time);
	strftime(buf, 80, "%H:%M:%S", &tm);
	sprintf(buf+strlen(buf), ".%03d %.100s: %d\n", tv.millitm, msg, err);
	OutputDebugString(buf);
}