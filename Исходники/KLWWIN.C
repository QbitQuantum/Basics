static BOOL klw_make_window()
{
    RECT rect, clientRect;
    
    if (hWndKalView)
        return TRUE;
    
    hWndKalView = CreateWindow("STATIC", 
                               KppMakeMultiTitle("KALView Debugger",
                                                 selection),
                               WS_OVERLAPPEDWINDOW,
                               80, 40, sXPixels - 100, sYPixels - 60,
                               NULL, NULL, hInstKlwDll, NULL);
    KlwInfo.hWndKALView = hWndKalView;
    SetWindowLong(hWndKalView, GWL_WNDPROC, (DWORD) KlwWndProc);
    SetMenu(hWndKalView, LoadMenu(hInstKlwDll, "KalViewMenu"));
    
    GetWindowRect(hWndKalView, &rect);
    GetClientRect(hWndKalView, &clientRect);
    ClientToScreen(hWndKalView, (LPPOINT) &clientRect);
    bwidth = clientRect.left - rect.left;
    
    CreateEmAll(hWndKalView);

    return TRUE;    
}