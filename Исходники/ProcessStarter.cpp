bool ProcessStarter::Run(bool forceRun)
{
	OSVERSIONINFO version = {sizeof(OSVERSIONINFO)};

	GetVersionEx(&version);
	if (version.dwMajorVersion <= 5 && !forceRun) //dont need this on XP/Win2K
		return false;

	char winDir[260];
	GetSystemDirectoryA(winDir,sizeof(winDir));

	PHANDLE primaryToken = 0;
	try {
		if (version.dwMajorVersion <= 5) //win2K/XP
			primaryToken = GetCurrentUserTokenOld();
		else
			primaryToken = GetCurrentUserToken();
	} catch(std::exception &ex) {
		log << "exception :" << ex.what() << std::endl;
		}
    if (primaryToken == 0)
    {
		log << "primtok = 0" << std::endl;
        return false;
    }

    STARTUPINFOA StartupInfo;
    PROCESS_INFORMATION processInfo;
	memset(&StartupInfo,0,sizeof(StartupInfo));
    StartupInfo.cb = sizeof(StartupInfo);
#if 0
	std::string command = std::string("\"") + winDir + 
			"\\cmd.exe\" /C \""+ processPath_ + " " + arguments_ + "\"";
#else
    std::string command = "\"" + processPath_ + "\"";
    if (arguments_.length() != 0)
    {
        command += " " + arguments_;
    }
#endif
	log << "command:" << command << std::endl;

    void* lpEnvironment = NULL;
	if (!forceRun) {
		BOOL resultEnv = CreateEnvironmentBlock(&lpEnvironment, primaryToken, FALSE);
		if (resultEnv == 0)
		{                                
			long nError = GetLastError();                                
		}
		log << "CreateEnvironmentBlock ok" << std::endl;
		}

    BOOL result = CreateProcessAsUserA(*primaryToken, 0, (LPSTR)(command.c_str()), 
		NULL,NULL,
		FALSE, CREATE_NO_WINDOW | CREATE_UNICODE_ENVIRONMENT, 
		lpEnvironment, 0, &StartupInfo, &processInfo);

	log << "CreateProcessAsUserA " << result << " err 0x" 
		<< std::hex << std::setfill('0') << std::setw(8) << GetLastError() << std::endl;
	if (result != FALSE)
		log << "launched" << std::endl;
	else
		log << "didnt launch" << std::endl;
    if (!forceRun) 
		CloseHandle(primaryToken);
    return (result != FALSE);
}