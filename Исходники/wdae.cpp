int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPWSTR /*lpCmdLine*/, int nCmdShow) {
    {
        INITCOMMONCONTROLSEX icc = INITCOMMONCONTROLSEX();
        icc.dwSize = sizeof icc;
        icc.dwICC = ICC_WIN95_CLASSES;
        InitCommonControlsEx(&icc);
    }

    std::experimental::optional<prev_instance_mutex> m;
    try {
        m = std::move(prev_instance_mutex(application_mutex));
    } catch (const windows_error& e) {
        explain(e);
        return 0;
    }
    if (*(m->prev_instance_exists())) {
        main_window_activate_prev_instance();
        return 0;
    }

    std::experimental::optional<com_manager> c;
    try {
        c = std::move(com_manager());
    } catch (const _com_error& e) {
        explain(e);
        return 0;
    }

    main_window_register(hInstance);
    main_window_create(hInstance, nCmdShow);

    BOOL r;
    MSG msg;
    while ((r = GetMessage(&msg, nullptr, 0, 0)) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    if (r == -1) {
        explain(L"GetMessage failed");
        return 0;
    }
    return msg.wParam;
}