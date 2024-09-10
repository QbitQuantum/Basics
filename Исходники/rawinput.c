void fs_ml_init_raw_input() {
    fs_log("fs_ml_init_raw_input\n");

    g_debug_keys = getenv("FS_DEBUG_INPUT") && \
            getenv("FS_DEBUG_INPUT")[0] == '1';

    //list_input_devices();
    init_key_mapping();

    SDL_SysWMinfo info;
    SDL_VERSION(&info.version); // this is important!
#if SDL_VERSION_ATLEAST(2, 0, 0)
    if (SDL_GetWindowWMInfo(g_fs_ml_window, &info)) {
#else
    if (SDL_GetWMInfo(&info)) {
#endif
#if SDL_VERSION_ATLEAST(2, 0, 0)
        g_window = info.info.win.window;
#else
        g_window = info.window;
#endif
        //g_hglrc = info.hglrc;
    }
 
    g_wndproc = (WNDPROC) GetWindowLongPtr(g_window, GWLP_WNDPROC);
    SetWindowLongPtr(g_window, GWLP_WNDPROC, (LONG_PTR) WndProc);
    fs_log("old window proc: %p new window proc: %p\n", g_wndproc, WndProc);

    RAWINPUTDEVICE rid;
    /*
    // mice
    rid.usUsagePage = 0x01;
    rid.usUsage = 0x02;
    rid.dwFlags = 0;
    //rid.dwFlags = RIDEV_INPUTSINK;
    //rid.dwFlags = RIDEV_NOLEGACY;
    rid.hwndTarget = hWnd;
    RegisterRawInputDevices(&rid, 1, sizeof(rid));
    */
    // keyboards
    rid.usUsagePage = 0x01;
    rid.usUsage = 0x06;
    rid.dwFlags = RIDEV_NOLEGACY | RIDEV_NOHOTKEYS;
    rid.hwndTarget = g_window;
    RegisterRawInputDevices(&rid, 1, sizeof(rid));

    g_keyboard_layout = GetKeyboardLayout(0);
}

#else

int libfsemu_ml_rawinput_dummy;