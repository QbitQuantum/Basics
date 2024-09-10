static bool get_32bit_system_dll_ver(const wchar_t *system_lib,
		struct win_version_info *ver)
{
	wchar_t path[MAX_PATH];
	UINT ret;

#ifdef _WIN64
	ret = GetSystemWow64DirectoryW(path, MAX_PATH);
#else
	ret = GetSystemDirectoryW(path, MAX_PATH);
#endif
	if (!ret) {
		blog(LOG_ERROR, "Failed to get windows 32bit system path: "
		                "%lu", GetLastError());
		return false;
	}

	wcscat(path, L"\\");
	wcscat(path, system_lib);
	return get_dll_ver(path, ver);
}