static int ReadRegistry(HKEY hroot,
						char * p1, char * p2, char * p3,
						char dest[1024])
{
	HKEY h1, h2;
	DWORD dwType;
	unsigned long size;
	LONG ret;

	if (RegOpenKeyExA(hroot, p1, 0, KEY_QUERY_VALUE, &h1) != ERROR_SUCCESS)
		return 0;
	if (RegOpenKeyExA(h1, p2, 0, KEY_QUERY_VALUE, &h2) != ERROR_SUCCESS) {
		RegCloseKey(h1);
		return 0;
	}
	dwType = REG_SZ;
	size = 1024;
	ret = RegQueryValueExA(h2, p3, 0, &dwType, dest, &size);
	RegCloseKey(h2);
	RegCloseKey(h1);
	return ret == ERROR_SUCCESS;
}