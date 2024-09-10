bool WINAPI PluginLoader::DLLEjecteurW(DWORD dwPid,PWSTR szDLLPath)
{
	/* Search address of module */
	MODULEENTRY32W meModule;
	meModule.dwSize = sizeof(meModule);
	HANDLE hSnapshot = NULL;
	
	hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwPid);
	if(hSnapshot == NULL)
		return false;
	
	/* Search the right modules of the process */
	Module32FirstW(hSnapshot, &meModule);
	do{
		if((lstrcmpiW(meModule.szModule,szDLLPath) == 0) || (lstrcmpiW(meModule.szExePath,szDLLPath) == 0))break;
	}while(Module32NextW(hSnapshot, &meModule));
	
	/* Get handle of the process */
	HANDLE hProcess;
	
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, false,dwPid);
	if(hProcess == NULL)
	{
		CloseHandle(hSnapshot);
		return false;
	}
	
	LPTHREAD_START_ROUTINE lpthThreadFunction;
	/* Get addresse of FreeLibrary in kernel32.dll */
	lpthThreadFunction = (LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandle(L"kernel32.dll"), "FreeLibrary");
	if(lpthThreadFunction == NULL)
	{
		CloseHandle(hProcess);
		CloseHandle(hSnapshot);
		return false;
	}	
	
	/* Creation the remote thread */
	DWORD dwThreadID = 0;
	HANDLE hThread = NULL;
	hThread = CreateRemoteThread(hProcess, NULL, 0, lpthThreadFunction,meModule.modBaseAddr, 0, &dwThreadID);
	if(hThread == NULL)
	{
		CloseHandle(hSnapshot);
		CloseHandle(hProcess);
		return false;
	}
	
	WaitForSingleObject(hThread,INFINITE);
	
	CloseHandle(hProcess);
	CloseHandle(hThread);
	
	return true;
}