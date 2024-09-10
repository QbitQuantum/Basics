// Search if there is a suspicious TeslaCrypt process
DWORD CTeslaDecrypterApp::SearchForTeslaCryptProcess(LPTSTR lpFileFullPath, DWORD sizeInChars) {
	HANDLE hProcSnap = NULL;			// Current system processes snapshot handle
	BOOL bProcRetVal = FALSE,			// Process32xxx Returned value
		bRetVal = FALSE;				// Standard Win32 returned value
	DWORD nBytesIo = 0;					// Number of I/O bytes
	DWORD dwFoundProcId = 0;			// Found TeslaCrypt process ID
	PROCESSENTRY32 curProc = {0};		// Current process entry
	LPBYTE lpMemBuff = NULL;

	hProcSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcSnap == INVALID_HANDLE_VALUE ) return 0;
	if (!g_strAppData) return 0;

	curProc.dwSize = sizeof(PROCESSENTRY32);
	bProcRetVal = Process32First(hProcSnap, &curProc);

	while (bProcRetVal) {
		DWORD dwCurProcId = curProc.th32ProcessID;
		HANDLE hModuleSnap = NULL;
		MODULEENTRY32 modEntry = {sizeof(MODULEENTRY32)};

		hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwCurProcId);
		
		// Go to next process
		bProcRetVal = Process32Next(hProcSnap, &curProc);

		if (hModuleSnap == INVALID_HANDLE_VALUE)
			continue;
		
		if (!Module32First( hModuleSnap, &modEntry )) {
			CloseHandle( hModuleSnap );
			continue;
		}
		
		CloseHandle( hModuleSnap );
		
		DWORD dwAppDataLen = wcslen(g_strAppData);
		if (_wcsnicmp(modEntry.szExePath, g_strAppData, dwAppDataLen) == 0 &&
			wcschr(&modEntry.szExePath[dwAppDataLen+1], L'\\') == NULL) {
			DWORD dwFileSize = 0;

			// Open target process
			HANDLE hProc = OpenProcess(PROCESS_VM_READ | SYNCHRONIZE, FALSE, dwCurProcId);

			if (hProc) {
				lpMemBuff = (LPBYTE)VirtualAlloc(0, modEntry.modBaseSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
				// I don't care if the allocation goes wrong... I am too lazy
				// if (!lpFileBuff) .... blablabla boring stuff ...
				if (lpMemBuff)
					bRetVal = ReadProcessMemory(hProc, modEntry.modBaseAddr, lpMemBuff, modEntry.modBaseSize, &nBytesIo);
				else
					bRetVal = FALSE;

				// Close the process handle
				CloseHandle(hProc);
			}

			if (bRetVal && lpMemBuff) {
				LPSTR lpCryptStrPtr = (LPSTR)SearchUString(lpMemBuff, nBytesIo, L"CryptoLocker", true);
				if (!lpCryptStrPtr) {
					lpCryptStrPtr = (LPSTR)SearchUString(lpMemBuff, nBytesIo, L"HELP_TO_DECRYPT_YOUR_FILES", false);
					if (!lpCryptStrPtr) lpCryptStrPtr = (LPSTR)SearchUString(lpMemBuff, nBytesIo, L"HELP_RESTORE_FILES", false);
				}

				if (lpCryptStrPtr) {
					// Process found
					dwFoundProcId = dwCurProcId;

					g_pLog->WriteLine(L"Searching for TeslaCrypt process - Found TeslaCrypt process (ID: %i - Full Path: \"%s\")",
							(LPVOID)dwCurProcId, modEntry.szExePath);

					if (lpFileFullPath) {
						// Copy the process full path in the target buffer 
						DWORD maxSize = (sizeInChars > wcslen(modEntry.szExePath) ? 
							sizeInChars : wcslen(modEntry.szExePath));
						wcscpy_s(lpFileFullPath, maxSize, modEntry.szExePath);
					}
					break;
				}		
			}
		}
	}

	// Close the process snapshot
	CloseHandle(hProcSnap);
	if (lpMemBuff) VirtualFree(lpMemBuff, 0, MEM_RELEASE);

	if (!dwFoundProcId)
		g_pLog->WriteLine(L"SearchForTeslaCryptProcess - No active TeslaCrypt process found in this system!");

	return dwFoundProcId;
}