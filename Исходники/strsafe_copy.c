HRESULT StringCbCopyExW(
        LPWSTR pszDest,
        size_t cbDest,
        LPCWSTR pszSrc,
        LPWSTR * ppszDestEnd,
        size_t * pcbRemaining,
        DWORD dwFlags){
    return StringCbCopyNExW(pszDest, cbDest, pszSrc, cbDest,
            ppszDestEnd, pcbRemaining, dwFlags);
}