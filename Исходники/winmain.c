int WINAPI
wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd)
{
    WNDCLASSEXW WndClass = {0};
    WCHAR szWindowClass[] = L"ROSAPPMGR";
    WCHAR szWindowName[MAX_STR_LEN];
    WCHAR szErrorText[MAX_STR_LEN];
    HANDLE hMutex = NULL;
    MSG Msg;

    switch (GetUserDefaultUILanguage())
  {
    case MAKELANGID(LANG_HEBREW, SUBLANG_DEFAULT):
      SetProcessDefaultLayout(LAYOUT_RTL);
      break;

    default:
      break;
  }

    hInst = hInstance;

    if (!IsUserAnAdmin())
    {
        LoadStringW(hInst, IDS_USER_NOT_ADMIN, szErrorText, sizeof(szErrorText) / sizeof(WCHAR));
        MessageBox(0, szErrorText, NULL, MB_OK | MB_ICONWARNING);
        return 1;
    }

    hMutex = CreateMutexW(NULL, FALSE, szWindowClass);
    if ((!hMutex) || (GetLastError() == ERROR_ALREADY_EXISTS))
    {
        /* If already started, it is found its window */
        HWND hWindow = FindWindowW(szWindowClass, NULL);

        /* Activate window */
        ShowWindow(hWindow, SW_SHOWNORMAL);
        SetForegroundWindow(hWindow);
        return 1;
    }

    if (!LoadSettings())
    {
        FillDefaultSettings(&SettingsInfo);
    }

    InitLogs();

    InitCommonControls();

    /* Create the window */
    WndClass.cbSize        = sizeof(WNDCLASSEXW);
    WndClass.lpszClassName = szWindowClass;
    WndClass.lpfnWndProc   = MainWindowProc;
    WndClass.hInstance     = hInstance;
    WndClass.hIcon         = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MAIN));
    WndClass.hCursor       = LoadCursor(NULL, IDC_ARROW);
    WndClass.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
    WndClass.lpszMenuName  = MAKEINTRESOURCEW(IDR_MAINMENU);

    if (RegisterClassExW(&WndClass) == (ATOM)0) goto Exit;

    LoadStringW(hInst, IDS_APPTITLE, szWindowName, sizeof(szWindowName) / sizeof(WCHAR));

    hMainWnd = CreateWindowExW(WS_EX_WINDOWEDGE,
                               szWindowClass,
                               szWindowName,
                               WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
                               CW_USEDEFAULT,
                               CW_USEDEFAULT,
                               680,
                               450,
                               NULL,
                               NULL,
                               hInstance,
                               NULL);

    if (!hMainWnd) goto Exit;

    /* Show it */
    ShowWindow(hMainWnd, SW_SHOW);
    UpdateWindow(hMainWnd);

    /* Message Loop */
    while (GetMessage(&Msg, NULL, 0, 0))
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }

Exit:
    if (hMutex) CloseHandle(hMutex);

    return 0;
}