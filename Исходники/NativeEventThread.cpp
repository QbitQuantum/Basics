HRESULT InitIEStuff (WebShellInitContext * initContext)
{
    HRESULT hr;
    HWND m_hWndClient;
    RECT rect;

    CMyDialog *bObj = initContext->browserObject;

    HRESULT hRes = CoInitializeEx(NULL,  COINIT_APARTMENTTHREADED);
    ATLASSERT(SUCCEEDED(hRes));

/*if (_WIN32_IE >= 0x0300)
	INITCOMMONCONTROLSEX iccx;
	iccx.dwSize = sizeof(iccx);
	iccx.dwICC = ICC_COOL_CLASSES | ICC_BAR_CLASSES;
	BOOL bRet = ::InitCommonControlsEx(&iccx);
	bRet;
	ATLASSERT(bRet);
#else
*/
//  ::InitCommonControls();
//#endif

    GetClientRect(initContext->parentHWnd, &rect);

    HINSTANCE newInst = GetModuleHandleA(NULL);
    hRes = _Module.Init(NULL, newInst);
    ATLASSERT(SUCCEEDED(hRes));

    AtlAxWinInit();

    m_hWndClient = bObj->Create(initContext->parentHWnd,
				rect,
				_T("about:blank"),
				WS_CHILD | WS_VISIBLE |
				   WS_CLIPSIBLINGS | WS_CLIPCHILDREN |
				   WS_VSCROLL | WS_HSCROLL,
				WS_EX_CLIENTEDGE,
				ID_WEBBROWSER);

    hr = bObj->QueryControl(&(initContext->browserObject->m_pWB));

    if FAILED(hr)
    {
	ATLTRACE(_T("Couldn't retrieve webbrowser"));
	return (-1);
    }

    if SUCCEEDED(hr)
    {
	ATLTRACE(_T("Browser successfully retrieved"));
    }

    initContext->browserHost = m_hWndClient;

    if (!bObj->spUnk) {
	hr = bObj->QueryControl(&(bObj->spUnk));
	hr = bObj->DispEventAdvise(bObj->spUnk);
    }

    if FAILED(hr)
    {
	ATLTRACE(_T("Couldn't establish connection points"));
	return -1;
    }

    hr = bObj->m_pWB->QueryInterface(IID_IServiceProvider,
                                     (void**)&(bObj->m_pISP));

    if (FAILED(hr) || (bObj->m_pISP == NULL))
    {
	ATLTRACE(_T("Couldn't obtain COM IServiceProvider"));
	return -1;
    }

    hr = bObj->m_pISP->QueryService(SID_STravelLogCursor,
                                    IID_ITravelLogStg,
				    (void**)&(bObj->m_pTLStg));

    if (FAILED(hr) || (bObj->m_pTLStg == NULL))
    {
	ATLTRACE(_T("Couldn't obtain ITravelLog interface"));
	return -1;
    }

    processEventLoop(initContext);

    return 0;
}