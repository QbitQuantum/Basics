int DoGetSpecialFolder(int CSIDL, PCHAR dest, int dest_len)
{
	OSVERSIONINFO osvi;
	char Path[MAX_PATH] = "";
	LPITEMIDLIST pidl;

	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&osvi);
	if ( (osvi.dwPlatformId == VER_PLATFORM_WIN32_NT && osvi.dwMajorVersion == 4) ||
	     (osvi.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) ) {
		switch (CSIDL) {
			case CSIDL_COMMON_DESKTOPDIRECTORY:
			case CSIDL_COMMON_STARTMENU:
			case CSIDL_COMMON_PROGRAMS:
			case CSIDL_COMMON_STARTUP:
				return 0;
		}
	}

	if (SHGetSpecialFolderLocation(NULL, CSIDL, &pidl) != S_OK) {
		return 0;
	}

	SHGetPathFromIDList(pidl, Path);
	CoTaskMemFree(pidl);

	strncpy_s(dest, dest_len, Path, _TRUNCATE);
	return 1;
}