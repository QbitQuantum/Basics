static
BOOL
DCB_ValidPort(unsigned long nPort)
{
	BOOL bRet;
	DWORD dwErr;
	WCHAR szPort[3 + 10 + 1];

	dwErr = GetLastError();

	_snwprintf(szPort, sizeof(szPort) / sizeof(szPort[0]), L"COM%lu", nPort);

	bRet = QueryDosDeviceW(szPort, NULL, 0) == 0 && GetLastError() == ERROR_INSUFFICIENT_BUFFER;

	if(!bRet)
		dwErr = ERROR_INVALID_PARAMETER;

	SetLastError(dwErr);
	return bRet;
}