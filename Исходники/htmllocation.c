static HRESULT WINAPI HTMLLocation_get_href(IHTMLLocation *iface, BSTR *p)
{
    HTMLLocation *This = impl_from_IHTMLLocation(iface);
    URL_COMPONENTSW url = {sizeof(URL_COMPONENTSW)};
    WCHAR *buf = NULL, *url_path = NULL;
    HRESULT hres, ret;
    DWORD len = 0;
    int i;

    TRACE("(%p)->(%p)\n", This, p);

    if(!p)
        return E_POINTER;

    url.dwSchemeLength = 1;
    url.dwHostNameLength = 1;
    url.dwUrlPathLength = 1;
    url.dwExtraInfoLength = 1;
    hres = get_url_components(This, &url);
    if(FAILED(hres))
        return hres;

    switch(url.nScheme) {
    case INTERNET_SCHEME_FILE:
        {
            /* prepend a slash */
            url_path = HeapAlloc(GetProcessHeap(), 0, (url.dwUrlPathLength + 1) * sizeof(WCHAR));
            if(!url_path)
                return E_OUTOFMEMORY;
            url_path[0] = '/';
            memcpy(url_path + 1, url.lpszUrlPath, url.dwUrlPathLength * sizeof(WCHAR));
            url.lpszUrlPath = url_path;
            url.dwUrlPathLength = url.dwUrlPathLength + 1;
        }
        break;

    case INTERNET_SCHEME_HTTP:
    case INTERNET_SCHEME_HTTPS:
    case INTERNET_SCHEME_FTP:
        if(!url.dwUrlPathLength) {
            /* add a slash if it's blank */
            url_path = url.lpszUrlPath = HeapAlloc(GetProcessHeap(), 0, 1 * sizeof(WCHAR));
            if(!url.lpszUrlPath)
                return E_OUTOFMEMORY;
            url.lpszUrlPath[0] = '/';
            url.dwUrlPathLength = 1;
        }
        break;

    default:
        break;
    }

    /* replace \ with / */
    for(i = 0; i < url.dwUrlPathLength; ++i)
        if(url.lpszUrlPath[i] == '\\')
            url.lpszUrlPath[i] = '/';

    if(InternetCreateUrlW(&url, ICU_ESCAPE, NULL, &len)) {
        FIXME("InternetCreateUrl succeeded with NULL buffer?\n");
        ret = E_FAIL;
        goto cleanup;
    }

    if(GetLastError() != ERROR_INSUFFICIENT_BUFFER) {
        FIXME("InternetCreateUrl failed with error: %08x\n", GetLastError());
        SetLastError(0);
        ret = E_FAIL;
        goto cleanup;
    }
    SetLastError(0);

    buf = HeapAlloc(GetProcessHeap(), 0, len * sizeof(WCHAR));
    if(!buf) {
        ret = E_OUTOFMEMORY;
        goto cleanup;
    }

    if(!InternetCreateUrlW(&url, ICU_ESCAPE, buf, &len)) {
        FIXME("InternetCreateUrl failed with error: %08x\n", GetLastError());
        SetLastError(0);
        ret = E_FAIL;
        goto cleanup;
    }

    *p = SysAllocStringLen(buf, len);
    if(!*p) {
        ret = E_OUTOFMEMORY;
        goto cleanup;
    }

    ret = S_OK;

cleanup:
    HeapFree(GetProcessHeap(), 0, buf);
    HeapFree(GetProcessHeap(), 0, url_path);

    return ret;
}