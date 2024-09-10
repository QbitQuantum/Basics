/// <summary>
/// Creates the main window and begins processing
/// </summary>
/// <param name="hInstance">handle to the application instance</param>
/// <param name="nCmdShow">whether to display minimized, maximized, or normally</param>
int CBackgroundRemovalBasics::Run(HINSTANCE hInstance, int nCmdShow)
{
    MSG       msg = {0};
    WNDCLASS  wc;

    // Dialog custom window class
    ZeroMemory(&wc, sizeof(wc));
    wc.style         = CS_HREDRAW | CS_VREDRAW;
    wc.cbWndExtra    = DLGWINDOWEXTRA;
    wc.hInstance     = hInstance;
    wc.hCursor       = LoadCursorW(NULL, IDC_ARROW);
    wc.hIcon         = LoadIconW(hInstance, MAKEINTRESOURCE(IDI_APP));
    wc.lpfnWndProc   = DefDlgProcW;
    wc.lpszClassName = L"BackgroundRemovalBasicsAppDlgWndClass";

    if (!RegisterClassW(&wc))
    {
        return 0;
    }

	DWORD threadId; 
	HANDLE hThread = CreateThread(NULL, 0, NetworkManager::ThreadFunc, (LPVOID)nManager, CREATE_SUSPENDED, &threadId); 
	ResumeThread(hThread);

    // Create main application window
    HWND hWndApp = CreateDialogParamW(
        hInstance,
        MAKEINTRESOURCE(IDD_APP),
        NULL,
        (DLGPROC)CBackgroundRemovalBasics::MessageRouter, 
        reinterpret_cast<LPARAM>(this));

    // Set the init sensor status
    UpdateNscControlStatus();

    // Show window
    ShowWindow(hWndApp, nCmdShow);
    UpdateWindow(hWndApp);

    const HANDLE hEvents[] = {m_hNextDepthFrameEvent, m_hNextColorFrameEvent, m_hNextSkeletonFrameEvent, m_hNextBackgroundRemovedFrameEvent};
    LoadResourceImage(L"Background", L"Image", m_colorWidth * m_colorHeight * cBytesPerPixel, m_backgroundRGBX);

    // Main message loop
    while (WM_QUIT != msg.message)
    {
        // Check to see if we have either a message (by passing in QS_ALLINPUT)
        // Or a Kinect event (hEvents)
        // Update() will check for Kinect events individually, in case more than one are signaled
        MsgWaitForMultipleObjects(_countof(hEvents), hEvents, FALSE, INFINITE, QS_ALLINPUT);

        // Individually check the Kinect stream events since MsgWaitForMultipleObjects
        // can return for other reasons even though these are signaled.
        Update();
        
        while (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE))
        {
            // If a dialog message will be taken care of by the dialog proc
            if ((hWndApp != NULL) && IsDialogMessageW(hWndApp, &msg))
            {
                continue;
            }

            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }
    }

    return static_cast<int>(msg.wParam);
}