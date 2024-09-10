/*--------------------------------------------------------------------------*/
static DWORD WINAPI ThreadSplashScreen(LPVOID lpParam)
{
    char *ScilabDirectory = NULL;
    char *ImageFilename = NULL;
    wchar_t *wImageFilename = NULL;

    size_t len = 0;
    Gdiplus::GdiplusStartupInput gdiplusStartupInput;

    ULONG_PTR gdiplusToken = NULL;
    Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    HINSTANCE hInstanceThisDll = (HINSTANCE)GetModuleHandle("scilab_windows");

    ScilabDirectory = getScilabDirectory(TRUE);
    if (ScilabDirectory == NULL)
    {
        return 0;
    }

    len = strlen(FORMAT_FULLPATH_SPLASH_IMAGE) + strlen(ScilabDirectory) + 1;
    ImageFilename = (char*)MALLOC(sizeof(char) * len);
    if (ImageFilename == NULL)
    {
        return 0;
    }

    sprintf(ImageFilename, FORMAT_FULLPATH_SPLASH_IMAGE, ScilabDirectory);
    FREE(ScilabDirectory);
    ScilabDirectory = NULL;

    wImageFilename = to_wide_string(ImageFilename);
    FREE(ImageFilename);
    ImageFilename = NULL;
    if (wImageFilename == NULL)
    {
        return 0;
    }

    pImage = Gdiplus::Image::FromFile((const WCHAR *)wImageFilename);
    FREE(wImageFilename);
    wImageFilename = NULL;
    if (pImage == NULL)
    {
        return 0;
    }

    WNDCLASS wndcls = {0};

    wndcls.style = CS_HREDRAW | CS_VREDRAW;
    wndcls.lpfnWndProc = SplashWndProc;
    wndcls.hInstance = GetModuleHandle(NULL);
    wndcls.hCursor = LoadCursor(NULL, IDC_APPSTARTING);
    wndcls.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wndcls.lpszClassName = SPLASH_WINDOW_CLASSNAME;
    wndcls.hIcon = LoadIcon(wndcls.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

    if (!RegisterClass(&wndcls))
    {
        if (GetLastError() != 0x00000582) // already registered
        {
            return 0;
        }
    }

    // try to find monitor where mouse was last time
    POINT point = {0};
    MONITORINFO mi = {sizeof(MONITORINFO), 0};
    HMONITOR hMonitor = 0;
    RECT rcArea = {0};

    ::GetCursorPos(&point);
    hMonitor = ::MonitorFromPoint(point, MONITOR_DEFAULTTONEAREST);
    if (::GetMonitorInfo(hMonitor, &mi))
    {
        rcArea.left = (mi.rcMonitor.right + mi.rcMonitor.left - pImage->GetWidth()) / 2;
        rcArea.top = (mi.rcMonitor.top + mi.rcMonitor.bottom - pImage->GetHeight()) / 2;
    }
    else
    {
        SystemParametersInfo(SPI_GETWORKAREA, NULL, &rcArea, NULL);
        rcArea.left = (rcArea.right + rcArea.left - pImage->GetWidth()) / 2;
        rcArea.top = (rcArea.top + rcArea.bottom - pImage->GetHeight()) / 2;
    }

    HWND hdlg = CreateWindowEx(WS_EX_TOOLWINDOW,
                               SPLASH_WINDOW_CLASSNAME,
                               SPLASH_WINDOW_CLASSNAME,
                               WS_CLIPCHILDREN | WS_POPUP,
                               rcArea.left,
                               rcArea.top,
                               pImage->GetWidth(),
                               pImage->GetHeight(),
                               NULL,
                               NULL,
                               wndcls.hInstance,
                               NULL);

    if (hdlg == NULL)
    {
        return 0;
    }

    ShowWindow(hdlg, SW_SHOWNORMAL);
    UpdateWindow(hdlg);
    SetWindowPos(hdlg, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);

    while (!stopSplashScreen(20, 1000))
    {
        Sleep(20);
    }

    DestroyWindow(hdlg);
    return 0;
}