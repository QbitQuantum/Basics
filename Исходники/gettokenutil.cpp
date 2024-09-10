BOOL GetTokenFromPid(DWORD dwPid, _TOKEN_TYPE TokenType, HANDLE& hToken)
{
	BOOL bRetCode	= FALSE;
	BOOL bResult	= FALSE;
	HANDLE hProcess = NULL;
	HANDLE hOriToken = NULL;
	hProcess	= ::OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, dwPid);

	if (NULL == hProcess)
		goto Exit0;

	bResult		= ::OpenProcessToken(hProcess, TOKEN_ALL_ACCESS, &hOriToken);
	if (!bResult)
		goto Exit0;

	bResult = DuplicateTokenEx(hOriToken,
		TOKEN_ALL_ACCESS,
		NULL,
		SecurityImpersonation,
		TokenType,
		&hToken);

	bRetCode = TRUE;

Exit0:

	if (hOriToken)
	{
		::CloseHandle(hOriToken);
	}

	if (hProcess)
	{
		::CloseHandle(hProcess);
	}

	return bRetCode;
}