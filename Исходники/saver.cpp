LRESULT WINAPI ScreenSaverProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HDC hDC;
    static HGLRC hRC;
    static RECT rect;

    switch (message)
    {
    case WM_CREATE:
        GetClientRect(hWnd, &rect);
        Width = rect.right;
        Height = rect.bottom;

        InitGL(hWnd, hDC, hRC);
        InitAnim();

        SetTimer(hWnd, TIMER, 10, NULL);
        return 0;

    case WM_DESTROY:
        KillTimer(hWnd, TIMER);
        DestroyAnim();
        CloseGL(hWnd, hDC, hRC);
        return 0;

    case WM_TIMER:
        DoAnim();
        SwapBuffers(hDC);
        return 0;

    }

    return DefScreenSaverProc(hWnd, message, wParam, lParam);
}