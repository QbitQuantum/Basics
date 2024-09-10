static PROC SetProcAddressA(
	__in  HINSTANCE targetModule,
	__in  LPCSTR lpLibFileName,
	__in  LPCSTR lpProcName,
	__in  PROC  newFunction
	)
{
	PROC pfnHookAPIAddr = GetProcAddress( LoadLibraryA( lpLibFileName ), lpProcName );

	HINSTANCE hInstance = targetModule; 

	ULONG ulSize;
	PIMAGE_IMPORT_DESCRIPTOR pImportDesc = 
		(PIMAGE_IMPORT_DESCRIPTOR)ImageDirectoryEntryToData(
		hInstance,
		TRUE,
		IMAGE_DIRECTORY_ENTRY_IMPORT,
		&ulSize
		);

	while (pImportDesc->Name)
	{
		PSTR pszModName = (PSTR)((PBYTE) hInstance + pImportDesc->Name);
		if (_stricmp(pszModName, lpLibFileName) == 0) 
			break;   
		pImportDesc++;
	}

	PIMAGE_THUNK_DATA pThunk = 
		(PIMAGE_THUNK_DATA)((PBYTE) hInstance + pImportDesc->FirstThunk);

	while (pThunk->u1.Function)
	{
		PROC* ppfn = (PROC*) &pThunk->u1.Function;
		BOOL bFound = (*ppfn == pfnHookAPIAddr);

		if (bFound) 
		{
			MEMORY_BASIC_INFORMATION mbi;
			VirtualQuery(
				ppfn,
				&mbi,
				sizeof(MEMORY_BASIC_INFORMATION)
				);
			VirtualProtect(
				mbi.BaseAddress,
				mbi.RegionSize,
				PAGE_READWRITE,
				&mbi.Protect);

			*ppfn = *newFunction;

			DWORD dwOldProtect;
			VirtualProtect(
				mbi.BaseAddress,
				mbi.RegionSize,
				mbi.Protect,
				&dwOldProtect
				);
			break;
		}
		pThunk++;
	}

	return pfnHookAPIAddr;
}