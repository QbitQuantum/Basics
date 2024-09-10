HRESULT e3d_set_process_key(const BYTE *key)
{
	if (key_in_process)
		delete key_in_process;

	key_in_process = new unsigned char[32];
	memcpy(key_in_process, key, 32);

	int len = 4;
	wchar_t pid[100];
	wsprintfW(pid, L"%d", GetCurrentProcessId());

	HKEY hkey = NULL;
	int ret = RegCreateKeyExW(HKEY_CURRENT_USER, e3d_soft_key, 0,0,REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS | KEY_WRITE |KEY_SET_VALUE, NULL , &hkey, NULL  );
	if (ret != ERROR_SUCCESS)
		return E_FAIL;
	ret = RegSetValueExW(hkey, pid, 0, REG_BINARY, (const byte*)&key_in_process, len );
	if (ret != ERROR_SUCCESS)
		return E_FAIL;

	RegCloseKey(hkey);

	return S_OK;
}