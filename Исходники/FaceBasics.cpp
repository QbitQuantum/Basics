/// <summary>
/// Creates the main window and begins processing
/// </summary>
/// <param name="hInstance">handle to the application instance</param>
/// <param name="nCmdShow">whether to display minimized, maximized, or normally</param>
int CFaceBasics::Run(HINSTANCE hInstance, int nCmdShow)
{
    MSG       msg = {0};
    WNDCLASS  wc;

    // Dialog custom window class
    ZeroMemory(&wc, sizeof(wc));
    wc.style         = CS_HREDRAW | CS_VREDRAW;
    wc.cbWndExtra    = DLGWINDOWEXTRA;
    wc.hCursor       = LoadCursorW(NULL, IDC_ARROW);
    wc.hIcon         = LoadIconW(hInstance, MAKEINTRESOURCE(IDI_APP));
	wc.lpszMenuName =  MAKEINTRESOURCE(IDR_MENU1);
    wc.lpfnWndProc   = DefDlgProcW;
    wc.lpszClassName = L"Face-And-HDFace-Basics-D2DAppDlgWndClass";

    if (!RegisterClassW(&wc))
    {
        return 0;
    }

	//hMenu = LoadMenuW(hInstance, MAKEINTRESOURCE(IDR_MENU1));
	
    // Create main application window
    HWND hWndApp = CreateDialogParamW(        NULL,         MAKEINTRESOURCE(IDD_APP),         NULL,        (DLGPROC)CFaceBasics::MessageRouter,         reinterpret_cast<LPARAM>(this));

	//HWND hWndApp = CreateDialogParamW(        NULL,         MAKEINTRESOURCE(IDD_APP),         NULL,        (DLGPROC)CFaceBasics::MessageRouter,  WS_CAPTION);


    // Show window
    ShowWindow(hWndApp, nCmdShow);
	//ShowWindow(hWndApp, 3);

    // Main message loop
    while (WM_QUIT != msg.message)
    {
        Update();

        while (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE))
        {
            // If a dialog message will be taken care of by the dialog proc
            if (hWndApp && IsDialogMessageW(hWndApp, &msg))
            {
                continue;
            }

            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }
    }

    return static_cast<int>(msg.wParam);
}