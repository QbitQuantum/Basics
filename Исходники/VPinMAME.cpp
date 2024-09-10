BOOL IsSingleThreadedApartment()
{
	HRESULT hr;

	CLSID ClsID;
	hr = CLSIDFromProgID(OLESTR("VPinMAME.Controller"), &ClsID);
	if ( FAILED(hr) )
		return FALSE;

	OLECHAR sClsID[256];
	StringFromGUID2(ClsID, (LPOLESTR) sClsID, 256);

	char szClsID[256];
	WideCharToMultiByte(CP_ACP, 0, (LPOLESTR) sClsID, -1, szClsID, sizeof szClsID, NULL, NULL);

	char szRegKey[256];
	lstrcpy(szRegKey, "CLSID\\");
	lstrcat(szRegKey, szClsID);
	lstrcat(szRegKey, "\\InprocServer32");

	HKEY hKey;
	if ( RegOpenKey(HKEY_CLASSES_ROOT, szRegKey, &hKey)!=ERROR_SUCCESS )
		return FALSE;

	char szThreadingModel[MAX_PATH];
	ULONG uSize = sizeof szThreadingModel;
	DWORD dwType = REG_SZ;
	if ( RegQueryValueEx(hKey, "ThreadingModel", NULL, &dwType, (LPBYTE) &szThreadingModel, &uSize)!=ERROR_SUCCESS ) {
		RegCloseKey(hKey);

		// if we don't have that entry, return TRUE (old style, but single threaded)
		return TRUE;
	}
	RegCloseKey(hKey);

	// if we don't have that entry, return TRUE (old style, but single threaded)
	if ( !szThreadingModel[0] )
		return TRUE;

	return _stricmp(szThreadingModel, "Apartment")?FALSE:TRUE;
}