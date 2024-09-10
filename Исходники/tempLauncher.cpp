int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	//UNREFERENCED_PARAMETER(lpCmdLine);

	char **	Command	= 0;
	CommandLineToArg(GetCommandLine(), &Command);
	if( strcmp("Updater", Command[1]) )
	{
		MessageBox(0, "Please start game from Launcher", "Start Error", ERROR);
		ExitProcess(0);
	}

	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

	HANDLE hToken;

	VMBEGIN

	if(!OpenThreadToken(GetCurrentThread(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, FALSE, &hToken))
    {
        if (GetLastError() == ERROR_NO_TOKEN)
        {
            if (!ImpersonateSelf(SecurityImpersonation))
			{
				MessageBox(NULL, "Code: 101", "Starter error", NULL);
				return 0;
			}

            if(!OpenThreadToken(GetCurrentThread(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, FALSE, &hToken)){
				MessageBox(NULL, "Code: 102", "Starter error", NULL);
				return 0;
            }
         }
        else
            return 0;
     }

	VMEND

	if( !SetPrivilege(hToken, SE_DEBUG_NAME, TRUE) )
    {
		MessageBox(NULL, "Code: 103", "Starter error", NULL);
        CloseHandle(hToken);
        return 0;
    }

	char szCmd[128];
	//DWORD dwTICK = ;
	//DWORD XOR = (DWORD)time(NULL);
	//dwTICK ^= XOR;
	sprintf(szCmd, "main.exe -test -k%d", GetTickCount());

    if( !CreateProcess( NULL,   // No module name (use command line)
        szCmd,        // Command line
        NULL,           // Process handle not inheritable
        NULL,           // Thread handle not inheritable
        FALSE,          // Set handle inheritance to FALSE
        NORMAL_PRIORITY_CLASS | CREATE_SUSPENDED,              // No creation flags
        NULL,           // Use parent's environment block
        NULL,           // Use parent's starting directory 
        &si,            // Pointer to STARTUPINFO structure
        &pi )           // Pointer to PROCESS_INFORMATION structure
    ) 
    {
		MessageBox(NULL, "Code: 104", "Starter error", NULL);
        return 0;
    }

	try
	{
		HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS,FALSE,pi.dwProcessId);

		if( !hProcess )
		{
			MessageBox(NULL, "Code: 105", "Starter error", NULL);
			return 0;
		}

		HANDLE hMainThread = OpenThread(THREAD_ALL_ACCESS,FALSE,pi.dwThreadId);

		if( !hMainThread )
		{
			MessageBox(NULL, "Code: 106", "Starter error", NULL);
			return 0;
		}

		VMBEGIN

		DWORD lOfs;
		BYTE jmp[2] = {0xEB,0xFE};
		BYTE original[2] = {0x60,0x9C};

		ReadProcessMemory(hProcess,(LPVOID)MAIN_EIP,original,2,&lOfs);
		WriteProcessMemory(hProcess,(LPVOID)MAIN_EIP,jmp,2,&lOfs);
		ResumeThread(hMainThread);

		CONTEXT context;

		for(int i = 0; i < 50 && context.Eip != MAIN_EIP; i++)	{
			Sleep(100);
			// read the thread context
			context.ContextFlags = CONTEXT_CONTROL;
			GetThreadContext( hMainThread, &context );
		}

		if( context.Eip != MAIN_EIP )
		{
			MessageBox(NULL, "Code: 107", "Starter error", NULL);
			return 0;
		}

		

		HANDLE hThread;
		char szLibPath[_MAX_PATH] = { "zClient.dll" };
		void* pLibRemote;
		HMODULE hKernel32 = ::GetModuleHandle("Kernel32");

		pLibRemote = ::VirtualAllocEx( hProcess, NULL, sizeof(szLibPath),MEM_COMMIT, PAGE_READWRITE );::WriteProcessMemory( hProcess, pLibRemote, (void*)szLibPath,sizeof(szLibPath), NULL );
		hThread = ::CreateRemoteThread( hProcess, NULL, 0,(LPTHREAD_START_ROUTINE) ::GetProcAddress( hKernel32,"LoadLibraryA" ),pLibRemote, 0, NULL );
		::WaitForSingleObject( hThread, INFINITE );

		SuspendThread(hMainThread);
		WriteProcessMemory(hProcess,(LPVOID)MAIN_EIP,original,2,&lOfs);
		ResumeThread(hMainThread);

		CloseHandle(hProcess);
		CloseHandle(hMainThread);

		VMEND
	}
	catch( ... )
	{
	}
	return true;
}