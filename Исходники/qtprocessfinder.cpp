bool QtProcessFinder::processUsesQt(int pid) {
	HANDLE hModuleSnap = INVALID_HANDLE_VALUE;
	MODULEENTRY32 me32;

	// Take a snapshot of all modules in the specified process.
	hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
	if (hModuleSnap == INVALID_HANDLE_VALUE) {
		qWarning("CreateToolhelp32Snapshot (of modules)");
		return false;
	}

	// Set the size of the structure before using it.
	me32.dwSize = sizeof(MODULEENTRY32);

	// Retrieve information about the first module,
	// and exit if unsuccessful
	if (!Module32First(hModuleSnap, &me32)) {
		qWarning("Module32First"); // show cause of failure
		CloseHandle(hModuleSnap);  // clean the snapshot object
		return false;
	}

	// Now walk the module list of the process,
	// and display information about each module
	do {
		if (wcsncmp(me32.szModule, L"Qt5", 3) == 0) {
			return true;
		}
	} while (Module32Next(hModuleSnap, &me32));

	CloseHandle(hModuleSnap);
	return false;
}