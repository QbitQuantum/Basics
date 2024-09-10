static BOOL register_raw_mouse( DWORD flags ) {
    RAWINPUTDEVICE rid;

    memset( &rid, 0, sizeof( rid ) );
    rid.usUsagePage = 0x01;
    rid.usUsage = 0x02;
    rid.dwFlags = flags;
    rid.hwndTarget = win.wnd;

    return RegisterRawInputDevices( &rid, 1, sizeof( rid ) );
}