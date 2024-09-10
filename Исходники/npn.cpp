static NPError
_OpenURL(NPP npp, const char *szURL, const char *szTarget, void *pNotifyData, const char *pData, uint32 len, NPBool isFile)
{
    if (!npp)
    {
        return NPERR_INVALID_INSTANCE_ERROR;
    }

    void *postData = NULL;
    uint32 postDataLen = 0;
    if (pData)
    {
        if (!isFile)
        {
            postData = (void *) pData;
            postDataLen = len;
        }
        else
        {
            // TODO read the file specified in the postdata param into memory
        }
    }

    nsPluginHostWnd *pWnd = (nsPluginHostWnd *) npp->ndata;
    ATLASSERT(pWnd);

    // Other window targets
    if (szTarget)
    {
        CComPtr<IWebBrowserApp> cpBrowser;
        pWnd->GetWebBrowserApp(&cpBrowser);
        if (!cpBrowser)
        {
            return NPERR_GENERIC_ERROR;
        }

        CComBSTR url(szURL);
        
        HRESULT hr;

        // Test if the input URL has a schema which means it's relative,
        // otherwise consider it to be relative to the current URL

        WCHAR szSchema[10];
        const DWORD cbSchema = sizeof(szSchema) / sizeof(szSchema[0]);
        DWORD cbSchemaUsed = 0;

        memset(szSchema, 0, cbSchema);
        hr = CoInternetParseUrl(url.m_str, PARSE_SCHEMA, 0,
            szSchema, cbSchema, &cbSchemaUsed, 0);

        if (hr != S_OK || cbSchemaUsed == 0)
        {
            // Convert relative URLs to absolute, so that they can be loaded
            // by the Browser

            CComBSTR bstrCurrentURL;
            cpBrowser->get_LocationURL(&bstrCurrentURL);
        
            if (bstrCurrentURL.Length())
            {
                USES_CONVERSION;
                DWORD cbNewURL = (url.Length() + bstrCurrentURL.Length() + 1) * sizeof(WCHAR);
                DWORD cbNewURLUsed = 0;
                WCHAR *pszNewURL = (WCHAR *) calloc(cbNewURL, 1);
                ATLASSERT(pszNewURL);

                CoInternetCombineUrl(
                    bstrCurrentURL.m_str,
                    url.m_str,
                    0,
                    pszNewURL,
                    cbNewURL,
                    &cbNewURLUsed,
                    0);

                ATLASSERT(cbNewURLUsed < cbNewURL);

                url = pszNewURL;
                free(pszNewURL);
            }
        }

        CComVariant vFlags;
        CComVariant vTarget(szTarget);
        CComVariant vPostData;
        CComVariant vHeaders;

        // Initialise postdata
        if (postData)
        {
            // According to the documentation.
            // The post data specified by PostData is passed as a SAFEARRAY
            // structure. The variant should be of type VT_ARRAY and point to
            // a SAFEARRAY. The SAFEARRAY should be of element type VT_UI1,
            // dimension one, and have an element count equal to the number of
            // bytes of post data.

            SAFEARRAYBOUND saBound[1];
            saBound[0].lLbound = 0;
            saBound[0].cElements = len;
            vPostData.vt = VT_ARRAY | VT_UI1;
            vPostData.parray = SafeArrayCreate(VT_UI1, 1, saBound);
            SafeArrayLock(vPostData.parray);
            memcpy(vPostData.parray->pvData, postData, postDataLen);
            SafeArrayUnlock(vPostData.parray);
        }

        cpBrowser->Navigate(url, &vFlags, &vTarget, &vPostData, &vHeaders);
        // TODO listen to navigation & send a URL notify to plugin when completed
        return NPERR_NO_ERROR;
    }

    USES_CONVERSION;
    HRESULT hr = pWnd->OpenURLStream(A2CT(szURL), pNotifyData, postData, postDataLen);
    return SUCCEEDED(hr) ? NPERR_NO_ERROR : NPERR_GENERIC_ERROR;
}