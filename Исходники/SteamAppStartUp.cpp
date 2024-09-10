// Handles launching the game indirectly via steam
void LaunchSelfViaSteam(const char *params)
{
	// calculate the details of our launch
	char appPath[MAX_PATH];
	::GetModuleFileName((HINSTANCE)GetModuleHandle(NULL), appPath, sizeof(appPath));

	// strip out the exe name
	char *slash = strrchr(appPath, '\\');
	if (slash)
	{
		*slash = '\0';
	}

	// save out our details to the registry
	HKEY hKey;
	if (ERROR_SUCCESS == RegOpenKey(HKEY_CURRENT_USER, "Software\\Valve\\Steam", &hKey))
	{
		DWORD dwType = REG_SZ;
		DWORD dwSize = static_cast<DWORD>( strlen(appPath) + 1 );
		RegSetValueEx(hKey, "TempAppPath", NULL, dwType, (LPBYTE)appPath, dwSize);
		dwSize = static_cast<DWORD>( strlen(params) + 1 );
		RegSetValueEx(hKey, "TempAppCmdLine", NULL, dwType, (LPBYTE)params, dwSize);
		// clear out the appID (since we don't know it yet)
		dwType = REG_DWORD;
		int appID = -1;
		RegSetValueEx(hKey, "TempAppID", NULL, dwType, (LPBYTE)&appID, sizeof(appID));
		RegCloseKey(hKey);
	}

	// search for an active steam instance
	HWND hwnd = ::FindWindow("Valve_SteamIPC_Class", "Hidden Window");
	if (hwnd)
	{
		::PostMessage(hwnd, WM_USER + 3, 0, 0);
	}
	else
	{
		// couldn't find steam, find and launch it

		// first, search backwards through our current set of directories
		char steamExe[MAX_PATH] = "";
		char dir[MAX_PATH];

		if (::GetCurrentDirectoryA(sizeof(dir), dir))
		{
			char *slash = strrchr(dir, '\\');
			while (slash)
			{
				// see if steam_dev.exe is in the directory first
				slash[1] = 0;
				strcat(slash, "steam_dev.exe");
				FILE *f = fopen(dir, "rb");
				if (f)
				{
					// found it
					fclose(f);
					strcpy(steamExe, dir);
					break;
				}

				// see if steam.exe is in the directory
				slash[1] = 0;
				strcat(slash, "steam.exe");
				f = fopen(dir, "rb");
				if (f)
				{
					// found it
					fclose(f);
					strcpy(steamExe, dir);
					break;
				}

				// kill the string at the slash
				slash[0] = 0;

				// move to the previous slash
				slash = strrchr(dir, '\\');
			}
		}

		if (!steamExe[0])
		{
			// still not found, use the one in the registry
			HKEY hKey;
			if (ERROR_SUCCESS == RegOpenKey(HKEY_CURRENT_USER, "Software\\Valve\\Steam", &hKey))
			{
				DWORD dwType;
				DWORD dwSize = sizeof(steamExe);
				RegQueryValueEx(hKey, "SteamExe", NULL, &dwType, (LPBYTE)steamExe, &dwSize);
				RegCloseKey(hKey);
			}
		}

		if (!steamExe[0])
		{
			// still no path, error
			::MessageBox(NULL, "Error running game: could not find steam.exe to launch", "Fatal Error", MB_OK | MB_ICONERROR);
			return;
		}

		// fix any slashes
		for (char *slash = steamExe; *slash; slash++)
		{
			if (*slash == '/')
			{
				*slash = '\\';
			}
		}

		// change to the steam directory
		strcpy(dir, steamExe);
		char *delimiter = strrchr(dir, '\\');
		if (delimiter)
		{
			*delimiter = 0;
			_chdir(dir);
		}

		// exec steam.exe, in silent mode, with the launch app param
		char *args[4] = { steamExe, "-silent", "-applaunch", '\0' };
		_spawnv(_P_NOWAIT, steamExe, args);
	}
}