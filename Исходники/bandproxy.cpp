HRESULT STDMETHODCALLTYPE CBandProxy::NavigateToPIDL(LPCITEMIDLIST pidl)
{
    CComPtr<IOleWindow>                     oleWindow;
    CComPtr<IServiceProvider>               serviceProvider;
    CComPtr<IUnknown>                       webBrowserUnknown;
    CComPtr<IWebBrowser2>                   webBrowser;
    HWND                                    browserWindow;
    CComVariant                             args;
    CComVariant                             emptyVariant;
    unsigned int                            arraySize;
    HRESULT                                 hResult;

    hResult = FindBrowserWindow(&webBrowserUnknown);
    if (FAILED_UNEXPECTEDLY(hResult))
        return hResult;
    hResult = webBrowserUnknown->QueryInterface(IID_PPV_ARG(IWebBrowser2, &webBrowser));
    if (FAILED_UNEXPECTEDLY(hResult))
        return hResult;
    hResult = webBrowser->put_Visible(TRUE);
    hResult = webBrowser->QueryInterface(IID_PPV_ARG(IServiceProvider, &serviceProvider));
    if (SUCCEEDED(hResult))
    {
        hResult = serviceProvider->QueryService(SID_STopLevelBrowser,
            IID_PPV_ARG(IOleWindow, &oleWindow));
        if (SUCCEEDED(hResult))
        {
            hResult = oleWindow->GetWindow(&browserWindow);
            if (IsIconic(browserWindow))
                ShowWindow(browserWindow, SW_RESTORE);
        }
    }
    arraySize = ILGetSize(pidl);
    V_VT(&args) = VT_ARRAY | VT_UI1;
    V_ARRAY(&args) = SafeArrayCreateVector(VT_UI1, 0, arraySize);
    if (V_ARRAY(&args) == NULL)
        return E_OUTOFMEMORY;
    memcpy(V_ARRAY(&args)->pvData, pidl, arraySize);
    hResult = webBrowser->Navigate2(&args, &emptyVariant, &emptyVariant, &emptyVariant, &emptyVariant);
    if (FAILED_UNEXPECTEDLY(hResult))
        return hResult;
    return S_OK;
}