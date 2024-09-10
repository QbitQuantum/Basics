	time_t getMicroseconds(){
		FILETIME time;

		// TODO: See about replacing this with less precise version
		GetSystemTimePreciseAsFileTime(&time);
		ULARGE_INTEGER lTime;
		lTime.LowPart = time.dwLowDateTime;
		lTime.HighPart = time.dwHighDateTime;
		return (lTime.QuadPart / 10);
	}