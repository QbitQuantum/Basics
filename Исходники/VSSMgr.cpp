BOOL CVSSMgr::GetDefaultDatabase(LPWSTR FilePathBuf,IN OUT PULONG BufLen)
{
	BOOL	bRet = FALSE;
	HKEY	hKey;
	DWORD	dwType;
	DWORD   dwValue = (*BufLen) * sizeof(WCHAR);

	LONG hr = RegOpenKeyExW(HKEY_LOCAL_MACHINE,
						L"SOFTWARE\\Microsoft\\SourceSafe",
						0,
						KEY_READ,
						&hKey);
	if(SUCCEEDED(hr))
	{
		hr = RegQueryValueExW(hKey,L"Current Database",0,&dwType,(LPBYTE)FilePathBuf,&dwValue);
		if(SUCCEEDED(hr))
		{
			*BufLen = dwValue/sizeof(WCHAR);
			bRet = TRUE;
		}
		RegCloseKey(hKey);
	}
	return bRet;
}