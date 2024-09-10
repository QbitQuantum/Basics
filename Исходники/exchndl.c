static
BOOL PEGetSymFromAddr(HANDLE hProcess, DWORD dwAddress, LPTSTR lpSymName, DWORD nSize)
{
	HMODULE hModule;
	PIMAGE_NT_HEADERS pNtHdr;
	IMAGE_NT_HEADERS NtHdr;
	PIMAGE_SECTION_HEADER pSection;
	DWORD dwNearestAddress = 0, dwNearestName;
	int i;

	if(!(hModule = (HMODULE) GetModuleBase(dwAddress)))
		return FALSE;

	{
		PIMAGE_DOS_HEADER pDosHdr;
		LONG e_lfanew;

		// Point to the DOS header in memory
		pDosHdr = (PIMAGE_DOS_HEADER)hModule;

		// From the DOS header, find the NT (PE) header
		if(!ReadProcessMemory(hProcess, &pDosHdr->e_lfanew, &e_lfanew, sizeof(e_lfanew), NULL))
			return FALSE;

		pNtHdr = (PIMAGE_NT_HEADERS)((DWORD)hModule + (DWORD)e_lfanew);

		if(!ReadProcessMemory(hProcess, pNtHdr, &NtHdr, sizeof(IMAGE_NT_HEADERS), NULL))
			return FALSE;
	}

	pSection = (PIMAGE_SECTION_HEADER) ((DWORD)pNtHdr + sizeof(DWORD) + sizeof(IMAGE_FILE_HEADER) + NtHdr.FileHeader.SizeOfOptionalHeader);

	// Look for export section
	for (i = 0; i < NtHdr.FileHeader.NumberOfSections; i++, pSection++)
	{
		IMAGE_SECTION_HEADER Section;
		PIMAGE_EXPORT_DIRECTORY pExportDir = NULL;
		BYTE ExportSectionName[IMAGE_SIZEOF_SHORT_NAME] = {'.', 'e', 'd', 'a', 't', 'a', '\0', '\0'};

		if(!ReadProcessMemory(hProcess, pSection, &Section, sizeof(IMAGE_SECTION_HEADER), NULL))
			return FALSE;

		if(memcmp(Section.Name, ExportSectionName, IMAGE_SIZEOF_SHORT_NAME) == 0)
			pExportDir = (PIMAGE_EXPORT_DIRECTORY) Section.VirtualAddress;
		else if ((NtHdr.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress >= Section.VirtualAddress) && (NtHdr.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress < (Section.VirtualAddress + Section.SizeOfRawData)))
			pExportDir = (PIMAGE_EXPORT_DIRECTORY) NtHdr.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress;

		if(pExportDir)
		{
			IMAGE_EXPORT_DIRECTORY ExportDir;

			if(!ReadProcessMemory(hProcess, (PVOID)((DWORD)hModule + (DWORD)pExportDir), &ExportDir, sizeof(IMAGE_EXPORT_DIRECTORY), NULL))
				return FALSE;

			{
				PDWORD *AddressOfFunctions = alloca(ExportDir.NumberOfFunctions*sizeof(PDWORD));
				int j;

				if(!ReadProcessMemory(hProcess, (PVOID)((DWORD)hModule + (DWORD)ExportDir.AddressOfFunctions), AddressOfFunctions, ExportDir.NumberOfFunctions*sizeof(PDWORD), NULL))
						return FALSE;

				for(j = 0; j < ExportDir.NumberOfNames; ++j)
				{
					DWORD pFunction = (DWORD)hModule + (DWORD)AddressOfFunctions[j];
					//ReadProcessMemory(hProcess, (DWORD) hModule + (DWORD) (&ExportDir.AddressOfFunctions[j]), &pFunction, sizeof(pFunction), NULL);

					if(pFunction <= dwAddress && pFunction > dwNearestAddress)
					{
						dwNearestAddress = pFunction;

						if(!ReadProcessMemory(hProcess, (PVOID)((DWORD)hModule + (DWORD)(&ExportDir.AddressOfNames)[j]), &dwNearestName, sizeof(dwNearestName), NULL))
							return FALSE;

						dwNearestName = (DWORD) hModule + dwNearestName;
					}
				}
			}
		}
    }

	if(!dwNearestAddress)
		return FALSE;

	if(!ReadProcessMemory(hProcess, (PVOID)dwNearestName, lpSymName, nSize, NULL))
		return FALSE;
	lpSymName[nSize - 1] = 0;

	return TRUE;
}