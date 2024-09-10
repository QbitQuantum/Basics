/******************************************************************************
 * HCR_GetFolderAttributes [Internal]
 *
 * Query the registry for a shell folders' attributes
 *
 * PARAMS
 *  pidlFolder    [I]  A simple pidl of type PT_GUID. 
 *  pdwAttributes [IO] In: Attributes to be queried, OUT: Resulting attributes.
 *
 * RETURNS
 *  TRUE:  Found information for the attributes in the registry
 *  FALSE: No attribute information found
 *
 * NOTES
 *  If queried for an attribute, which is set in the CallForAttributes registry
 *  value, the function binds to the shellfolder objects and queries it.
 */
BOOL HCR_GetFolderAttributes(LPCITEMIDLIST pidlFolder, LPDWORD pdwAttributes)
{
    HKEY hSFKey;
    LPOLESTR pwszCLSID;
    LONG lResult;
    DWORD dwTemp, dwLen;
    static const WCHAR wszAttributes[] = { 'A','t','t','r','i','b','u','t','e','s',0 };
    static const WCHAR wszCallForAttributes[] = { 
        'C','a','l','l','F','o','r','A','t','t','r','i','b','u','t','e','s',0 };
    WCHAR wszShellFolderKey[] = { 'C','L','S','I','D','\\','{','0','0','0','2','1','4','0','0','-',
        '0','0','0','0','-','0','0','0','0','-','C','0','0','0','-','0','0','0','0','0','0','0',
        '0','0','0','4','6','}','\\','S','h','e','l','l','F','o','l','d','e','r',0 };

    TRACE("(pidlFolder=%p, pdwAttributes=%p)\n", pidlFolder, pdwAttributes);
       
    if (!_ILIsPidlSimple(pidlFolder)) { 
        static BOOL firstHit = TRUE;
        if (firstHit) {
            ERR("should be called for simple PIDL's only!\n");
            firstHit = FALSE;
        }
        return FALSE;
    }
    
    if (!_ILIsDesktop(pidlFolder)) {
        if (FAILED(StringFromCLSID(_ILGetGUIDPointer(pidlFolder), &pwszCLSID))) return FALSE;
        memcpy(&wszShellFolderKey[6], pwszCLSID, 38 * sizeof(WCHAR));
        CoTaskMemFree(pwszCLSID);
    }
    
    lResult = RegOpenKeyExW(HKEY_CLASSES_ROOT, wszShellFolderKey, 0, KEY_READ, &hSFKey);
#ifdef __REACTOS__
    if (lResult != ERROR_SUCCESS)
    {
        ERR("Cannot open key: %ls\n", wszShellFolderKey);
        return FALSE;
    }
#else
    if (lResult != ERROR_SUCCESS) return FALSE;
#endif
    
    dwLen = sizeof(DWORD);
    lResult = RegQueryValueExW(hSFKey, wszCallForAttributes, 0, NULL, (LPBYTE)&dwTemp, &dwLen);
    if ((lResult == ERROR_SUCCESS) && (dwTemp & *pdwAttributes)) {
        LPSHELLFOLDER psfDesktop, psfFolder;
        HRESULT hr;

        RegCloseKey(hSFKey);
        hr = SHGetDesktopFolder(&psfDesktop);
        if (SUCCEEDED(hr)) {
            hr = IShellFolder_BindToObject(psfDesktop, pidlFolder, NULL, &IID_IShellFolder, 
                                           (LPVOID*)&psfFolder);
            if (SUCCEEDED(hr)) { 
                hr = IShellFolder_GetAttributesOf(psfFolder, 0, NULL, pdwAttributes);
                IShellFolder_Release(psfFolder);
            }
            IShellFolder_Release(psfDesktop);
        }
        if (FAILED(hr)) return FALSE;
    } else {
        lResult = RegQueryValueExW(hSFKey, wszAttributes, 0, NULL, (LPBYTE)&dwTemp, &dwLen);
        RegCloseKey(hSFKey);
        if (lResult == ERROR_SUCCESS) {
            *pdwAttributes &= dwTemp;
        } else {
            return FALSE;
        }
    }

    TRACE("-- *pdwAttributes == 0x%08x\n", *pdwAttributes);

    return TRUE;
}