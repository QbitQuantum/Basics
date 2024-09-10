int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
                   LPSTR lpCmdLine,   int nCmdShow)
{
    char szAppName[] = "Hello world";
    MSG msg;
    WNDCLASS wnd;
    ZWindow zwnd;
    
    wnd.cbClsExtra    = NULL;
    wnd.cbWndExtra    = NULL;
    wnd.hbrBackground    = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wnd.hCursor    = LoadCursor(NULL, IDC_ARROW);
    wnd.hIcon        = LoadIcon(NULL, IDI_APPLICATION);
    wnd.hInstance    = hInstance;
    wnd.lpfnWndProc    = zwnd.WndProc;
    wnd.lpszClassName    = szAppName;
    wnd.lpszMenuName    = NULL;
    wnd.style        = CS_HREDRAW | CS_VREDRAW;
    
    if (!RegisterClass(&wnd))
    {
        MessageBox(NULL, "Can not register window class", "Error", 
			MB_OK | MB_ICONINFORMATION);
        return -1;
    }
	
    g_pWnd = &zwnd;
    zwnd.Create(szAppName, "Hell world", hInstance);
    zwnd.ShowWindow(nCmdShow);
    zwnd.UpdateWindow();
	
    while (GetMessage(&msg, NULL, 0, 0))
    {
        DispatchMessage(&msg);
    }
    
    return msg.wParam;
}