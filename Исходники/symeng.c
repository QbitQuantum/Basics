static int InitSymEng(void)
{
	HANDLE hProcess = GetCurrentProcess();
	char szPath[MAX_PATH + 128];
	HMODULE hDbgHelp;

	GetWindowsDirectoryA(szPath, sizeof(szPath));
	strcat(szPath, "\\symbols\\dbghelp\\"
#ifdef _WIN64
		"x64"
#else
		"x86"
#endif
		"\\dbghelp.dll"
		);

	if ((hDbgHelp = LoadLibraryA(szPath)) &&
		(SymInitialize = (fpSymInitialize)GetProcAddress(hDbgHelp, "SymInitialize")) &&
		(SymSetOptions = (fpSymSetOptions)GetProcAddress(hDbgHelp, "SymSetOptions")) &&
		(SymGetOptions = (fpSymGetOptions)GetProcAddress(hDbgHelp, "SymGetOptions")) &&
		(SymSetSearchPath = (fpSymSetSearchPath)GetProcAddress(hDbgHelp, "SymSetSearchPath")) &&
		(SymLoadModule64 = (fpSymLoadModule64)GetProcAddress(hDbgHelp, "SymLoadModule64")) &&
		(SymFromName = (fpSymFromName)GetProcAddress(hDbgHelp, "SymFromName")) &&
		(SymUnloadModule64 = (fpSymUnloadModule64)GetProcAddress(hDbgHelp, "SymUnloadModule64"))
		)
	{
		strcpy(szPath, "SRV*");
		GetTempPathA(sizeof(szPath) - 4, szPath + 4);
		strcat(szPath, "SymbolCache");
		CreateDirectoryA(szPath + 4, NULL);

		strcat(szPath, "*http://msdl.microsoft.com/download/symbols");
		if (!SymInitialize(hProcess, 0, FALSE))
		{
			TRACE("SymInitialize failed: %08X", GetLastError());
			return -2;
		}

		TRACE("Symsrv options: %08X", SymGetOptions());

		SymSetOptions(SymGetOptions() | SYMOPT_ALLOW_ABSOLUTE_SYMBOLS | SYMOPT_DEBUG);
		SymSetOptions(SymGetOptions() & (~SYMOPT_DEFERRED_LOADS));
		SymSetSearchPath(hProcess, szPath);

		return 0;
	}
	TRACE("InitSymEng failed.");
	return -1;
}