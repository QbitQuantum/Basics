void CDlgFileAssoc::ExtAssignDyn(LPWSTR extName, LPWSTR extCmd, int iconIndex) {

	HKEY hKey;
	DWORD len = 100;
	wchar_t buf[100];

	wchar_t szKeyUpr[20];
	wchar_t szKeyName[20];
	wchar_t szKeyDesc[50];
	wchar_t szKeyStr[50];

	wcscpy(szKeyUpr, extName);
	wcsupr(szKeyUpr);

	wsprintf(szKeyName, L".%s", extName);
	wsprintf(szKeyStr, L"%s file", szKeyUpr);
	wsprintf(szKeyDesc, L"Nitrogen%sFile", szKeyUpr);

	RegCreateKeyExW(HKEY_CLASSES_ROOT, szKeyName, 0, NULL, REG_OPTION_NON_VOLATILE, 0, NULL, &hKey, NULL);

	if (RegQueryValueExW(hKey, NULL, NULL, NULL, (BYTE*)buf, &len) == ERROR_SUCCESS) {
		if (len > 0) {
			RegSetValueExW(hKey, L"Nitrogen backup", 0, REG_SZ, (BYTE*)buf, len);
		}
	}
	
	RegSetValueExW(hKey, NULL, 0, REG_SZ, (BYTE*)szKeyDesc, wcslen(szKeyDesc)*2+2);

	wchar_t oldSettings[100];
	oldSettings[0] = 0;
	len = 100;

	if (RegQueryValueExW(hKey, L"Nitrogen backup", NULL, NULL, (BYTE*)buf, &len) == ERROR_SUCCESS) {
		wcscpy(oldSettings, buf);
	}

	RegCloseKey(hKey);

	RegCreateKeyExW(HKEY_CLASSES_ROOT, szKeyDesc, 0, NULL, REG_OPTION_NON_VOLATILE, 0, NULL, &hKey, NULL);
	RegSetValueExW(hKey, NULL, 0, REG_SZ, (BYTE*)szKeyStr, wcslen(szKeyStr)*2+2);
	RegCloseKey(hKey);

	wchar_t sIco[100];
	wsprintf(sIco, L"%s\\DefaultIcon", szKeyDesc);
	RegCreateKeyExW(HKEY_CLASSES_ROOT, sIco, 0, NULL, REG_OPTION_NON_VOLATILE, 0, NULL, &hKey, NULL);
	wchar_t s[MAX_PATH];
	wsprintf(s, L"%sNitrogen.exe,%i", player()->Path, iconIndex);
	RegSetValueExW(hKey, NULL, 0, REG_SZ, (BYTE*)s, wcslen(s)*2+2);
	RegCloseKey(hKey);

	wchar_t sCmd[100];
	wsprintf(sCmd, L"%s\\Shell\\Open\\Command", szKeyDesc);
	RegCreateKeyExW(HKEY_CLASSES_ROOT, sCmd, 0, NULL, REG_OPTION_NON_VOLATILE, 0, NULL, &hKey, NULL);
	wsprintf(s, L"\"%sNitrogen.exe\" %s", player()->Path, extCmd);
	RegSetValueExW(hKey, NULL, 0, REG_SZ, (BYTE*)s, wcslen(s)*2+2);
	RegCloseKey(hKey);

	if (oldSettings[0] != 0) {
		HKEY hKeyIn;
		wchar_t PathShellExIn[MAX_PATH];
		wsprintf(PathShellExIn, L"%s\\ShellEx", oldSettings);
		if (RegOpenKeyExW(HKEY_CLASSES_ROOT, PathShellExIn, 0, 0, &hKeyIn) == ERROR_SUCCESS) {
			wchar_t PathShellExOut[MAX_PATH];
			wsprintf(PathShellExOut, L"%s\\ShellEx", szKeyDesc);
			HKEY hKeyOut;
			if (RegCreateKeyExW(HKEY_CLASSES_ROOT, PathShellExOut, 0, NULL, REG_OPTION_NON_VOLATILE, 0, NULL, &hKeyOut, NULL) == ERROR_SUCCESS) {
				RegCopyData(hKeyIn, hKeyOut);
				RegCloseKey(hKeyOut);
			}
			RegCloseKey(hKeyIn);
		}
	}
}