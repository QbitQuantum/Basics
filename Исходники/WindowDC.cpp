int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
    HDC hDC1 = CreateIC(_T("DISPLAY"), NULL, NULL, NULL);
    HDC hDC2 = CreateDC(_T("DISPLAY"), NULL, NULL, NULL);

    BOOL r = Rectangle(hDC1, 10, 10, 20, 200);

    int rs = GetLastError();

    r = Rectangle(hDC2, 10, 10, 20, 200);

    rs = GetLastError();

    HWND hWnd = CreateWindow(_T("EDIT"), NULL,
                             WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
                             10, 10, 200, 100, GetDesktopWindow(),
                             NULL, hInstance, NULL);

    HWND hWnd1 = CreateWindow(_T("EDIT"), NULL, WS_VISIBLE | WS_CHILD | WS_BORDER,
                              5, 5, 20, 20, hWnd, NULL, hInstance, NULL);

    ShowWindow(hWnd, SW_SHOW);

    Test(hWnd, _T("Rectangular Window"));

    HRGN hRgn = CreateEllipticRgn(0, 0, 300, 300);

    SetWindowRgn(hWnd, hRgn, TRUE);

    Test(hWnd, _T("Elliptic Window"));

    DestroyWindow(hWnd);

    DeleteDC(hDC1);
    DeleteDC(hDC2);

    return 0;
}