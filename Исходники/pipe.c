BOOL WaitNamedPipeA(LPCSTR lpNamedPipeName, DWORD nTimeOut)
{
	BOOL status;
	DWORD nWaitTime;
	char* lpFilePath;
	DWORD dwSleepInterval;

	if (!lpNamedPipeName)
		return FALSE;

	lpFilePath = GetNamedPipeUnixDomainSocketFilePathA(lpNamedPipeName);

	if (nTimeOut == NMPWAIT_USE_DEFAULT_WAIT)
		nTimeOut = 50;

	nWaitTime = 0;
	status = TRUE;
	dwSleepInterval = 10;

	while (!PathFileExistsA(lpFilePath))
	{
		Sleep(dwSleepInterval);
		nWaitTime += dwSleepInterval;

		if (nWaitTime >= nTimeOut)
		{
			status = FALSE;
			break;
		}
	}

	free(lpFilePath);
	return status;
}