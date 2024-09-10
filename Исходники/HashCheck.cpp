HRESULT Uninstall( )
{
	HRESULT hr = S_OK;

	TCHAR szCurrentDllPath[MAX_PATH << 1];
	TCHAR szTemp[MAX_PATH << 1];

	LPTSTR lpszFileToDelete = szCurrentDllPath;
	LPTSTR lpszTempAppend = szTemp + GetModuleFileName(g_hModThisDll, szTemp, countof(szTemp));

    StringCbCopy(szCurrentDllPath, sizeof(szCurrentDllPath), szTemp);

#ifdef _WIN64
    // If this 64-bit dll was installed to the default location,
    // uninstall the 32-bit dll if it exists in its default location

    TCHAR lpszDefInstallPath[MAX_PATH + 0x20];
    UINT uSize = GetSystemDirectory(lpszDefInstallPath, MAX_PATH);

    if (uSize && uSize < MAX_PATH)
    {
        LPTSTR lpszPathAppend = lpszDefInstallPath + uSize;

        if (*(lpszPathAppend - 1) != TEXT('\\'))
            *lpszPathAppend++ = TEXT('\\');

        static const TCHAR szFolderAndFilename[] = TEXT("ShellExt") TEXT("\\") TEXT(HASHCHECK_FILENAME_STR);
        SSStaticCpy(lpszPathAppend, szFolderAndFilename);

        // If this 64-bit dll was installed to the default location
        if (StrCmpI(szCurrentDllPath, lpszDefInstallPath) == 0)
        {
            TCHAR lpszSystemWow64[MAX_PATH + 0x20];
            uSize = GetSystemWow64Directory(lpszSystemWow64, MAX_PATH);

            if (uSize && uSize < MAX_PATH)
            {
                LPTSTR lpszSystemWow64Append = lpszSystemWow64 + uSize;

                if (*(lpszSystemWow64Append - 1) != TEXT('\\'))
                    SSCpy2Ch(lpszSystemWow64Append++, TEXT('\\'), 0);

                StringCbCopyEx(lpszDefInstallPath, sizeof(lpszDefInstallPath), lpszSystemWow64, &lpszPathAppend, NULL, 0);

                SSStaticCpy(lpszPathAppend, szFolderAndFilename);

                // If the 32-bit dll exists in its default location
                if (PathFileExists(lpszDefInstallPath))
                {
                    static const TCHAR szRegsvr32[] = TEXT("regsvr32.exe");
                    SSStaticCpy(lpszSystemWow64Append, szRegsvr32);
                    // the lpszSystemWow64 buffer now contains the full regsvr32.exe path

                    TCHAR lpszCommandLine[MAX_PATH + 0x20];
                    LPTSTR lpszCommandLineAppend;
                    
                    static const TCHAR szCommandOpts[] = TEXT("regsvr32.exe /u /i /n /s ");
                    lpszCommandLineAppend = SSStaticCpy(lpszCommandLine, szCommandOpts) - 1;

                    StringCbCopy(lpszCommandLineAppend, sizeof(lpszCommandLine)-sizeof(szCommandOpts), lpszDefInstallPath);

                    STARTUPINFO si;
                    memset(&si, 0, sizeof(si));
                    si.cb = sizeof(si);

                    PROCESS_INFORMATION pi;
                    memset(&pi, 0, sizeof(pi));

                    if (!CreateProcess(lpszSystemWow64, lpszCommandLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
                        return E_FAIL;

                    DWORD dwExit;
                    WaitForSingleObject(pi.hProcess, INFINITE);
                    GetExitCodeProcess(pi.hProcess, &dwExit);
                    CloseHandle(pi.hThread);
                    CloseHandle(pi.hProcess);

                    if (dwExit != 0)
                        return E_FAIL;
                }
            }
        }
    }
#endif

	// Rename the DLL prior to scheduling it for deletion
	*lpszTempAppend++ = TEXT('.');
	SSCpy2Ch(lpszTempAppend, 0, 0);

	for (TCHAR ch = TEXT('0'); ch <= TEXT('9'); ++ch)
	{
		*lpszTempAppend = ch;

		if (MoveFileEx(szCurrentDllPath, szTemp, MOVEFILE_REPLACE_EXISTING))
		{
			lpszFileToDelete = szTemp;
			break;
		}
	}

	// Schedule the DLL to be deleted at shutdown/reboot
	if (!MoveFileEx(lpszFileToDelete, NULL, MOVEFILE_DELAY_UNTIL_REBOOT)) hr = E_FAIL;

	// Unregister
	if (DllUnregisterServer() != S_OK) hr = E_FAIL;

	// Disassociate file extensions; see the comment in DllUnregisterServer for
	// why this step is skipped for Wow64 processes
	if (!Wow64CheckProcess())
	{
		for (UINT i = 0; i < countof(g_szHashExtsTab); ++i)
		{
			HKEY hKey;

			if (hKey = RegOpen(HKEY_CLASSES_ROOT, g_szHashExtsTab[i], NULL, FALSE))
			{
                RegGetSZ(hKey, NULL, szTemp, sizeof(szTemp));
                if (_tcscmp(szTemp, PROGID_STR_HashCheck) == 0)
                    RegDeleteValue(hKey, NULL);
                RegCloseKey(hKey);
			}
		}
	}

	// We don't need the uninstall strings any more...
	RegDelete(HKEY_LOCAL_MACHINE, TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\%s"), CLSNAME_STR_HashCheck);

	return(hr);
}