DWORD WINAPI QueryRecycleBinThreadProc(void* pParam)
{
	// NOTE: Do not use CRT functions (since thread was created with CreateThread())!

	SHQUERYRBINFO rbi = {0};
	rbi.cbSize = sizeof(SHQUERYRBINFO);
	SHQueryRecycleBin(NULL, &rbi);
	g_BinCount = (double)rbi.i64NumItems;
	g_BinSize = (double)rbi.i64Size;

	EnterCriticalSection(&g_CriticalSection);
	HMODULE module = NULL;
	if (g_FreeInstanceInThread)
	{
		DWORD flags = GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT;
		GetModuleHandleEx(flags, (LPCWSTR)DllMain, &module);
		g_FreeInstanceInThread = false;
	}

	g_Thread = false;
	LeaveCriticalSection(&g_CriticalSection);

	if (module)
	{
		// Decrement the ref count and possibly unload the module if this is
		// the last instance.
		FreeLibraryAndExitThread(module, 0);
	}

	return 0;
}