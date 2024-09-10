static void* GetCurrentThreadEntryPoint()
{
	pNtQIT NtQueryInformationThread = (pNtQIT)GetProcAddress(GetModuleHandle(_T("ntdll.dll")), "NtQueryInformationThread");
	if (NtQueryInformationThread == NULL)
		return 0;

	HANDLE hDupHandle, hCurrentProcess = GetCurrentProcess();
	if (!DuplicateHandle(hCurrentProcess, GetCurrentThread(), hCurrentProcess, &hDupHandle, THREAD_QUERY_INFORMATION, FALSE, 0)) {
		SetLastError(ERROR_ACCESS_DENIED);
		return NULL;
	}
	
	DWORD_PTR dwStartAddress;
	LONG ntStatus = NtQueryInformationThread(hDupHandle, ThreadQuerySetWin32StartAddress, &dwStartAddress, sizeof(DWORD_PTR), NULL);
	CloseHandle(hDupHandle);

	return (ntStatus != ERROR_SUCCESS) ? NULL : (void*)dwStartAddress;
}