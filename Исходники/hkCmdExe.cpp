// cmd.exe only!
LONG WINAPI OnRegQueryValueExW(HKEY hKey, LPCWSTR lpValueName, LPDWORD lpReserved, LPDWORD lpType, LPBYTE lpData, LPDWORD lpcbData)
{
	//typedef LONG (WINAPI* OnRegQueryValueExW_t)(HKEY hKey, LPCWSTR lpValueName, LPDWORD lpReserved, LPDWORD lpType, LPBYTE lpData, LPDWORD lpcbData);
	ORIGINAL_EX(RegQueryValueExW);
	LONG lRc = -1;

	if (gbIsCmdProcess && hKey && lpValueName)
	{
		// Allow `CD` to network paths
		if (lstrcmpi(lpValueName, L"DisableUNCCheck") == 0)
		{
			if (lpData)
			{
				if (lpcbData && *lpcbData >= sizeof(DWORD))
					*((LPDWORD)lpData) = gbAllowUncPaths;
				else
					*lpData = gbAllowUncPaths;
			}
			if (lpType)
				*lpType = REG_DWORD;
			if (lpcbData)
				*lpcbData = sizeof(DWORD);
			lRc = 0;
			goto wrap;
		}

		if (gbIsCmdProcess && hKey && lpValueName
			&& (lstrcmpi(lpValueName, L"AutoRun") == 0)
			&& InitializeClink())
		{
			if (gbAllowClinkUsage && gszClinkCmdLine
				&& IsInteractive())
			{
				// Is already loaded?
				if (!IsClinkLoaded()
					&& !gbClinkInjectRequested)
				{
					// Do this once, to avoid multiple initializations
					gbClinkInjectRequested = true;
					// May be it is set up itself?
					typedef LONG (WINAPI* RegOpenKeyEx_t)(HKEY hKey, LPCWSTR lpSubKey, DWORD ulOptions, REGSAM samDesired, PHKEY phkResult);
					typedef LONG (WINAPI* RegCloseKey_t)(HKEY hKey);
					HMODULE hAdvApi = LoadLibrary(L"AdvApi32.dll");
					if (hAdvApi)
					{
						RegOpenKeyEx_t _RegOpenKeyEx = (RegOpenKeyEx_t)GetProcAddress(hAdvApi, "RegOpenKeyExW");
						RegCloseKey_t  _RegCloseKey  = (RegCloseKey_t)GetProcAddress(hAdvApi, "RegCloseKey");
						if (_RegOpenKeyEx && _RegCloseKey)
						{
							const DWORD cchMax = 0x3FF0;
							const DWORD cbMax = cchMax*2;
							wchar_t* pszCmd = (wchar_t*)malloc(cbMax);
							if (pszCmd)
							{
								DWORD cbSize;
								bool bClinkInstalled = false;
								for (int i = 0; i <= 1 && !bClinkInstalled; i++)
								{
									HKEY hk;
									if (_RegOpenKeyEx(i?HKEY_LOCAL_MACHINE:HKEY_CURRENT_USER, L"Software\\Microsoft\\Command Processor", 0, KEY_READ, &hk))
										continue;
									if (!F(RegQueryValueExW)(hk, lpValueName, NULL, NULL, (LPBYTE)pszCmd, &(cbSize = cbMax))
										&& (cbSize+2) < cbMax)
									{
										cbSize /= 2; pszCmd[cbSize] = 0;
										CharLowerBuffW(pszCmd, cbSize);
										if (wcsstr(pszCmd, L"\\clink.bat"))
											bClinkInstalled = true;
									}
									_RegCloseKey(hk);
								}
								// Not installed via "Autorun"
								if (!bClinkInstalled)
								{
									int iLen = lstrlen(gszClinkCmdLine);
									_wcscpy_c(pszCmd, cchMax, gszClinkCmdLine);
									_wcscpy_c(pszCmd+iLen, cchMax-iLen, L" & "); // conveyer next command indifferent to %errorlevel%

									cbSize = cbMax - (iLen + 3)*sizeof(*pszCmd);
									if (F(RegQueryValueExW)(hKey, lpValueName, NULL, NULL, (LPBYTE)(pszCmd + iLen + 3), &cbSize)
										|| (pszCmd[iLen+3] == 0))
									{
										pszCmd[iLen] = 0; // There is no self value in registry
									}
									cbSize = (lstrlen(pszCmd)+1)*sizeof(*pszCmd);

									// Return
									lRc = 0;
									if (lpData && lpcbData)
									{
										if (*lpcbData < cbSize)
											lRc = ERROR_MORE_DATA;
										else
											_wcscpy_c((wchar_t*)lpData, (*lpcbData)/2, pszCmd);
									}
									if (lpcbData)
										*lpcbData = cbSize;
									free(pszCmd);
									FreeLibrary(hAdvApi);
									goto wrap;
								}
								free(pszCmd);
							}
						}
						FreeLibrary(hAdvApi);
					}
				}
			}
		}
	}

	if (F(RegQueryValueExW))
		lRc = F(RegQueryValueExW)(hKey, lpValueName, lpReserved, lpType, lpData, lpcbData);

wrap:
	return lRc;
}