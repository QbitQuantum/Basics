BOOL COXHistoryCombo::SaveContentsToRegistry(HKEY hKeyRoot, LPCTSTR pszCompany, 
											 LPCTSTR pszApplication,
											 LPCTSTR pszValueName, LPCTSTR pszValue)
{
	ASSERT(hKeyRoot != NULL);
	ASSERT((pszCompany != NULL) && (*pszCompany != _T('\0')));
	ASSERT((pszApplication != NULL) && (*pszApplication != _T('\0')));
	ASSERT((pszValueName != NULL) && (*pszValueName != _T('\0')));
	// ... Value may be empty string
	ASSERT((pszValue != NULL));

	// Open key for hKeyRoot\<szSoftware>\<pszCompany>\<pszApplication>\<szHistoryCombo>
	HKEY hSoftwareKey = NULL;
	HKEY hCompanyKey = NULL;
	HKEY hApplicationKey = NULL;
	HKEY hHistoryKey = NULL;
	if (::RegOpenKeyEx(hKeyRoot, szSoftware, 0, KEY_WRITE | KEY_READ,
		&hSoftwareKey) == ERROR_SUCCESS)
	{
		DWORD dw;
		if (::RegCreateKeyEx(hSoftwareKey, pszCompany, 0, REG_NONE,
			REG_OPTION_NON_VOLATILE, KEY_WRITE | KEY_READ, NULL,
			&hCompanyKey, &dw) == ERROR_SUCCESS)
		{
			if (::RegCreateKeyEx(hCompanyKey, pszApplication, 0, REG_NONE,
				REG_OPTION_NON_VOLATILE, KEY_WRITE | KEY_READ, NULL,
				&hApplicationKey, &dw) == ERROR_SUCCESS)
			{
				::RegCreateKeyEx(hApplicationKey, szHistoryCombo, 0, REG_NONE,
					REG_OPTION_NON_VOLATILE, KEY_WRITE | KEY_READ, NULL,
					&hHistoryKey, &dw);
			}
		}
	}
	if (hSoftwareKey != NULL)
		::RegCloseKey(hSoftwareKey);
	if (hCompanyKey != NULL)
		::RegCloseKey(hCompanyKey);
	if (hApplicationKey != NULL)
		::RegCloseKey(hApplicationKey);

	if (hHistoryKey == NULL)
	{
		TRACE0("COXHistoryCombo::SaveContentsToRegistry : Failed to open history key\n");
		return FALSE;
	}

	// Set value
	LONG nResult;
	if (*pszValue == _T('\0'))
		// ... Necessary to cast away const 
		nResult = ::RegDeleteValue(hHistoryKey, (LPTSTR)pszValueName);
	else
		nResult = RegSetValueEx(hHistoryKey, pszValueName, NULL, REG_SZ,
			(LPBYTE)pszValue, PtrToLong((_tcslen(pszValue) + 1) * sizeof(TCHAR)));
	::RegCloseKey(hHistoryKey);

#ifdef _DEBUG
	if (nResult != ERROR_SUCCESS)
		TRACE0("COXHistoryCombo::SaveContentsToRegistry : Failed to set value\n");
#endif // _DEBUG

	return (nResult == ERROR_SUCCESS);
}