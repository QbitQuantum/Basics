void LoadModules()
{
	const int MAX_MOD_HANDLES = 1024;
	HMODULE StaticModuleHandleArray[MAX_MOD_HANDLES];
	HMODULE* ModuleHandleArray;
	DWORD Needed;

	HANDLE hProcess = GetCurrentProcess();
	ModuleHandleArray = &StaticModuleHandleArray[0];

	BOOL result = EnumProcessModules(hProcess, ModuleHandleArray, sizeof(ModuleHandleArray), &Needed);

	if( !result )
	{
		DWORD error = GetLastError();
		DebugLog("EnumProcessModule failed: error = %d", error);
		return;
	}

	if( Needed > sizeof(ModuleHandleArray) )  // was our static array not big enough?
	{
		ModuleHandleArray = (HMODULE*)DialogAllocator.AllocateBytes(Needed, sizeof(void*));
		BOOL result = EnumProcessModules(hProcess, ModuleHandleArray, Needed, &Needed);

		if( !result )
		{
			DWORD error = GetLastError();
			DebugLog("EnumProcessModule(2) failed: error = %d", error);
			return;
		}
	}

	int NumModules = Needed / sizeof(HMODULE);

	MODULEINFO ModuleInfo;
	char ModuleFilePath[MAX_PATH];
	char ModuleName[256];
	char SearchFilePath[MAX_PATH];

	for( int i = 0; i < NumModules; i++ )
	{
		GetModuleInformation(hProcess, ModuleHandleArray[i], &ModuleInfo, sizeof(MODULEINFO));
		GetModuleFileNameExA(hProcess, ModuleHandleArray[i], ModuleFilePath, MAX_PATH);
		GetModuleBaseNameA(hProcess, ModuleHandleArray[i], ModuleName, 256);

		char* FileName = nullptr;
		GetFullPathNameA(ModuleFilePath, MAX_PATH, SearchFilePath, &FileName);
		*FileName = 0;

		SymSetSearchPath(hApplicationProcess, SearchFilePath);

		DWORD64 BaseAddress = SymLoadModule64(hApplicationProcess, ModuleHandleArray[i], ModuleFilePath, ModuleName, (DWORD64)ModuleInfo.lpBaseOfDll, (DWORD) ModuleInfo.SizeOfImage);
		if( !BaseAddress )
		{
			DWORD error = GetLastError();
			DebugLog("SymLoadModule64 failed: error = %d", error);
		}
	}
}