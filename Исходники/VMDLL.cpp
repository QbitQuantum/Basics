HRESULT CDolphinVMModule::RegisterAsEventSource() const
{
	static TCHAR* szKeyStem = _T("SYSTEM\\CurrentControlSet\\Services\\EventLog\\Application\\");
	HRESULT hr;

	TCHAR szKey[512];
	_tcscpy(szKey, szKeyStem);
	_tcscat(szKey, _T("Dolphin"));

	CRegKey rkeyEvSrc;
	// Register as an event source with message table in this DLL
	LONG ret = rkeyEvSrc.Create(HKEY_LOCAL_MACHINE, szKey);
	if (ret == ERROR_SUCCESS)
	{
		TCHAR szModule[_MAX_PATH];
		::GetModuleFileName(_AtlBaseModule.GetModuleInstance(), szModule, _MAX_PATH);
		rkeyEvSrc.SetStringValue(_T("EventMessageFile"), szModule);
		rkeyEvSrc.SetDWORDValue(_T("TypesSupported"), 7);
		hr = S_OK;
	}
	else
		hr = AtlHresultFromWin32(ret);

	return hr;
}