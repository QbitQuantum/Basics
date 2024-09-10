/**
 * Saves a rendering of the current site by its host container as a PNG file.
 * This implementation is derived from IECapt.
 *
 * @param outputFile  the file to save the PNG output as
 * @link http://iecapt.sourceforge.net/
 */
STDMETHODIMP CCoSnapsie::saveSnapshot(
    BSTR outputFile,
    BSTR frameId,
    LONG drawableScrollWidth,
    LONG drawableScrollHeight,
    LONG drawableClientWidth,
    LONG drawableClientHeight,
    LONG drawableClientLeft,
    LONG drawableClientTop,
    LONG frameBCRLeft,
    LONG frameBCRTop)
{
    HRESULT hr;
    HWND hwndBrowser;

    CComPtr<IOleClientSite>     spClientSite;
    CComQIPtr<IServiceProvider> spISP;
    CComPtr<IWebBrowser2>       spBrowser;
    CComPtr<IDispatch>          spDispatch; 
    CComQIPtr<IHTMLDocument2>   spDocument;
    CComPtr<IHTMLWindow2>       spScrollableWindow;
    CComQIPtr<IViewObject2>     spViewObject;
    CComPtr<IHTMLStyle>         spStyle;
    CComQIPtr<IHTMLElement2>    spScrollableElement;

    CComVariant documentHeight;
    CComVariant documentWidth;
    CComVariant viewportHeight;
    CComVariant viewportWidth;

    GetSite(IID_IUnknown, (void**)&spClientSite);

    if (spClientSite == NULL)
    {
        Error(L"There is no site.");
        return E_FAIL;
    }

    spISP = spClientSite;
    if (spISP == NULL)
    {
        Error(L"Unable to convert client site to service provider.");
        return E_FAIL;
    }

    // from http://support.microsoft.com/kb/257717
    hr = spISP->QueryService(IID_IWebBrowserApp, IID_IWebBrowser2, (void **)&spBrowser);

    if (FAILED(hr)) {
        // if we can't query the client site for IWebBrowser2, we're probably
        // in an HTA. Obtain the IHTMLWindow2 interface pointer by directly
        // querying the client site's service provider.
        // http://groups.google.com/group/microsoft.public.vc.language/browse_thread/thread/f8987a31d47cccfe/884cb8f13423039e
        CComPtr<IHTMLWindow2> spWindow;
        hr = spISP->QueryService(IID_IHTMLWindow2, &spWindow);
        if (FAILED(hr)) {
            Error("Failed to obtain IHTMLWindow2 from service provider");
            return E_FAIL;
        }

        hr = spWindow->get_document(&spDocument);
        if (FAILED(hr)) {
            Error("Failed to obtain IHTMLDocument2 from window");
            return E_FAIL;
        }

        CComQIPtr<IOleWindow> spOleWindow = spDocument;
        if (spOleWindow == NULL) {
            Error("Failed to obtain IOleWindow from document");
            return E_FAIL;
        }

        hr = spOleWindow->GetWindow(&hwndBrowser);
        if (FAILED(hr)) {
            Error("Failed to obtain HWND from OLE window");
            return E_FAIL;
        }

        hwndBrowser = GetAncestor(hwndBrowser, GA_ROOTOWNER);
    }
    else {
        hr = spBrowser->get_HWND((long*)&hwndBrowser);
        if (FAILED(hr)) {
            Error("Failed to get HWND for browser (is this a frame?)");
            return E_FAIL;
        }

        ie = GetAncestor(hwndBrowser, GA_ROOTOWNER);

        CComPtr<IDispatch> spDispatch;
        hr = spBrowser->get_Document(&spDispatch);
        if (FAILED(hr))
            return E_FAIL;

        spDocument = spDispatch;
        if (spDocument == NULL)
            return E_FAIL;


        IServiceProvider* pServiceProvider = NULL;
        if (SUCCEEDED(spBrowser->QueryInterface(
                            IID_IServiceProvider, 
                            (void**)&pServiceProvider)))
        {
            IOleWindow* pWindow = NULL;
            if (SUCCEEDED(pServiceProvider->QueryService(
                            SID_SShellBrowser,
                            IID_IOleWindow,
                            (void**)&pWindow)))
            {

                if (SUCCEEDED(pWindow->GetWindow(&hwndBrowser)))
                {
                    hwndBrowser = FindWindowEx(hwndBrowser, NULL, _T("Shell DocObject View"), NULL);
                    if (hwndBrowser)
                    {
                        hwndBrowser = FindWindowEx(hwndBrowser, NULL, _T("Internet Explorer_Server"), NULL);
                    }
                }

                pWindow->Release();
            }
         
            pServiceProvider->Release();
        } 
    }

    // Nobody else seems to know how to get IViewObject2?!
    // http://starkravingfinkle.org/blog/2004/09/
    spViewObject = spDocument;
    if (spViewObject == NULL)
    {
        Error(L"Unable to convert document to view object.");
        return E_FAIL;
    }

    CComQIPtr<IHTMLDocument5> spDocument5;
    spDocument->QueryInterface(IID_IHTMLDocument5, (void**)&spDocument5);
    if (spDocument5 == NULL)
    {
        Error(L"Snapsie requires IE6 or greater.");
        return E_FAIL;
    }

    CComBSTR compatMode;
    spDocument5->get_compatMode(&compatMode);

    // In non-standards-compliant mode, the BODY element represents the canvas.
    if (compatMode == L"BackCompat")
    {
        CComPtr<IHTMLElement> spBody;
        spDocument->get_body(&spBody);
        if (NULL == spBody)
        {
            return E_FAIL;
        }

        spBody->getAttribute(CComBSTR("scrollHeight"), 0, &documentHeight);
        spBody->getAttribute(CComBSTR("scrollWidth"), 0, &documentWidth);
        spBody->getAttribute(CComBSTR("clientHeight"), 0, &viewportHeight);
        spBody->getAttribute(CComBSTR("clientWidth"), 0, &viewportWidth);
    }

    // In standards-compliant mode, the HTML element represents the canvas.
    else
    {
        CComQIPtr<IHTMLDocument3> spDocument3;
        spDocument->QueryInterface(IID_IHTMLDocument3, (void**)&spDocument3);
        if (NULL == spDocument3)
        {
            Error(L"Unable to get IHTMLDocument3 handle from document.");
            return E_FAIL;
        }

        // The root node should be the HTML element.
        CComPtr<IHTMLElement> spRootNode;
        spDocument3->get_documentElement(&spRootNode);
        if (NULL == spRootNode)
        {
            Error(L"Could not retrieve root node.");
            return E_FAIL;
        }

        CComPtr<IHTMLHtmlElement> spHtml;
        spRootNode->QueryInterface(IID_IHTMLHtmlElement, (void**)&spHtml);
        if (NULL == spHtml)
        {
            Error(L"Root node is not the HTML element.");
            return E_FAIL;
        }

        spRootNode->getAttribute(CComBSTR("scrollHeight"), 0, &documentHeight);
        spRootNode->getAttribute(CComBSTR("scrollWidth"), 0, &documentWidth);
        spRootNode->getAttribute(CComBSTR("clientHeight"), 0, &viewportHeight);
        spRootNode->getAttribute(CComBSTR("clientWidth"), 0, &viewportWidth);
    }


    // Figure out how large to make the window.  It's not sufficient to just use the dimensions of the scrolled
    // viewport because the browser chrome occupies space that must be accounted for as well.
    RECT ieWindowRect;
    GetWindowRect(ie, &ieWindowRect);
    int ieWindowWidth = ieWindowRect.right - ieWindowRect.left;
    int ieWindowHeight = ieWindowRect.bottom - ieWindowRect.top;

    RECT contentClientRect;
    GetClientRect(hwndBrowser, &contentClientRect);
    int contentClientWidth = contentClientRect.right - contentClientRect.left;
    int contentClientHeight = contentClientRect.bottom - contentClientRect.top;

    int chromeWidth = ieWindowWidth - contentClientWidth;
    int chromeHeight = 2 * (ieWindowHeight - contentClientHeight);

    int imageHeight = documentHeight.intVal;
    int imageWidth = documentWidth.intVal;

    maxWidth = imageWidth + chromeWidth;
    maxHeight = imageHeight + chromeHeight;

    long originalHeight, originalWidth;
    spBrowser->get_Height(&originalHeight);
    spBrowser->get_Width(&originalWidth);


    // The resize message is being ignored if the window appears to be maximized.  There's likely a
    // way to bypass that.  My ghetto way is to unmaximize the window, then move on with setting
    // the window to the dimensions we really want.  This is okay because we revert back to the
    // original dimensions afterward.
    BOOL isMaximized = IsZoomed(ie);
    if (isMaximized)
    {
        ShowWindow(ie, SW_SHOWNORMAL);
    }

    // Get the path to this DLL so we can load it up with LoadLibrary.
    TCHAR dllPath[_MAX_PATH];
    GetModuleFileName((HINSTANCE) &__ImageBase, dllPath, _MAX_PATH);

    // Get the path to the Windows hook we use to allow resizing the window greater than the virtual screen resolution.
    HINSTANCE hinstDLL = LoadLibrary(dllPath);
    HOOKPROC hkprcSysMsg = (HOOKPROC)GetProcAddress(hinstDLL, "CallWndProc");
    if (hkprcSysMsg == NULL)
        PrintError(L"GetProcAddress");

    // Install the Windows hook.
    nextHook = SetWindowsHookEx(WH_CALLWNDPROC, hkprcSysMsg, hinstDLL, 0);
    if (nextHook == 0)
        PrintError(L"SetWindowsHookEx");

    spBrowser->put_Height(maxHeight);
    spBrowser->put_Width(maxWidth);


    // Capture the window's canvas to a DIB.
    CImage image;
    image.Create(imageWidth, imageHeight, 24);
    CImageDC imageDC(image);
    
    hr = PrintWindow(hwndBrowser, imageDC, PW_CLIENTONLY);
    if (FAILED(hr))
    {
        Error(L"PrintWindow");
    }

    // I'm not sure if PrintWindow captures alpha blending or not.  OleDraw does, but I was having
    // issues with sizing the browser correctly between quirks and standards modes to capture everything we need.
    //
    //RECT rcBounds = { 0, 0, imageWidth, imageHeight };
    //hr = OleDraw(spViewObject, DVASPECT_DOCPRINT, imageDC, &rcBounds);
    //if (FAILED(hr))
    //{
    //    Error(L"OleDraw");
    //}

    UnhookWindowsHookEx(nextHook);

    // Restore the browser to the original dimensions.
    if (isMaximized)
    {
        ShowWindow(ie, SW_MAXIMIZE);
    }
    else
    {
        spBrowser->put_Height(originalHeight);
        spBrowser->put_Width(originalWidth);
    }

    hr = image.Save(CW2T(outputFile));
    if (FAILED(hr))
    {
        PrintError(L"Failed saving image.");
        return E_FAIL;
    }

    return hr;
}