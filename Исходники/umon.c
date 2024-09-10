/***********************************************************************
 *           URLDownloadToCacheFileW (URLMON.@)
 */
HRESULT WINAPI URLDownloadToCacheFileW(LPUNKNOWN lpUnkCaller, LPCWSTR szURL, LPWSTR szFileName,
                DWORD dwBufLength, DWORD dwReserved, LPBINDSTATUSCALLBACK pBSC)
{
    WCHAR cache_path[MAX_PATH + 1];
    FILETIME expire, modified;
    HRESULT hr;
    LPWSTR ext;

    static WCHAR header[] = {
        'H','T','T','P','/','1','.','0',' ','2','0','0',' ',
        'O','K','\\','r','\\','n','\\','r','\\','n',0
    };

    TRACE("(%p, %s, %p, %d, %d, %p)\n", lpUnkCaller, debugstr_w(szURL),
          szFileName, dwBufLength, dwReserved, pBSC);

    if (!szURL || !szFileName)
        return E_INVALIDARG;

    ext = PathFindExtensionW(szURL);

    if (!CreateUrlCacheEntryW(szURL, 0, ext, cache_path, 0))
        return E_FAIL;

    hr = URLDownloadToFileW(lpUnkCaller, szURL, cache_path, 0, pBSC);
    if (FAILED(hr))
        return hr;

    expire.dwHighDateTime = 0;
    expire.dwLowDateTime = 0;
    modified.dwHighDateTime = 0;
    modified.dwLowDateTime = 0;

    if (!CommitUrlCacheEntryW(szURL, cache_path, expire, modified, NORMAL_CACHE_ENTRY,
                              header, sizeof(header), NULL, NULL))
        return E_FAIL;

    if (strlenW(cache_path) > dwBufLength)
        return E_OUTOFMEMORY;

    lstrcpyW(szFileName, cache_path);

    return S_OK;
}