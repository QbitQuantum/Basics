bool SkOSWindow::makeFullscreen() {
    if (fFullscreen) {
        return true;
    }
    if (fHGLRC) {
        this->detachGL();
    }
    // This is hacked together from various sources on the web. It can certainly be improved and be
    // made more robust.

    // Save current window/resolution information. We do this in case we ever implement switching
    // back to windowed mode.
    fSavedWindowState.fZoomed = SkToBool(IsZoomed((HWND)fHWND));
    if (fSavedWindowState.fZoomed) {
        SendMessage((HWND)fHWND, WM_SYSCOMMAND, SC_RESTORE, 0);
    }
    fSavedWindowState.fStyle = GetWindowLong((HWND)fHWND, GWL_STYLE);
    fSavedWindowState.fExStyle = GetWindowLong((HWND)fHWND, GWL_EXSTYLE);
    GetWindowRect((HWND)fHWND, &fSavedWindowState.fRect);
    DEVMODE currScreenSettings;
    memset(&currScreenSettings,0,sizeof(currScreenSettings));
    currScreenSettings.dmSize = sizeof(currScreenSettings);
    EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &currScreenSettings);
    fSavedWindowState.fScreenWidth = currScreenSettings.dmPelsWidth;
    fSavedWindowState.fScreenHeight = currScreenSettings.dmPelsHeight;
    fSavedWindowState.fScreenBits = currScreenSettings.dmBitsPerPel;
    fSavedWindowState.fHWND = fHWND;

    // Try different sizes to find an allowed setting? Use ChangeDisplaySettingsEx?
    static const int kWidth = 1280;
    static const int kHeight = 1024;
    DEVMODE newScreenSettings;
    memset(&newScreenSettings, 0, sizeof(newScreenSettings));
    newScreenSettings.dmSize = sizeof(newScreenSettings);
    newScreenSettings.dmPelsWidth    = kWidth;
    newScreenSettings.dmPelsHeight   = kHeight;
    newScreenSettings.dmBitsPerPel   = 32;
    newScreenSettings.dmFields = DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;
    if (ChangeDisplaySettings(&newScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL) {
        return false;
    }
    RECT WindowRect;
    WindowRect.left = 0;
    WindowRect.right = kWidth;
    WindowRect.top = 0;
    WindowRect.bottom = kHeight;     
    ShowCursor(FALSE);
    AdjustWindowRectEx(&WindowRect, WS_POPUP, FALSE, WS_EX_APPWINDOW);
    HWND fsHWND = CreateWindowEx(
        WS_EX_APPWINDOW,
        fWinInit.fClass,
        NULL,
        WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
        0, 0, WindowRect.right-WindowRect.left, WindowRect.bottom-WindowRect.top,
        NULL,
        NULL,
        fWinInit.fInstance,
        NULL
    );
    if (!fsHWND) {
        return false;
    }
    // Hide the old window and set the entry in the global mapping for this SkOSWindow to the
    // new HWND.
    ShowWindow((HWND)fHWND, SW_HIDE);
    gHwndToOSWindowMap.remove(fHWND);
    fHWND = fsHWND;
    gHwndToOSWindowMap.set(fHWND, this);
    this->updateSize();

    fFullscreen = true;
    return true;
}