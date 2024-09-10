BOOL WINAPI EjectLibW(DWORD dwProcessId, PCWSTR pszLibFile) 
{
	BOOL fOk = FALSE; 
	HANDLE hthSnapshot = NULL;
	HANDLE hProcess = NULL, hThread = NULL;
	__try 
	{
		//нужен будет base address на pszLibFile, берем его HMODULE (MODULEENTRY32W)
		hthSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwProcessId);
		if (hthSnapshot == NULL) __leave;
		MODULEENTRY32W me = { sizeof(me) };
		BOOL fFound = FALSE;
		BOOL fMoreMods = Module32FirstW(hthSnapshot, &me);
		for (; fMoreMods; fMoreMods = Module32NextW(hthSnapshot, &me)) 
		{
			fFound = (lstrcmpiW(me.szModule, pszLibFile) == 0) || (lstrcmpiW(me.szExePath, pszLibFile) == 0);
			if (fFound) break;
		}
		if (!fFound) __leave;
		
		hProcess = OpenProcess(
			PROCESS_CREATE_THREAD |
			PROCESS_VM_OPERATION, 
			FALSE, dwProcessId);
		if (hProcess == NULL) __leave;
		
		//выгружаем dll (FreeLibrary) из удаленного процесса
		PTHREAD_START_ROUTINE pfnThreadRtn = (PTHREAD_START_ROUTINE) GetProcAddress(GetModuleHandle(TEXT("Kernel32")), "FreeLibrary");
		if (pfnThreadRtn == NULL) __leave;
		hThread = CreateRemoteThread(hProcess, NULL, 0, pfnThreadRtn, me.modBaseAddr, 0, NULL);
		if (hThread == NULL) __leave;
		
		WaitForSingleObject(hThread, INFINITE);
		fOk = TRUE; 
	}
	__finally 
	{ 
		if (hthSnapshot != NULL)
			CloseHandle(hthSnapshot);
		if (hThread != NULL)
			CloseHandle(hThread);
		if (hProcess != NULL)
			CloseHandle(hProcess);
	}
	return(fOk);
}