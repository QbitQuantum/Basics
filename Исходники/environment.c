BOOL
WINAPI
ExpandEnvironmentStringsForUserA(IN HANDLE hToken,
                                 IN LPCSTR lpSrc,
                                 OUT LPSTR lpDest,
                                 IN DWORD dwSize)
{
    BOOL Ret = FALSE;
    DWORD dwSrcLen;
    LPWSTR lpSrcW = NULL, lpDestW = NULL;

    if (lpSrc == NULL || lpDest == NULL || dwSize == 0)
    {
        SetLastError(ERROR_INVALID_PARAMETER);
        return FALSE;
    }

    dwSrcLen = strlen(lpSrc);
    lpSrcW = (LPWSTR)GlobalAlloc(GMEM_FIXED,
                                 (dwSrcLen + 1) * sizeof(WCHAR));
    if (lpSrcW == NULL ||
        MultiByteToWideChar(CP_ACP,
                            0,
                            lpSrc,
                            -1,
                            lpSrcW,
                            dwSrcLen + 1) == 0)
    {
        goto Cleanup;
    }

    lpDestW = (LPWSTR)GlobalAlloc(GMEM_FIXED,
                                  dwSize * sizeof(WCHAR));
    if (lpDestW == NULL)
        goto Cleanup;

    Ret = ExpandEnvironmentStringsForUserW(hToken,
                                           lpSrcW,
                                           lpDestW,
                                           dwSize);
    if (Ret)
    {
        if (WideCharToMultiByte(CP_ACP,
                                0,
                                lpDestW,
                                -1,
                                lpDest,
                                dwSize,
                                NULL,
                                NULL) == 0)
        {
            Ret = FALSE;
        }
    }

Cleanup:
    if (lpSrcW != NULL)
        GlobalFree((HGLOBAL)lpSrcW);

    if (lpDestW != NULL)
        GlobalFree((HGLOBAL)lpDestW);

    return Ret;
}