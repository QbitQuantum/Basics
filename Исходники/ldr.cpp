int main_f()
{	
	lpMyReserved = &__ImageBase;
	//simulation the host exe
	//HMEMORYMODULE hMemMod = LoadMemDll("patchframe.dll");

	unsigned char *buffer = (unsigned char*)VirtualAlloc(NULL, iPeModLen, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	memcpy(buffer, PeMod, iPeModLen);
	typedef ULONG_PTR (WINAPI *PF_ReflectiveLoader)(LPVOID lpParameter);
	PF_ReflectiveLoader pPF_ReflectiveLoader = (PF_ReflectiveLoader)GetRefLdrOffset((char*)buffer, "_ReflectiveLoader@4");
	if (pPF_ReflectiveLoader)
		pPF_ReflectiveLoader(lpMyReserved);
	
	//HMEMORYMODULE hMemMod = MemoryLoadLibrary(PeMod, iPeModLen);
	//HMODULE hMod = LoadLibraryA("patchframe.dll");
	//HMODULE hMod = LoadLibraryA("G:\\dev_code_x\\patchframe\\Debug\\patchframe.dll");

	// call in the dll and not return
	Sleep(INFINITE);
	DebugBreak();
	return 0;

	unsigned char *buf;
	unsigned int bufsize;
	buf = (unsigned char*)VirtualAlloc(NULL, bufsize + 5, MEM_COMMIT, PAGE_EXECUTE_READWRITE);


	//move self to another place and run
	PIMAGE_DOS_HEADER dos_header = &__ImageBase;
	PIMAGE_NT_HEADERS old_header = (PIMAGE_NT_HEADERS)&((const unsigned char *)(&__ImageBase))[dos_header->e_lfanew];
	DWORD dwProtect = 0;
	BOOL bChge = VirtualProtectEx(GetCurrentProcess(), &__ImageBase, old_header->OptionalHeader.SizeOfImage, PAGE_EXECUTE_READWRITE, &dwProtect);
	
	
	
	SYSTEM_INFO sysInfo;
	GetNativeSystemInfo(&sysInfo);
	size_t alignedImageSize = ALIGN_VALUE_UP(old_header->OptionalHeader.SizeOfImage, sysInfo.dwPageSize);

	// reserve memory for image of library
	// XXX: is it correct to commit the complete memory region at once?
	//      calling DllEntry raises an exception if we don't...
	unsigned char *code = (unsigned char *)VirtualAlloc(NULL,
			alignedImageSize,
			MEM_RESERVE | MEM_COMMIT,
			PAGE_READWRITE
			);
		if (code == NULL) {
			SetLastError(ERROR_OUTOFMEMORY);
			return NULL;
		};
	//do copy
		memcpy(code, dos_header, alignedImageSize);
		ptrdiff_t locationDelta = (ptrdiff_t)(code - old_header->OptionalHeader.ImageBase);

		bool isRelocated = PerformBaseRelocation(code, locationDelta);
		//fix the mem flag

		HANDLE hProcess = GetCurrentProcess();
		BOOL bExpandRegions = FALSE;
		BOOL bOk = TRUE;
		PVOID pvAddress = NULL;
		while (bOk) {

			VMQUERY vmq;
			bOk = VMQuery(hProcess, pvAddress, &vmq);

			if (bOk) {
				// Construct the line to be displayed, and add it to the list box.
				TCHAR szLine[1024];
// 				ConstructRgnInfoLine(hProcess, &vmq, szLine, _countof(szLine));
// 				ListBox_AddString(hWndLB, szLine);

				if (bExpandRegions) {
					for (DWORD dwBlock = 0; bOk && (dwBlock < vmq.dwRgnBlocks);
						dwBlock++) {

// 						ConstructBlkInfoLine(&vmq, szLine, _countof(szLine));
// 						ListBox_AddString(hWndLB, szLine);

						// Get the address of the next region to test.
						pvAddress = ((PBYTE)pvAddress + vmq.BlkSize);
						if (dwBlock < vmq.dwRgnBlocks - 1) {
							// Don't query the memory info after the last block.
							bOk = VMQuery(hProcess, pvAddress, &vmq);
						}
					}
				}

				// Get the address of the next region to test.
				pvAddress = ((PBYTE)vmq.pvRgnBaseAddress + vmq.RgnSize);
			}
		}
		CloseHandle(hProcess);


	int argsCount;
	arglist = CommandLineToArgvW(GetCommandLineW(), &argsCount);
	if (!arglist)
		return 0;

}