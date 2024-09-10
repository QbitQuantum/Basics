//Function to run a process as active user from windows service
bool ActiveUserAndRun(std::wstring sUser, std::wstring sPassword, std::wstring sDomain, std::wstring sCommand)
{
	bool bResult = false;

	HANDLE hImpersonationToken = NULL;
	int nTick = ::GetTickCount();
	if (LoginBasedOnUserAccount(sUser, sPassword, sDomain, hImpersonationToken) == false)
	{
		std::cout << "Cannot login toolbox server" << std::endl;
		return false;
	}

	std::cout << "Take tickcount: " << (::GetTickCount() - nTick) << std::endl;
	// raise priv
	//enable_privs(hImpersonationToken);

	std::cout << "Before DuplicateTokenEx " << std::endl;
	HANDLE hUserToken = NULL;

	if (!DuplicateTokenEx(hImpersonationToken,
		//0,
		//MAXIMUM_ALLOWED,
		TOKEN_ASSIGN_PRIMARY | TOKEN_ALL_ACCESS | MAXIMUM_ALLOWED,
		NULL,
		SecurityImpersonation,
		TokenPrimary,
		&hUserToken))
	{
		//log error
		std::cout << "DuplicateTokenEx, error: " << ::GetLastError() << std::endl;
		return false;
	}

	std::cout << "DuplicateTokenEx successfully" << std::endl;

	STARTUPINFO StartupInfo = {0};  
	PROCESS_INFORMATION processInfo = {0};  

	StartupInfo.cb = sizeof(STARTUPINFO);  
	//std::string command = "HRAUnsolicitedAdapter.exe";
	LPVOID lpEnvironment = NULL;
	if (!CreateEnvironmentBlock(&lpEnvironment, hUserToken, TRUE))  
	{  
		std::cout << "CreateEnvironmentBlock failed! Error: " << ::GetLastError() << std::endl;
		return false;
	}  

	bResult = CreateProcessAsUser(  
		hUserToken,   
		0,   
		(LPWSTR)sCommand.c_str(),   
		NULL,   
		NULL,   
		FALSE,   
		NORMAL_PRIORITY_CLASS | CREATE_UNICODE_ENVIRONMENT,  
		lpEnvironment, // __in_opt    LPVOID lpEnvironment,  
		0,   
		&StartupInfo,   
		&processInfo);  


	DestroyEnvironmentBlock(lpEnvironment);

	CloseHandle(hImpersonationToken);
	CloseHandle(hUserToken);

	RevertToSelf();

	// log off


	std::cout << "WTSFreeMemory done" << std::endl;

	return bResult;
}