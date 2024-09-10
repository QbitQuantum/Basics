bool ProcessStarter::run( bool forceRun )
{
	OSVERSIONINFO version = {sizeof(OSVERSIONINFO)};

	GetVersionEx(&version);
	if ((version.dwMajorVersion == 5 && version.dwMinorVersion == 0 ) && !forceRun) { //dont need this on XP/Win2K 
		d->log << "not being forced to run .." << std::endl;
		return false;
		}

	PHANDLE primaryToken = 0;
	try {
		if ((version.dwMajorVersion == 5) && (version.dwMinorVersion == 0) ) //win2K
			primaryToken = d->GetCurrentUserTokenOld();
		else
			primaryToken = d->GetCurrentUserToken();
	} catch(std::exception &ex) {
		d->log << "exception :" << ex.what() << std::endl;
		}
    if (primaryToken == 0)
    {
		d->log << "primtok = 0" << std::endl;
		if (!forceRun) 
	        return false;

    }

	STARTUPINFO StartupInfo;
    PROCESS_INFORMATION processInfo;
	memset(&StartupInfo,0,sizeof(StartupInfo));
    StartupInfo.cb = sizeof(StartupInfo);
	if (version.dwMajorVersion <= 5)
		StartupInfo.lpDesktop = L"winsta0\\default";
#if 0
	char winDir[260];
	GetSystemDirectoryA(winDir,sizeof(winDir));
	QString command = QString( "\"%1\\cmd.exe\" /C \"%2 %3\"" )
		.arg( winDir, d->processPath, d->arguments.join( " " ) );
#else
	QString command = d->processPath;
	if( !d->arguments.isEmpty() )
		command += " " + d->arguments.join( " " );
#endif
	d->log << "command:'" << command.toStdString() << "'" << std::endl;

    void* lpEnvironment = NULL;
	if (!forceRun)
	{
		BOOL resultEnv = CreateEnvironmentBlock(&lpEnvironment, *primaryToken, TRUE);
		if (resultEnv == 0)
			long nError = GetLastError();                                
		d->log << "CreateEnvironmentBlock ok" << std::endl;
	}

	BOOL result;
	if (!primaryToken)
	{
		result = CreateProcessW(0, (WCHAR*)command.utf16(),
			NULL,NULL,
			FALSE, CREATE_NO_WINDOW | CREATE_UNICODE_ENVIRONMENT, 
			lpEnvironment, 0, &StartupInfo, &processInfo);
	}
	else
	{
		d->log << "creating as user " << std::endl;
		result = CreateProcessAsUserW(*primaryToken, 0, (WCHAR*)command.utf16(),
			NULL,NULL,
			FALSE, CREATE_NO_WINDOW | CREATE_UNICODE_ENVIRONMENT, 
			lpEnvironment, 0, &StartupInfo, &processInfo);
	}

	if (result != FALSE)
		d->log << "launched PID=" << processInfo.dwProcessId << std::endl;
	else
	{
		d->log << "didnt launch" << std::endl;
		d->log << "CreateProcessAsUserW " << result << " err 0x"
			<< std::hex << std::setfill('0') << std::setw(8) << GetLastError() << std::endl;
	}
    if (!forceRun) 
		CloseHandle(primaryToken);
    return (result != FALSE);
}