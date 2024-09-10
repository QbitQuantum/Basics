/**
 * Get the real (no symlinks, no . or .. components) path, must exist.
 *
 * @returns iprt status code.
 * @param   pszPath         The path to resolve.
 * @param   pszRealPath     Where to store the real path.
 * @param   cchRealPath     Size of the buffer.
 */
RTDECL(int) RTPathReal(const char *pszPath, char *pszRealPath, size_t cchRealPath)
{
    /*
     * Convert to UTF-16, call Win32 APIs, convert back.
     */
    PRTUTF16 pwszPath;
    int rc = RTStrToUtf16(pszPath, &pwszPath);
    if (!RT_SUCCESS(rc))
        return (rc);

    LPWSTR lpFile;
    WCHAR  wsz[RTPATH_MAX];
    rc = GetFullPathNameW((LPCWSTR)pwszPath, RT_ELEMENTS(wsz), &wsz[0], &lpFile);
    if (rc > 0 && rc < RT_ELEMENTS(wsz))
    {
        /* Check that it exists. (Use RTPathAbs() to just resolve the name.) */
        DWORD dwAttr = GetFileAttributesW(wsz);
        if (dwAttr != INVALID_FILE_ATTRIBUTES)
            rc = RTUtf16ToUtf8Ex((PRTUTF16)&wsz[0], RTSTR_MAX, &pszRealPath, cchRealPath, NULL);
        else
            rc = RTErrConvertFromWin32(GetLastError());
    }
    else if (rc <= 0)
        rc = RTErrConvertFromWin32(GetLastError());
    else
        rc = VERR_FILENAME_TOO_LONG;

    RTUtf16Free(pwszPath);

    return rc;
}