HRESULT StringCbPrintfExW(
    LPWSTR pszDest,
    size_t cbDest,
    LPWSTR * ppszDestEnd,
    size_t * pcbRemaining,
    DWORD dwFlags,
    LPCWSTR pszFormat,
    ...) {
    va_list argList;
    HRESULT result;

    va_start(argList, pszFormat);
    result = StringCbVPrintfExW(pszDest, cbDest, ppszDestEnd,
                                pcbRemaining, dwFlags, pszFormat, argList);
    va_end(argList);

    return result;
}