// Program entry point
int APIENTRY wWinMain(__in HINSTANCE hinst, __in_opt HINSTANCE hinstPrev, __in LPWSTR lpCmdLine,__in int nCmdShow)
{
    (void)HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);
    UNREFERENCED_PARAMETER(hinstPrev);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nCmdShow);
    BOOL success = TRUE;
    MSG msg;
    
    // Initialize global strings
    LoadString(hinst, IDS_WINDOW, g_tszWindowClass, MAX_LOADSTRING);
    LoadString(hinst, IDS_CAPTION, g_tszMainTitle, MAX_LOADSTRING);

    // D2D automatically handles high DPI settings
    SetProcessDPIAware();

    // Register Class
    MyRegisterClass(hinst);

    // Initialize Application
    if (!InitInstance(hinst, SW_SHOWMAXIMIZED)) 
    {
        wprintf(L"Failed to initialize application");
        success = FALSE;
    }
    
    if(success)
    {
        // Main message loop
        while (GetMessage(&msg, NULL, 0, 0))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    return success;
} 