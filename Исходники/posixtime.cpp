int gettimeofday(struct timeval*tv, struct timezone*tz)
{
	FILETIME ft;
	unsigned __int64 tmpres = 0;
	static int tzflag;

	if (tv != nullptr)
	{
		GetSystemTimeAsFileTime(&ft);
		
		tmpres |= ft.dwHighDateTime;
		tmpres <<= 32;
		tmpres |= ft.dwLowDateTime;
		
		/*converting file time to unix epoch*/
		tmpres -= DELTA_EPOCH_IN_MICROSECS; 
		tmpres /= 10;  /*convert into microseconds*/
		tv->tv_sec = (long)(tmpres / 1000000UL);
		tv->tv_usec = (long)(tmpres % 1000000UL);
	}

	if (tz != nullptr)
	{
		if (!tzflag)
		{
			_tzset();
			tzflag++;
		}
		long timezoneseconds = 0;
		_get_timezone(&timezoneseconds);
		tz->tz_minuteswest = (int)(timezoneseconds / 60);
		int dsthours = 0;
		_get_daylight(&dsthours);
		tz->tz_dsttime = dsthours;
	}

	return 0;
}