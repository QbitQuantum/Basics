UINT CSAStatusLog::Init(const TCHAR *pLogFilename)
{
	UINT ErrorCode;

	// get application path
	TCHAR szAppPath[MAX_PATH]={0};
	if (! GetModuleFileName(NULL,szAppPath,MAX_PATH))
	{
		OutputDebugStringW(L"GetModuleFileName Error");
		return GetLastError();
	}

	// Call to "PathRemoveFileSpec". get app path.
	if (!PathRemoveFileSpec(szAppPath))
	{
		OutputDebugStringW(L"PathRemoveFileSpec Error");
		return GetLastError();
	}

	// Create Log Dir
	TCHAR szLogDir[MAX_PATH]={0};
	_stprintf_s(szLogDir,_T("%s\\Log"),szAppPath);

	BOOL rt = CreateDirectory(szLogDir,NULL);
	if (!rt && GetLastError() != 183)
	{
		OutputDebugStringW(L"CreateDirectory Error");
		int err = GetLastError();
		_tprintf(_T("Create directory %s error(%d).\r\n"),szLogDir,err);
		return err;
	}

	SYSTEMTIME sys; 
	GetLocalTime( &sys ); 
	_stprintf_s(m_szLogfile,_T("C:\\Log\\%s_%02d%02d%02d_%02d%02d.Log"),pLogFilename,sys.wYear,sys.wMonth,sys.wDay,sys.wHour,sys.wMinute);
	OutputDebugStringW(m_szLogfile);
	// create log file
	ErrorCode = CreateLogfile(m_hFile);
	if (ErrorCode)
	{
		OutputDebugStringW(L"CreateLogfile Error");
		return ErrorCode;
	}

	m_bEnable = TRUE;
	return 0;
}