HRESULT SetAppID(LPCTSTR appID)
{
	HRESULT hRes = S_FALSE;
	typedef HRESULT STDAPICALLTYPE SetCurrentProcessExplicitAppUserModelIDFN(PCWSTR AppID);
	CAutoLibrary hShell = AtlLoadSystemLibraryUsingFullPath(_T("shell32.dll"));
	if (hShell)
	{
		SetCurrentProcessExplicitAppUserModelIDFN *pfnSetCurrentProcessExplicitAppUserModelID = (SetCurrentProcessExplicitAppUserModelIDFN*)GetProcAddress(hShell, "SetCurrentProcessExplicitAppUserModelID");
		if (pfnSetCurrentProcessExplicitAppUserModelID)
			hRes = pfnSetCurrentProcessExplicitAppUserModelID(appID);
	}
	return hRes;
}