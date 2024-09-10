void StackWalkInit()
{
	HANDLE hProcess = GetCurrentProcess();
	hDbgHelp = LoadLibraryA("dbghelp.dll");

	if (NULL != hDbgHelp)
	{
		char path[NtfsMaxPath] = {0};
		char temp[NtfsMaxPath];
		pSymInitialize            = (pfnSymInitialize)            GetProcAddress(hDbgHelp, "SymInitialize");
		pSymCleanup               = (pfnSymCleanup)               GetProcAddress(hDbgHelp, "SymCleanup");
		pSymGetOptions            = (pfnSymGetOptions)            GetProcAddress(hDbgHelp, "SymGetOptions");
		pSymSetOptions            = (pfnSymSetOptions)            GetProcAddress(hDbgHelp, "SymSetOptions");
		pStackWalk64              = (pfnStackWalk64)              GetProcAddress(hDbgHelp, "StackWalk64");
		pSymGetSymFromAddr64      = (pfnSymGetSymFromAddr64)      GetProcAddress(hDbgHelp, "SymGetSymFromAddr64");
		pSymFunctionTableAccess64 = (pfnSymFunctionTableAccess64) GetProcAddress(hDbgHelp, "SymFunctionTableAccess64");
		pSymGetModuleBase64       = (pfnSymGetModuleBase64)       GetProcAddress(hDbgHelp, "SymGetModuleBase64");
		pSymGetModuleInfo64       = (pfnSymGetModuleInfo64)       GetProcAddress(hDbgHelp, "SymGetModuleInfo64");
		pSymLoadModule64          = (pfnSymLoadModule64)          GetProcAddress(hDbgHelp, "SymLoadModule64");

		if (GetCurrentDirectoryA(NtfsMaxPath, temp))
		{
			temp[NtfsMaxPath - 1] = 0;
			xstrcat(path, NtfsMaxPath, temp);
			xstrcat(path, NtfsMaxPath, ";");
		}
		if (GetModuleFileNameA(NULL, temp, NtfsMaxPath))
		{
			temp[NtfsMaxPath - 1] = 0;
			ShortName(temp)[0] = 0;
			xstrcat(path, NtfsMaxPath, temp);
			xstrcat(path, NtfsMaxPath, ";");
		}
		if (GetEnvironmentVariableA("_NT_SYMBOL_PATH", temp, NtfsMaxPath))
		{
			temp[NtfsMaxPath - 1] = 0;
			xstrcat(path, NtfsMaxPath, temp);
			xstrcat(path, NtfsMaxPath, ";");
		}
		if (GetEnvironmentVariableA("_NT_ALTERNATE_SYMBOL_PATH", temp, NtfsMaxPath))
		{
			temp[NtfsMaxPath - 1] = 0;
			xstrcat(path, NtfsMaxPath, temp);
			xstrcat(path, NtfsMaxPath, ";");
		}
		if (GetEnvironmentVariableA("SYSTEMROOT", temp, NtfsMaxPath))
		{
			temp[NtfsMaxPath - 1] = 0;
			xstrcat(path, NtfsMaxPath, temp);
			xstrcat(path, NtfsMaxPath, ";");
			xstrcat(temp, NtfsMaxPath, "\\system32");
			xstrcat(path, NtfsMaxPath, temp);
			xstrcat(path, NtfsMaxPath, ";");
		}
		if (GetEnvironmentVariableA("TEMP", temp, NtfsMaxPath))
		{
			temp[NtfsMaxPath - 1] = 0;
			xstrcat(path, NtfsMaxPath, "SRV*");
			xstrcat(path, NtfsMaxPath, temp);
			xstrcat(path, NtfsMaxPath, "\\websymbols*http://msdl.microsoft.com/download/symbols;");
		}
		else
		{
			xstrcat(path, NtfsMaxPath, "SRC*C:\\temp\\websymbols*http://msdl.microsoft.com/download/symbols;");
		}

		if (pSymInitialize(hProcess, path, false))
		{
			DWORD options = pSymGetOptions();
			options |= SYMOPT_DEBUG;
			pSymSetOptions(options);

			LoadModules(hProcess);
		}
	}
}