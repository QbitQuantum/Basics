static BOOL InitInstance(HINSTANCE hInst, int nCmdShow)
{
    HWND hWnd;
    WCHAR wszAppName[MAX_LOAD_STRING];
    WCHAR wszTitle[MAX_LOAD_STRING];
    TBBUTTON tB[] = {
        {0, 0, 0, BTNS_SEP, {0, 0}, 0, 0},
        {0, IDM_BIND, TBSTATE_ENABLED, BTNS_BUTTON, {0, 0}, 0, 0},
        {1, IDM_TYPELIB, TBSTATE_ENABLED, BTNS_BUTTON, {0, 0}, 0, 0},
        {0, 0, 0, BTNS_SEP, {0, 0}, 0, 0},
        {2, IDM_REGEDIT, TBSTATE_ENABLED, BTNS_BUTTON, {0, 0}, 0, 0},
        {0, 0, 0, BTNS_SEP, {0, 0}, 0, 0},
        {3, IDM_CREATEINST, TBSTATE_ENABLED, BTNS_BUTTON, {0, 0}, 0, 0},
        {4, IDM_RELEASEINST, TBSTATE_ENABLED, BTNS_BUTTON, {0, 0}, 0, 0},
        {0, 0, 0, BTNS_SEP, {0, 0}, 0, 0},
        {5, IDM_VIEW, TBSTATE_ENABLED, BTNS_BUTTON, {0, 0}, 0, 0}
    };

    LoadStringW(hInst, IDS_APPNAME, wszAppName, sizeof(wszAppName)/sizeof(wszAppName[0]));
    LoadStringW(hInst, IDS_APPTITLE, wszTitle, sizeof(wszTitle)/sizeof(wszTitle[0]));

    hWnd = CreateWindowW(wszAppName, wszTitle, WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInst, NULL);
    if(!hWnd) return FALSE;

    globals.hStatusBar = CreateStatusWindowW(WS_VISIBLE|WS_CHILD,
            wszTitle, hWnd, 0);

    globals.hToolBar = CreateToolbarEx(hWnd, WS_CHILD|WS_VISIBLE, 0, 1, hInst,
            IDB_TOOLBAR, tB, 10, 16, 16, 16, 16, sizeof(TBBUTTON));
    SendMessageW(globals.hToolBar, TB_ENABLEBUTTON, IDM_CREATEINST, FALSE);
    SendMessageW(globals.hToolBar, TB_ENABLEBUTTON, IDM_RELEASEINST, FALSE);
    SendMessageW(globals.hToolBar, TB_ENABLEBUTTON, IDM_VIEW, FALSE);

    globals.hMainWnd = hWnd;
    globals.hMainInst = hInst;
    globals.bExpert = TRUE;
    globals.dwClsCtx = CLSCTX_INPROC_SERVER|CLSCTX_LOCAL_SERVER;

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}