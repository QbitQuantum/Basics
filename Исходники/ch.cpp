LONG WINAPI MyUnhandledExceptionFilter(struct _EXCEPTION_POINTERS* ExceptionInfo)
{
	// Step1 - should not fail - prepare some more unique crash name, create under the path where ch data exists
	TCHAR szPath[_MAX_PATH];
	HRESULT hResult = SHGetFolderPath(NULL, CSIDL_LOCAL_APPDATA, NULL, 0, szPath);
	if(FAILED(hResult))
		_tcscpy(szPath, _T("c:\\"));

	CString strPath(szPath);
	// make sure to create the required directories if they does not exist
	strPath += _T("\\Copy Handler");
	CreateDirectory(strPath, NULL);
	strPath += _T("\\Dumps");
	CreateDirectory(strPath, NULL);

	// current date
	SYSTEMTIME st;
	GetLocalTime(&st);
	
	TCHAR szName[_MAX_PATH];
	_sntprintf(szName, _MAX_PATH, _T("%s\\ch_crashdump-%s-%I64u-%s.dmp"), (PCTSTR)strPath, _T(PRODUCT_VERSION), (ull_t)_time64(NULL),
#ifdef _WIN64
		_T("64")
#else
		_T("32")
#endif
		);
	szPath[_MAX_PATH - 1] = _T('\0');

	// Step 2 - create the crash dump in case anything happens later
	bool bResult = false;
	HANDLE hFile = CreateFile(szName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile != INVALID_HANDLE_VALUE)
	{
		MINIDUMP_EXCEPTION_INFORMATION mei;
		mei.ThreadId = GetCurrentThreadId();
		mei.ExceptionPointers = ExceptionInfo;
		mei.ClientPointers = TRUE;

		if(MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hFile, MiniDumpWithProcessThreadData, &mei, NULL, NULL))
			bResult = true;
	}

	CloseHandle(hFile);

	CCrashDlg dlgCrash(bResult, szName);
	dlgCrash.DoModal();

	return EXCEPTION_EXECUTE_HANDLER;
}