static HRESULT GetDesktopShellView(
    __in REFIID riid,
    __out void **ppv
    )
{
    HRESULT hr = S_OK;
    IShellWindows* psw = NULL;
    HWND hwnd = NULL;
    IDispatch* pdisp = NULL;
    VARIANT vEmpty = {}; // VT_EMPTY
    IShellBrowser* psb = NULL;
    IShellFolder* psf = NULL;
    IShellView* psv = NULL;

    // use the shell view for the desktop using the shell windows automation to find the 
    // desktop web browser and then grabs its view
    // returns IShellView, IFolderView and related interfaces
    hr = ::CoCreateInstance(CLSID_ShellWindows, NULL, CLSCTX_LOCAL_SERVER, IID_PPV_ARGS(&psw));
    ExitOnFailure(hr, "Failed to get shell view.");

    hr = psw->FindWindowSW(&vEmpty, &vEmpty, SWC_DESKTOP, (long*)&hwnd, SWFO_NEEDDISPATCH, &pdisp);
    if (S_OK == hr)
    {
        hr = IUnknown_QueryService(pdisp, SID_STopLevelBrowser, IID_PPV_ARGS(&psb));
        ExitOnFailure(hr, "Failed to get desktop window.");

        hr = psb->QueryActiveShellView(&psv);
        ExitOnFailure(hr, "Failed to get active shell view.");

        hr = psv->QueryInterface(riid, ppv);
        ExitOnFailure(hr, "Failed to query for the desktop shell view.");
    }
    else if (S_FALSE == hr)
    {
        //Windows XP
        hr = SHGetDesktopFolder(&psf);
        ExitOnFailure(hr, "Failed to get desktop folder.");

        hr = psf->CreateViewObject(NULL, IID_IShellView, ppv);
        ExitOnFailure(hr, "Failed to query for the desktop shell view.");
    }
    else
    {
        ExitOnFailure(hr, "Failed to get desktop window.");
    }

LExit:
    ReleaseObject(psv);
    ReleaseObject(psb);
    ReleaseObject(psf);
    ReleaseObject(pdisp);
    ReleaseObject(psw);

    return hr;
}