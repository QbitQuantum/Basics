LRESULT WINAPI ScreenSaverProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    unsigned long ul;
    switch(uMsg)
    {
    case WM_CREATE:
        if (ss_init(hWnd) == 0)
            return -1;

        SetTimer(hWnd, 999, 0, NULL);
        break;

    case WM_DESTROY:
        KillTimer(hWnd, 999);
        ss_term();
        break;

    case WM_TIMER:
        KillTimer(hWnd, 999);
        ul = hack_draw(ss.dpy, ss.window, ss.closure);
        SetTimer(hWnd, 999, ul / 1000, NULL);
        break;

    default:
        return DefScreenSaverProc(hWnd, uMsg, wParam, lParam);
    }

    return 0;
}