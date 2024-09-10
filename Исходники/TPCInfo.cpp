/////////////////////////////////////////////////////////
//
// GetComponentInfo
//
//        This helper function, provided with a component
//        ProgId, gathers the component's name and version
//        info and formats them into output strings
//
// Parameters:
//        CLSID  clsid  : [in] component's CLSID
//        SInfo& info   : [in, out] a structure of buffers
//                        to get the formatted strings into
//
// Return Values:
//        TRUE, if the function succeeds
//        FALSE, if it fails
//
/////////////////////////////////////////////////////////
BOOL GetComponentInfo(CLSID clsid, SInfo& info)
{
    info.wchName[0] = info.wchVersion[0] = 0;

    // Format Registry Key string
    WCHAR wszKey[45] = L"CLSID\\";  // the key buffer should be large enough for a string
                                    // like "CLSID\{xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx}"
    // Convert CLSID to String
    UINT uPos = lstrlenW(wszKey);
    if (0 == StringFromGUID2(clsid, &wszKey[uPos], countof(wszKey) - uPos))
        return FALSE;
    wszKey[countof(wszKey)-1] = 0;

    // Open key to find path of application
    HKEY hKeyRoot;
    if (RegOpenKeyExW(HKEY_CLASSES_ROOT, wszKey, 0, KEY_READ, &hKeyRoot) != ERROR_SUCCESS)
        return FALSE;

    // Query value of key to get the name of the component
    ULONG cSize = sizeof(info.wchName);  // size of the buffer in bytes
    if (RegQueryValueExW(hKeyRoot, NULL, NULL, NULL, (BYTE*)info.wchName, &cSize) != ERROR_SUCCESS)
    {
        RegCloseKey(hKeyRoot);
        return FALSE;
    }
    info.wchName[countof(info.wchName) - 1] = 0;

    // Open the version info subkey
    UINT iVersionMaxLen = countof(info.wchVersion);
    HKEY hKey = NULL;
    if (RegOpenKeyExW(hKeyRoot, L"Version", 0, KEY_READ, &hKey) == ERROR_SUCCESS)
    {
        const WCHAR* pcwsVersion = L"version ";
        UINT iLen = lstrlenW(pcwsVersion);
        // Query value of key to get version string
        if (iLen < iVersionMaxLen)
        {
            // copy the "version " string including terminating 0
            wcsncpy_s(info.wchVersion, iVersionMaxLen, pcwsVersion, iLen + 1);

            // get the version string
            cSize = (iVersionMaxLen - iLen) * sizeof(WCHAR); // the size is in bytes
            if (RegQueryValueExW(hKey, NULL, NULL, NULL,
                                 (BYTE*)&info.wchVersion[iLen],
                                 &cSize) == ERROR_SUCCESS)
            {
                info.wchVersion[iVersionMaxLen-1] = 0;
            }
        }
        RegCloseKey(hKey);
    }

    // Open InprocServer32 subkey to get the path to the component
    if (RegOpenKeyExW(hKeyRoot, L"InprocServer32", 0, KEY_READ, &hKey) == ERROR_SUCCESS)
    {
        // Query value of key to get the path string
        WCHAR wchPath[MAX_PATH];
        cSize = sizeof(wchPath);
        if (RegQueryValueExW(hKey, NULL, NULL, NULL, (BYTE*)wchPath, &cSize) == ERROR_SUCCESS)
        {
            // Get the build number from the file version info
            DWORD dwHandle = 0;
            cSize = GetFileVersionInfoSizeW(wchPath, &dwHandle); // returns the size in bytes
            WCHAR* pwchFileVerInfo = NULL;
            if (cSize)
            {
                pwchFileVerInfo = (WCHAR*)new BYTE[cSize];
            }
            if (NULL != pwchFileVerInfo)
            {
                // Retrieve version information for the file
                if (GetFileVersionInfoW(wchPath, 0, cSize, pwchFileVerInfo))
                {
                    // Get the default language id and code page number
                    UINT *pdwLang;
                    UINT cch = 0;
                    if (VerQueryValueW(pwchFileVerInfo, L"\\VarFileInfo\\Translation",
                                       (void**)&pdwLang, &cch) == TRUE)
                    {
                        // Read the file description for the language and code page.
                        const int MAX_SUBBLOCK = 40;
                        WCHAR wchSubBlock[MAX_SUBBLOCK];  // large enough for the string
                        StringCchPrintfExW(wchSubBlock,
                                          MAX_SUBBLOCK,
                                          NULL,
                                          NULL,
                                          STRSAFE_NULL_ON_FAILURE,
                                          L"\\StringFileInfo\\%04x%04x\\FileVersion",
                                          LOWORD(*pdwLang), HIWORD(*pdwLang));

                        WCHAR* pwchBuildVer = NULL;
                        if ((VerQueryValueW(pwchFileVerInfo, wchSubBlock,
                                            (void**)&pwchBuildVer, &cch) == TRUE)
                            && (NULL != pwchBuildVer))
                        {
                            // Format the version string
                            UINT iLen = (UINT)lstrlenW(info.wchVersion);
                            if (0 < iLen)
                            {
                                if (iLen < iVersionMaxLen)
                                {
                                    const WCHAR* pcwsBuild = L", build ";
                                    wcsncpy_s(info.wchVersion + iLen, iVersionMaxLen - iLen, pcwsBuild, iVersionMaxLen - iLen);
                                    iLen += lstrlenW(pcwsBuild);
                                    if (iLen < iVersionMaxLen)
                                    {
                                        wcsncpy_s(info.wchVersion + iLen, iVersionMaxLen - iLen, pwchBuildVer, iVersionMaxLen - iLen);
                                    }
                                }
                            }
                            else
                            {
                                wcsncpy_s(info.wchVersion, iVersionMaxLen, pwchBuildVer, iVersionMaxLen);
                            }
                            info.wchVersion[iVersionMaxLen-1] = 0;
                        }
                    }
                }
                delete [] pwchFileVerInfo;
            }

        }
        RegCloseKey(hKey);
    }

    RegCloseKey(hKeyRoot);

    return TRUE;
}