HRESULT Drosera::initUI(HINSTANCE hInstance, int nCmdShow)
{
    // Initialize global strings
    LoadString(hInstance, IDS_APP_TITLE, szTitle, ARRAYSIZE(szTitle));
    LoadString(hInstance, IDC_DROSERA, szWindowClass, ARRAYSIZE(szWindowClass));
    registerDroseraClass(hInstance);

    Drosera::setInst(hInstance); // Store instance handle in our local variable

    m_hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, 0, 0, hInstance, 0);

    if (!m_hWnd)
        return HRESULT_FROM_WIN32(GetLastError());

    SetLastError(0);
    SetWindowLongPtr(m_hWnd, 0, reinterpret_cast<LONG_PTR>(this));
    HRESULT ret = HRESULT_FROM_WIN32(GetLastError());
    if (FAILED(ret))
        return ret;

    ret = OleInitialize(0);
    if (FAILED(ret))
        return ret;

    ret = CoCreateInstance(CLSID_WebView, 0, CLSCTX_ALL, IID_IWebView, (void**)&m_webView);
    if (FAILED(ret))
        return ret;

    ret = m_webView->QueryInterface(IID_IWebViewPrivate, reinterpret_cast<void**>(&m_webViewPrivate));
    if (FAILED(ret))
        return ret;

    ret = m_webView->setHostWindow(reinterpret_cast<OLE_HANDLE>(m_hWnd));
    if (FAILED(ret))
        return ret;

    ret = m_webView->setFrameLoadDelegate(this);
    if (FAILED(ret))
        return ret;

    ret = m_webView->setUIDelegate(this);
    if (FAILED(ret))
        return ret;

    RECT rect = {0};
    ret = m_webView->initWithFrame(rect, 0, 0);
    if (FAILED(ret))
        return ret;

    HWND viewWindow;
    ret = m_webViewPrivate->viewWindow(reinterpret_cast<OLE_HANDLE*>(&viewWindow));
    if (FAILED(ret))
        return ret;

    ::SetProp(viewWindow, kDroseraPointerProp, (HANDLE)this);

    COMPtr<IWebFrame> mainFrame;
    ret = m_webView->mainFrame(&mainFrame);
    if (FAILED(ret))
        return ret;

    COMPtr<IWebMutableURLRequest> request;
    ret = CoCreateInstance(CLSID_WebMutableURLRequest, 0, CLSCTX_ALL, IID_IWebMutableURLRequest, (void**)&request);
    if (FAILED(ret))
        return ret;

    RetainPtr<CFURLRef> htmlURLRef(AdoptCF, ::CFBundleCopyResourceURL(::CFBundleGetBundleWithIdentifier(CFSTR("org.webkit.drosera")), CFSTR("debugger"), CFSTR("html"), CFSTR("Drosera")));
    if (!htmlURLRef)
        return E_FAIL;

    CFStringRef urlStringRef = ::CFURLGetString(htmlURLRef.get());
    BSTR tempStr = cfStringToBSTR(urlStringRef);    // Both initWithRUL and SysFreeString can handle 0.
    ret = request->initWithURL(tempStr, WebURLRequestUseProtocolCachePolicy, 60);
    SysFreeString(tempStr);
    if (FAILED(ret))
        return ret;

    ret = mainFrame->loadRequest(request.get());
    if (FAILED(ret))
        return ret;

    m_webViewLoaded = true;

    // FIXME: Implement window size/position save/restore

    RECT frame;
    frame.left = 60;
    frame.top = 200;
    frame.right = 750;
    frame.bottom = 550;
    ::SetWindowPos(m_hWnd, HWND_TOPMOST, frame.left, frame.top, frame.right - frame.left, frame.bottom - frame.top, 0);
    ShowWindow(m_hWnd, nCmdShow);
    UpdateWindow(m_hWnd);

    return 0;
}