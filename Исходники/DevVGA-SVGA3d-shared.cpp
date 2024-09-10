/**
 * The async window handling thread
 *
 * @returns VBox status code.
 * @param   hThreadSelf     This thread.
 * @param   pvUser          Request sempahore handle.
 */
DECLCALLBACK(int) vmsvga3dWindowThread(RTTHREAD hThreadSelf, void *pvUser)
{
    RT_NOREF(hThreadSelf);
    RTSEMEVENT      WndRequestSem = (RTSEMEVENT)pvUser;
    WNDCLASSEX      wc;

    /* Register our own window class. */
    wc.cbSize           = sizeof(wc);
    wc.style            = CS_OWNDC;
    wc.lpfnWndProc      = (WNDPROC) vmsvga3dWndProc;
    wc.cbClsExtra       = 0;
    wc.cbWndExtra       = 0;
    wc.hInstance        = GetModuleHandle("VBoxDD.dll");    /** @todo hardcoded name.. */
    wc.hIcon            = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor          = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground    = NULL;
    wc.lpszMenuName     = NULL;
    wc.lpszClassName    = VMSVGA3D_WNDCLASSNAME;
    wc.hIconSm          = NULL;

    if (!RegisterClassEx(&wc))
    {
        Log(("RegisterClass failed with %x\n", GetLastError()));
        return VERR_INTERNAL_ERROR;
    }

    LogFlow(("vmsvga3dWindowThread: started loop\n"));
    while (true)
    {
        MSG msg;

        if (GetMessage(&msg, 0, 0, 0))
        {
            if (msg.message == WM_VMSVGA3D_EXIT)
            {
                /* Signal to the caller that we're done. */
                RTSemEventSignal(WndRequestSem);
                break;
            }

            if (msg.message == WM_VMSVGA3D_WAKEUP)
            {
                continue;
            }
            if (msg.message == WM_VMSVGA3D_CREATEWINDOW)
            {
                HWND          *pHwnd = (HWND *)msg.wParam;
                LPCREATESTRUCT pCS = (LPCREATESTRUCT) msg.lParam;

#ifdef DEBUG_GFX_WINDOW
                RECT rectClient;

                rectClient.left     = 0;
                rectClient.top      = 0;
                rectClient.right    = pCS->cx;
                rectClient.bottom   = pCS->cy;
                AdjustWindowRectEx(&rectClient, WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_VISIBLE | WS_CAPTION, FALSE, WS_EX_NOACTIVATE | WS_EX_NOPARENTNOTIFY | WS_EX_TRANSPARENT);
                pCS->cx = rectClient.right - rectClient.left;
                pCS->cy = rectClient.bottom - rectClient.top;
#endif
                *pHwnd = CreateWindowEx(pCS->dwExStyle,
                                        VMSVGA3D_WNDCLASSNAME,
                                        pCS->lpszName,
                                        pCS->style,
#ifdef DEBUG_GFX_WINDOW
                                        0,
                                        0,
#else
                                        pCS->x,
                                        pCS->y,
#endif
                                        pCS->cx,
                                        pCS->cy,
#ifdef DEBUG_GFX_WINDOW
                                        0,
#else
                                        pCS->hwndParent,
#endif
                                        pCS->hMenu,
                                        pCS->hInstance,
                                        NULL);
                AssertMsg(*pHwnd, ("CreateWindowEx %x %s %s %x (%d,%d)(%d,%d), %x %x %x error=%x\n", pCS->dwExStyle, pCS->lpszName, VMSVGA3D_WNDCLASSNAME, pCS->style, pCS->x,
                                    pCS->y, pCS->cx, pCS->cy,pCS->hwndParent, pCS->hMenu, pCS->hInstance, GetLastError()));

                /* Signal to the caller that we're done. */
                RTSemEventSignal(WndRequestSem);
                continue;
            }
            if (msg.message == WM_VMSVGA3D_DESTROYWINDOW)
            {
                BOOL fRc = DestroyWindow((HWND)msg.wParam);
                Assert(fRc); NOREF(fRc);
                /* Signal to the caller that we're done. */
                RTSemEventSignal(WndRequestSem);
                continue;
            }
            if (msg.message == WM_VMSVGA3D_RESIZEWINDOW)
            {
                HWND hwnd = (HWND)msg.wParam;
                LPCREATESTRUCT pCS = (LPCREATESTRUCT) msg.lParam;

#ifdef DEBUG_GFX_WINDOW
                RECT rectClient;

                rectClient.left     = 0;
                rectClient.top      = 0;
                rectClient.right    = pCS->cx;
                rectClient.bottom   = pCS->cy;
                AdjustWindowRectEx(&rectClient, WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_VISIBLE | WS_CAPTION, FALSE, WS_EX_NOACTIVATE | WS_EX_NOPARENTNOTIFY | WS_EX_TRANSPARENT);
                pCS->cx = rectClient.right - rectClient.left;
                pCS->cy = rectClient.bottom - rectClient.top;
#endif
                BOOL fRc = SetWindowPos(hwnd, 0, pCS->x, pCS->y, pCS->cx, pCS->cy, SWP_NOZORDER | SWP_NOMOVE);
                Assert(fRc); NOREF(fRc);

                /* Signal to the caller that we're done. */
                RTSemEventSignal(WndRequestSem);
                continue;
            }

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            Log(("GetMessage failed with %x\n", GetLastError()));
            break;
        }
    }

    Log(("vmsvga3dWindowThread: end loop\n"));
    return VINF_SUCCESS;
}