static HWND CreateWND(HINSTANCE const hInstance,
                      std::string const &window_name)
{
    std::wstring const window_wname(window_name.begin(), window_name.end());

    HWND const wnd = CreateWindowExW(0,                      // dwExStyle
                                     GetWNDCLASS(hInstance), // lpClassName
                                     window_wname.c_str(),   // lpWindowName
                                     WS_OVERLAPPEDWINDOW,    // dwStyle
                                     CW_USEDEFAULT,          // X
                                     CW_USEDEFAULT,          // Y
                                     CW_USEDEFAULT,          // nWidth
                                     CW_USEDEFAULT,          // nHeight
                                     HWND_DESKTOP,           // hWndParent
                                     nullptr,                // hMenu
                                     hInstance,              // hInstance
                                     nullptr);               // lpParam
    return wnd;
}