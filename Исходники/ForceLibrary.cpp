BOOL ForceLibraryNT(CHAR* szLibraryPath,PROCESS_INFORMATION* pProcInfo)
{
	sLibLoadCodeNT  LibLoadCode;
	DWORD           dwRemoteThreadID;
	HANDLE          hRemoteThread;
	_CodeEntry      CodeEntry;

    
	// import NT only stuff manually
	HMODULE kernel = GetModuleHandle("kernel32.dll");

	typedef LPVOID (WINAPI*VirtualAllocExFunc)(
	HANDLE hProcess,          // process to allocate memory
	LPVOID lpAddress,         // desired starting address 
	SIZE_T dwSize,            // size of region to allocate
	DWORD flAllocationType,   // type of allocation
	DWORD flProtect           // type of access protection
	);
	VirtualAllocExFunc VirtualAllocExPtr = (VirtualAllocExFunc)GetProcAddress(kernel,"VirtualAllocEx");

	typedef BOOL (WINAPI*VirtualFreeExFunc)(
	HANDLE hProcess,   // handle to process
	LPVOID lpAddress,  // starting address of memory region
	SIZE_T dwSize,     // size of memory region
	DWORD dwFreeType   // operation type
	);
	VirtualFreeExFunc VirtualFreeExPtr = (VirtualFreeExFunc)GetProcAddress(kernel,"VirtualFreeEx");

	if(!VirtualFreeExPtr || !VirtualAllocExPtr)
	{
		//MessageBox(0,"couldnt import virtualallocex",0,0);
		printf("couldnt import virtualallocex\n");
		ExitProcess(1);
	}

	

	// get some mem in the target's process memory
	dwCodeStart = (DWORD)VirtualAllocExPtr(
		pProcInfo->hProcess,
		NULL,
		sizeof(LibLoadCode),
		MEM_COMMIT,
		PAGE_EXECUTE_READWRITE);
	if (!dwCodeStart)
		return FALSE;

	// init the LibLoadCode struct
	if (!InitCodeStruct(0, &LibLoadCode, szLibraryPath, dwCodeStart))
	{
		VirtualFreeExPtr(
			pProcInfo->hProcess,
			(VOID*)dwCodeStart,
			sizeof(LibLoadCode),
			MEM_DECOMMIT);
		return FALSE;
	}

	// copy the code into the allocated mem
	if (!WriteProcessMemory(
		pProcInfo->hProcess,
		(VOID*)dwCodeStart,
		&LibLoadCode,
		sizeof(LibLoadCode),
		&dwBytesWritten))
	{
		VirtualFreeExPtr(
			pProcInfo->hProcess,
			(VOID*)dwCodeStart,
			sizeof(LibLoadCode),
			MEM_DECOMMIT);
		return FALSE;
	}

	// execute it
	CodeEntry = (_CodeEntry)dwCodeStart;
	if (!(hRemoteThread = CreateRemoteThread(
		pProcInfo->hProcess,
		NULL,
		0,
		CodeEntry,
		NULL,
		0,
		&dwRemoteThreadID)))
	{
		VirtualFreeExPtr(
			pProcInfo->hProcess,
			(VOID*)dwCodeStart,
			sizeof(LibLoadCode),
			MEM_DECOMMIT);
		return FALSE;
	}

	// wait until the thread finishes
	WaitForSingleObject(hRemoteThread, INFINITE);
	if (!GetExitCodeThread(hRemoteThread, &dwLibBase))
	{
		VirtualFreeExPtr(
			pProcInfo->hProcess,
			(VOID*)dwCodeStart,
			sizeof(LibLoadCode),
			MEM_DECOMMIT);
		return FALSE;
	}

	// clean up
	VirtualFreeExPtr(
		pProcInfo->hProcess,
		(VOID*)dwCodeStart,
		sizeof(LibLoadCode),
		MEM_DECOMMIT);
	CloseHandle(hRemoteThread);

	if (dwLibBase)
		return TRUE;
	else
		return FALSE;
}