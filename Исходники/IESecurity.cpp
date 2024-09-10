void DumpIID(REFIID iid, LPCTSTR pszClassName)
{
	USES_CONVERSION;
	CRegKey key;
	TCHAR szName[100];
	DWORD dwType;
	DWORD dw = sizeof(szName);

	LPOLESTR pszGUID = NULL;
	if (FAILED(StringFromCLSID(iid, &pszGUID)))
		return;

	OutputDebugString(pszClassName);
	OutputDebugString(_T(" - "));

	bool bFound = false;
	// Attempt to find it in the interfaces section
	if (key.Open(HKEY_CLASSES_ROOT, _T("Interface"), KEY_READ) == ERROR_SUCCESS)
	{
		if (key.Open(key, OLE2T(pszGUID), KEY_READ) == ERROR_SUCCESS)
		{
			*szName = 0;
			if (RegQueryValueEx(key.m_hKey, (LPTSTR)NULL, NULL, &dwType, (LPBYTE)szName, &dw) == ERROR_SUCCESS)
			{
				OutputDebugString(szName);
				bFound = true;
			}
		}
	}
	// Attempt to find it in the clsid section
	else if (key.Open(HKEY_CLASSES_ROOT, _T("CLSID"), KEY_READ) == ERROR_SUCCESS)
	{
		if (key.Open(key, OLE2T(pszGUID), KEY_READ) == ERROR_SUCCESS)
		{
			*szName = 0;
			if (RegQueryValueEx(key.m_hKey, (LPTSTR)NULL, NULL, &dwType, (LPBYTE)szName, &dw) == ERROR_SUCCESS)
			{
				OutputDebugString(_T("(CLSID\?\?\?) "));
				OutputDebugString(szName);
				bFound = true;
			}
		}
	}
	
	if (!bFound)
		OutputDebugString(OLE2T(pszGUID));
	OutputDebugString(_T("\n"));
	CoTaskMemFree(pszGUID);
}