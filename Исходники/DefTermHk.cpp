bool InitDefTerm()
{
	bool lbRc = true;

	wchar_t szInfo[MAX_PATH*2];
	msprintf(szInfo, countof(szInfo), L"!!! TH32CS_SNAPMODULE, TID=%u, InitDefaultTerm\n", GetCurrentThreadId());
	DebugStr(szInfo); // Don't call DefTermLogString here - gpDefTerm was not initialized yet

	_ASSERTEX(gpDefTerm==NULL);
	gpDefTerm = new CDefTermHk();
	if (!gpDefTerm)
	{
		_ASSERTEX(gpDefTerm!=NULL);
		return false;
	}

	//_ASSERTE(FALSE && "InitDefaultTerm");

	// При обновлении ConEmu может обновиться и ConEmuHk.dll
	// Но в процессы с "DefTerm" грузится копия dll-ки, поэтому
	// после обновления в уже хукнутый процесс загружается
	// вторая "ConEmuHk.YYMMDD.dll", а старую при этом нужно
	// выгрузить. Этим и займемся.
	HMODULE hPrevHooks = NULL;
	_ASSERTEX(gnSelfPID!=0 && ghOurModule!=NULL);
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, gnSelfPID);
	if (hSnap != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 mi = {sizeof(mi)};
		//wchar_t szOurName[MAX_PATH] = L"";
		//GetModuleFileName(ghOurModule, szOurName, MAX_PATH);
		wchar_t szMinor[8] = L""; lstrcpyn(szMinor, WSTRING(MVV_4a), countof(szMinor));
		wchar_t szAddName[40];
		msprintf(szAddName, countof(szAddName),
			CEDEFTERMDLLFORMAT /*L"ConEmuHk%s.%02u%02u%02u%s.dll"*/,
			WIN3264TEST(L"",L"64"), MVV_1, MVV_2, MVV_3, szMinor);
		//LPCWSTR pszOurName = PointToName(szOurName);
		wchar_t* pszDot = wcschr(szAddName, L'.');
		wchar_t szCheckName[MAX_PATH+1];

		if (pszDot && Module32First(hSnap, &mi))
		{
			pszDot[1] = 0; // Need to check only name, without version number
			int nCurLen = lstrlen(szAddName);
			do {
				if (mi.hModule == ghOurModule)
					continue;
				lstrcpyn(szCheckName, PointToName(mi.szExePath), nCurLen+1);
				if (lstrcmpi(szCheckName, szAddName) == 0)
				{
					msprintf(szInfo, countof(szInfo),
						L"Prevous ConEmuHk module found at address " WIN3264TEST(L"0x%08X",L"0x%X%08X") L": %s",
						WIN3264WSPRINT(mi.hModule), mi.szExePath);
					DefTermLogString(szInfo);

					hPrevHooks = mi.hModule;
					break; // Prev (old version) instance found!
				}
			} while (Module32Next(hSnap, &mi));
		}

		CloseHandle(hSnap);
	}

	// Old library was found, unload it before continue
	if (hPrevHooks)
	{
		DefTermLogString(L"Trying to unload previous ConEmuHk module");
		if (!FreeLibrary(hPrevHooks))
		{
			lbRc = false;
			gpDefTerm->DisplayLastError(L"Unloading failed", GetLastError());
		}
		else
		{
			DefTermLogString(L"Unloading succeeded");
		}
	}

	// For Visual Studio check all spawned processes (children of gnSelfPID), find *.vshost.exe
	if (gbIsVStudio)
	{
		//_ASSERTEX(FALSE && "Continue to find existing *.vshost.exe");
		HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		if (hSnap != INVALID_HANDLE_VALUE)
		{
			PROCESSENTRY32 pe = {sizeof(pe)};
			if (Process32First(hSnap, &pe)) do
			{
				if (pe.th32ParentProcessID == gnSelfPID)
				{
					if (IsVsNetHostExe(pe.szExeFile)) // *.vshost.exe
					{
						// Found! Hook it!
						DefTermLogString(L"Child VsNetHost found, hooking");
						gpDefTerm->StartDefTermHooker(pe.th32ProcessID);
						break;
					}
				}
			} while (Process32Next(hSnap, &pe));
			CloseHandle(hSnap);
		}
	}

	DefTermLogString(L"InitDefaultTerm finished, calling StartDefTerm");

	gpDefTerm->StartDefTerm();

	return lbRc;
}