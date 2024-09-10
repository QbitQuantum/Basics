TimerWord ThreadUserTimer::GetCurrentTimerValue()
{
#if defined(CRYPTOPP_WIN32_AVAILABLE) && defined(THREAD_TIMER_AVAILABLE)
	static bool getCurrentThreadImplemented = true;
	if (getCurrentThreadImplemented)
	{
		FILETIME now, ignored;
		if (!GetThreadTimes(GetCurrentThread(), &ignored, &ignored, &ignored, &now))
		{
			const DWORD lastError = GetLastError();
			if (lastError == ERROR_CALL_NOT_IMPLEMENTED)
			{
				getCurrentThreadImplemented = false;
				goto GetCurrentThreadNotImplemented;
			}
			throw Exception(Exception::OTHER_ERROR, "ThreadUserTimer: GetThreadTimes failed with error " + IntToString(lastError));
		}
		return now.dwLowDateTime + ((TimerWord)now.dwHighDateTime << 32);
	}
GetCurrentThreadNotImplemented:
	return (TimerWord)clock() * (10*1000*1000 / CLOCKS_PER_SEC);
#elif defined(CRYPTOPP_WIN32_AVAILABLE) && !defined(THREAD_TIMER_AVAILABLE)
	LARGE_INTEGER now;
	if (!QueryPerformanceCounter(&now))
	{
		const DWORD lastError = GetLastError();
		throw Exception(Exception::OTHER_ERROR, "ThreadUserTimer: QueryPerformanceCounter failed with error " + IntToString(lastError));
	}
	return now.QuadPart;
#elif defined(CRYPTOPP_UNIX_AVAILABLE)
	tms now;
	times(&now);
	return now.tms_utime;
#else
	return clock();
#endif
}