HRESULT STDMETHODCALLTYPE CAddressEditBox::SetOwner(IUnknown *pOwner)
{
    if (!pOwner)
    {
        CComPtr<IBrowserService> browserService;
        HRESULT hResult = IUnknown_QueryService(fSite, SID_SShellBrowser, IID_PPV_ARG(IBrowserService, &browserService));
        if (SUCCEEDED(hResult))
            AtlUnadvise(browserService, DIID_DWebBrowserEvents, fAdviseCookie);
        fSite = NULL; 
    }
    // connect to browser connection point
    return 0;
}