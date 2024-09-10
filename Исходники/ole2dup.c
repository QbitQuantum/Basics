STDAPI SHCoCreateInstance(LPCTSTR pszCLSID, const CLSID * pclsid,
                LPUNKNOWN pUnkOuter, REFIID riid, LPVOID FAR* ppv)
{
    HRESULT hres = ResultFromScode(REGDB_E_CLASSNOTREG);
    CLSID clsidT;
    TCHAR szClass[GUIDSTR_MAX+ARRAYSIZE(c_szInProcServer)];

    if (pclsid)
    {
        if (!pszCLSID)
        {
            StringFromGUID2A(pclsid, szClass, ARRAYSIZE(szClass));
        }
    }
    else
    {
        if (pszCLSID)
        {
            lstrcpy(szClass,pszCLSID);
            if (SUCCEEDED(SHCLSIDFromString(pszCLSID, &clsidT)))
                pclsid=&clsidT;
        }
    }


    if (pclsid)
    {
        LONG err;
        HKEY hkeyDll;
        IClassFactory *pCF;

        Assert(hres == ResultFromScode(REGDB_E_CLASSNOTREG));

        lstrcat(szClass,c_szInProcServer);  // Add "\InProcServer32"

        hres = _FindRegisteredClass(pclsid, &pCF);
        if (SUCCEEDED(hres))
        {
            hres = pCF->lpVtbl->CreateInstance(pCF, pUnkOuter, riid, ppv);
            pCF->lpVtbl->Release(pCF);
        }
        else
        {
            if (g_hkcrCLSID && RegOpenKey(g_hkcrCLSID, szClass, &hkeyDll) == ERROR_SUCCESS)
            {
                TCHAR szDllName[MAX_PATH];
                LONG cbValue = SIZEOF(szDllName);

                //            1         2         3
                //  012345678901234567890123456789012345678  = nul is at 38!
                // "{12345678-1234-1234-1234-123456789012}"
                //
                szClass[38] = TEXT('\0');   // Get rid of "\InProcServer32"

                err = RegQueryValue(hkeyDll, NULL, szDllName, &cbValue);

#ifdef WINNT
                //
                // On NT, we must check to ensure that this CLSID exists in
                // the list of approved CLSIDs that can be used in-process.
                // If not, we fail the creation with ERROR_ACCESS_DENIED.
                // We explicitly allow anything serviced by this DLL
                //

                if (err == ERROR_SUCCESS && NULL != g_hklmApprovedExt)
                {
                    TCHAR szBuf[MAX_PATH];

                    //
                    // Check to see if we are using this DLL
                    //
                    // BUGBUG Assumes no parameters in InProcServer32.  We
                    // should remove this assumption once we lose shellalt,
                    // after which we can just lstrcpyn(,,<length of dll name>);

                    LPCTSTR pszDllName = PathFindFileName(szDllName);

                    if (lstrcmp(pszDllName, TEXT("shell32.dll")) &&
                        lstrcmp(pszDllName, TEXT("shellalt.dll")))
                    {
                        DWORD dwType;
                        TCHAR szValue[MAX_PATH];
                        DWORD cbSize = SIZEOF(szValue);

                        if (ERROR_SUCCESS != RegQueryValueEx(g_hklmApprovedExt,
                                                             szClass,
                                                             0,
                                                             &dwType,
                                                             (LPBYTE) szValue,
                                                             &cbSize))
                        {
                            hres = HRESULT_FROM_WIN32(ERROR_ACCESS_DENIED);
                            return hres;
                        }
                    }
                }
#endif

                if (err == ERROR_SUCCESS)
                {
                    TCHAR szThreadingModel[MAX_PATH];
                    BOOL fMultiThreadAware = FALSE;
                    DWORD dwRegType;
                    DWORD cbRead = SIZEOF(szThreadingModel);

                    err = RegQueryValueEx(hkeyDll, c_szThreadingModel, NULL,
                            &dwRegType, (LPBYTE)szThreadingModel, &cbRead);
                    if (err == ERROR_SUCCESS && dwRegType == REG_SZ)
                    {
                        if (lstrcmpi(szThreadingModel, c_szApartment)==0
                            || lstrcmpi(szThreadingModel, c_szBoth)==0)
                        {
                            fMultiThreadAware = TRUE;
                        }
                    }

// #define HACK_APARTMENT_ONLY_ASSERT
#ifdef HACK_APARTMENT_ONLY_ASSERT
                    if (!fMultiThreadAware)
                    {
                        _asm {
                            int 3;
                        }
                    }
                    Assert(fMultiThreadAware);
                    hres = _CreateInstance(pclsid, szDllName, pUnkOuter, riid, ppv);
#else
                    if (fMultiThreadAware)
                    {
                        hres = _CreateInstance(pclsid, szDllName, pUnkOuter, riid, ppv);
                    }
                    else
                    {
                        Assert(hres == ResultFromScode(REGDB_E_CLASSNOTREG));
                        DebugMsg(DM_ERROR, TEXT("sh TR - SHCoCreateInstance !!! InProcServer32 (%s) does not support multi-threading"), szDllName);
                        Assert(0);
                    }
#endif

                }

                RegCloseKey(hkeyDll);
            }