VOID LoadSatellites(PWCHAR Satellites, HANDLE hModuleToPatch, char* szExportName)
{
	PWCHAR CurrSatellite = Satellites;
	NTSTATUS ntStatus;

	while (CurrSatellite[0] != 0)
	{
		WCHAR WinDir[MAX_PATH];
		WCHAR SysDir[MAX_PATH];
		WCHAR Path[MAX_PATH*4];
		WCHAR Name[MAX_PATH];
		UNICODE_STRING SatelliteName;
		HANDLE hModule;
		DWORD CurrSatellite_PathLen = (DWORD)wcslen(CurrSatellite);
		WCHAR ExeName[MAX_PATH];

// prepare parameters
		memcpy(Path, CurrSatellite, sizeof(WCHAR)*(CurrSatellite_PathLen+1));
		PathRemoveFileSpecW(Path);
		if (GetWindowsDirectoryW(WinDir, _countof(WinDir)))
		{
			wcscat(Path, L";");
			wcscat(Path, WinDir);
		}
		if (GetSystemDirectoryW(SysDir, _countof(SysDir)))
		{
			wcscat(Path, L";");
			wcscat(Path, SysDir);
		}

		memcpy(Name, CurrSatellite, sizeof(WCHAR)*(CurrSatellite_PathLen+1));
		PathStripPathW(Name);

		SatelliteName.Length = (USHORT)wcslen(Name)*sizeof(WCHAR);
		SatelliteName.MaximumLength = (USHORT)(SatelliteName.Length+sizeof(WCHAR));
		SatelliteName.Buffer = Name;

// call original LdrLoadDll
		ntStatus = ((fLdrLoadDll)g_pLdrLoadDll_Context->m_Thunk)(Path, 0, &SatelliteName, &hModule);

		ExeName[0] = 0;
		GetModuleFileNameW(NULL, ExeName, _countof(ExeName));
		PathStripPathW(ExeName);
		DbPrint("r3hook::LoadSatellites - %hs \'%ls\' module into process \'%ls\', search path \'%ls\'\n",
			ntStatus == 0 ? "successefully loaded(or it was already loaded)" : "failed to load",
			Name, ExeName, Path);

		if (ntStatus == 0L && hModule)
		{
			if (szExportName)
			{
				t_fHookHandlerExport f_HookExport;

				DbPrint("r3hook::LoadSatellites - trying to call %hs...\n", szExportName);
				f_HookExport = (t_fHookHandlerExport)GetProcAddress(hModule, szExportName);
				if (f_HookExport)
				{
					//DbPrint("r3hook::LoadSatellites - calling HookExports\n");
					f_HookExport(hModuleToPatch);
				}
				else
					DbPrint("r3hook::LoadSatellites - export '%hs' not found in module %ls\n", szExportName, Name);
			}
		}

		CurrSatellite += CurrSatellite_PathLen+1;
	}
}