int rtldrNativeLoadSystem(const char *pszFilename, const char *pszExt, uint32_t fFlags, PRTLDRMOD phLdrMod)
{
    /*
     * We only try the System32 directory.
     */
    WCHAR wszSysDir[MAX_PATH];
    UINT cwcSysDir = GetSystemDirectoryW(wszSysDir, MAX_PATH);
    if (cwcSysDir >= MAX_PATH)
        return VERR_FILENAME_TOO_LONG;

    char szPath[RTPATH_MAX];
    char *pszPath = szPath;
    int rc = RTUtf16ToUtf8Ex(wszSysDir, RTSTR_MAX, &pszPath, sizeof(szPath), NULL);
    if (RT_SUCCESS(rc))
    {
        rc = RTPathAppend(szPath, sizeof(szPath), pszFilename);
        if (pszExt && RT_SUCCESS(rc))
            rc = RTStrCat(szPath, sizeof(szPath), pszExt);
        if (RT_SUCCESS(rc))
        {
            if (RTFileExists(szPath))
                rc = RTLdrLoadEx(szPath, phLdrMod, fFlags, NULL);
            else
                rc = VERR_MODULE_NOT_FOUND;
        }
    }

    return rc;
}