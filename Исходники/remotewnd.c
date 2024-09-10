/*
 * Create - displays the dialog box
 */
HWND RemoteWnd_Create(HWND parentWnd)
{
    HWND remoteWnd;

    if (Prog_remoteWnd) {
        if (IsIconic(Prog_remoteWnd)) {
            OpenIcon(Prog_remoteWnd);
        }
        BringWindowToTop(Prog_remoteWnd);
        remoteWnd = Prog_remoteWnd;
    } else {
        RECT wndRect = { 60, 60, 685, 120 };
        DWORD wndExStyles = WS_EX_LEFT;
        DWORD wndStyles = WS_POPUPWINDOW | WS_CAPTION | WS_SYSMENU;
        int i;

        if (!AdjustWindowRectEx(&wndRect, wndStyles, FALSE, wndExStyles)) {
            MsgBox_LastErrorF(parentWnd, _T("Error adjusting window rect"));
        }
        remoteWnd = CreateWindowEx(
                wndExStyles                               /* extended styles */
                , RemoteWnd_className                     /* window class */
                , _T("Remote")                            /* caption text */
                , wndStyles                               /* styles */
                , wndRect.left, wndRect.top               /* left, top */
                , RECT_W(wndRect), RECT_H(wndRect)        /* width, height */
                , NULL                                    /* parent window */
                , (HMENU) NULL                            /* menu */
                , Prog_instance                           /* program instance */
                , NULL                                    /* creation data */
            );
        if (!remoteWnd) {
            MsgBox_LastErrorF(parentWnd
                    , _T("Error creating remote control window"));
            return NULL;
        }
        /*
         * Add "Stay On Top" system menu item.
         */
        Window_AddSysMenuItem(remoteWnd, _T("Stay On Top"), IDM_STAY_ON_TOP
                , TRUE);
        rw_StayOnTop(remoteWnd);

        /*
         * Initialize buttons.
         */
        for (i = 0; i < btnInitCnt; i++) {
            HWND btn = CreateWindowEx(
                    0                                         /* extended styles */
                    , _T("BUTTON")                            /* window class */
                    , _T("TX81Z Remote")                      /* caption text */
                    , BS_OWNERDRAW | WS_CHILD | WS_VISIBLE    /* styles */
                    , btnInits[i].x, btnInits[i].y            /* left, top */
                    , btnInits[i].w, btnInits[i].h            /* width, height */
                    , remoteWnd                               /* parent window */
                    , (HMENU) btnInits[i].btnID               /* menu */
                    , Prog_instance                           /* program instance */
                    , NULL                                    /* creation data */
                );
            if (!btn) {
                MsgBox_LastErrorF(parentWnd
                        , _T("Error creating remote control button"));
                return NULL;
            }
            rw_origBtnProc = (WNDPROC) SetWindowLong(btn, GWL_WNDPROC
                    , (long) rw_BtnProc);
        }
        ShowWindow(remoteWnd, SW_SHOW);
    }

    return remoteWnd;
}