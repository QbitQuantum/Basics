BOOL CTSFMainWnd::Initialize(int nCmdShow)
{
    HRESULT hr;
#if 1
    hr = CoCreateInstance(  CLSID_TF_ThreadMgr, 
                            NULL, 
                            CLSCTX_INPROC_SERVER, 
                            IID_ITfThreadMgr, 
                            (void**)&g_pThreadMgr);
#else
    hr = TF_CreateThreadMgr(&g_pThreadMgr);
#endif
    if(SUCCEEDED(hr))
    {
        hr = g_pThreadMgr->Activate(&m_tfClientID);

        if(SUCCEEDED(hr))
        {
            WNDCLASS  wc;

            ZeroMemory(&wc, sizeof(wc));
   
            wc.style          = CS_HREDRAW | CS_VREDRAW;
            wc.lpfnWndProc    = CTSFMainWnd::_WndProc;
            wc.cbClsExtra     = 0;
            wc.cbWndExtra     = sizeof(CTSFMainWnd*);
            wc.hInstance      = m_hInst;
            wc.hIcon          = LoadIcon(m_hInst, MAKEINTRESOURCE(IDI_MAIN_ICON));
            wc.hCursor        = LoadCursor(NULL, IDC_ARROW);
            wc.hbrBackground  = (HBRUSH)(COLOR_DESKTOP + 1);
            wc.lpszMenuName   = MAKEINTRESOURCE(IDR_MAIN_MENU);
            wc.lpszClassName  = g_szTSFMainClassName;

            if(0 != RegisterClass(&wc))
            {
                //create the main window
                m_hWnd = CreateWindowEx(    0,
                                            g_szTSFMainClassName,
                                            g_szTSFAppTitle,
                                            WS_OVERLAPPEDWINDOW,
                                            CW_USEDEFAULT,
                                            CW_USEDEFAULT,
                                            CW_USEDEFAULT,
                                            CW_USEDEFAULT,
                                            NULL,
                                            NULL,
                                            m_hInst,
                                            (LPVOID)this);

                if(NULL != m_hWnd)
                {
                    ShowWindow(m_hWnd, nCmdShow);
                    UpdateWindow(m_hWnd);
            
                    return TRUE;
                }
            }
        }
    }

    return FALSE;
}