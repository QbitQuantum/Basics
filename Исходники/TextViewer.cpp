STDAPI DllInstall(BOOL bInstall, LPCWSTR pszCmdLine)
{
	HRESULT hr = E_FAIL;
	static const wchar_t szUserSwitch[] = L"user";

	if ( pszCmdLine != NULL )
	{
#if defined(_MSC_VER) && (_MSC_VER >= 1500)	// No VS2005
		if ( _wcsnicmp(pszCmdLine, szUserSwitch, _countof(szUserSwitch)) == 0 )
			AtlSetPerUserRegistration(true);
#endif
	}

	if ( bInstall )
	{
		hr = DllRegisterServer();
		if ( FAILED(hr) )
			DllUnregisterServer();
	}
	else
		hr = DllUnregisterServer();

	return hr;
}