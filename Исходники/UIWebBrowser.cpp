void CWebBrowserUI::Navigate2( LPCTSTR lpszUrl )
{
    if (lpszUrl == NULL)
        return;

    if (m_pWebBrowser2)
    {
        CVariant url;
        url.vt=VT_BSTR;
        url.bstrVal=T2BSTR(lpszUrl);
        HRESULT hr = m_pWebBrowser2->Navigate2(&url, NULL, NULL, NULL, NULL);
    }
}