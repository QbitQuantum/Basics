BOOL InstallHook(LPCSTR module, LPCSTR function, void* hook, void** original) {
	HMODULE process = GetModuleHandle(NULL);

	// Save original address to function
	*original = (void*)GetProcAddress(
		GetModuleHandleA(module), function);

	ULONG entrySize;

	IMAGE_IMPORT_DESCRIPTOR* iid =
		(IMAGE_IMPORT_DESCRIPTOR*)ImageDirectoryEntryToData(
			process,
			1,
			IMAGE_DIRECTORY_ENTRY_IMPORT,
			&entrySize);

	// Search for module
	while (iid->Name) {
		const char* name = ((char*)process) + iid->Name;

		if (_stricmp(name, module) == 0) {
			return ModifyImportTable(iid, *original, hook);
		}
		iid += 1;
	}

	return FALSE;
}