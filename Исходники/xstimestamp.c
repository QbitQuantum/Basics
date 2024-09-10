/*! \relates XsTimeStamp
	\brief Converts the timestamp into an XsUtcTime object
	\param utc The UTC time object to write the conversion result to
*/
void XsTimeStamp_toUtcTime(struct XsTimeStamp* thisPtr, struct XsUtcTime* utc)
{	
	struct tm tmUtc;
#ifdef _WIN32		
	__time64_t t;
	t = (__time64_t)(thisPtr->m_msTime / 1000);
	if (_gmtime64_s(&tmUtc, &t))
	{
		//in case of an error the result is an invalid XsUtctime
		utc->m_valid = 0;
		return;
	}
#else
	time_t t;
	t = (time_t)(thisPtr->m_msTime / 1000);
	if (gmtime_r(&t, &tmUtc) == 0)
	{
		//in case of an error the result is an invalid XsUtctime
		utc->m_valid = 0;
		return;
	}
#endif

	utc->m_day = tmUtc.tm_mday + 1;
	utc->m_hour = tmUtc.tm_hour;
	utc->m_minute = tmUtc.tm_min;
	utc->m_month = tmUtc.tm_mon + 1;
	utc->m_nano = (uint32_t)((thisPtr->m_msTime % 1000) * 1e6);
	utc->m_second = tmUtc.tm_sec;
	utc->m_year = tmUtc.tm_year + 1900;
	utc->m_valid = 1;
}