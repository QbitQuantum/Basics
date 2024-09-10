LRESULT msg_handler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static UINT taskbarRestartMsg; /* static here means value is kept across multiple calls to this func */

    switch(msg) {
    case WM_CREATE:
        taskbarRestartMsg = RegisterWindowMessage("TaskbarCreated");
        break;

    case WM_TIMER:
#if 0
        KillTimer(hWnd, timerID);
        call_caml_systray_clicked(SYSTRAY_LBUTTONCLK);
#endif
        break;

    case WM_DESTROY:
        break;

    case WM_TRAYMESSAGE:
#if 0
        switch (lParam) {
        case WM_RBUTTONUP:
            call_caml_systray_clicked(SYSTRAY_RBUTTONCLK);
            break;

        case WM_LBUTTONDBLCLK:
            KillTimer(hWnd, timerID);
            call_caml_systray_clicked(SYSTRAY_LBUTTONDBLCLK);
            break;

        case WM_LBUTTONDOWN:
            SetTimer(hWnd, timerID, GetDoubleClickTime(), NULL);
            break;

        }
#endif
    default:
        if (msg == taskbarRestartMsg) {
            /* explorer crashed and left us hanging...
               This will put the systray icon back in it's place, when it restarts */
            Shell_NotifyIcon(NIM_ADD,&nid);
        }
        break;

    }/* end switch */

    return DefWindowProc(hWnd, msg, wParam, lParam);

}