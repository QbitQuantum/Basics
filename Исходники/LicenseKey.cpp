void CLicenseKey::InitUID()
{
	USES_CONVERSION;

	TCHAR szDir [MAX_PATH];
	::GetWindowsDirectory (szDir, MAX_PATH);
	
	TCHAR szDrive [MAX_PATH];  
	_tsplitpath_s (szDir, szDrive,MAX_PATH, NULL,0, NULL,0, NULL,0);
	
	DWORD dwSerialNumber=0;
    ::GetVolumeInformation (szDrive, NULL, 0, &dwSerialNumber, NULL, NULL, NULL, 0 );

	int nLen = _tcslen (szDrive);
	if (nLen < MAX_PATH)
	{
		szDrive[nLen] = _T('\\');
		szDrive[nLen+1] = _T('\0');
	}

	CString m_strUID;
	m_strUID.Format (_T("%s%X%s%s"), m_szAppName, dwSerialNumber, 
		(LPCTSTR)theApp.GetUser(), (LPCTSTR)theApp.GetCompany() );

	LPCSTR szUID = T2CA (   m_strUID );

	long nUID = CalcCRC32(szUID, m_strUID.GetLength() );
	nUID = nUID < 0 ? -nUID : nUID;

	m_nUID = nUID;
}