STDAPI DllRegisterServer(void)
{   
    char       szID[128];
    WCHAR      wcID[128];
    char       szCLSID[128];
    TCHAR       szModule[MAX_PATH+ 1];
    char * pName = "WMI Sample Prop Provider";
    char * pModel = "Both";
	size_t * intReturnValue = NULL;
    HKEY hKey1, hKey2;

	 // Create the path.

	memset(wcID, NULL, sizeof(wcID));
	memset(szID, NULL, sizeof(szID));	

    StringFromGUID2(CLSID_PropProvider, wcID, sizeof(wcID)/sizeof(WCHAR) - 1);
    wcstombs_s(intReturnValue, szID, sizeof(szID), wcID,  sizeof(szID));
	StringCbCopy(szCLSID, sizeof(szCLSID), "Software\\classes\\CLSID\\");
	StringCbCat(szCLSID, sizeof(szCLSID), (LPCTSTR)szID);


    // Create entries under CLSID

	LONG lRet = RegCreateKeyEx( HKEY_LOCAL_MACHINE, szCLSID, 0, NULL,
                    REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, 
                    &hKey1, NULL );
	if (lRet != ERROR_SUCCESS)
	{
		return E_FAIL;
	}

    lRet = RegSetValueEx(hKey1, NULL, 0, REG_SZ, (BYTE *)pName, strlen(pName)+1);
	if (lRet != ERROR_SUCCESS)
	{
		RegCloseKey(hKey1);
		return E_FAIL;
	}

	lRet = RegCreateKeyEx( hKey1, "InprocServer32", 0, NULL,
                    REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, 
                    &hKey2, NULL );
	if (lRet != ERROR_SUCCESS)
	{
		RegCloseKey(hKey1);
		return E_FAIL;
	}

	memset(&szModule, NULL, sizeof(szModule));
    GetModuleFileName(ghModule, szModule,  sizeof(szModule)/sizeof(TCHAR) - 1);
    lRet = RegSetValueEx(hKey2, NULL, 0, REG_SZ, (BYTE *)szModule, 
                                        strlen(szModule)+1);
	if (lRet != ERROR_SUCCESS)
	{
	    RegCloseKey(hKey2);
		RegCloseKey(hKey1);
		return E_FAIL;
	}
    lRet = RegSetValueEx(hKey2, "ThreadingModel", 0, REG_SZ, 
                                        (BYTE *)pModel, strlen(pModel)+1);
	if (lRet != ERROR_SUCCESS)
	{
	    RegCloseKey(hKey2);
		RegCloseKey(hKey1);
		return E_FAIL;
	}
    RegCloseKey(hKey1);
    RegCloseKey(hKey2);

    return NOERROR;
  
}