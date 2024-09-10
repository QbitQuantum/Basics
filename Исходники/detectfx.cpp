/******************************************************************
Function Name:  CheckNetfxVersionUsingMscoree
Description:    Uses the logic described in the sample code at http://msdn2.microsoft.com/library/ydh6b3yb.aspx
				to load mscoree.dll and call its APIs to determine
				whether or not a specific version of the .NET
				Framework is installed on the system
Inputs:         pszNetfxVersionToCheck - version to look for
Results:        true if the requested version is installed
				false otherwise
******************************************************************/
bool CheckNetfxVersionUsingMscoree(const TCHAR *pszNetfxVersionToCheck)
{
	bool bFoundRequestedNetfxVersion = false;
	HRESULT hr = S_OK;

	// Check input parameter
	if (NULL == pszNetfxVersionToCheck)
		return false;

	HMODULE hmodMscoree = LoadLibraryEx(_T("mscoree.dll"), NULL, 0);
	if (NULL != hmodMscoree)
	{
		typedef HRESULT (STDAPICALLTYPE *GETCORVERSION)(LPWSTR szBuffer, DWORD cchBuffer, DWORD* dwLength);
		GETCORVERSION pfnGETCORVERSION = (GETCORVERSION)GetProcAddress(hmodMscoree, "GetCORVersion");

		// Some OSs shipped with a placeholder copy of mscoree.dll. The existence of mscoree.dll
		// therefore does NOT mean that a version of the .NET Framework is installed.
		// If this copy of mscoree.dll does not have an exported function named GetCORVersion
		// then we know it is a placeholder DLL.
		if (NULL == pfnGETCORVERSION)
			goto Finish;

		typedef HRESULT (STDAPICALLTYPE *CORBINDTORUNTIME)(LPCWSTR pwszVersion, LPCWSTR pwszBuildFlavor, REFCLSID rclsid, REFIID riid, LPVOID FAR *ppv);
		CORBINDTORUNTIME pfnCORBINDTORUNTIME = (CORBINDTORUNTIME)GetProcAddress(hmodMscoree, "CorBindToRuntime");

		typedef HRESULT (STDAPICALLTYPE *GETREQUESTEDRUNTIMEINFO)(LPCWSTR pExe, LPCWSTR pwszVersion, LPCWSTR pConfigurationFile, DWORD startupFlags, DWORD runtimeInfoFlags, LPWSTR pDirectory, DWORD dwDirectory, DWORD *dwDirectoryLength, LPWSTR pVersion, DWORD cchBuffer, DWORD* dwlength);
		GETREQUESTEDRUNTIMEINFO pfnGETREQUESTEDRUNTIMEINFO = (GETREQUESTEDRUNTIMEINFO)GetProcAddress(hmodMscoree, "GetRequestedRuntimeInfo");

		if (NULL != pfnCORBINDTORUNTIME)
		{
			TCHAR szRetrievedVersion[50];
			DWORD dwLength = CountOf(szRetrievedVersion);

			if (NULL == pfnGETREQUESTEDRUNTIMEINFO)
			{
				// Having CorBindToRuntimeHost but not having GetRequestedRuntimeInfo means that
				// this machine contains no higher than .NET Framework 1.0, but the only way to
				// 100% guarantee that the .NET Framework 1.0 is installed is to call a function
				// to exercise its functionality
				if (0 == _tcscmp(pszNetfxVersionToCheck, g_szNetfx10VersionString))
				{
					hr = pfnGETCORVERSION(szRetrievedVersion, dwLength, &dwLength);

					if (SUCCEEDED(hr))
					{
						if (0 == _tcscmp(szRetrievedVersion, g_szNetfx10VersionString))
							bFoundRequestedNetfxVersion = true;
					}

					goto Finish;
				}
			}

			// Set error mode to prevent the .NET Framework from displaying
			// unfriendly error dialogs
			UINT uOldErrorMode = SetErrorMode(SEM_FAILCRITICALERRORS);

			TCHAR szDirectory[MAX_PATH];
			DWORD dwDirectoryLength = 0;
			DWORD dwRuntimeInfoFlags = RUNTIME_INFO_DONT_RETURN_DIRECTORY | GetProcessorArchitectureFlag();

			// Check for the requested .NET Framework version
			hr = pfnGETREQUESTEDRUNTIMEINFO(NULL, pszNetfxVersionToCheck, NULL, STARTUP_LOADER_OPTIMIZATION_MULTI_DOMAIN_HOST, NULL, szDirectory, CountOf(szDirectory), &dwDirectoryLength, szRetrievedVersion, CountOf(szRetrievedVersion), &dwLength);

			if (SUCCEEDED(hr))
				bFoundRequestedNetfxVersion = true;

			// Restore the previous error mode
			SetErrorMode(uOldErrorMode);
		}
	}

Finish:
	if (hmodMscoree)
	{
		FreeLibrary(hmodMscoree);
	}

	return bFoundRequestedNetfxVersion;
}