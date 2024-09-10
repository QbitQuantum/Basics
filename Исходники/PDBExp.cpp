int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE, PTSTR, int nShowCmd)
{
    AtlInitCommonControls(ICC_WIN95_CLASSES);
    _Module.Init(NULL, hInstance);

    CMainFrame *frameWnd = new CMainFrame;
    if (!frameWnd->Create(NULL, NULL, PDBEXP_WNDCAPTION)) {
        delete frameWnd;
        return EXIT_FAILURE;
    }

    frameWnd->CenterWindow();
    frameWnd->ShowWindow(nShowCmd);

    MSG msg;
    HACCEL hAccTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR));
    while (GetMessage(&msg, NULL, 0, 0)) {
        if (0 == TranslateAccelerator(*frameWnd, hAccTable, &msg)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    _Module.Term();
    return (int)msg.wParam;
}