static gchar *get_7z_path_entry(HKEY root_hkey, LPWSTR name)
{
	HKEY hkey;
	DWORD size, type;
	LPWSTR wpath;
	gchar *path;

	debug_print("get_7z_path_entry: read %s/Software/7-Zip/%ls\n", root_hkey == HKEY_CURRENT_USER ? "HKCU" : "HKLM", name);

	if (RegOpenKeyExW(root_hkey, L"Software\\7-Zip", 0, KEY_READ, &hkey) != ERROR_SUCCESS) {
		return NULL;
	}

	if (RegQueryValueExW(hkey, name, 0, &type, 0, &size) != ERROR_SUCCESS) {
		RegCloseKey(hkey);
		return NULL;
	}
	if (type != REG_SZ) {
		RegCloseKey(hkey);
		return NULL;
	}
	++size;
	wpath = g_malloc(size);
	if (RegQueryValueExW(hkey, name, 0, &type, (LPBYTE)wpath, &size) != ERROR_SUCCESS) {
		RegCloseKey(hkey);
		return NULL;
	}
	RegCloseKey(hkey);

	path = g_utf16_to_utf8(wpath, -1, NULL, NULL, NULL);
	g_free(wpath);

	debug_print("get_7z_path_entry: %s\n", path);

	return path;
}