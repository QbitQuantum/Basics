//
//    Main entry point
//
int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrev, LPTSTR szCmdLine, int iCmdShow)
{
    HWND        hwnd;
    MSG            msg;
    WNDCLASS    wndclass;
    INITCOMMONCONTROLSEX ice;
    HACCEL        hAccelTable;

    hInstance = hInst;

    // Load application title
    LoadString(hInst, IDS_SOL_NAME, szAppName, sizeof(szAppName) / sizeof(szAppName[0]));
    // Load MsgBox() texts here to avoid loading them many times later
    LoadString(hInst, IDS_SOL_ABOUT, MsgAbout, sizeof(MsgAbout) / sizeof(MsgAbout[0]));
    LoadString(hInst, IDS_SOL_QUIT, MsgQuit, sizeof(MsgQuit) / sizeof(MsgQuit[0]));
    LoadString(hInst, IDS_SOL_WIN, MsgWin, sizeof(MsgWin) / sizeof(MsgWin[0]));
    LoadString(hInst, IDS_SOL_DEAL, MsgDeal, sizeof(MsgDeal) / sizeof(MsgDeal[0]));

    //Window class for the main application parent window
    wndclass.style            = 0;//CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc    = WndProc;
    wndclass.cbClsExtra        = 0;
    wndclass.cbWndExtra        = 0;
    wndclass.hInstance        = hInst;
    wndclass.hIcon            = LoadIcon (hInst, MAKEINTRESOURCE(IDI_SOLITAIRE));
    wndclass.hCursor        = LoadCursor (NULL, IDC_ARROW);
    wndclass.hbrBackground    = (HBRUSH)NULL;
    wndclass.lpszMenuName    = MAKEINTRESOURCE(IDR_MENU1);
    wndclass.lpszClassName    = szAppName;

    RegisterClass(&wndclass);

    ice.dwSize = sizeof(ice);
    ice.dwICC = ICC_BAR_CLASSES;
    InitCommonControlsEx(&ice);

    srand((unsigned)GetTickCount());//timeGetTime());

//    InitCardLib();

    LoadSettings();

    //Construct the path to our help file
    MakePath(szHelpPath, MAX_PATH, _T(".hlp"));

    hwnd = CreateWindow(szAppName,        // window class name
                szAppName,                // window caption
                WS_OVERLAPPEDWINDOW
                ,//|WS_CLIPCHILDREN,      // window style
                CW_USEDEFAULT,            // initial x position
                CW_USEDEFAULT,            // initial y position
                0,                        // The real size will be computed in WndProc through WM_GETMINMAXINFO
                0,                        // The real size will be computed in WndProc through WM_GETMINMAXINFO
                NULL,                     // parent window handle
                NULL,                     // use window class menu
                hInst,                    // program instance handle
                NULL);                    // creation parameters

    hwndMain = hwnd;

    ShowWindow(hwnd, iCmdShow);
    UpdateWindow(hwnd);

    hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR1));

    while(GetMessage(&msg, NULL,0,0))
    {
        if(!TranslateAccelerator(hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    SaveSettings();

    return msg.wParam;
}