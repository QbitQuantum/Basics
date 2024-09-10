CString FormatDateTime ( COleDateTime &DateTime, LPCTSTR pFormat )
{
	// If null, return empty string
	if ( DateTime.GetStatus() == COleDateTime::null || DateTime.GetStatus() == COleDateTime::invalid )
		return _T("");

	UDATE ud;
	if (S_OK != VarUdateFromDate(DateTime.m_dt, 0, &ud))
	{
		return _T("");
	}

	TCHAR *weeks[]={_T("Sun"),_T("Mon"),_T("Tue"),_T("Wen"),_T("Thu"),_T("Fri"),_T("Sat")};
	TCHAR *month[]={_T("JAN"),_T("FEB"),_T("MAR"),_T("APR"),
					_T("MAY"),_T("JUN"),_T("JUL"),_T("AUG"),
					_T("SEP"),_T("OCT"),_T("NOV"),_T("DEC")};

	TIME_ZONE_INFORMATION stTimeZone;
	GetTimeZoneInformation(&stTimeZone);

	CString strDate;
	strDate.Format(_T("%s, %d %s %02d %d:%d:%d %c%04d")
		,weeks[ud.st.wDayOfWeek],
		ud.st.wDay,month[ud.st.wMonth-1],ud.st.wYear%100,ud.st.wHour,
		ud.st.wMinute,ud.st.wSecond,
		stTimeZone.Bias>0?_T('-'):_T('+'),
		abs(stTimeZone.Bias*10/6)
		);
	return strDate;
}