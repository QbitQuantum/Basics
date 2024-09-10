void little::initWindow()
{
    RECT& rc = m_rcDesktop;
    GetWindowRect(GetDesktopWindow(), &m_rcDesktop);
    m_rect.x       = rc.left;
    m_rect.y       = rc.top;
    m_rect.width   = rc.right - rc.left;
    m_rect.height  = rc.bottom - rc.top;
    m_cyFullScreen = GetSystemMetrics(SM_CYFULLSCREEN);
    
    WNDCLASSEXW wndCls;
    wndCls.cbSize        = sizeof(wndCls);
    wndCls.hInstance     = m_hInst;
    wndCls.lpszClassName = WNDCLASSNAME;
    wndCls.style         = CS_HREDRAW | CS_VREDRAW;
    wndCls.lpfnWndProc   = WndProc;
    wndCls.hIcon         = NULL; // todo
    wndCls.hIconSm       = NULL; // todo
    wndCls.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wndCls.cbClsExtra    = 0;
    wndCls.cbWndExtra    = 0;
    wndCls.hbrBackground = NULL;
    wndCls.lpszMenuName  = NULL;

    RegisterClassExW(&wndCls);

    m_hWnd = CreateWindowExW(WS_EX_LAYERED |
                             WS_EX_TOPMOST |
                             WS_EX_TOOLWINDOW|  // Òþ²ØÈÎÎñÀ¸Í¼±ê
                             WS_EX_TRANSPARENT, // Êó±ê´©Í¸
                                WNDCLASSNAME,
                                NULL,
                                WS_OVERLAPPEDWINDOW,
                                m_rect.x,
                                m_rect.y,
                                m_rect.width,
                                m_rect.height,
                                NULL,
                                NULL,
                                m_hInst,
                                NULL);
}