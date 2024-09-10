// Program entry point
int APIENTRY wWinMain(_In_ HINSTANCE hinst, _In_opt_ HINSTANCE /*hinstPrev*/, _In_ LPWSTR /*lpCmdLine*/, _In_ int /*nCmdShow*/)
{
    // Initialize localized global strings
    if (LoadString(hinst, IDS_WINDOW, g_windowClass, MAX_LOADSTRING) == 0)
    {
        fprintf(stderr, "LoadString() failed with error code %u.\n", GetLastError());
        return -1;
    }
    if (LoadString(hinst, IDS_CAPTION, g_mainTitle, MAX_LOADSTRING) == 0)
    {
        fprintf(stderr, "LoadString() failed with error code %u.\n", GetLastError());
        return -1;
    }
    if (LoadString(hinst, IDS_TOUCHHITTESTING_ON, g_touchHitTestingOnText, MAX_LOADSTRING) == 0)
    {
        fprintf(stderr, "LoadString() failed with error code %u.\n", GetLastError());
        return -1;
    }
    if (LoadString(hinst, IDS_TOUCHHITTESTING_OFF, g_touchHitTestingOffText, MAX_LOADSTRING) == 0)
    {
        fprintf(stderr, "LoadString() failed with error code %u.\n", GetLastError());
        return -1;
    }
    if (LoadString(hinst, IDS_RESET, g_resetText, MAX_LOADSTRING) == 0)
    {
        fprintf(stderr, "LoadString() failed with error code %u.\n", GetLastError());
        return -1;
    }

    // D2D automatically handles high DPI settings
    SetProcessDPIAware();

    // Register Class
    if (!MyRegisterClass(hinst))
    {
        return -1;
    }

    // Initialize Application
    if (!InitInstance(hinst, SW_SHOWMAXIMIZED))
    {
        return -1;
    }

    // Main message loop
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0) != 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    delete g_driver;
    g_driver = nullptr;

    return 0;
}