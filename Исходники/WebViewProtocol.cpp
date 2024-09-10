HRESULT WebViewProtocol::ParseWebViewUrl(const wchar_t *url, LONG_PTR *webViewId, wchar_t **path)
{
    *webViewId = 0;
    *path = NULL;

    // Parse out the numeric web view ID
    swscanf_s(url, L"webview://%d/", webViewId);

    if (*webViewId != 0)
    {
        // Find the // authority section marker. If the string ends with //, authDelim
        // points to the null terminator
        wchar_t *authDelim = wcsstr(const_cast<wchar_t*>(url), L"//") + 1;

        if (authDelim != NULL)
        {
            // Find the first slash after the authority section.  If the string ends with /,
            /// path points to the null terminator
            *path = wcschr(authDelim + wcslen(L"//"), '/') + 1;
        }
    }

    return S_OK;
}