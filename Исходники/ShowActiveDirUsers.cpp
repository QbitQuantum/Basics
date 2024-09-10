BOOL CShowActiveDirUsers::GetFullUserName(LPTSTR szUser, LPTSTR szDomain, 
							LPTSTR szFullUserName, LPTSTR szDescription)
{
	BOOL	bResult = FALSE;
	LPWSTR	pServer = NULL;
	BOOL	bLocal = FALSE;
	TCHAR	szComputerName[_MAX_PATH];
	TCHAR   szDomainName[_MAX_PATH];
	TCHAR   szServer[_MAX_PATH];
	TCHAR   szPDC[_MAX_PATH];
	DWORD	dwLevel = 10;
	LPUSER_INFO_10 pUserInfoBuffer = NULL;

	// init
	ZeroMemory(szComputerName, _MAX_PATH);
	ZeroMemory(szDomainName, _MAX_PATH);
	ZeroMemory(szServer, _MAX_PATH);
	ZeroMemory(szPDC, _MAX_PATH);
	

	GetLocalComputerName(szComputerName);

	if (_tcsicmp(szComputerName, szDomain) == 0)
		bLocal = TRUE;

	// for active directory native, szUser comes in as [email protected]
	if (!bLocal) 
	{
		GetDCName(szPDC, szDomain);
		if (_tcschr(szUser, _T('@')) )
		{
			GetUserAndDomainNameFromUPN(szUser, szFullUserName, szDomainName);
			_tcscpy(szUser, szFullUserName);
			_tcscpy(szDomain, szDomainName);
		}
	}
	else
	{
		NetApiBufferAllocate(_MAX_PATH,  (LPVOID*)&pServer);
		ZeroMemory(pServer, _MAX_PATH);
		_tcscpy(pServer, _T("\\\\"));
		_tcscat(pServer, szComputerName);

	}

	// grab the details of the user account, 
	// may fail if AD=native & user not in proper security group
	if (NERR_Success == NetUserGetInfo(szPDC, szUser, dwLevel, 
											(LPBYTE*)&pUserInfoBuffer))
	{
		if (pUserInfoBuffer)
		{
			_tcscpy(szFullUserName, pUserInfoBuffer->usri10_full_name);
			_tcscpy(szDescription, pUserInfoBuffer->usri10_comment);
			bResult = TRUE;
		}
	}

	if (pUserInfoBuffer)
		NetApiBufferFree(pUserInfoBuffer);

	if (pServer)
		NetApiBufferFree(pServer);

	return bResult;
}