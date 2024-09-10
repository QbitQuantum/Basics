void Main_OnActivate(HWND hwnd, UINT state, HWND /* hwndActDeact */, BOOL /* fMinimized */)
{
    APPBARDATA abd;

    // Always send the activate message to the system
    abd.cbSize = sizeof(APPBARDATA);
    abd.hWnd = hwnd;
    abd.lParam = 0;
    SHAppBarMessage(ABM_ACTIVATE, &abd);

    // Now determine if we're getting or losing activation
    switch (state)
    {
    case WA_ACTIVE:
    case WA_CLICKACTIVE:
        // If we're gaining activation, make sure we're visible
        AppBar_UnHide(hwnd);
        KillTimer(hwnd, IDT_AUTOHIDE);
        break;

    case WA_INACTIVE:
        // If we're losing activation, check to see if we need to autohide.
        AppBar_Hide(hwnd);
        break;
    }
}