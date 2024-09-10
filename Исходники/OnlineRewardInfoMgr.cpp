time_t COnlineRewardInfoMgr::GetResetTime(time_t nNow)
{
	if (nNow == 0) {
		nNow = time(NULL);
	}

	struct tm tTime;
	LocalTime(&nNow, &tTime);

	tTime.tm_hour = m_nResetHour;
	tTime.tm_min = m_nResetMin;
	tTime.tm_sec = m_nResetSec;

	time_t nTodayResetTime = mktime(&tTime);
	time_t nResetTime = nTodayResetTime;
	if (nNow >= nTodayResetTime) {
		nResetTime = nTodayResetTime + 24 * 60 * 60 ;
	} 

	return nResetTime;
}