/** @callback_method_impl{FNRTTHREAD,
 *      Thread that creates service a window the DIFx can destroy, thereby
 *      triggering process termination. }
 */
static DECLCALLBACK(int) DIFxKillableProcessThreadProc(RTTHREAD hThreadSelf, void *pvUser)
{
    RT_NOREF(hThreadSelf, pvUser);
    HINSTANCE hInstance = (HINSTANCE)GetModuleHandle(NULL);

    /* Register the Window Class. */
    WNDCLASSW WndCls;
    WndCls.style         = 0;
    WndCls.lpfnWndProc   = DIFxKillableWindowProc;
    WndCls.cbClsExtra    = 0;
    WndCls.cbWndExtra    = sizeof(void *);
    WndCls.hInstance     = hInstance;
    WndCls.hIcon         = NULL;
    WndCls.hCursor       = NULL;
    WndCls.hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 1);
    WndCls.lpszMenuName  = NULL;
    WndCls.lpszClassName = g_wszWndClassName;

    ATOM atomWindowClass = RegisterClassW(&WndCls);
    if (atomWindowClass != 0)
    {
        /* Create the window. */
        HWND hwnd = CreateWindowExW(WS_EX_TOOLWINDOW | WS_EX_TRANSPARENT | WS_EX_TOPMOST,
                                    g_wszWndClassName, g_wszWndClassName,
                                    WS_POPUPWINDOW,
                                    -200, -200, 100, 100, NULL, NULL, hInstance, NULL);
        if (hwnd)
        {
            SetWindowPos(hwnd, HWND_TOPMOST, -200, -200, 0, 0,
                         SWP_NOACTIVATE | SWP_HIDEWINDOW | SWP_NOCOPYBITS | SWP_NOREDRAW | SWP_NOSIZE);

            MSG msg;
            while (GetMessage(&msg, NULL, 0, 0))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }

            DestroyWindow(hwnd);
        }

        UnregisterClassW(g_wszWndClassName, hInstance);

        if (hwnd && g_fExitProcessOnQuit)
            exit(0);
    }
    return 0;
}