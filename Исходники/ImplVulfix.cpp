INT CImplVulfix::ExpressScanSystem()
{
	// Not use IUpdate 
	HRESULT hr = Scan( VULSCAN_EXPRESS_SCAN );
	if(FAILED(hr))
		return 0;
	
	// check date 
	T_Date date;
	GetLatestPackgeDate(date.nYear, date.nMonth, date.nDay);

	// 上次扫描为安全的库版本号 
	CString strLastSafePkgDate;
	ReadVulConfig(_T("VulScan"), _T("LastSafePkgDate"), strLastSafePkgDate);
	T_Date dateSafe;

	SHOWMSG(_T("PkgDate %04d-%02d-%02d \r\nLastScan.PkgDate %s"), date.nYear, date.nMonth, date.nDay, strLastSafePkgDate);
	if(!strLastSafePkgDate.IsEmpty() && ParseDateString(strLastSafePkgDate, dateSafe.nYear, dateSafe.nMonth, dateSafe.nDay) )
	{
		if(date.Compare(dateSafe.nYear, dateSafe.nMonth, dateSafe.nDay)<=0)
			return -1;
	}
	
	FILETIME ft;
	SYSTEMTIME systime={0};
	if( GetLatestInstalledKBDate(ft) && FileTimeToSystemTime(&ft, &systime) )
	{
		SHOWMSG(_T("ExpressScanSystem.DateCompare %d-%d-%d - %d-%d-%d"), date.nYear, date.nMonth, date.nDay, systime.wYear, systime.wMonth, systime.wDay);
		return date.Compare(systime.wYear, systime.wMonth, systime.wDay);
	}
	return 0;
}