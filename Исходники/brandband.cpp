HRESULT STDMETHODCALLTYPE CBrandBand::SetSite(IUnknown* pUnkSite)
{
    CComPtr<IBrowserService>                browserService;
    CComPtr<IOleWindow>                     oleWindow;
    CComPtr<IServiceProvider>               serviceProvider;
    CComPtr<IProfferService>                profferService;
    HWND                                    parentWindow;
    HWND                                    hwnd;
    HRESULT                                 hResult;

    fSite.Release();
    if (pUnkSite == NULL)
    {
        hResult = AtlUnadvise(fSite, DIID_DWebBrowserEvents, fAdviseCookie);
        // TODO: revoke brand band service
        return S_OK;
    }

    // get window handle of parent
    hResult = pUnkSite->QueryInterface(IID_PPV_ARG(IDockingWindowSite, &fSite));
    if (FAILED_UNEXPECTEDLY(hResult))
        return hResult;
    parentWindow = NULL;
    hResult = pUnkSite->QueryInterface(IID_PPV_ARG(IOleWindow, &oleWindow));
    if (SUCCEEDED(hResult))
        hResult = oleWindow->GetWindow(&parentWindow);
    if (!::IsWindow(parentWindow))
        return E_FAIL;

    // create worker window in parent window
    hwnd = SHCreateWorkerWindowW(0, parentWindow, 0,
        WS_VISIBLE | WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, NULL, 0);
    if (hwnd == NULL)
        return E_FAIL;
    SubclassWindow(hwnd);

    // take advice to watch events
    hResult = pUnkSite->QueryInterface(IID_PPV_ARG(IServiceProvider, &serviceProvider));
    if (SUCCEEDED(hResult))
    {
        hResult = serviceProvider->QueryService(
            SID_SBrandBand, IID_PPV_ARG(IProfferService, &profferService));
        if (SUCCEEDED(hResult))
            hResult = profferService->ProfferService(SID_SBrandBand,
                static_cast<IServiceProvider *>(this), &fProfferCookie);
        hResult = serviceProvider->QueryService(SID_SShellBrowser,
            IID_PPV_ARG(IBrowserService, &browserService));
        if (SUCCEEDED(hResult))
            hResult = AtlAdvise(browserService, static_cast<IDispatch *>(this), DIID_DWebBrowserEvents, &fAdviseCookie);
    }

    // ignore any hResult errors up to here - they are nonfatal
    hResult = S_OK;
    SelectImage();
    return hResult;
}