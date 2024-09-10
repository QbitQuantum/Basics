void ALog::AddViewer(AViewer* viewer)
{
	ASSERT(viewer != NULL);
	BOOL bFirstTime = FALSE;
	if (m_pViewer == NULL)
	{
		bFirstTime = TRUE;
		m_pViewer = new MultiViewer;
	}
	m_pViewer->AddViewer(viewer);
	if (bFirstTime)
	{
		SYSTEMTIME t;
		::GetLocalTime(&t);
		TCHAR bf[300];
		_sntprintf(bf, 200, _T("@@ ------Start Logging: %d-%d-%d %0.2d:%0.2d:%0.2d .%0.3dms\r\n"),
			t.wDay, t.wMonth, t.wYear, t.wHour, t.wMinute, t.wSecond,  t.wMilliseconds);
		Log(bf);
		OSVERSIONINFO osVer;
		osVer.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
		GetVersionEx(&osVer);
		_sntprintf(bf, 200, _T("@@ VersionInfo: %d.%d.%d\r\n"), osVer.dwMajorVersion, osVer.dwMinorVersion, osVer.dwBuildNumber);
		Log(bf);
		MEMORYSTATUS memStat;
		GlobalMemoryStatus (&memStat);
		Log(_T("@@ MemInfo: %d / %d (MB)\r\n"), memStat.dwAvailPhys/1024/1024, memStat.dwTotalPhys/1024/1024);
		GetWindowsDirectory(bf, MAX_PATH);
		Log(_T("@@ <WINDIR>: %s\r\n"), bf);
		Log(_T("@@ SysDefLangID: %d\r\n"), GetSystemDefaultLangID());
		Log(_T("@@ ---\r\n"));
	}
	else
		Log(_T("@@ New Viewer Added\r\n"));
}