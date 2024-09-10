//---------------------------------------------------------------------------
// @func    Adds necessary keys to the registry.
//
// @rdesc Returns one of the following
// @flag NOERROR    | Registration succeeded
// @flag E_FAIL     | Something didn't work
//
// @comm
// Special Notes:   This allows us to avoid using a .reg file.
// Here is what was in the SampProv.REG file of yore.
// Note that now we have two CLSID's, one for DEBUG.  Then each one
// can point to a different .DLL.
//
//---------------------------------------------------------------------------
STDAPI DllRegisterServer
    (
    void
    )
{
    HKEY        hk;
    HMODULE     hModule;
    DWORD       dwDisposition;
    LONG        stat;
	CHAR		strFileName[MAX_PATH+1];
    CHAR        strOutBuff[300+1];
	HRESULT		hr = S_OK;

    // Get the full path name for this DLL.
    if (NULL == (hModule = GetModuleHandle( s_strDllName )))
        return ResultFromScode( E_FAIL );
    if (0 == GetModuleFileName( hModule, strFileName, sizeof( strFileName ) / sizeof( char )))
        return ResultFromScode( E_FAIL );

    // Make a clean start
    DllUnregisterServer();

    // Loop through s_rgRegInfo, and put everything in it.
    // Every entry is based on HKEY_CLASSES_ROOT.
    for (ULONG i=0; i < NUMELEM( s_rgRegInfo ); i++)
        {

		// Fill in any "%s" arguments with the name of this DLL.
		if (s_rgRegInfo[i].dwType == REG_DWORD)
			*(DWORD*)strOutBuff = atol( s_rgRegInfo[i].strValue );
		else
			StringCchPrintfA( strOutBuff, sizeof(strOutBuff), s_rgRegInfo[i].strValue, strFileName );

        // Create the Key.  If it exists, we open it.
        // Thus we can still change the value below.
        stat = RegCreateKeyEx(
                HKEY_CLASSES_ROOT,
                s_rgRegInfo[i].strRegKey,
                0,  // dwReserved
                NULL,   // lpszClass
                REG_OPTION_NON_VOLATILE,
                KEY_ALL_ACCESS, // security access mask
                NULL,   // lpSecurityAttributes
                &hk,    // phkResult
                &dwDisposition );
        if (stat != ERROR_SUCCESS)
            return ResultFromScode( E_FAIL );

        stat = RegSetValueEx(
                hk,								// created above
                s_rgRegInfo[i].strValueName,	// lpszValueName
                0,								// dwReserved
                s_rgRegInfo[i].dwType,			// fdwType
				(BYTE *) strOutBuff,			// value
                s_rgRegInfo[i].dwType == REG_SZ ?
                (DWORD)strlen( strOutBuff ) + 1 :		// cbData, including null terminator
				sizeof(DWORD));					
        RegCloseKey( hk );
        if (stat != ERROR_SUCCESS)
            return ResultFromScode( E_FAIL );
        }

	IRegisterProvider*	pIRegisterProvider = NULL;
	//Register with the RootBinder
	if(SUCCEEDED(CoCreateInstance(CLSID_RootBinder, NULL, CLSCTX_ALL, IID_IRegisterProvider, (void**)&pIRegisterProvider)))
	{
		//Register Sampprov's URL prefix with the RootBinder
		hr = pIRegisterProvider->SetURLMapping(SAMPPROV_URL_PREFIX, 0, CLSID_SampProvBinder);
		pIRegisterProvider->Release();
	}

    return ResultFromScode( hr );
}