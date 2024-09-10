static void _power_notification_thread() {
    // This uses a thread with its own window message pump to get power
    // notifications. If adb runs from a non-interactive service account, this
    // might not work (not sure). If that happens to not work, we could use
    // heavyweight WMI APIs to get power notifications. But for the common case
    // of a developer's interactive session, a window message pump is more
    // appropriate.
    D("Created power notification thread");
    adb_thread_setname("Power Notifier");

    // Window class names are process specific.
    static const WCHAR kPowerNotificationWindowClassName[] = L"PowerNotificationWindow";

    // Get the HINSTANCE corresponding to the module that _power_window_proc
    // is in (the main module).
    const HINSTANCE instance = GetModuleHandleW(nullptr);
    if (!instance) {
        // This is such a common API call that this should never fail.
        LOG(FATAL) << "GetModuleHandleW failed: "
                   << android::base::SystemErrorCodeToString(GetLastError());
    }

    WNDCLASSEXW wndclass;
    memset(&wndclass, 0, sizeof(wndclass));
    wndclass.cbSize = sizeof(wndclass);
    wndclass.lpfnWndProc = _power_window_proc;
    wndclass.hInstance = instance;
    wndclass.lpszClassName = kPowerNotificationWindowClassName;
    if (!RegisterClassExW(&wndclass)) {
        LOG(FATAL) << "RegisterClassExW failed: "
                   << android::base::SystemErrorCodeToString(GetLastError());
    }

    if (!CreateWindowExW(WS_EX_NOACTIVATE, kPowerNotificationWindowClassName,
                         L"ADB Power Notification Window", WS_POPUP, 0, 0, 0, 0, nullptr, nullptr,
                         instance, nullptr)) {
        LOG(FATAL) << "CreateWindowExW failed: "
                   << android::base::SystemErrorCodeToString(GetLastError());
    }

    MSG msg;
    while (GetMessageW(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    // GetMessageW() will return false if a quit message is posted. We don't
    // do that, but it might be possible for that to occur when logging off or
    // shutting down. Not a big deal since the whole process will be going away
    // soon anyway.
    D("Power notification thread exiting");
}