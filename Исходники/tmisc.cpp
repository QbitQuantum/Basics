BOOL TMakeVirtualStorePathW(WCHAR *org_path, WCHAR *buf)
{
	if (!IsWinVista()) return FALSE;

	if (!TIsVirtualizedDirW(org_path)
	|| !SHGetSpecialFolderPathW(NULL, buf, CSIDL_LOCAL_APPDATA, FALSE)
	||	org_path[1] != ':' || org_path[2] != '\\') {
		wcscpy(buf, org_path);
		return	FALSE;
	}

	swprintf(buf + wcslen(buf), L"\\VirtualStore%s", org_path + 2);
	return	TRUE;
}