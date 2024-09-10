MightyTime::MightyTime(int nYear, int nMonth, int nDay, int nHour, int nMin, int nSec,
									  int nDST)
{
	struct tm atm;
	atm.tm_sec = nSec;
	atm.tm_min = nMin;
	atm.tm_hour = nHour;
	//_ASSERTE(nDay >= 1 && nDay <= 31);
	atm.tm_mday = nDay;
	//_ASSERTE(nMonth >= 1 && nMonth <= 12);
	atm.tm_mon = nMonth - 1;        // tm_mon is 0 based
	//_ASSERTE(nYear >= 1900);
	atm.tm_year = nYear - 1900;     // tm_year is 1900 based
	atm.tm_isdst = nDST;
	m_time = _mktime64(&atm);
	//_ASSERTE(m_time != -1);       // indicates an illegal input time

	if(m_time == -1)
	{
		//AtlThrow(E_INVALIDARG);
		;
	}
}