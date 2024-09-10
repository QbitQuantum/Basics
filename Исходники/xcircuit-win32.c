int look_paths()
{
	HKEY hKey;
	DWORD bufLen = 1024 * sizeof(wchar_t);
	wchar_t buf[1100];
	int i;

	if (RegOpenKeyW(HKEY_LOCAL_MACHINE, L"Software\\Microsoft\\Windows\\CurrentVersion\\App Paths\\xcircuit-dev-win32.exe", &hKey))
		return -1;
	if (RegQueryValueExW(
				hKey,
				L"WishExe",
				NULL,
				NULL,
				(LPBYTE)wish_exe,
				&bufLen)) {
		RegCloseKey(hKey);
		return -1;
	}
	bufLen = 1024 * sizeof(wchar_t);
	if (RegQueryValueExW(
				hKey,
				L"LibPath",
				NULL,
				NULL,
				(LPBYTE)lib_path,
				&bufLen)) {
		RegCloseKey(hKey);
		return -1;
	}
	for (i=0; lib_path[i] != 0; i++)
		if (lib_path[i] == L'\\')
			lib_path[i] = L'/';
	_snwprintf(buf, 1100, L"XCIRCUIT_LIB_DIR=%ws", lib_path);
	_wputenv(buf);
	RegCloseKey(hKey);
	return 0;
}