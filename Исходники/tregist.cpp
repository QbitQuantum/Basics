BOOL TRegistry::GetLongW(const WCHAR *subKey, long *val)
{
	DWORD	type = REG_DWORD, dw_size = sizeof(long);

	if (::RegQueryValueExW(hKey[openCnt -1], subKey, 0, &type, (BYTE *)val, &dw_size)
			== ERROR_SUCCESS) {
		return	TRUE;
	}
// 昔の互換性用
	WCHAR	wbuf[100];
	long	size_byte = sizeof(wbuf);

	if (::RegQueryValueW(hKey[openCnt -1], subKey, wbuf, &size_byte) != ERROR_SUCCESS)
		return	FALSE;
	*val = wcstol(wbuf, 0, 10);
	return	TRUE;
}