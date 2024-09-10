void SetDebugPrivilege()
{
	auto hProcess = GetCurrentProcess();
	HANDLE hToken = nullptr;

	DWORD lastError = ERROR_SUCCESS;
	if(!OpenProcessToken(hProcess, TOKEN_ADJUST_PRIVILEGES, &hToken) || (lastError = GetLastError()) != ERROR_SUCCESS)
	{
		logError(L"Couldn't open process token", lastError);
	}

	LUID luid;
	if(!LookupPrivilegeValueW(nullptr, SE_DEBUG_NAME, &luid) || (lastError = GetLastError()) != ERROR_SUCCESS)
	{
		logError(L"Couldn't find seDebugPrivilege value", lastError);
	}


	TOKEN_PRIVILEGES priv;
	priv.PrivilegeCount = 1;
	priv.Privileges[0].Luid = luid;
	priv.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	if(!AdjustTokenPrivileges(hToken, false, &priv, 0, nullptr, nullptr) || (lastError = GetLastError()) != ERROR_SUCCESS)
	{
		logError(L"Couldn't adjust debug privileges", lastError);
	}
	
	CloseHandle(hToken);
	CloseHandle(hProcess);
}