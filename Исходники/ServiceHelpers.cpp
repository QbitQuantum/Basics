std::shared_ptr<PROCESS_INFORMATION> LaunchProcess(wchar_t* commandline, DWORD sessionid){
	auto ProcessInfo = std::shared_ptr<PROCESS_INFORMATION>(new PROCESS_INFORMATION(), [=](PROCESS_INFORMATION* p){
		CloseHandle(p->hThread);
		CloseHandle(p->hProcess);
		delete p;
	});
	STARTUPINFO StartUPInfo;
	memset(&StartUPInfo, 0, sizeof(STARTUPINFO));
	memset(ProcessInfo.get(), 0, sizeof(PROCESS_INFORMATION));

	StartUPInfo.lpDesktop = L"Winsta0\\Winlogon";
	StartUPInfo.cb = sizeof(STARTUPINFO);
	HANDLE winloginhandle = NULL;
	PVOID	lpEnvironment = NULL;

	if (GetWinlogonHandle(&winloginhandle, sessionid)){
		if (CreateEnvironmentBlock(&lpEnvironment, winloginhandle, FALSE) == FALSE) lpEnvironment = NULL;
		SetLastError(0);
		CreateProcessAsUser(winloginhandle, NULL, commandline, NULL, NULL, FALSE, CREATE_UNICODE_ENVIRONMENT | NORMAL_PRIORITY_CLASS | CREATE_NO_WINDOW | DETACHED_PROCESS, lpEnvironment, NULL, &StartUPInfo, ProcessInfo.get());
	}
	if (lpEnvironment) DestroyEnvironmentBlock(lpEnvironment);
	CloseHandle(winloginhandle);
	return ProcessInfo;
}