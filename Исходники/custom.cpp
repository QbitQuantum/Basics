/* Uninstall NSIS */
MSIDLLEXPORT UninstallNsisInstallation( MSIHANDLE hInstall )
{
	DWORD rv = ERROR_SUCCESS;
	// lookup the NSISUNINSTALL property value
	LPTSTR cNsisUninstall = _T("UPGRADENSIS");
	HANDLE hIo = NULL;
	DWORD dwSize = 0;
	LPTSTR strPathUninst = NULL;
	HANDLE hJob = NULL;
	STARTUPINFO sInfo;
	PROCESS_INFORMATION pInfo;

	pInfo.hProcess = NULL;
	pInfo.hThread = NULL;

	rv = MsiGetProperty( hInstall, cNsisUninstall, _T(""), &dwSize );
	if(rv != ERROR_MORE_DATA) goto _cleanup;

	strPathUninst = new TCHAR[ ++dwSize ];

	rv = MsiGetProperty( hInstall, cNsisUninstall, strPathUninst, &dwSize );
	if(rv != ERROR_SUCCESS) goto _cleanup;

	// Create a process for the uninstaller
	sInfo.cb = sizeof(sInfo);
	sInfo.lpReserved = NULL;
	sInfo.lpDesktop = _T("");
	sInfo.lpTitle = _T("NSIS Uninstaller for Kerberos for Windows");
	sInfo.dwX = 0;
	sInfo.dwY = 0;
	sInfo.dwXSize = 0;
	sInfo.dwYSize = 0;
	sInfo.dwXCountChars = 0;
	sInfo.dwYCountChars = 0;
	sInfo.dwFillAttribute = 0;
	sInfo.dwFlags = 0;
	sInfo.wShowWindow = 0;
	sInfo.cbReserved2 = 0;
	sInfo.lpReserved2 = 0;
	sInfo.hStdInput = 0;
	sInfo.hStdOutput = 0;
	sInfo.hStdError = 0;

	if(!CreateProcess( 
		strPathUninst,
		_T("Uninstall /S"),
		NULL,
		NULL,
		FALSE,
		CREATE_SUSPENDED,
		NULL,
		NULL,
		&sInfo,
		&pInfo)) {
            DWORD lastError = GetLastError();
            MSIHANDLE hRecord;

            hRecord = MsiCreateRecord(4);
            MsiRecordClearData(hRecord);
            MsiRecordSetInteger(hRecord, 1, ERR_NSS_FAILED_CP);
            MsiRecordSetString(hRecord, 2, strPathUninst);
            MsiRecordSetInteger(hRecord, 3, lastError);

            MsiProcessMessage( hInstall, INSTALLMESSAGE_ERROR, hRecord );
	
            MsiCloseHandle( hRecord );

            pInfo.hProcess = NULL;
            pInfo.hThread = NULL;
            rv = 40;
            goto _cleanup;
        };

	// Create a job object to contain the NSIS uninstall process tree

	JOBOBJECT_ASSOCIATE_COMPLETION_PORT acp;

	acp.CompletionKey = 0;

	hJob = CreateJobObject(NULL, _T("NSISUninstallObject"));
	if(!hJob) {
		rv = 41;
		goto _cleanup;
	}

	hIo = CreateIoCompletionPort(INVALID_HANDLE_VALUE,0,0,0);
	if(!hIo) {
		rv = 42;
		goto _cleanup;
	}

	acp.CompletionPort = hIo;

	SetInformationJobObject( hJob, JobObjectAssociateCompletionPortInformation, &acp, sizeof(acp));

	AssignProcessToJobObject( hJob, pInfo.hProcess );

	ResumeThread( pInfo.hThread );

	DWORD a,b,c;
	for(;;) {
		if(!GetQueuedCompletionStatus(hIo, &a, (PULONG_PTR) &b, (LPOVERLAPPED *) &c, INFINITE)) {
			Sleep(1000);
			continue;
		}
		if(a == JOB_OBJECT_MSG_ACTIVE_PROCESS_ZERO) {
			break;
		}
	}

	rv = ERROR_SUCCESS;
    
_cleanup:
	if(hIo) CloseHandle(hIo);
	if(pInfo.hProcess)	CloseHandle( pInfo.hProcess );
	if(pInfo.hThread) 	CloseHandle( pInfo.hThread );
	if(hJob) CloseHandle(hJob);
	if(strPathUninst) delete strPathUninst;

	if(rv != ERROR_SUCCESS && rv != 40) {
            ShowMsiError( hInstall, ERR_NSS_FAILED, rv );
	}
	return rv;
}