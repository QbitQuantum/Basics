void
resizeWindow(HWND hWnd, int width, int height) {
    RECT rClient;
    GetClientRect(hWnd, &rClient);
    if (width  == rClient.right  - rClient.left &&
        height == rClient.bottom - rClient.top) {
        return;
    }

    RECT rWindow;
    GetWindowRect(hWnd, &rWindow);
    width  += (rWindow.right  - rWindow.left) - rClient.right;
    height += (rWindow.bottom - rWindow.top)  - rClient.bottom;

    // SetWindowPos will hang if this ever happens.
    assert(GetCurrentThreadId() == GetWindowThreadProcessId(hWnd, NULL));

    SetWindowPos(hWnd, NULL, rWindow.left, rWindow.top, width, height, SWP_NOMOVE);
}