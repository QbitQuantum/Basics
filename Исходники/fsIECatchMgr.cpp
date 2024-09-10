BOOL fsIECatchMgr::InstallIeIntegration(BOOL bInstall, BOOL bCurrentUserOnly, BOOL bOverrideHKCR)
{
	bOverrideHKCR = bCurrentUserOnly && bOverrideHKCR;

	if (bOverrideHKCR)
	{
		CRegKey key;
		if (ERROR_SUCCESS == key.Open (HKEY_CURRENT_USER, _T ("Software\\Classes"), KEY_ALL_ACCESS))
			RegOverridePredefKey (HKEY_CLASSES_ROOT, key);
	}

	typedef HRESULT (_stdcall *fntDllRegUnregServer)(void);
	typedef HRESULT (_stdcall *fntInstaller)(bool, bool);
	fntDllRegUnregServer pfnDll = NULL;
	fntInstaller pfnInstaller = NULL;

	bool bFdmdm = false, bBho = false;

	
	HMODULE hLib = LoadLibrary ("iefdmdm.dll");
	if (hLib)
	{
		pfnInstaller = (fntInstaller) GetProcAddress (hLib, "vmsInstaller");
		if (pfnInstaller)
			bFdmdm = SUCCEEDED (pfnInstaller (bInstall, bCurrentUserOnly));
		FreeLibrary (hLib);
	}

	
	hLib = LoadLibrary ("iefdm2.dll");
	if (hLib)
	{
		pfnDll = (fntDllRegUnregServer) GetProcAddress (hLib, bInstall ? "DllRegisterServer" : "DllUnregisterServer");
		if (pfnDll)
			bBho = SUCCEEDED (pfnDll ());
		FreeLibrary (hLib);
	}

	if (bOverrideHKCR)
		RegOverridePredefKey (HKEY_CLASSES_ROOT, NULL);

	return bFdmdm && bBho;
}