bool SteamLaunch(void)
{
	std::string	steamRoot = GetSteamRoot();
	_MESSAGE("steam root = %s", steamRoot.c_str());

	if(steamRoot.empty())
		return false;

	std::string	steamEXEPath = steamRoot + "\\Steam.exe";

	STARTUPINFO			startupInfo = { 0 };
	PROCESS_INFORMATION	procInfo = { 0 };

	startupInfo.cb = sizeof(startupInfo);

	if(!CreateProcess(
		steamEXEPath.c_str(),
		NULL,	// no args
		NULL,	// default process security
		NULL,	// default thread security
		FALSE,	// don't inherit handles
		0,		// no options
		NULL,	// no new environment block
		steamRoot.c_str(),	// new cwd
		&startupInfo, &procInfo))
	{
		PrintLoaderError("Launching Steam failed (%08X).", GetLastError());
		return false;
	}

	// this doesn't do anything useful
	//	bool result = SteamCheckActive();

	// this is an ugly hack. wait for steam to start pumping messages
	WaitForInputIdle(procInfo.hProcess, INFINITE);

	// and then you know some more just because even then it isn't ready
	Sleep(1000 * 5);

	// clean up
	CloseHandle(procInfo.hProcess);
	CloseHandle(procInfo.hThread);

	return true;
}