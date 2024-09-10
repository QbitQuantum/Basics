void _formatTime(std::ostringstream &ss, time_t t)
{
	struct tm tm1;
	char szTime[24];
#ifdef _WIN32
	localtime_s(&tm1, &t);
	sprintf_s(szTime, 24, "%04d-%02d-%02d %02d:%02d:%02d",
		tm1.tm_year + 1900, tm1.tm_mon + 1, tm1.tm_mday,
		tm1.tm_hour, tm1.tm_min, tm1.tm_sec);
#else
	localtime_r(&t, &tm1);
	snprintf(szTime, 24, "%04d-%02d-%02d %02d:%02d:%02d",
		tm1.tm_year + 1900, tm1.tm_mon + 1, tm1.tm_mday,
		tm1.tm_hour, tm1.tm_min, tm1.tm_sec);
#endif
	
	ss << szTime;
}