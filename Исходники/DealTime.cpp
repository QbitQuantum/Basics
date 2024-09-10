CDealTime::CDealTime(UINT year,UINT month,UINT day,UINT hour,UINT min,UINT sec)
{
	struct tm tmNow;
	tmNow.tm_year = year - 1900;
	tmNow.tm_mon = month;
	tmNow.tm_mday = day;
	tmNow.tm_hour = hour;
	tmNow.tm_min = min;
	tmNow.tm_sec = sec;
	m_time = _mktime64(&tmNow); 
}