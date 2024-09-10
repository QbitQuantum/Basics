/********************************************************************
 *      CoInternetGetSecurityUrl (URLMON.@)
 */
HRESULT WINAPI CoInternetGetSecurityUrl(LPCWSTR pwzUrl, LPWSTR *ppwzSecUrl, PSUACTION psuAction, DWORD dwReserved)
{
    WCHAR *secure_url;
    HRESULT hres;

    TRACE("(%p,%p,%u,%u)\n", pwzUrl, ppwzSecUrl, psuAction, dwReserved);

    hres = parse_security_url(pwzUrl, psuAction, &secure_url);
    if(FAILED(hres))
        return hres;

    if(psuAction != PSU_SECURITY_URL_ONLY) {
        PARSEDURLW parsed_url = { sizeof(parsed_url) };
        DWORD size;

        /* FIXME: Use helpers from uri.c */
        if(SUCCEEDED(ParseURLW(secure_url, &parsed_url))) {
            WCHAR *new_url;

            switch(parsed_url.nScheme) {
            case URL_SCHEME_FTP:
            case URL_SCHEME_HTTP:
            case URL_SCHEME_HTTPS:
                size = strlenW(secure_url)+1;
                new_url = CoTaskMemAlloc(size * sizeof(WCHAR));
                if(new_url)
                    hres = UrlGetPartW(secure_url, new_url, &size, URL_PART_HOSTNAME, URL_PARTFLAG_KEEPSCHEME);
                else
                    hres = E_OUTOFMEMORY;
                CoTaskMemFree(secure_url);
                if(hres != S_OK) {
                    WARN("UrlGetPart failed: %08x\n", hres);
                    CoTaskMemFree(new_url);
                    return FAILED(hres) ? hres : E_FAIL;
                }
                secure_url = new_url;
            }
        }
    }

    *ppwzSecUrl = secure_url;
    return S_OK;
}