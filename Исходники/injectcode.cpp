int InjectDLL(HANDLE hProcess, TCHAR *szDllPath)
{
	int szDllPathLen = lstrlen(szDllPath) + 1;

	PWSTR RemoteProcessMemory = (PWSTR)VirtualAllocEx(hProcess, 
		NULL, szDllPathLen, MEM_RESERVE|MEM_COMMIT, PAGE_READWRITE);
	if(RemoteProcessMemory == NULL)
		return -1;
	
	BOOL bRet = WriteProcessMemory(hProcess, 
		RemoteProcessMemory, (PVOID)szDllPath, szDllPathLen, NULL);
	if(bRet == FALSE)
		return -1;
	
	PTHREAD_START_ROUTINE pfnThreadRtn;
	pfnThreadRtn = (PTHREAD_START_ROUTINE)GetProcAddress(
		GetModuleHandle("kernel32"), "LoadLibraryA");
	if(pfnThreadRtn == NULL)
		return -1;
	
	HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, 
		pfnThreadRtn, RemoteProcessMemory, 0, NULL);
	if(hThread == NULL)
		return -1;

	WaitForSingleObject(hThread, INFINITE);
	
	VirtualFreeEx(hProcess, 
		RemoteProcessMemory, szDllPathLen, MEM_RELEASE);

	CloseHandle(hThread);
	return 0;
}