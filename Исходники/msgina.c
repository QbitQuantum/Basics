/*
 * @implemented
 */
BOOL WINAPI
WlxActivateUserShell(
	PVOID pWlxContext,
	PWSTR pszDesktopName,
	PWSTR pszMprLogonScript,
	PVOID pEnvironment)
{
	HKEY hKey;
	DWORD BufSize, ValueType;
	WCHAR pszUserInitApp[MAX_PATH + 1];
	WCHAR pszExpUserInitApp[MAX_PATH];
	DWORD len;
	LONG rc;

	TRACE("WlxActivateUserShell()\n");

	UNREFERENCED_PARAMETER(pszMprLogonScript);

	/* Get the path of userinit */
	rc = RegOpenKeyExW(
		HKEY_LOCAL_MACHINE, 
		L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon",
		0,
		KEY_QUERY_VALUE,
		&hKey);
	if (rc != ERROR_SUCCESS)
	{
		WARN("RegOpenKeyExW() failed with error %lu\n", rc);
		return FALSE;
	}

	/* Query userinit application */
	BufSize = sizeof(pszUserInitApp) - sizeof(UNICODE_NULL);
	rc = RegQueryValueExW(
		hKey,
		L"Userinit",
		NULL,
		&ValueType,
		(LPBYTE)pszUserInitApp,
		&BufSize);
	RegCloseKey(hKey);
	if (rc != ERROR_SUCCESS || (ValueType != REG_SZ && ValueType != REG_EXPAND_SZ))
	{
		WARN("RegQueryValueExW() failed with error %lu\n", rc);
		return FALSE;
	}
	pszUserInitApp[MAX_PATH] = UNICODE_NULL;

	len = ExpandEnvironmentStringsW(pszUserInitApp, pszExpUserInitApp, MAX_PATH);
	if (len > MAX_PATH)
	{
		WARN("ExpandEnvironmentStringsW() failed. Required size %lu\n", len);
		return FALSE;
	}

	/* Start userinit app */
	return WlxStartApplication(pWlxContext, pszDesktopName, pEnvironment, pszExpUserInitApp);
}