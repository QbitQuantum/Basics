void VDAgent::input_desktop_message_loop()
{
    TCHAR desktop_name[MAX_PATH];
    HDESK hdesk;

    hdesk = OpenInputDesktop(0, FALSE, GENERIC_ALL);
    if (!hdesk) {
        vd_printf("OpenInputDesktop() failed: %lu", GetLastError());
        _running = false;
        return;
    }
    if (!SetThreadDesktop(hdesk)) {
        vd_printf("SetThreadDesktop failed %lu", GetLastError());
        _running = false;
        return;
    }
    if (GetUserObjectInformation(hdesk, UOI_NAME, desktop_name, sizeof(desktop_name), NULL)) {
        vd_printf("Desktop: %S", desktop_name);
    } else {
        vd_printf("GetUserObjectInformation failed %lu", GetLastError());
    }

    // loading the display settings for the current session's logged on user only
    // after 1) we receive logon event, and 2) the desktop switched from Winlogon
    if (_tcscmp(desktop_name, TEXT("Winlogon")) == 0) {
        _logon_desktop = true;
    } else {
        // first load after connection
        if (!_display_setting_initialized) {
            vd_printf("First display setting");
            _display_setting.load();
            _display_setting_initialized = true;
        } else if (_logon_occured && _logon_desktop) {
            vd_printf("LOGON display setting");
            _display_setting.load();
        }
        _logon_occured = false;
        _logon_desktop = false;
    }

    _hwnd = CreateWindow(VD_AGENT_WINCLASS_NAME, NULL, 0, 0, 0, 0, 0, NULL, NULL, NULL, NULL);
    if (!_hwnd) {
        vd_printf("CreateWindow() failed: %lu", GetLastError());
        _running = false;
        return;
    }
    if (!WTSRegisterSessionNotification(_hwnd, NOTIFY_FOR_ALL_SESSIONS)) {
        vd_printf("WTSRegisterSessionNotification() failed: %lu", GetLastError());
    }
    if (_system_version == SYS_VER_WIN_7_CLASS) {
        _add_clipboard_listener(_hwnd);
    } else {
        _hwnd_next_viewer = SetClipboardViewer(_hwnd);
    }
    while (_running && !_desktop_switch) {
        event_dispatcher(INFINITE, QS_ALLINPUT);
    }
    _desktop_switch = false;
    if (_pending_input) {
        KillTimer(_hwnd, VD_TIMER_ID);
        _pending_input = false;
    }
    if (_system_version == SYS_VER_WIN_7_CLASS) {
        _remove_clipboard_listener(_hwnd);
    } else {
        ChangeClipboardChain(_hwnd, _hwnd_next_viewer);
    }
    WTSUnRegisterSessionNotification(_hwnd);
    DestroyWindow(_hwnd);
    CloseDesktop(hdesk);
}