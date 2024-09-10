static HMODULE HelperGetToucanDLL()
{
	if (g_toucan_dll)
		return g_toucan_dll;

	/*
	** We need to enumerate the DLLs loaded to find toucan dll.
	** This is done because the toucan dll changes with each update.
	** The toucan dll has the following format. "xfire_toucan_{BUILD_NUMBER}.dll"
	** We simply try to find a dll w/ the prefix "xfire_toucan"
	*/
	HANDLE snapshot_handle = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, GetCurrentProcessId());
	if (snapshot_handle != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 module_entry;
		module_entry.dwSize = sizeof(MODULEENTRY32); 

		BOOL result = Module32First(snapshot_handle, &module_entry);
		char module_name[] = "xfire_toucan";
		DWORD module_name_len = sizeof(module_name)-1;
		while (result)
		{
			if (CompareStringA(LOCALE_USER_DEFAULT, NORM_IGNORECASE, module_entry.szModule, module_name_len, module_name, module_name_len) == CSTR_EQUAL)
			{
				g_toucan_dll = module_entry.hModule;
				break;
			}
			result = Module32Next(snapshot_handle, &module_entry);
		}

		CloseHandle(snapshot_handle);
	}

	return g_toucan_dll;
}