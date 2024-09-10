LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
    static HICON hIcon;
    static int cxIcon, cyIcon, cxClient, cyClient;
    HDC hdc;
    HINSTANCE hInstance;
    PAINTSTRUCT ps;
    int x, y;

    switch (message){
        case WM_CREATE:
            hInstance = ((LPCREATESTRUCT)lParam)->hInstance;
            hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON));
            cxIcon = GetSystemMetrics(SM_CXICON);
            cyIcon = GetSystemMetrics(SM_CYICON);
            return 0;

        case WM_SIZE:
            cxClient = LOWORD(lParam);
            cyClient = HIWORD(lParam);
            return 0;

        case WM_PAINT:
            hdc = BeginPaint(hwnd, &ps);
            for(y=0; y<cyClient; y+=cyIcon)for(x=0; x<cxClient; x+=cxIcon)
                DrawIcon(hdc, x, y, hIcon);
            EndPaint(hwnd, &ps);
            return 0;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}