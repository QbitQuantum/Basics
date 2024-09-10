BOOL KFunction::RebootSystem()
{
	HANDLE hToken = NULL;
	BOOL bReturn = FALSE;
	BOOL bRetCode = FALSE;

	bRetCode = OpenProcessToken(
		GetCurrentProcess(),
		TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, 
		&hToken
		);
	if (!bRetCode)
	{
		goto Exit0;
	}

	TOKEN_PRIVILEGES tkp; 
	bRetCode = LookupPrivilegeValue(
		NULL, 
		SE_SHUTDOWN_NAME, 
		&tkp.Privileges[0].Luid
		); 
	if (!bRetCode)
		goto Exit0;

	tkp.PrivilegeCount = 1;  
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; 

	AdjustTokenPrivileges(
		hToken, 
		FALSE, 
		&tkp, 
		0, 
		(PTOKEN_PRIVILEGES)NULL,
		0
		); 
	if (GetLastError() != ERROR_SUCCESS) 
	{
		goto Exit0;
	}

	DWORD dwOption = 0;

	dwOption = EWX_REBOOT | EWX_FORCE;
	bRetCode = ExitWindowsEx(
		dwOption, 
		SHTDN_REASON_MAJOR_APPLICATION
		);
	goto Exit0;

	bReturn = TRUE;

Exit0:
	if (hToken) CloseHandle(hToken);

	log_a("KFunction::RebootSystem return:%d\n", bReturn);

	return bReturn;
}