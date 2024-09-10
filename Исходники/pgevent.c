HRESULT
DllInstall(BOOL bInstall,
		   LPCWSTR pszCmdLine)
{

	if (pszCmdLine && *pszCmdLine != '\0')
		wcstombs(event_source, pszCmdLine, sizeof(event_source));

	/*
	 * This is an ugly hack due to the strange behavior of "regsvr32 /i".
	 *
	 * When installing, regsvr32 calls DllRegisterServer before DllInstall.
	 * When uninstalling (i.e. "regsvr32 /u /i"), on the other hand, regsvr32
	 * calls DllInstall and then DllUnregisterServer as expected.
	 *
	 * This strange behavior forces us to specify -n (i.e. "regsvr32 /n /i").
	 * Without -n, DllRegisterServer called before DllInstall would mistakenly
	 * overwrite the default "PostgreSQL" event source registration.
	 */
	if (bInstall)
		DllRegisterServer();
	return S_OK;
}