CTime::operator FILETIME() const
{
	FILETIME ft;
	FILETIME localTime;
	SYSTEMTIME st;
	struct tm Time;
	localtime_s(&Time,&m_time);
	st.wYear=Time.tm_year+1900;
	st.wMonth=Time.tm_mon+1;
	st.wDayOfWeek=Time.tm_wday;
	st.wDay=Time.tm_mday;
	st.wHour=Time.tm_hour;
	st.wMinute=Time.tm_min;
	st.wSecond=Time.tm_sec;
	st.wMilliseconds=msec;
	SystemTimeToFileTime(&st,&localTime);
	LocalFileTimeToFileTime(&localTime,&ft);
	return ft;
}