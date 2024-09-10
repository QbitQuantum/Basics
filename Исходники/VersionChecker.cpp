void CVersionChecker::SetNextCheck(int nDays)
{
	CTimeSpan tPeriod( nDays, 0, 0, 0 );
	CTime tNextCheck = CTime::GetCurrentTime() + tPeriod;
	theApp.WriteProfileInt( _T("VersionCheck"), _T("NextCheck"), (DWORD)tNextCheck.GetTime() );
}