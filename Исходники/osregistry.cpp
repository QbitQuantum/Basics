bool get_user_sid(SCP_string& outStr)
{
	HANDLE hToken = NULL;
	if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken) == FALSE)
	{
		mprintf(("Failed to get process token! Error Code: %d", GetLastError()));

		return false;
	}

	DWORD dwBufferSize;
	GetTokenInformation(hToken, TokenUser, NULL, 0, &dwBufferSize);

	PTOKEN_USER ptkUser = (PTOKEN_USER) new byte[dwBufferSize];

	if (GetTokenInformation(hToken, TokenUser, ptkUser, dwBufferSize, &dwBufferSize))
	{
		CloseHandle(hToken);
	}

	if (IsValidSid(ptkUser->User.Sid) == FALSE)
	{
		mprintf(("Invalid SID structure detected!"));

		delete[] ptkUser;
		return false;
	}

	LPTSTR sidName = NULL;
	if (ConvertSidToStringSid(ptkUser->User.Sid, &sidName) == 0)
	{
		mprintf(("Failed to convert SID structure to string! Error Code: %d", GetLastError()));

		delete[] ptkUser;
		return false;
	}

	outStr.assign(sidName);

	LocalFree(sidName);
	delete[](byte*) ptkUser;

	return true;
}