DWORD WINAPI ProgressMainLoop(LPVOID pv)
{    
    MSG msg;     
    DWORD cyVScroll;
    HFONT hFont = (HFONT) GetStockObject(DEFAULT_GUI_FONT); //(ANSI_FIXED_FONT);
    WCHAR wzStr[1024];

    if(g_fInitCommonControls)
    {
        InitCommonControls();
        g_fInitCommonControls = FALSE;
    }
    g_ulCount = 0;
    if(g_fRegisterClass)
    {
        _ASSERTE(g_hResources != NULL);
        WNDCLASSW  wndClass;

        wndClass.style          = CS_HREDRAW|CS_VREDRAW|CS_NOCLOSE;
        wndClass.lpfnWndProc    = ProgBoxWndProc;
        wndClass.cbClsExtra     = 0;
        wndClass.cbWndExtra     = 0;
        wndClass.hInstance      = g_hInstance;
        wndClass.hIcon          = WszLoadIcon(g_hResources,MAKEINTRESOURCE(IDI_ICON2));
        wndClass.hCursor        = NULL;
        wndClass.hbrBackground  = (HBRUSH) GetStockObject(LTGRAY_BRUSH);
        wndClass.lpszMenuName   = NULL; 
        wndClass.lpszClassName  = L"ProgressBox";

        if (WszRegisterClass(&wndClass) == 0) return 0;

        g_fRegisterClass = FALSE;
    }
    cyVScroll = GetSystemMetrics(SM_CYVSCROLL); 
    if(g_hwndProgBox = WszCreateWindowEx (0,
                                    RstrW(IDS_PROGRESSBOX), //"ProgressBox",
                                    RstrW(IDS_DISASSEMBLING), //"Disassembling",
                                    WS_VISIBLE | WS_CAPTION | WS_POPUP | WS_SYSMENU | WS_CLIPCHILDREN,
                                    400, 200, 400, 8*cyVScroll,
                                    HWND_DESKTOP, 
                                    (HMENU)0, 
                                    g_hInstance,
                                    NULL))
    {
        GetClientRect(g_hwndProgBox, &rcClient);
        
        if(g_hwndFromFile = WszCreateWindowEx (0,
                                        L"STATIC",
                                        L"",
                                        WS_CHILD|WS_VISIBLE|SS_CENTER,
                                        rcClient.left, rcClient.bottom-6*cyVScroll,rcClient.right, cyVScroll,
                                        g_hwndProgBox, 
                                        (HMENU)0, 
                                        g_hInstance,
                                        NULL))
        {
            SendMessageA(g_hwndFromFile,WM_SETFONT,(LPARAM)hFont,FALSE);
            WCHAR* wzFileName = UtfToUnicode(g_szInputFile);
            if(wcslen(wzFileName) <= 60) swprintf_s(wzStr,1024,RstrW(IDS_PB_FILE) /*"File  %s"*/,wzFileName);
            else 
            {
                WCHAR * p=wzFileName;
                while(p = wcschr(p,L'\\'))
                {
                    if(wcslen(p) <= 60) break;
                    p++;
                }
                if(p == NULL) p = &wzFileName[wcslen(wzFileName)-50];
                swprintf_s(wzStr,1024,RstrW(IDS_PB_FILE1) /*"File ...%s"*/,p);
            }
            WszSendMessage(g_hwndFromFile, WM_SETTEXT,0,(LPARAM)wzStr);
        }
        if(g_hwndToFile = WszCreateWindowEx (0,
                                        L"STATIC",
                                        L"",
                                        WS_CHILD|WS_VISIBLE|SS_CENTER,
                                        rcClient.left, rcClient.bottom-5*cyVScroll,rcClient.right, cyVScroll,
                                        g_hwndProgBox, 
                                        (HMENU)0, 
                                        g_hInstance,
                                        NULL))
        {
            SendMessageA(g_hwndToFile,WM_SETFONT,(LPARAM)hFont,FALSE);
            WCHAR* wzFileName = UtfToUnicode(g_szOutputFile);
            if(wcslen(wzFileName) <= 60) swprintf_s(wzStr,1024,RstrW(IDS_PB_TOFILE) /*"To file  %s"*/,wzFileName);
            else 
            {
                WCHAR * p=wzFileName;
                while(p = wcschr(p,L'\\'))
                {
                    if(wcslen(p) <= 60) break;
                    p++;
                }
                if(p == NULL) p = &wzFileName[wcslen(wzFileName)-50];
                swprintf_s(wzStr,1024,RstrW(IDS_PB_TOFILE1) /*"To file ...%s"*/,p);
            }
            WszSendMessage(g_hwndToFile, WM_SETTEXT,0,(LPARAM)wzStr);
        }
        if(g_hwndTally = WszCreateWindowEx (0,
                                        L"STATIC",
                                        L"",
                                        WS_CHILD|WS_VISIBLE|SS_CENTER,
                                        rcClient.left, rcClient.bottom-4*cyVScroll,rcClient.right, cyVScroll,
                                        g_hwndProgBox, 
                                        (HMENU)0, 
                                        g_hInstance,
                                        NULL))
        {
            SendMessageA(g_hwndTally,WM_SETFONT,(LPARAM)hFont,FALSE);
            if(g_ulCount <= g_NumClasses) swprintf_s(wzStr,1024,RstrW(IDS_PB_CLASSESDONE) /*"%d classes, %d done"*/,g_NumClasses,g_ulCount);
            else swprintf_s(wzStr,1024,RstrW(IDS_PB_GLOBALSDONE) /*"%d global methods, %d done"*/,g_ulRange-g_NumClasses,g_ulCount-g_NumClasses);
            WszSendMessage(g_hwndTally, WM_SETTEXT,0,(LPARAM)wzStr);
        }
        if(g_hwndProgress = WszCreateWindowEx (0,
                                        PROGRESS_CLASS,
                                        L"",
                                        WS_CHILD|WS_VISIBLE|SS_CENTER, // SS_CENTER gives smooth progress and solid bar
                                        rcClient.left, rcClient.bottom-3*cyVScroll,rcClient.right, cyVScroll,
                                        g_hwndProgBox, 
                                        (HMENU)0, 
                                        g_hInstance,
                                        NULL))
        {
            // Set the range for the progress bar.
            SendMessageA (g_hwndProgress, PBM_SETRANGE, 0L, MAKELPARAM(0, g_ulRange));
            // Set the step.
            SendMessageA (g_hwndProgress, PBM_SETSTEP, (WPARAM)1, 0L);
        }
        if(g_hwndCancel = WszCreateWindowEx (0,
                                        L"BUTTON",
                                        RstrW(IDS_PB_CANCEL), //"Cancel",
                                        WS_CHILD|WS_VISIBLE|BS_DEFPUSHBUTTON|BS_TEXT,
                                        rcClient.left+150, rcClient.bottom-3*cyVScroll/2,rcClient.right-300, 4*cyVScroll/3,
                                        g_hwndProgBox, 
                                        (HMENU)IDC_CANCEL, 
                                        g_hInstance,
                                        NULL))
        {
            SendMessageA(g_hwndCancel,WM_SETFONT,(LPARAM)hFont,FALSE);
        }
    }
    SetEvent(g_hThreadReady);
    while (WszGetMessage(&msg, NULL, 0, 0)) 
    { 
        TranslateMessage(&msg); 
        WszDispatchMessage(&msg); 
    }
    return 0;
}