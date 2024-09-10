LRESULT WINAPI ScreenSaverProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
    case WM_CREATE:
        if (ss_init(hWnd) == 0)
            return -1;

        SetTimer(hWnd, 999, hack_delay / 1000, NULL);
        break;

    case WM_DESTROY:
        KillTimer(hWnd, 999);
        ss_term();
        break;

    case WM_TIMER:
        hack_draw(&ss.modeinfo);
        break;

    default:
        return DefScreenSaverProc(hWnd, uMsg, wParam, lParam);
    }

    return 0;
}