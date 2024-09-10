/*--------------------------------------------------------------------------*/
wchar_t *getCpuVendor(void)
{
	wchar_t *CpuManufacturer = NULL;
	HKEY key;
	DWORD result;
	ULONG length = LenMaxLine;
	ULONG Type = 0;

	result = RegOpenKeyExW(HKEY_LOCAL_MACHINE, KeyCentralProcessor, 0, KEY_QUERY_VALUE , &key);
	if (result == ERROR_SUCCESS)
	{
		wchar_t LineResult[LenMaxLine];

		if ( RegQueryValueExW(key, KeyVendorIdentifier,
								0, &Type, (LPBYTE)LineResult, &length) ==  ERROR_SUCCESS )
		{
			if( Type == REG_SZ )
			{
				CpuManufacturer = _wcsdup(LineResult);
			}
		}
		RegCloseKey(key);
	}
	return CpuManufacturer;
}