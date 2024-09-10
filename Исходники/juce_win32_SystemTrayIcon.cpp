    Pimpl (SystemTrayIconComponent& owner_, HICON hicon, HWND hwnd)
        : owner (owner_),
          originalWndProc ((WNDPROC) GetWindowLongPtr (hwnd, GWLP_WNDPROC)),
          taskbarCreatedMessage (RegisterWindowMessage (TEXT ("TaskbarCreated")))
    {
        SetWindowLongPtr (hwnd, GWLP_WNDPROC, (LONG_PTR) hookedWndProc);

        zerostruct (iconData);
        iconData.cbSize = sizeof (iconData);
        iconData.hWnd = hwnd;
        iconData.uID = (UINT) (pointer_sized_int) hwnd;
        iconData.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
        iconData.uCallbackMessage = WM_TRAYNOTIFY;
        iconData.hIcon = hicon;

        notify (NIM_ADD);

        // In order to receive the "TaskbarCreated" message, we need to request that it's not filtered out.
        // (Need to load dynamically, as ChangeWindowMessageFilter is only available in Vista and later)
        typedef BOOL (WINAPI* ChangeWindowMessageFilterType) (UINT, DWORD);

        if (ChangeWindowMessageFilterType changeWindowMessageFilter
                = (ChangeWindowMessageFilterType) getUser32Function ("ChangeWindowMessageFilter"))
            changeWindowMessageFilter (taskbarCreatedMessage, 1 /* MSGFLT_ADD */);
    }