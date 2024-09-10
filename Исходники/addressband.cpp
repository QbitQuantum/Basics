HRESULT STDMETHODCALLTYPE CAddressBand::SetSite(IUnknown *pUnkSite)
{
    CComPtr<IShellService>                  shellService;
    HWND                                    parentWindow;
    HWND                                    combobox;
    HRESULT                                 hResult;
    IImageList                              *piml;

    if (pUnkSite == NULL)
    {
        fSite.Release();
        return S_OK;
    }

    fSite.Release();

    hResult = pUnkSite->QueryInterface(IID_PPV_ARG(IDockingWindowSite, &fSite));
    if (FAILED_UNEXPECTEDLY(hResult))
        return hResult;

    // get window handle of parent
    parentWindow = NULL;
    hResult = IUnknown_GetWindow(fSite, &parentWindow);

    if (!::IsWindow(parentWindow))
        return E_FAIL;

    // create combo box ex
    combobox = CreateWindowEx(WS_EX_TOOLWINDOW, WC_COMBOBOXEXW, NULL, WS_CHILD | WS_VISIBLE |
        WS_CLIPCHILDREN | WS_TABSTOP | CCS_NODIVIDER | CCS_NOMOVEY | CBS_OWNERDRAWFIXED,
                    0, 0, 500, 250, parentWindow, (HMENU)IDM_TOOLBARS_ADDRESSBAR, _AtlBaseModule.GetModuleInstance(), 0);
    if (combobox == NULL)
        return E_FAIL;
    SubclassWindow(combobox);

    HRESULT hr = SHGetImageList(SHIL_SMALL, IID_PPV_ARG(IImageList, &piml));
    if (FAILED_UNEXPECTEDLY(hr))
    {
        SendMessageW(combobox, CBEM_SETIMAGELIST, 0, 0);
    }
    else
    {
        SendMessageW(combobox, CBEM_SETIMAGELIST, 0, reinterpret_cast<LPARAM>(piml));
    }

    SendMessage(CBEM_SETEXTENDEDSTYLE,
        CBES_EX_CASESENSITIVE | CBES_EX_NOSIZELIMIT, CBES_EX_CASESENSITIVE | CBES_EX_NOSIZELIMIT);

    fEditControl = reinterpret_cast<HWND>(SendMessage(CBEM_GETEDITCONTROL, 0, 0));
    fComboBox = reinterpret_cast<HWND>(SendMessage(CBEM_GETCOMBOCONTROL, 0, 0));
    hResult = CAddressEditBox_CreateInstance(IID_PPV_ARG(IAddressEditBox, &fAddressEditBox));
    if (FAILED_UNEXPECTEDLY(hResult))
        return hResult;

    hResult = fAddressEditBox->QueryInterface(IID_PPV_ARG(IShellService, &shellService));
    if (FAILED_UNEXPECTEDLY(hResult))
        return hResult;
    hResult = fAddressEditBox->Init(combobox, fEditControl, 8, fSite /*(IAddressBand *)this*/);
    if (FAILED_UNEXPECTEDLY(hResult))
        return hResult;
    hResult = shellService->SetOwner(fSite);
    if (FAILED_UNEXPECTEDLY(hResult))
        return hResult;

    fGoButtonShown = SHRegGetBoolUSValueW(L"Software\\Microsoft\\Internet Explorer\\Main", L"ShowGoButton", FALSE, TRUE);
    if (fGoButtonShown)
        CreateGoButton();

    return hResult;
}