/*----------------------------------------------------------------------------------------------
	Adds/Removes entries to the system registry per user per machine
----------------------------------------------------------------------------------------------*/
STDAPI DLLEXPORT__ DllInstall(BOOL fInstall, LPCWSTR pszCmdLine)
{
	ENTER_DLL();
	HRESULT hr = E_FAIL;
#if WIN32 // TODO-Linux
	static const wchar_t szUserSwitch[] = _T("user");

	if (pszCmdLine != NULL)
	{
		if (_wcsnicmp(pszCmdLine, szUserSwitch, _countof(szUserSwitch)) == 0)
		{
			ModuleEntry::SetPerUserRegistration(true);
		}
	}

	if (fInstall)
	{
		hr = DllRegisterServer();
		if (FAILED(hr))
		{
			DllUnregisterServer();
		}
	}
	else
	{
		hr = DllUnregisterServer();
	}
#endif // WIN32
	return hr;
}