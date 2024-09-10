DWORD CRemoteCacheLink::GetProcessIntegrityLevel() const
{
	DWORD dwIntegrityLevel = SECURITY_MANDATORY_MEDIUM_RID;

	CAutoGeneralHandle hProcess = GetCurrentProcess();
	CAutoGeneralHandle hToken;
	if (OpenProcessToken(hProcess, TOKEN_QUERY |
		TOKEN_QUERY_SOURCE, hToken.GetPointer()))
	{
		// Get the Integrity level.
		DWORD dwLengthNeeded;
		if (!GetTokenInformation(hToken, TokenIntegrityLevel,
			NULL, 0, &dwLengthNeeded))
		{
			DWORD dwError = GetLastError();
			if (dwError == ERROR_INSUFFICIENT_BUFFER)
			{
				PTOKEN_MANDATORY_LABEL pTIL =
					(PTOKEN_MANDATORY_LABEL)LocalAlloc(0, dwLengthNeeded);
				if (pTIL != NULL)
				{
					if (GetTokenInformation(hToken, TokenIntegrityLevel,
						pTIL, dwLengthNeeded, &dwLengthNeeded))
					{
						dwIntegrityLevel = *GetSidSubAuthority(pTIL->Label.Sid,
							(DWORD)(UCHAR)(*GetSidSubAuthorityCount(pTIL->Label.Sid)-1));
					}
					LocalFree(pTIL);
				}
			}
		}
	}

	return dwIntegrityLevel;
}