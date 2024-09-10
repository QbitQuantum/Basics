// Enumerate the modules we have running and load their symbols.
// Return true if successful.
bool EnumAndLoadModuleSymbols(HANDLE hProcess, DWORD pid )
{
	HANDLE hSnapShot;
	MODULEENTRY32 me = { sizeof me };
	bool keepGoing;
	hSnapShot = CreateToolhelp32Snapshot( TH32CS_SNAPMODULE, pid );
	if ( hSnapShot == (HANDLE) -1 )
		return false;

	keepGoing = Module32First( hSnapShot, &me );
	while ( keepGoing )
	{
		// here, we have a filled-in MODULEENTRY32. Use it to load symbols.
		// Don't check errors, if we can't load symbols for some modules we just
		// won't be able to do symbolic reports on them.
		StrAnsi staExePath(me.szExePath);
		StrAnsi staModule(me.szModule);
//		SymLoadModule( hProcess, 0, me.szExePath, me.szModule, (DWORD) me.modBaseAddr,
//			me.modBaseSize);
		::SymLoadModule( hProcess, 0, const_cast<char *>(staExePath.Chars()),
			const_cast<char *>(staModule.Chars()), (DWORD)me.modBaseAddr, me.modBaseSize);
		keepGoing = Module32Next( hSnapShot, &me );
	}

	CloseHandle( hSnapShot );
	return true;
}