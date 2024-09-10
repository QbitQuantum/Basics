static void StartStartMenu( DWORD sessionId )
{
	// run the classic start menu on logon
	HANDLE hUser;
	if (WTSQueryUserToken(sessionId,&hUser))
	{
		STARTUPINFO startupInfo={sizeof(STARTUPINFO),NULL,L"Winsta0\\Default"};
		PROCESS_INFORMATION processInfo;
		wchar_t path[_MAX_PATH];
		GetModuleFileName(NULL,path,_countof(path));
		PathRemoveFileSpec(path);
		PathAppend(path,L"ClassicStartMenu.exe -startup");
		LogText("Starting process: %S\n",path);
		if(CreateProcessAsUser(hUser,NULL,path,NULL,NULL,TRUE,NORMAL_PRIORITY_CLASS,NULL,NULL,&startupInfo,&processInfo))
		{
			CloseHandle(processInfo.hProcess);
			CloseHandle(processInfo.hThread);
		}
		else
		{
			int err=GetLastError();
			LogText("CreateProcessAsUser failed: %d\n",err);
		}
		CloseHandle(hUser);
	}
	else
	{
		int err=GetLastError();
		LogText("WTSQueryUserToken failed: %d\n",err);
	}
}