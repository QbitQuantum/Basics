bool SetRegistryString(const char *szSubKey,
                       const char *szValueName,
                       const char *szValue)
{

	long qerr;
	HKEY ckey;
	DWORD disposition;

	// Open the key
	if ((qerr=RegCreateKeyExW(HKEY_CURRENT_USER,
	                         GetWideChar(szSubKey),
	                         0,
	                         L"",
	                         REG_OPTION_NON_VOLATILE,
	                         KEY_ALL_ACCESS,
	                         NULL,
	                         &ckey,
	                         &disposition
	                        ))!=ERROR_SUCCESS) return false;

	// Set the value
	StdBuf v = GetWideCharBuf(szValue);
	if ((qerr=RegSetValueExW(ckey,
	                        GetWideChar(szValueName),
	                        0,
	                        REG_SZ,
	                        getBufPtr<BYTE>(v),
	                        v.getSize()
	                       ))!=ERROR_SUCCESS) { RegCloseKey(ckey); return false; }

	// Close the key
	RegCloseKey(ckey);

	return true;
}