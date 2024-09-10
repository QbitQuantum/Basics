HRESULT RemoveCOMRegistryEntries()
{
	HKEY hRootKey;
	if ( !RegOpenKeyExA(HKEY_CLASSES_ROOT, "miranda.shlext", 0, KEY_READ, &hRootKey)) {
		// need to delete the subkey before the parent key is deleted under NT/2000/XP
		RegDeleteKeyA(hRootKey, "CLSID");
		// close the key
		RegCloseKey(hRootKey);
		// delete it
		if ( RegDeleteKeyA(HKEY_CLASSES_ROOT, "miranda.shlext") != ERROR_SUCCESS)
			MessageBoxA(0,
				"Unable to delete registry key for 'shlext COM', this key may already be deleted or you may need admin rights.",
				"Problem", MB_ICONERROR);
	}
	if ( !RegOpenKeyExA(HKEY_CLASSES_ROOT, "\\*\\shellex\\ContextMenuHandlers", 0, KEY_ALL_ACCESS, &hRootKey)) {
		if ( RegDeleteKeyA(hRootKey, "miranda.shlext") != ERROR_SUCCESS)
			MessageBoxA(0,
				"Unable to delete registry key for 'File context menu handlers', this key may already be deleted or you may need admin rights.",
				"Problem", MB_ICONERROR);
		RegCloseKey(hRootKey);
	}
	if ( !RegOpenKeyExA(HKEY_CLASSES_ROOT, "Directory\\shellex\\ContextMenuHandlers", 0, KEY_ALL_ACCESS, &hRootKey)) {
		if ( RegDeleteKeyA(hRootKey, "miranda.shlext") != ERROR_SUCCESS)
			MessageBoxA(0,
				"Unable to delete registry key for 'Directory context menu handlers', this key may already be deleted or you may need admin rights.",
				"Problem", MB_ICONERROR);
		RegCloseKey(hRootKey);
	}
	if ( !RegOpenKeyExA(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Shell Extensions\\Approved", 0, KEY_ALL_ACCESS, &hRootKey)) {
		if ( RegDeleteValueA(hRootKey, "{72013A26-A94C-11d6-8540-A5E62932711D}") != ERROR_SUCCESS) {
			MessageBoxA(0,
				"Unable to delete registry entry for 'Approved context menu handlers', this key may already be deleted or you may need admin rights.",
				"Problem", MB_ICONERROR);
		}
		RegCloseKey(hRootKey);
	}
	return S_OK;
}