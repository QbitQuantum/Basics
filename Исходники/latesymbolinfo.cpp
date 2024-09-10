void LateSymbolInfo::loadMinidump(std::wstring& dumppath, bool delete_when_done)
{
	// Method credit to http://stackoverflow.com/a/8119364/21501

	if (debugClient5 || debugControl4 || debugSymbols3)
	{
		//throw SleepyException(L"Minidump symbols already loaded.");

		// maybe the user moved a .pdb to somewhere where we can now find it?
		unloadMinidump();
	}

	IDebugClient *debugClient = NULL;

	SetLastError(0);
	comenforce(DebugCreate(__uuidof(IDebugClient), (void**)&debugClient), "DebugCreate");
	comenforce(debugClient->QueryInterface(__uuidof(IDebugClient5 ), (void**)&debugClient5 ), "QueryInterface(IDebugClient5)" );
	comenforce(debugClient->QueryInterface(__uuidof(IDebugControl4), (void**)&debugControl4), "QueryInterface(IDebugControl4)");
	comenforce(debugClient->QueryInterface(__uuidof(IDebugSymbols3), (void**)&debugSymbols3), "QueryInterface(IDebugSymbols3)");
	comenforce(debugClient5->SetOutputCallbacksWide(debugOutputCallbacks), "IDebugClient5::SetOutputCallbacksWide");
	comenforce(debugSymbols3->SetSymbolOptions(SYMOPT_UNDNAME | SYMOPT_LOAD_LINES | SYMOPT_OMAP_FIND_NEAREST | SYMOPT_AUTO_PUBLICS | SYMOPT_DEBUG), "IDebugSymbols::SetSymbolOptions");

	std::wstring sympath;
	prefs.AdjustSymbolPath(sympath, true);

	comenforce(debugSymbols3->SetSymbolPathWide(sympath.c_str()), "IDebugSymbols::SetSymbolPath");
	comenforce(debugClient5->OpenDumpFileWide(dumppath.c_str(), NULL), "IDebugClient4::OpenDumpFileWide");
	comenforce(debugControl4->WaitForEvent(0, INFINITE), "IDebugControl::WaitForEvent");

	// Since we can't just enumerate all symbols in all modules referenced by the minidump,
	// we have to keep the debugger session open and query symbols as requested by the
	// profiler GUI.

	debugClient->Release(); // but keep the other ones

	// If we are given a temporary file, clean it up later
	if (delete_when_done)
		file_to_delete = dumppath;
}