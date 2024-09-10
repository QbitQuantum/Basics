// deprecated - remove once a registry-free version of Safari has shipped (first major version after 3.1.1)
static void registerWebKitNightly()
{
    // look up server's file name
    TCHAR szFileName[MAX_PATH];
    GetModuleFileName(gInstance, szFileName, MAX_PATH);

    typedef HRESULT (WINAPI *RegisterTypeLibForUserPtr)(ITypeLib*, OLECHAR*, OLECHAR*);
    COMPtr<ITypeLib> typeLib;
    LoadTypeLibEx(szFileName, REGKIND_NONE, &typeLib);
    if (RegisterTypeLibForUserPtr registerTypeLibForUser = reinterpret_cast<RegisterTypeLibForUserPtr>(GetProcAddress(GetModuleHandle(TEXT("oleaut32.dll")), "RegisterTypeLibForUser")))
        registerTypeLibForUser(typeLib.get(), szFileName, 0);
    else
        RegisterTypeLib(typeLib.get(), szFileName, 0);

    HKEY userClasses;
    if (RegOpenKeyEx(HKEY_CURRENT_USER, TEXT("SOFTWARE\\CLASSES"), 0, KEY_WRITE, &userClasses) != ERROR_SUCCESS)
        userClasses = 0;

    // register entries from table
    int nEntries = ARRAYSIZE(gRegTable);
    HRESULT hr = S_OK;
    for (int i = 0; SUCCEEDED(hr) && i < nEntries; i++) {
        LPTSTR pszKeyName   = _tcsdup(gRegTable[i][0]);
        LPTSTR pszValueName = gRegTable[i][1] ? _tcsdup(gRegTable[i][1]) : 0;
        LPTSTR allocatedValue   = (gRegTable[i][2] != (LPTSTR)-1) ? _tcsdup(gRegTable[i][2]) : (LPTSTR)-1;
        LPTSTR pszValue     = allocatedValue;

        if (pszKeyName && pszValue) {

            int clsidIndex = i/gSlotsPerEntry;
            substituteGUID(pszKeyName, &gRegCLSIDs[clsidIndex]);
            substituteGUID(pszValueName, &gRegCLSIDs[clsidIndex]);

            // map rogue value to module file name
            if (pszValue == (LPTSTR)-1)
                pszValue = szFileName;
            else
                substituteGUID(pszValue, &gRegCLSIDs[clsidIndex]);

            // create the key
            HKEY hkey;
            LONG err = RegCreateKey(HKEY_CLASSES_ROOT, pszKeyName, &hkey);
            if (err != ERROR_SUCCESS && userClasses)
                err = RegCreateKey(userClasses, pszKeyName, &hkey);
            if (err == ERROR_SUCCESS) {
                // set the value
                err = RegSetValueEx(hkey, pszValueName, 0, REG_SZ, (const BYTE*)pszValue, (DWORD) sizeof(pszValue[0])*(_tcslen(pszValue) + 1));
                RegCloseKey(hkey);
            }
        }
        if (pszKeyName)
            free(pszKeyName);
        if (pszValueName)
            free(pszValueName);
        if (allocatedValue && allocatedValue != (LPTSTR)-1)
            free(allocatedValue);
    }

    if (userClasses)
        RegCloseKey(userClasses);
}