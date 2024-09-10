MSICA_IMP
ReplaceEula(MSIHANDLE hInstall)
{
	// ::DebugBreak();

    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
    
    //
    // EULA File Content is MBCS (RTF) not Unicode
    AutoProcessHeapPtr<LPSTR> lpEula = pReadEulaFromFileA(hInstall);
    if (NULL == (LPSTR) lpEula)
    {
        _RPT0(_CRT_ERROR, "pReadEulaFromFile failed\n");
        return ERROR_INSTALL_FAILURE;
    }
    
    _RPT0(_CRT_WARN, "ReplaceEula\n");
    
	PMSIHANDLE hDatabase = MsiGetActiveDatabase(hInstall);

	if (0 == hDatabase)
	{
        _RPT0(_CRT_ERROR, "MsiGetActiveDatabase failed\n");
		return ERROR_INSTALL_FAILURE;
	}

	PMSIHANDLE hView;
	LPCTSTR query = _T("SELECT * FROM `Control` WHERE `Dialog_` = 'LicenseAgreement' AND `Control` = 'Memo'");
	UINT msiret = MsiDatabaseOpenView(hDatabase, query, &hView);

	if (ERROR_SUCCESS != msiret)
	{
        _RPT0(_CRT_ERROR, "MsiDatabaseOpenView failed\n");
		return ERROR_INSTALL_FAILURE;
	}

	msiret = MsiViewExecute(hView, 0);

	if (ERROR_SUCCESS != msiret)
	{
        _RPT0(_CRT_ERROR, "MsiViewExecute failed\n");
		return ERROR_INSTALL_FAILURE;
	}

	PMSIHANDLE hRecord;
	msiret = MsiViewFetch(hView, &hRecord);

	if (ERROR_SUCCESS != msiret)
	{
        _RPT0(_CRT_ERROR, "MsiViewFetch failed\n");
		return ERROR_INSTALL_FAILURE;
	}

	msiret = MsiViewModify(hView, MSIMODIFY_DELETE, hRecord);

	if (ERROR_SUCCESS != msiret)
	{
        _RPT0(_CRT_ERROR, "MsiViewModify failed\n");
		return ERROR_INSTALL_FAILURE;
	}

	UINT nFields = MsiRecordGetFieldCount(hRecord);

	AutoProcessHeapPtr<LPTSTR> buffer;
	DWORD chBuffer = 0;
	msiret = MsiRecordGetString(hRecord, 10, _T(""), &chBuffer);

	if (ERROR_MORE_DATA == msiret)
	{
		++chBuffer;
		buffer = (LPTSTR) ::HeapAlloc(
            GetProcessHeap(), 
            HEAP_ZERO_MEMORY, 
            chBuffer * sizeof(TCHAR));
		msiret = MsiRecordGetString(hRecord, 1, buffer, &chBuffer);
	}
    
	msiret = MsiRecordSetStringA(hRecord, 10, lpEula);
    
	if (ERROR_SUCCESS != msiret)
	{
        _RPT0(_CRT_ERROR, "MsiRecordSetString failed\n");
		return ERROR_INSTALL_FAILURE;
	}

	msiret = MsiViewModify(hView, MSIMODIFY_INSERT_TEMPORARY, hRecord);
    
	if (ERROR_SUCCESS != msiret)
	{
        _RPT0(_CRT_ERROR, "MsiViewModify failed\n");
		return ERROR_INSTALL_FAILURE;
	}

	//msiret = MsiViewExecute(hView, hRecord);
	//if (ERROR_SUCCESS != msiret)
	//{
	//	return ERROR_INSTALL_FAILURE;
	//}

	_RPT0(_CRT_WARN, "ReplaceEula completed successfully.\n");

	return ERROR_SUCCESS;
}