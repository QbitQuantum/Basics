void FHTML5PlatformTime::UtcTime( int32& Year, int32& Month, int32& DayOfWeek, int32& Day, int32& Hour, int32& Min, int32& Sec, int32& MSec )
{
	time_t ltime;
	time(&ltime);
	struct tm gmt;

	_gmtime64_s(&gmt, &ltime);

	Year		= gmt.tm_year + 1900;
	Month		= gmt.tm_mon + 1;
	DayOfWeek	= gmt.tm_wday;
	Day			= gmt.tm_mday;
	Hour		= gmt.tm_hour;
	Min			= gmt.tm_min;
	Sec			= gmt.tm_sec;
	MSec		= 0;
}