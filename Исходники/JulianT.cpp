void
CJulianTime::FinishInit()
{
	COleDateTimeSpan cSpan(m_dDouble/SECONDS_PER_YEAR);
	COleDateTime cTime(BASE_YEAR,BASE_MONTH,BASE_DAY,
		BASE_HOUR,BASE_MINUTE,BASE_SECOND);
	cTime = cTime + cSpan;
	cTime -= HALF_MILLISECOND;

	m_bIsValid = cTime.GetStatus() == COleDateTime::valid;
	sprintf(m_pDate,"%04i.%02i.%02i",
		cTime.GetYear(),cTime.GetMonth(),cTime.GetDay());
	sprintf(m_pTime,"%02i:%02i:%02i",
		cTime.GetHour(),cTime.GetMinute(),cTime.GetSecond());
	m_Year = cTime.GetYear();
	m_Month = cTime.GetMonth();
	m_Day = cTime.GetDay();
	m_Hour = cTime.GetHour();
	m_Minute = cTime.GetMinute();
	m_Second = cTime.GetSecond();
}