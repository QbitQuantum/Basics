BOOL InjectDll(DWORD dwPID, LPCTSTR szDllPath)
{
	HANDLE                  hProcess = NULL;
    HANDLE                  hThread = NULL;
	LPVOID                  pRemoteBuf = NULL;
	DWORD                   dwBufSize = (DWORD)(_tcslen(szDllPath) + 1) * sizeof(TCHAR);
	LPTHREAD_START_ROUTINE  pThreadProc = NULL;
    BOOL                    bRet = FALSE;
    HMODULE                 hMod = NULL;
    DWORD                   dwDesiredAccess = 0;
    TCHAR                   szProcName[MAX_PATH] = {0,};

    dwDesiredAccess = PROCESS_ALL_ACCESS;
    //dwDesiredAccess = MAXIMUM_ALLOWED;
	if ( !(hProcess = OpenProcess(dwDesiredAccess, FALSE, dwPID)) )
    {
        _tprintf(L"InjectDll() : OpenProcess(%d) failed!!! [%d]\n", 
                  dwPID, GetLastError());
		goto INJECTDLL_EXIT;
    }

	pRemoteBuf = VirtualAllocEx(hProcess, NULL, dwBufSize, 
                                MEM_COMMIT, PAGE_READWRITE);
    if( pRemoteBuf == NULL )
    {
        _tprintf(L"InjectDll() : VirtualAllocEx() failed!!! [%d]\n", 
                  GetLastError());
        goto INJECTDLL_EXIT;
    }

	if( !WriteProcessMemory(hProcess, pRemoteBuf, 
                           (LPVOID)szDllPath, dwBufSize, NULL) )
    {
        _tprintf(L"InjectDll() : WriteProcessMemory() failed!!! [%d]\n",
                  GetLastError());
        goto INJECTDLL_EXIT;
    }

    hMod = GetModuleHandle(L"kernel32.dll");
    if( hMod == NULL )
    {
        _tprintf(L"InjectDll() : GetModuleHandle(\"kernel32.dll\") failed!!! [%d]\n",
                  GetLastError());
        goto INJECTDLL_EXIT;
    }

	pThreadProc = (LPTHREAD_START_ROUTINE)GetProcAddress(hMod, "LoadLibraryW");
    if( pThreadProc == NULL )
    {
        _tprintf(L"InjectDll() : GetProcAddress(\"LoadLibraryW\") failed!!! [%d]\n", 
                  GetLastError());
        goto INJECTDLL_EXIT;
    }

    if( !MyCreateRemoteThread(hProcess, pThreadProc, pRemoteBuf) )
    {
        _tprintf(L"InjectDll() : MyCreateRemoteThread() failed!!!\n");
        goto INJECTDLL_EXIT;
    }

    bRet = CheckDllInProcess(dwPID, szDllPath);

INJECTDLL_EXIT:

    wsprintf(szProcName, L"%s", GetProcName(dwPID));
    if( szProcName[0] == '\0' )
        _tcscpy_s(szProcName, L"(no_process)");

    _tprintf(L"%s(%d) %s!!! [%d]\n", szProcName, dwPID, bRet ? L"SUCCESS" : L"-->> FAILURE", GetLastError());

    if( pRemoteBuf )
        VirtualFreeEx(hProcess, pRemoteBuf, 0, MEM_RELEASE);

    if( hThread )
	    CloseHandle(hThread);

    if( hProcess )
	    CloseHandle(hProcess);

	return bRet;
}