	BOOL DuiSystem::DllUnregisterServer(LPCTSTR lpszFileName)
	{
		return DllRegisterServer(lpszFileName, TRUE);
	}