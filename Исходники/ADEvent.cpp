STDAPI DllRegisterServer(void)
{
    int      i;
    HKEY     hKey;
    LRESULT  lResult;
    DWORD    dwDisp;
    TCHAR    szSubKey[MAX_PATH];
    TCHAR    szCLSID[MAX_PATH];
    TCHAR    szModule[MAX_PATH];
    LPWSTR   pwsz;

    //get the CLSID in string form
    StringFromIID(CLSID_AdminEventHandler, &pwsz);

    if(pwsz)
    {
        WideCharToLocal(szCLSID, ARRAYSIZE(szCLSID), pwsz, ARRAYSIZE(szCLSID));

        //free the string
        LPMALLOC pMalloc;
        CoGetMalloc(1, &pMalloc);
        if(pMalloc)
        {
            pMalloc->Free(pwsz);
            pMalloc->Release();
        }
    }

    //get this DLL's path and file name
    GetModuleFileName(g_hInst, szModule, ARRAYSIZE(szModule));

    //register the CLSID entries
    REGSTRUCT ClsidEntries[] = {HKEY_CLASSES_ROOT,   TEXT("CLSID\\%s"),                                   NULL,                   g_szMainTitle,
                                HKEY_CLASSES_ROOT,   TEXT("CLSID\\%s\\InprocServer32"),                   NULL,                   TEXT("%s"),
                                HKEY_CLASSES_ROOT,   TEXT("CLSID\\%s\\InprocServer32"),                   TEXT("ThreadingModel"), TEXT("Apartment"),
                                NULL,                NULL,                                                NULL,                   NULL};

    for(i = 0; ClsidEntries[i].hRootKey; i++)
    {
        //Create the sub key string.
        _stprintf_s(szSubKey, ARRAYSIZE(szSubKey), ClsidEntries[i].lpszSubKey, szCLSID);

        lResult = RegCreateKeyEx(   ClsidEntries[i].hRootKey,
                                    szSubKey,
                                    0,
                                    NULL,
                                    REG_OPTION_NON_VOLATILE,
                                    KEY_WRITE,
                                    NULL,
                                    &hKey,
                                    &dwDisp);
           
        if(NOERROR == lResult)
        {
            TCHAR szData[MAX_PATH] = TEXT("");

            //if necessary, create the value string
            _stprintf_s(szData, ARRAYSIZE(szData), ClsidEntries[i].lpszData, szModule);

            lResult = RegSetValueEx(    hKey,
                                        ClsidEntries[i].lpszValueName,
                                        0,
                                        REG_SZ,
                                        (LPBYTE)szData,
                                        lstrlen(szData) + 1);

            RegCloseKey(hKey);
        }
        else
        {
            return SELFREG_E_CLASS;
        }
    }

    return S_OK;
}