int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd){
    static wchar_t szAppName[] = L"Checker2";
    HWND hwnd;
    MSG msg;
    WNDCLASS wndcls;

    wndcls.cbClsExtra = 0;
    wndcls.cbWndExtra = 0;
    wndcls.hbrBackground = (HBRUSH)GetStockObject(DC_BRUSH);
    wndcls.hCursor = LoadCursor(NULL,IDC_ARROW);
    wndcls.hIcon = LoadIcon(NULL,IDI_APPLICATION);
    wndcls.hInstance = hInstance;
    wndcls.lpfnWndProc = WndProc;
    wndcls.lpszClassName = szAppName;
    wndcls.lpszMenuName = NULL;
    wndcls.style = CS_HREDRAW | CS_VREDRAW;

    if(!RegisterClassW(&wndcls)){
        MessageBoxW(NULL,L"This program requires Windows NT!",szAppName,MB_ICONERROR);
        return 0;
    }

    hwnd = CreateWindowW(szAppName,L"Checker2 Mouse Hit-Test Demo",WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,
        NULL,NULL,hInstance,NULL);

    ShowWindow(hwnd,nShowCmd);
    UpdateWindow(hwnd);

    while(GetMessage(&msg,NULL,0,0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    return msg.wParam;
}