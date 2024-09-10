int
ntp_set_tod(
	struct timespec *tp
	)
{
	SYSTEMTIME st;
	union {
		FILETIME ft;
		ULONGLONG ull;
	} t;

	t.ull = FILETIME_1970 +
		(ULONGLONG)tv->tv_sec * 10 * 1000 * 1000 +
		(ULONGLONG)tv->tv_nsec / 100;

	if (!FileTimeToSystemTime(&t.ft, &st) || !SetSystemTime(&st)) {
		msyslog(LOG_ERR, "SetSystemTime failed: %m");
		return -1;
	}

	return 0;
}