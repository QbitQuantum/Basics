BOOL WINAPI DllMain(HANDLE hDllHandle, DWORD dwReason, LPVOID lpReserved)
{
	CHAR* pFileName;
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		GetModuleFileName(NULL, g_szAutoExpFullPathName, sizeof(g_szAutoExpFullPathName));
		pFileName = StrRChr(g_szAutoExpFullPathName, NULL, '\\');
		if (pFileName) 
			pFileName++;
		else
			pFileName = g_szAutoExpFullPathName;
		lstrcpy(pFileName, "AUTOEXP.DAT");
	}
	return TRUE;
}