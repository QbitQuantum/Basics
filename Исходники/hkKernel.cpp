// Helper function
bool FindModuleByAddress(const BYTE* lpAddress, LPWSTR pszModule, int cchMax)
{
	bool bFound = false;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, GetCurrentProcessId());
	if (hSnap != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 mi = {sizeof(mi)};
		if (Module32First(hSnap, &mi))
		{
			do {
				if ((lpAddress >= mi.modBaseAddr) && (lpAddress < (mi.modBaseAddr + mi.modBaseSize)))
				{
					bFound = true;
					if (pszModule)
						lstrcpyn(pszModule, mi.szExePath, cchMax);
					break;
				}
			} while (Module32Next(hSnap, &mi));
		}
		CloseHandle(hSnap);
	}

	if (!bFound && pszModule)
		*pszModule = 0;
	return bFound;
}