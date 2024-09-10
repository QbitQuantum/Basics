NOEXPORT int gui_loop() {
#ifdef _WIN32_WCE
    WNDCLASS wc;
#else
    WNDCLASSEX wc;
#endif
    MSG msg;
    LPTSTR classname=TEXT("stunnel_main_window_class");

    /* register the class */
#ifndef _WIN32_WCE
    wc.cbSize=sizeof wc;
#endif
    wc.style=CS_VREDRAW|CS_HREDRAW;
    wc.lpfnWndProc=window_proc;
    wc.cbClsExtra=wc.cbWndExtra=0;
    wc.hInstance=ghInst;
    wc.hIcon=LoadIcon(ghInst, MAKEINTRESOURCE(IDI_STUNNEL_MAIN));
    wc.hCursor=LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground=(HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName=NULL;
    wc.lpszClassName=classname;
#ifdef _WIN32_WCE
    RegisterClass(&wc);
#else
    /* load 16x16 icon */
    wc.hIconSm=LoadImage(ghInst, MAKEINTRESOURCE(IDI_STUNNEL_MAIN), IMAGE_ICON,
        GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON), 0);
    RegisterClassEx(&wc);
#endif

    /* create main window */
#ifdef _WIN32_WCE
    hwnd=CreateWindow(classname, win32_name, 0,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL, NULL, ghInst, NULL);
#else
    main_menu_handle=LoadMenu(ghInst, MAKEINTRESOURCE(IDM_MAINMENU));
    if(main_menu_handle && cmdline.service) {
        /* block unsafe operations in the service mode */
        EnableMenuItem(main_menu_handle, IDM_EDIT_CONFIG, MF_GRAYED);
        EnableMenuItem(main_menu_handle, IDM_SAVE_LOG, MF_GRAYED);
    }
    hwnd=CreateWindow(classname, win32_name, WS_TILEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL, main_menu_handle, ghInst, NULL);
#endif

    /* auto-reset, non-signaled events */
    main_initialized=CreateEvent(NULL, FALSE, FALSE, NULL);
    config_ready=CreateEvent(NULL, FALSE, FALSE, NULL);
    /* hwnd needs to be initialized before _beginthread() */
    _beginthread(daemon_thread, DEFAULT_STACK_SIZE, NULL);
    WaitForSingleObject(main_initialized, INFINITE);
    /* logging subsystem is now available */

    /* setup periodic event to trigger update_logs() */
    SetTimer(NULL, 0, 1000, timer_proc); /* run callback once per second */

    s_log(LOG_DEBUG, "GUI message loop initialized");
    for(;;)
        switch(GetMessage(&msg, NULL, 0, 0)) {
        case -1:
            ioerror("GetMessage");
            return 0;
        case 0:
            s_log(LOG_DEBUG, "GUI message loop terminated");
            return (int)msg.wParam;
        default:
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
}