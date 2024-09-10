/*************************************************************************
 * SHCoCreateInstance [SHELL32.102]
 *
 * Equivalent to CoCreateInstance. Under Windows 9x this function could sometimes
 * use the shell32 built-in "mini-COM" without the need to load ole32.dll - see
 * SHLoadOLE for details.
 *
 * Under wine if a "LoadWithoutCOM" value is present or the object resides in
 * shell32.dll the function will load the object manually without the help of ole32
 *
 * NOTES
 *     exported by ordinal
 *
 * SEE ALSO
 *     CoCreateInstace, SHLoadOLE
 */
HRESULT WINAPI SHCoCreateInstance(
    LPCWSTR aclsid,
    const CLSID *clsid,
    LPUNKNOWN pUnkOuter,
    REFIID refiid,
    LPVOID *ppv)
{
    DWORD    hres;
    CLSID    iid;
    const    CLSID * myclsid = clsid;
    WCHAR    sKeyName[MAX_PATH];
    const    WCHAR sCLSID[7] = {'C','L','S','I','D','\\','\0'};
    WCHAR    sClassID[60];
    const WCHAR sInProcServer32[16] ={'\\','I','n','p','r','o','c','S','e','r','v','e','r','3','2','\0'};
    const WCHAR sLoadWithoutCOM[15] ={'L','o','a','d','W','i','t','h','o','u','t','C','O','M','\0'};
    WCHAR    sDllPath[MAX_PATH];
    HKEY    hKey;
    DWORD    dwSize;
    BOOLEAN bLoadFromShell32 = FALSE;
    BOOLEAN bLoadWithoutCOM = FALSE;
    CComPtr<IClassFactory>        pcf;

    if(!ppv) return E_POINTER;
    *ppv=NULL;

    /* if the clsid is a string, convert it */
    if (!clsid)
    {
      if (!aclsid) return REGDB_E_CLASSNOTREG;
      CLSIDFromString((LPOLESTR)aclsid, &iid);
      myclsid = &iid;
    }

    TRACE("(%p,%s,unk:%p,%s,%p)\n",
        aclsid, shdebugstr_guid(myclsid), pUnkOuter, shdebugstr_guid(&refiid), ppv);

    /* we look up the dll path in the registry */
        __SHGUIDToStringW(*myclsid, sClassID);
    wcscpy(sKeyName, sCLSID);
    wcscat(sKeyName, sClassID);
    wcscat(sKeyName, sInProcServer32);

    if (ERROR_SUCCESS == RegOpenKeyExW(HKEY_CLASSES_ROOT, sKeyName, 0, KEY_READ, &hKey)) {
        dwSize = sizeof(sDllPath);
        SHQueryValueExW(hKey, NULL, 0,0, sDllPath, &dwSize );

        /* if a special registry key is set, we load a shell extension without help of OLE32 */
        bLoadWithoutCOM = (ERROR_SUCCESS == SHQueryValueExW(hKey, sLoadWithoutCOM, 0, 0, 0, 0));

        /* if the com object is inside shell32, omit use of ole32 */
        bLoadFromShell32 = (0==lstrcmpiW( PathFindFileNameW(sDllPath), sShell32));

        RegCloseKey (hKey);
    } else {
        /* since we can't find it in the registry we try internally */
        bLoadFromShell32 = TRUE;
    }

    TRACE("WithoutCom=%u FromShell=%u\n", bLoadWithoutCOM, bLoadFromShell32);

    /* now we create an instance */
    if (bLoadFromShell32) {
        if (! SUCCEEDED(DllGetClassObject(*myclsid, IID_IClassFactory, (LPVOID*)&pcf))) {
            ERR("LoadFromShell failed for CLSID=%s\n", shdebugstr_guid(myclsid));
        }
    } else if (bLoadWithoutCOM) {

        /* load an external dll without ole32 */
        HINSTANCE hLibrary;
        typedef HRESULT (CALLBACK *DllGetClassObjectFunc)(REFCLSID clsid, REFIID iid, LPVOID *ppv);
        DllGetClassObjectFunc DllGetClassObject;

        if ((hLibrary = LoadLibraryExW(sDllPath, 0, LOAD_WITH_ALTERED_SEARCH_PATH)) == 0) {
            ERR("couldn't load InprocServer32 dll %s\n", debugstr_w(sDllPath));
        hres = E_ACCESSDENIED;
            goto end;
        } else if (!(DllGetClassObject = (DllGetClassObjectFunc)GetProcAddress(hLibrary, "DllGetClassObject"))) {
            ERR("couldn't find function DllGetClassObject in %s\n", debugstr_w(sDllPath));
            FreeLibrary( hLibrary );
        hres = E_ACCESSDENIED;
            goto end;
        } else if (! SUCCEEDED(hres = DllGetClassObject(*myclsid, IID_IClassFactory, (LPVOID*)&pcf))) {
            TRACE("GetClassObject failed 0x%08x\n", hres);
            goto end;
        }

    } else {

        /* load an external dll in the usual way */
        hres = CoCreateInstance(*myclsid, pUnkOuter, CLSCTX_INPROC_SERVER, refiid, ppv);
        goto end;
    }

    /* here we should have a ClassFactory */
    if (!pcf) return E_ACCESSDENIED;

    hres = pcf->CreateInstance(pUnkOuter, refiid, ppv);
end:
    if(hres!=S_OK)
    {
      ERR("failed (0x%08x) to create CLSID:%s IID:%s\n",
              hres, shdebugstr_guid(myclsid), shdebugstr_guid(&refiid));
      ERR("class not found in registry\n");
    }

    TRACE("-- instance: %p\n",*ppv);
    return hres;
}