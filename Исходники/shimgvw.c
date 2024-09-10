LONG WINAPI
ImageView_CreateWindow(HWND hwnd, LPWSTR szFileName)
{
    struct GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    WNDCLASS WndClass = {0};
    TCHAR szBuf[512];
    WCHAR szInitialFile[MAX_PATH];
    HWND hMainWnd;
    MSG msg;

    if (!ImageView_LoadSettings())
    {
        shiSettings.Maximized = FALSE;
        shiSettings.Left      = 0;
        shiSettings.Top       = 0;
        shiSettings.Right     = 520;
        shiSettings.Bottom    = 400;
    }

    // Initialize GDI+
    gdiplusStartupInput.GdiplusVersion              = 1;
    gdiplusStartupInput.DebugEventCallback          = NULL;
    gdiplusStartupInput.SuppressBackgroundThread    = FALSE;
    gdiplusStartupInput.SuppressExternalCodecs      = FALSE;

    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
    pLoadImage(szFileName);

    // Create the window
    WndClass.lpszClassName  = _T("shimgvw_window");
    WndClass.lpfnWndProc    = ImageView_WndProc;
    WndClass.hInstance      = hInstance;
    WndClass.style          = CS_HREDRAW | CS_VREDRAW;
    WndClass.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPICON));
    WndClass.hCursor        = LoadCursor(hInstance, IDC_ARROW);
    WndClass.hbrBackground  = (HBRUSH)COLOR_WINDOW;

    if (!RegisterClass(&WndClass)) return -1;

    LoadString(hInstance, IDS_APPTITLE, szBuf, sizeof(szBuf) / sizeof(TCHAR));
    hMainWnd = CreateWindow(_T("shimgvw_window"), szBuf,
                            WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_CAPTION,
                            CW_USEDEFAULT, CW_USEDEFAULT,
                            0, 0, NULL, NULL, hInstance, NULL);

    // make sure the path has no quotes on it
    wcscpy(szInitialFile, szFileName);
    PathUnquoteSpacesW(szInitialFile);

    currentFile = pBuildFileList(szInitialFile);
    if (currentFile)
    {
        pLoadImageFromNode(currentFile, hMainWnd);
    }

    // Show it
    ShowWindow(hMainWnd, SW_SHOW);
    UpdateWindow(hMainWnd);

    // Message Loop
    while(GetMessage(&msg,NULL,0,0))
    {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    pFreeFileList(currentFile);

    if (image)
        GdipDisposeImage(image);
    GdiplusShutdown(gdiplusToken);
    return -1;
}