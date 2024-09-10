//----------------------------------------------------------------------------
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE, LPSTR acArgument, int)
{
    FWinApplication* pkTheApp = FWinApplication::GetApplication();
    assert( pkTheApp );
    if ( !pkTheApp )
        return -1;

    gs_hInstance = hInstance;

    if ( acArgument && strlen(acArgument) > 0 )
    {
        char* acProcessed = ProcessArgument(acArgument);
        pkTheApp->SetCommand(new Command(acProcessed));
        delete[] acProcessed;
    }

    if ( !pkTheApp->OnPrecreate() )
        return -2;

    // register the window class
    WNDCLASS kWC;
    kWC.style         = CS_HREDRAW | CS_VREDRAW;
    kWC.lpfnWndProc   = WinProc;
    kWC.cbClsExtra    = 0;
    kWC.cbWndExtra    = 0;
    kWC.hInstance     = hInstance;
    kWC.hIcon         = LoadIcon(NULL,IDI_APPLICATION);
    kWC.hCursor       = LoadCursor(NULL,IDC_ARROW);
    kWC.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    kWC.lpszClassName = gs_acWindowClassName;
    if ( pkTheApp->GetMenuID() )
        kWC.lpszMenuName  = MAKEINTRESOURCE(pkTheApp->GetMenuID());
    else
        kWC.lpszMenuName = 0;

    RegisterClass(&kWC);

    // require the window to have the specified client area
    RECT kRect = { 0, 0, pkTheApp->GetWidth()-1, pkTheApp->GetHeight()-1 };
    AdjustWindowRect(&kRect,gs_dwWindowStyle,pkTheApp->GetMenuID());

    // create the application window
    int iXPos = CW_USEDEFAULT;
    int iYPos = CW_USEDEFAULT;
    int iXSize = kRect.right - kRect.left + 1;
    int iYSize = kRect.bottom - kRect.top + 1;
    HWND hWnd = CreateWindow(gs_acWindowClassName,pkTheApp->GetCaption(),
        gs_dwWindowStyle,iXPos,iYPos,iXSize,iYSize,0,0,hInstance,0);

    pkTheApp->SetWindowHandle(hWnd);

    // create status window
    if ( pkTheApp->GetStatusPaneQuantity() )
    {
        InitCommonControls();

        HWND hStatusWnd = CreateWindow(STATUSCLASSNAME,"",
            WS_CHILD | WS_VISIBLE,0,0,0,0,hWnd,0,hInstance,0);

        pkTheApp->SetStatusWindowHandle(hStatusWnd);
    }

    // display the window
    ShowWindow(hWnd,SW_SHOW);
    UpdateWindow(hWnd);

    // allow the application to initialize before starting the message pump
    if ( !pkTheApp->OnInitialize() )
        return -3;

    MSG kMsg;
    while ( true )
    {
        if ( PeekMessage(&kMsg,0,0,0,PM_REMOVE) )
        {
            if ( kMsg.message == WM_QUIT )
                break;

            HACCEL hAccel = 0;
            if ( !TranslateAccelerator(hWnd,hAccel,&kMsg) )
            {
                TranslateMessage(&kMsg);
                DispatchMessage(&kMsg);
            }
        }
        else
        {
            pkTheApp->OnIdle();
        }
    }

    pkTheApp->OnTerminate();

    UnregisterClass(gs_acWindowClassName,hInstance);

    return 0;
}