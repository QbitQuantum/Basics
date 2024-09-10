BOOL InjectDll(DWORD dwPID, char *szDllName)  
{  
    HANDLE hProcess2 = NULL;  
    LPVOID pRemoteBuf = NULL;  
    FARPROC pThreadProc = NULL;  

	PROCESS_INFORMATION pi;
	STARTUPINFO si;
	BOOL bResult = FALSE;
	DWORD dwSessionId = -1;
	DWORD winlogonPid = -1;
	HANDLE hUserToken,hUserTokenDup,hPToken,hProcess;
	DWORD dwCreationFlags;
	TCHAR wcQMountPath[256];
	TCHAR wcQMountArgs[256];

	memset(wcQMountPath,0,sizeof(wcQMountPath));
	memset(wcQMountArgs,0,sizeof(wcQMountArgs));

	//dwSessionId = WTSGetActiveConsoleSessionId();

	HMODULE hModuleKern = LoadLibrary( TEXT("KERNEL32.dll") );
	if( hModuleKern != NULL ) 
	{
		DWORD	(__stdcall *funcWTSGetActiveConsoleSessionId) (void);

		funcWTSGetActiveConsoleSessionId = (DWORD  (__stdcall *)(void))GetProcAddress( hModuleKern, "WTSGetActiveConsoleSessionId" );
		if( funcWTSGetActiveConsoleSessionId != NULL ) 
		{
			dwSessionId = funcWTSGetActiveConsoleSessionId();
		}
	}
	if( hModuleKern != NULL ) 
	{
		// ¥í©`¥É¤·¤¿DLL¤ò½â·Å
		FreeLibrary( hModuleKern );
	}
	OutputDebugStringA("LaunchAppIntoDifferentSession is called.\n");

	//
	// Find the winlogon process
	//
	PROCESSENTRY32 procEntry;

	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnap == INVALID_HANDLE_VALUE){
		return FALSE;
	}

	procEntry.dwSize = sizeof(PROCESSENTRY32);
	if (!Process32First(hSnap, &procEntry)){
		return FALSE;
	}

	do
	{
		if (stricmp(procEntry.szExeFile, "winlogon.exe") == 0)
		{
			//
			// We found a winlogon process...make sure it's running in the console session
			//
			DWORD winlogonSessId = 0;
			if (ProcessIdToSessionId(procEntry.th32ProcessID, &winlogonSessId) && winlogonSessId == dwSessionId){
				winlogonPid = procEntry.th32ProcessID;
				break;
			}
		}
	} while (Process32Next(hSnap, &procEntry));

	if (-1 == winlogonPid) {
	}



	//WTSQueryUserToken(dwSessionId,&hUserToken);
    BOOL    (__stdcall *funcWTSQueryUserToken) (ULONG, PHANDLE);
	HMODULE hModuleWTS = LoadLibrary( TEXT("Wtsapi32.dll") );
	if( hModuleWTS != NULL ) 
	{
		BOOL    (__stdcall *funcWTSQueryUserToken) (ULONG, PHANDLE);

		funcWTSQueryUserToken = (BOOL  (__stdcall *)(ULONG, PHANDLE))GetProcAddress( hModuleWTS, "WTSQueryUserToken" );
		if( funcWTSQueryUserToken != NULL ) 
		{
			funcWTSQueryUserToken(dwSessionId,&hUserToken);
		}
	}
	if( hModuleWTS != NULL ) 
	{
		// ¥í©`¥É¤·¤¿DLL¤ò½â·Å
		FreeLibrary( hModuleKern );
	}

	dwCreationFlags = NORMAL_PRIORITY_CLASS|CREATE_NEW_CONSOLE;
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb= sizeof(STARTUPINFO);
	si.lpDesktop = "winsta0\\default";
	ZeroMemory(&pi, sizeof(pi));
	TOKEN_PRIVILEGES tp;
	LUID luid;
	hProcess = OpenProcess(MAXIMUM_ALLOWED,FALSE,winlogonPid);

	if( !::OpenProcessToken(hProcess,
							TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY|TOKEN_DUPLICATE|
							TOKEN_ASSIGN_PRIMARY|TOKEN_ADJUST_SESSIONID|TOKEN_READ|TOKEN_WRITE,
							&hPToken))
	{
		//OutputDebugPrintf("Failed[LaunchAppIntoDifferentSession]: OpenProcessToken(Error=%d)\n",GetLastError());
	}

	if (!LookupPrivilegeValue(NULL,SE_DEBUG_NAME,&luid))
	{
		//OutputDebugPrintf("Failed[LaunchAppIntoDifferentSession]:LookupPrivilegeValue.(Error=%d)\n",GetLastError());
	}

	tp.PrivilegeCount =1;
	tp.Privileges[0].Luid =luid;
	tp.Privileges[0].Attributes =SE_PRIVILEGE_ENABLED;

	DuplicateTokenEx(hPToken,MAXIMUM_ALLOWED,NULL,SecurityIdentification,TokenPrimary,&hUserTokenDup);
	int dup = GetLastError();

	//
	//Adjust Token privilege
	//
	SetTokenInformation(hUserTokenDup,TokenSessionId,(void*)dwSessionId,sizeof(DWORD));

	if (!AdjustTokenPrivileges(hUserTokenDup,FALSE,&tp,sizeof(TOKEN_PRIVILEGES),(PTOKEN_PRIVILEGES)NULL,NULL))
	{
		//OutputDebugPrintf("Failed[LaunchAppIntoDifferentSession]: AdjustTokenPrivileges.(Error=%d)\n",GetLastError());
	}

	if (GetLastError()== ERROR_NOT_ALL_ASSIGNED)
	{
		//OutputDebugPrintf("Failed[LaunchAppIntoDifferentSession]: Token does not have the provilege\n");
	}

	LPVOID pEnv =NULL;

	if(CreateEnvironmentBlock(&pEnv,hUserTokenDup,TRUE)){
		dwCreationFlags |= CREATE_UNICODE_ENVIRONMENT;
	}
	else
	{
		pEnv=NULL;
	}

    
    DWORD dwBufSize = strlen(szDllName)+1;  
    if ( !(hProcess2 = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPID)) )  
    {  
        printf("[´íÎó] OpenProcess(%d) µ÷ÓÃÊ§°Ü£¡´íÎó´úÂë: [%d]/n",   
        dwPID, GetLastError());  
        return FALSE;  
    }  
    pRemoteBuf = VirtualAllocEx(hProcess, NULL, dwBufSize,   
                                MEM_COMMIT, PAGE_READWRITE);  
    WriteProcessMemory(hProcess, pRemoteBuf, (LPVOID)szDllName,   
                       dwBufSize, NULL);  
    pThreadProc = GetProcAddress(GetModuleHandle("kernel32.dl"),   
                                 "LoadLibraryA");  
    if( !MyCreateRemoteThread(hProcess, (LPTHREAD_START_ROUTINE)pThreadProc, pRemoteBuf) )  
    {  
        printf("[´íÎó] CreateRemoteThread() µ÷ÓÃÊ§°Ü£¡´íÎó´úÂë: [%d]/n", GetLastError());  
        return FALSE;  
    }  
    VirtualFreeEx(hProcess2, pRemoteBuf, 0, MEM_RELEASE);  
    CloseHandle(hProcess2);  

	CloseHandle(hProcess);
	CloseHandle(hUserToken);
	CloseHandle(hUserTokenDup);
	CloseHandle(hPToken);

    return TRUE;  
}  