void FSTimeLimiter(int iYear, int iMonth, int iDay)
{
	time_t secs=time(0);
#if defined (WIN32)
	tm now_s;
	localtime_s(&now_s, &secs);
	const tm *now=&now_s;
#else
	tm *now=localtime(&secs);
#endif
	if (now->tm_year+1900 > iYear) throw CFSException();
	if (now->tm_year+1900 == iYear) {
		if (now->tm_mon+1 > iMonth) throw CFSException();
		if (now->tm_mon+1 == iMonth) {
			if (now->tm_mday >= iDay) throw CFSException();
		}
	}
}