static unsigned __stdcall
windowThreadFunction( LPVOID _lpParam )
{
    WindowThreadParam *lpParam = (WindowThreadParam *)_lpParam;

    // Actually create the window
    lpParam->hWnd = CreateWindowExA(dwExStyle,
                                    g_lpszClassName,
                                    lpParam->lpszWindowName,
                                    dwStyle,
                                    0, // x
                                    0, // y
                                    lpParam->nWidth,
                                    lpParam->nHeight,
                                    NULL, // hWndParent
                                    NULL, // hMenu
                                    NULL, // hInstance
                                    NULL); // lpParam

    // Notify parent thread that window has been created
    SetEvent(lpParam->hEvent);

    BOOL bRet;
    MSG msg;
    while ((bRet = GetMessage(&msg, NULL, 0, 0 )) != FALSE) {
        if (bRet == -1) {
            // handle the error and possibly exit
        } else {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    // Return the exit code
    return msg.wParam;
}