time_t xTime::getMonthStart(time_t time)
{
	struct tm tm;
	getLocalTime(tm, time);
	return time - (((tm.tm_mday - 1) * 24 + tm.tm_hour) * 60 + tm.tm_min) * 60 - tm.tm_sec;
}