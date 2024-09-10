int Init_ConsoleWin(void)
{
    HDC conDC;
    WNDCLASS wndclass;
    TEXTMETRIC metrics;
    RECT cRect;
    int width,height;
    int scr_width,scr_height;
    HINSTANCE hInstance;
    char titlebuffer[2048];

    if (con_hWnd)
      return TRUE;
    hInstance = GetModuleHandle(NULL);
    Init_Console();
    /* Register the frame class */
    wndclass.style         = CS_OWNDC;
    wndclass.lpfnWndProc   = (WNDPROC)ConWndProc;
    wndclass.cbClsExtra    = 0;
    wndclass.cbWndExtra    = 0;
    wndclass.hInstance     = hInstance;
    wndclass.hIcon         = LoadIcon (hInstance, IDI_WINLOGO);
    wndclass.hCursor       = LoadCursor (NULL,IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)GetStockObject (BLACK_BRUSH);
    wndclass.lpszMenuName  = szConName;
    wndclass.lpszClassName = szConName;

    if (!RegisterClass(&wndclass))
        return FALSE;

    width=100;
    height=100;
    strcpy(titlebuffer,PACKAGE);
    strcat(titlebuffer," ");
    strcat(titlebuffer,VERSION);
    strcat(titlebuffer," console");
    con_hWnd = CreateWindow(szConName, titlebuffer,
             WS_CAPTION | WS_POPUP,
             0, 0, width, height,
             NULL, NULL, hInstance, NULL);
    conDC=GetDC(con_hWnd);
    OemFont = GetStockObject(OEM_FIXED_FONT);
    SelectObject(conDC, OemFont);
    GetTextMetrics(conDC, &metrics);
    OemWidth = metrics.tmAveCharWidth;
    OemHeight = metrics.tmHeight;
    GetClientRect(con_hWnd, &cRect);
    width += (OemWidth * 80) - cRect.right;
    height += (OemHeight * 25) - cRect.bottom;
    // proff 11/09/98: Added code for centering console
    scr_width = GetSystemMetrics(SM_CXFULLSCREEN);
    scr_height = GetSystemMetrics(SM_CYFULLSCREEN);
    MoveWindow(con_hWnd, (scr_width-width)/2, (scr_height-height)/2, width, height, TRUE);
    GetClientRect(con_hWnd, &cRect);
    ConWidth = cRect.right;
    ConHeight = cRect.bottom;
    SetTextColor(conDC, RGB(192,192,192));
    SetBkColor(conDC, RGB(0,0,0));
    SetBkMode(conDC, OPAQUE);
    ReleaseDC(con_hWnd,conDC);
    ShowWindow(con_hWnd, SW_SHOW);
    UpdateWindow(con_hWnd);
    return TRUE;
}