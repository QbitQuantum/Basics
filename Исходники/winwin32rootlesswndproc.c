LRESULT CALLBACK
winMWExtWMWindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    WindowPtr pWin = NULL;
    win32RootlessWindowPtr pRLWinPriv = NULL;
    ScreenPtr pScreen = NULL;
    winPrivScreenPtr pScreenPriv = NULL;
    winScreenInfo *pScreenInfo = NULL;
    HWND hwndScreen = NULL;
    POINT ptMouse;
    static Bool s_fTracking = FALSE;
    HDC hdcUpdate;
    PAINTSTRUCT ps;
    LPWINDOWPOS pWinPos = NULL;
    RECT rcClient;
    winWMMessageRec wmMsg;
    Bool fWMMsgInitialized = FALSE;

    /* Check if the Windows window property for our X window pointer is valid */
    if ((pRLWinPriv =
         (win32RootlessWindowPtr) GetProp(hwnd, WIN_WINDOW_PROP)) != NULL) {
        pWin = pRLWinPriv->pFrame->win;
        pScreen = pWin->drawable.pScreen;
        if (pScreen)
            pScreenPriv = winGetScreenPriv(pScreen);
        if (pScreenPriv)
            pScreenInfo = pScreenPriv->pScreenInfo;
        if (pScreenPriv)
            hwndScreen = pScreenPriv->hwndScreen;

        wmMsg.msg = 0;
        wmMsg.hwndWindow = hwnd;
        wmMsg.iWindow = (Window) pWin->drawable.id;

        wmMsg.iX = pRLWinPriv->pFrame->x;
        wmMsg.iY = pRLWinPriv->pFrame->y;
        wmMsg.iWidth = pRLWinPriv->pFrame->width;
        wmMsg.iHeight = pRLWinPriv->pFrame->height;

        fWMMsgInitialized = TRUE;
#if CYGDEBUG
        winDebugWin32Message("winMWExtWMWindowProc", hwnd, message, wParam,
                             lParam);

        winDebug("\thWnd %08X\n", hwnd);
        winDebug("\tpScreenPriv %08X\n", pScreenPriv);
        winDebug("\tpScreenInfo %08X\n", pScreenInfo);
        winDebug("\thwndScreen %08X\n", hwndScreen);
        winDebug("winMWExtWMWindowProc (%08x) %08x %08x %08x\n",
                 pRLWinPriv, message, wParam, lParam);
#endif
    }
    /* Branch on message type */
    switch (message) {
    case WM_CREATE:
#if CYGMULTIWINDOW_DEBUG
        winDebug("winMWExtWMWindowProc - WM_CREATE\n");
#endif
        /* */
        SetProp(hwnd,
                WIN_WINDOW_PROP,
                (HANDLE) ((LPCREATESTRUCT) lParam)->lpCreateParams);
        return 0;

    case WM_CLOSE:
#if CYGMULTIWINDOW_DEBUG
        winDebug("winMWExtWMWindowProc - WM_CLOSE %d\n", pRLWinPriv->fClose);
#endif
        /* Tell window-manager to close window */
        if (pRLWinPriv->fClose) {
            DestroyWindow(hwnd);
        }
        else {
            if (winIsInternalWMRunning(pScreenInfo)) {
                /* Tell our Window Manager thread to kill the window */
                wmMsg.msg = WM_WM_KILL;
                if (fWMMsgInitialized)
                    winSendMessageToWM(pScreenPriv->pWMInfo, &wmMsg);
            }
            winWindowsWMSendEvent(WindowsWMControllerNotify,
                                  WindowsWMControllerNotifyMask,
                                  1,
                                  WindowsWMCloseWindow,
                                  pWin->drawable.id, 0, 0, 0, 0);
        }
        return 0;

    case WM_DESTROY:
#if CYGMULTIWINDOW_DEBUG
        winDebug("winMWExtWMWindowProc - WM_DESTROY\n");
#endif
        /* Free the shaodw DC; which allows the bitmap to be freed */
        DeleteDC(pRLWinPriv->hdcShadow);
        pRLWinPriv->hdcShadow = NULL;

        /* Free the shadow bitmap */
        DeleteObject(pRLWinPriv->hbmpShadow);
        pRLWinPriv->hbmpShadow = NULL;

        /* Free the screen DC */
        ReleaseDC(pRLWinPriv->hWnd, pRLWinPriv->hdcScreen);
        pRLWinPriv->hdcScreen = NULL;

        /* Free shadow buffer info header */
        free(pRLWinPriv->pbmihShadow);
        pRLWinPriv->pbmihShadow = NULL;

        pRLWinPriv->fResized = FALSE;
        pRLWinPriv->pfb = NULL;
        free(pRLWinPriv);
        RemoveProp(hwnd, WIN_WINDOW_PROP);
        break;

    case WM_MOUSEMOVE:
#if CYGMULTIWINDOW_DEBUG && 0
        winDebug("winMWExtWMWindowProc - WM_MOUSEMOVE\n");
#endif
        /* Unpack the client area mouse coordinates */
        ptMouse.x = GET_X_LPARAM(lParam);
        ptMouse.y = GET_Y_LPARAM(lParam);

        /* Translate the client area mouse coordinates to screen coordinates */
        ClientToScreen(hwnd, &ptMouse);

        /* Screen Coords from (-X, -Y) -> Root Window (0, 0) */
        ptMouse.x -= GetSystemMetrics(SM_XVIRTUALSCREEN);
        ptMouse.y -= GetSystemMetrics(SM_YVIRTUALSCREEN);

        /* We can't do anything without privates */
        if (pScreenPriv == NULL || pScreenInfo->fIgnoreInput)
            break;

        /* Has the mouse pointer crossed screens? */
        if (pScreen != miPointerGetScreen(inputInfo.pointer))
             miPointerSetScreen(inputInfo.pointer, pScreenInfo->dwScreen,
                                ptMouse.x - pScreenInfo->dwXOffset,
                                ptMouse.y - pScreenInfo->dwYOffset);

        /* Are we tracking yet? */
        if (!s_fTracking) {
            TRACKMOUSEEVENT tme;

            /* Setup data structure */
            ZeroMemory(&tme, sizeof(tme));
            tme.cbSize = sizeof(tme);
            tme.dwFlags = TME_LEAVE;
            tme.hwndTrack = hwnd;

            /* Call the tracking function */
            if (!TrackMouseEvent(&tme))
                ErrorF("winMWExtWMWindowProc - TrackMouseEvent failed\n");

            /* Flag that we are tracking now */
            s_fTracking = TRUE;
        }

        /* Kill the timer used to poll mouse events */
        if (g_uipMousePollingTimerID != 0) {
            KillTimer(pScreenPriv->hwndScreen, WIN_POLLING_MOUSE_TIMER_ID);
            g_uipMousePollingTimerID = 0;
        }

        /* Deliver absolute cursor position to X Server */
        winEnqueueMotion(ptMouse.x - pScreenInfo->dwXOffset,
                         ptMouse.y - pScreenInfo->dwYOffset);

        return 0;

    case WM_NCMOUSEMOVE:
#if CYGMULTIWINDOW_DEBUG && 0
        winDebug("winMWExtWMWindowProc - WM_NCMOUSEMOVE\n");
#endif
        /*
         * We break instead of returning 0 since we need to call
         * DefWindowProc to get the mouse cursor changes
         * and min/max/close button highlighting in Windows XP.
         * The Platform SDK says that you should return 0 if you
         * process this message, but it fails to mention that you
         * will give up any default functionality if you do return 0.
         */

        /* We can't do anything without privates */
        if (pScreenPriv == NULL || pScreenInfo->fIgnoreInput)
            break;

        /*
         * Timer to poll mouse events.  This is needed to make
         * programs like xeyes follow the mouse properly.
         */
        if (g_uipMousePollingTimerID == 0)
            g_uipMousePollingTimerID = SetTimer(pScreenPriv->hwndScreen,
                                                WIN_POLLING_MOUSE_TIMER_ID,
                                                MOUSE_POLLING_INTERVAL, NULL);
        break;

    case WM_MOUSELEAVE:
#if CYGMULTIWINDOW_DEBUG
        winDebug("winMWExtWMWindowProc - WM_MOUSELEAVE\n");
#endif
        /* Mouse has left our client area */

        /* Flag that we are no longer tracking */
        s_fTracking = FALSE;

        /*
         * Timer to poll mouse events.  This is needed to make
         * programs like xeyes follow the mouse properly.
         */
        if (g_uipMousePollingTimerID == 0)
            g_uipMousePollingTimerID = SetTimer(pScreenPriv->hwndScreen,
                                                WIN_POLLING_MOUSE_TIMER_ID,
                                                MOUSE_POLLING_INTERVAL, NULL);
        return 0;

    case WM_LBUTTONDBLCLK:
    case WM_LBUTTONDOWN:
#if CYGMULTIWINDOW_DEBUG
        winDebug("winMWExtWMWindowProc - WM_LBUTTONDBLCLK\n");
#endif
        if (pScreenPriv == NULL || pScreenInfo->fIgnoreInput)
            break;
        SetCapture(hwnd);
        return winMouseButtonsHandle(pScreen, ButtonPress, Button1, wParam);

    case WM_LBUTTONUP:
#if CYGMULTIWINDOW_DEBUG
        winDebug("winMWExtWMWindowProc - WM_LBUTTONUP\n");
#endif
        if (pScreenPriv == NULL || pScreenInfo->fIgnoreInput)
            break;
        ReleaseCapture();
        return winMouseButtonsHandle(pScreen, ButtonRelease, Button1, wParam);

    case WM_MBUTTONDBLCLK:
    case WM_MBUTTONDOWN:
#if CYGMULTIWINDOW_DEBUG
        winDebug("winMWExtWMWindowProc - WM_MBUTTONDBLCLK\n");
#endif
        if (pScreenPriv == NULL || pScreenInfo->fIgnoreInput)
            break;
        SetCapture(hwnd);
        return winMouseButtonsHandle(pScreen, ButtonPress, Button2, wParam);

    case WM_MBUTTONUP:
#if CYGMULTIWINDOW_DEBUG
        winDebug("winMWExtWMWindowProc - WM_MBUTTONUP\n");
#endif
        if (pScreenPriv == NULL || pScreenInfo->fIgnoreInput)
            break;
        ReleaseCapture();
        return winMouseButtonsHandle(pScreen, ButtonRelease, Button2, wParam);

    case WM_RBUTTONDBLCLK:
    case WM_RBUTTONDOWN:
#if CYGMULTIWINDOW_DEBUG
        winDebug("winMWExtWMWindowProc - WM_RBUTTONDBLCLK\n");
#endif
        if (pScreenPriv == NULL || pScreenInfo->fIgnoreInput)
            break;
        SetCapture(hwnd);
        return winMouseButtonsHandle(pScreen, ButtonPress, Button3, wParam);

    case WM_RBUTTONUP:
#if CYGMULTIWINDOW_DEBUG
        winDebug("winMWExtWMWindowProc - WM_RBUTTONUP\n");
#endif
        if (pScreenPriv == NULL || pScreenInfo->fIgnoreInput)
            break;
        ReleaseCapture();
        return winMouseButtonsHandle(pScreen, ButtonRelease, Button3, wParam);

    case WM_XBUTTONDBLCLK:
    case WM_XBUTTONDOWN:
        if (pScreenPriv == NULL || pScreenInfo->fIgnoreInput)
            break;
        SetCapture(hwnd);
        return winMouseButtonsHandle(pScreen, ButtonPress, HIWORD(wParam) + 5,
                                     wParam);
    case WM_XBUTTONUP:
        if (pScreenPriv == NULL || pScreenInfo->fIgnoreInput)
            break;
        ReleaseCapture();
        return winMouseButtonsHandle(pScreen, ButtonRelease, HIWORD(wParam) + 5,
                                     wParam);

    case WM_MOUSEWHEEL:
#if CYGMULTIWINDOW_DEBUG
        winDebug("winMWExtWMWindowProc - WM_MOUSEWHEEL\n");
#endif

        /* Pass the message to the root window */
        SendMessage(hwndScreen, message, wParam, lParam);
        return 0;

    case WM_MOUSEACTIVATE:
#if CYGMULTIWINDOW_DEBUG
        winDebug("winMWExtWMWindowProc - WM_MOUSEACTIVATE\n");
#endif
#if 1
        /* Check if this window needs to be made active when clicked */
        if (winIsInternalWMRunning(pScreenInfo) && pWin->overrideRedirect) {
#if CYGMULTIWINDOW_DEBUG
            winDebug("winMWExtWMWindowProc - WM_MOUSEACTIVATE - "
                     "MA_NOACTIVATE\n");
#endif

            /* */
            return MA_NOACTIVATE;
        }
#endif
        if (!winIsInternalWMRunning(pScreenInfo) && !IsMouseActive(pWin))
            return MA_NOACTIVATE;

        break;

    case WM_KILLFOCUS:
        /* Pop any pressed keys since we are losing keyboard focus */
        winKeybdReleaseKeys();
        return 0;

    case WM_SYSDEADCHAR:
    case WM_DEADCHAR:
        /*
         * NOTE: We do nothing with WM_*CHAR messages,
         * nor does the root window, so we can just toss these messages.
         */
        return 0;

    case WM_SYSKEYDOWN:
    case WM_KEYDOWN:
#if CYGMULTIWINDOW_DEBUG
        winDebug("winMWExtWMWindowProc - WM_*KEYDOWN\n");
#endif

        /*
         * Don't pass Alt-F4 key combo to root window,
         * let Windows translate to WM_CLOSE and close this top-level window.
         *
         * NOTE: We purposely don't check the fUseWinKillKey setting because
         * it should only apply to the key handling for the root window,
         * not for top-level window-manager windows.
         *
         * ALSO NOTE: We do pass Ctrl-Alt-Backspace to the root window
         * because that is a key combo that no X app should be expecting to
         * receive, since it has historically been used to shutdown the X server.
         * Passing Ctrl-Alt-Backspace to the root window preserves that
         * behavior, assuming that -unixkill has been passed as a parameter.
         */
        if (wParam == VK_F4 && (GetKeyState(VK_MENU) & 0x8000))
            break;

        /* Pass the message to the root window */
        SendMessage(hwndScreen, message, wParam, lParam);
        return 0;

    case WM_SYSKEYUP:
    case WM_KEYUP:

#if CYGMULTIWINDOW_DEBUG
        winDebug("winMWExtWMWindowProc - WM_*KEYUP\n");
#endif

        /* Pass the message to the root window */
        SendMessage(hwndScreen, message, wParam, lParam);
        return 0;

    case WM_HOTKEY:
#if CYGMULTIWINDOW_DEBUG
        winDebug("winMWExtWMWindowProc - WM_HOTKEY\n");
#endif

        /* Pass the message to the root window */
        SendMessage(hwndScreen, message, wParam, lParam);
        return 0;

    case WM_ERASEBKGND:
#if CYGDEBUG
        winDebug("winMWExtWMWindowProc - WM_ERASEBKGND\n");
#endif
        /*
         * Pretend that we did erase the background but we don't care,
         * since we repaint the entire region anyhow
         * This avoids some flickering when resizing.
         */
        return TRUE;

    case WM_PAINT:

        /* BeginPaint gives us an hdc that clips to the invalidated region */
        hdcUpdate = BeginPaint(hwnd, &ps);

        /* Try to copy from the shadow buffer */
        if (!BitBlt(hdcUpdate,
                    ps.rcPaint.left, ps.rcPaint.top,
                    ps.rcPaint.right - ps.rcPaint.left,
                    ps.rcPaint.bottom - ps.rcPaint.top,
                    pRLWinPriv->hdcShadow,
                    ps.rcPaint.left, ps.rcPaint.top, SRCCOPY)) {
            LPVOID lpMsgBuf;

            /* Display a fancy error message */
            FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
                          FORMAT_MESSAGE_FROM_SYSTEM |
                          FORMAT_MESSAGE_IGNORE_INSERTS,
                          NULL,
                          GetLastError(),
                          MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                          (LPTSTR) &lpMsgBuf, 0, NULL);

            ErrorF("winMWExtWMWindowProc - BitBlt failed: %s\n",
                   (LPSTR) lpMsgBuf);
            LocalFree(lpMsgBuf);
        }

        /* EndPaint frees the DC */
        EndPaint(hwnd, &ps);
        break;

    case WM_ACTIVATE:
#if CYGMULTIWINDOW_DEBUG
        winDebug("winMWExtWMWindowProc - WM_ACTIVATE\n");
#endif
        if (LOWORD(wParam) != WA_INACTIVE) {
            if (winIsInternalWMRunning(pScreenInfo)) {
#if 0
                /* Raise the window to the top in Z order */
                wmMsg.msg = WM_WM_RAISE;
                if (fWMMsgInitialized)
                    winSendMessageToWM(pScreenPriv->pWMInfo, &wmMsg);
#endif
                /* Tell our Window Manager thread to activate the window */
                wmMsg.msg = WM_WM_ACTIVATE;
                if (fWMMsgInitialized)
                    if (!pWin || !pWin->overrideRedirect)       /* for OOo menus */
                        winSendMessageToWM(pScreenPriv->pWMInfo, &wmMsg);
            }
            winWindowsWMSendEvent(WindowsWMControllerNotify,
                                  WindowsWMControllerNotifyMask,
                                  1,
                                  WindowsWMActivateWindow,
                                  pWin->drawable.id, 0, 0, 0, 0);
        }
        return 0;

#if 1
    case WM_WINDOWPOSCHANGING:
        pWinPos = (LPWINDOWPOS) lParam;
        if (!(pWinPos->flags & SWP_NOZORDER)) {
            if (pRLWinPriv->fRestackingNow || pScreenPriv->fRestacking) {
#if CYGMULTIWINDOW_DEBUG
                winDebug("Win %08x is now restacking.\n",
                         (unsigned int) pRLWinPriv);
#endif
                break;
            }

            if (winIsInternalWMRunning(pScreenInfo) || IsRaiseOnClick(pWin)) {
#if CYGMULTIWINDOW_DEBUG
                winDebug("Win %08x has WINDOWSWM_RAISE_ON_CLICK.\n",
                         (unsigned int) pRLWinPriv);
#endif
                break;
            }

#if CYGMULTIWINDOW_DEBUG
            winDebug("Win %08x forbid to change z order (%08x).\n",
                     (unsigned int) pRLWinPriv,
                     (unsigned int) pWinPos->hwndInsertAfter);
#endif
            pWinPos->flags |= SWP_NOZORDER;
        }
        break;
#endif

    case WM_MOVE:
#if CYGMULTIWINDOW_DEBUG
        winDebug("winMWExtWMWindowProc - WM_MOVE - %d ms\n",
                 (unsigned int) GetTickCount());
#endif
        if (g_fNoConfigureWindow)
            break;
#if 0
        /* Bail if Windows window is not actually moving */
        if (pRLWinPriv->dwX == (short) LOWORD(lParam)
            && pRLWinPriv->dwY == (short) HIWORD(lParam))
            break;

        /* Also bail if we're maximizing, we'll do the whole thing in WM_SIZE */
        {
            WINDOWPLACEMENT windPlace;

            windPlace.length = sizeof(WINDOWPLACEMENT);

            /* Get current window placement */
            GetWindowPlacement(hwnd, &windPlace);

            /* Bail if maximizing */
            if (windPlace.showCmd == SW_MAXIMIZE
                || windPlace.showCmd == SW_SHOWMAXIMIZED)
                break;
        }
#endif

#if CYGMULTIWINDOW_DEBUG
        winDebug("\t(%d, %d)\n", (short) LOWORD(lParam),
                 (short) HIWORD(lParam));
#endif
        if (!pRLWinPriv->fMovingOrSizing) {
            if (winIsInternalWMRunning(pScreenInfo))
                winAdjustXWindow(pWin, hwnd);

            winMWExtWMMoveXWindow(pWin, (LOWORD(lParam) - wBorderWidth(pWin)
                                         - GetSystemMetrics(SM_XVIRTUALSCREEN)),
                                  (HIWORD(lParam) - wBorderWidth(pWin)
                                   - GetSystemMetrics(SM_YVIRTUALSCREEN)));
        }
        return 0;

    case WM_SHOWWINDOW:
#if CYGMULTIWINDOW_DEBUG || TRUE
        winDebug("winMWExtWMWindowProc - WM_SHOWWINDOW - %d ms\n",
                 (unsigned int) GetTickCount());
#endif
        /* Bail out if the window is being hidden */
        if (!wParam)
            return 0;

        if (!pScreenInfo->fInternalWM)  //XXXX
            return 0;

        winMWExtWMUpdateWindowDecoration(pRLWinPriv, pScreenInfo);

        if (winIsInternalWMRunning(pScreenInfo)) {
#if CYGMULTIWINDOW_DEBUG || TRUE
            winDebug("\tMapWindow\n");
#endif
            /* Tell X to map the window */
            MapWindow(pWin, wClient(pWin));

            if (!pRLWinPriv->pFrame->win->overrideRedirect)
                /* Bring the Windows window to the foreground */
                SetForegroundWindow(hwnd);

            /* Setup the Window Manager message */
            wmMsg.msg = WM_WM_MAP;
            wmMsg.iWidth = pRLWinPriv->pFrame->width;
            wmMsg.iHeight = pRLWinPriv->pFrame->height;

            /* Tell our Window Manager thread to map the window */
            if (fWMMsgInitialized)
                winSendMessageToWM(pScreenPriv->pWMInfo, &wmMsg);
        }
        break;

    case WM_SIZING:
        /* Need to legalize the size according to WM_NORMAL_HINTS */
        /* for applications like xterm */
        return ValidateSizing(hwnd, pWin, wParam, lParam);

    case WM_WINDOWPOSCHANGED:
    {
        pWinPos = (LPWINDOWPOS) lParam;
#if CYGMULTIWINDOW_DEBUG
        winDebug("winMWExtWMWindowProc - WM_WINDOWPOSCHANGED\n");
        winDebug("\tflags: %s%s%s%s%s%s%s%s%s%s%s%s\n",
                 (pWinPos->flags & SWP_DRAWFRAME) ? "SWP_DRAWFRAME " : "",
                 (pWinPos->flags & SWP_FRAMECHANGED) ? "SWP_FRAMECHANGED " : "",
                 (pWinPos->flags & SWP_HIDEWINDOW) ? "SWP_HIDEWINDOW " : "",
                 (pWinPos->flags & SWP_NOACTIVATE) ? "SWP_NOACTIVATE " : "",
                 (pWinPos->flags & SWP_NOCOPYBITS) ? "SWP_NOCOPYBITS " : "",
                 (pWinPos->flags & SWP_NOMOVE) ? "SWP_NOMOVE " : "",
                 (pWinPos->
                  flags & SWP_NOOWNERZORDER) ? "SWP_NOOWNERZORDER " : "",
                 (pWinPos->flags & SWP_NOSIZE) ? "SWP_NOSIZE " : "",
                 (pWinPos->flags & SWP_NOREDRAW) ? "SWP_NOREDRAW " : "",
                 (pWinPos->
                  flags & SWP_NOSENDCHANGING) ? "SWP_NOSENDCHANGING " : "",
                 (pWinPos->flags & SWP_NOZORDER) ? "SWP_NOZORDER " : "",
                 (pWinPos->flags & SWP_SHOWWINDOW) ? "SWP_SHOWWINDOW " : "");
        winDebug("\tno_configure: %s\n", (g_fNoConfigureWindow ? "Yes" : "No"));
        winDebug("\textend: (%d, %d, %d, %d)\n",
                 pWinPos->x, pWinPos->y, pWinPos->cx, pWinPos->cy);

#endif
        if (pWinPos->flags & SWP_HIDEWINDOW)
            break;

        /* Reorder if window z order was changed */
        if ((pScreenPriv != NULL)
            && !(pWinPos->flags & SWP_NOZORDER)
            && !(pWinPos->flags & SWP_SHOWWINDOW)
            && winIsInternalWMRunning(pScreenInfo)) {
#if CYGMULTIWINDOW_DEBUG
            winDebug("\twindow z order was changed\n");
#endif
            if (pWinPos->hwndInsertAfter == HWND_TOP
                || pWinPos->hwndInsertAfter == HWND_TOPMOST
                || pWinPos->hwndInsertAfter == HWND_NOTOPMOST) {
#if CYGMULTIWINDOW_DEBUG
                winDebug("\traise to top\n");
#endif
                /* Raise the window to the top in Z order */
                wmMsg.msg = WM_WM_RAISE;
                if (fWMMsgInitialized)
                    winSendMessageToWM(pScreenPriv->pWMInfo, &wmMsg);
            }
#if 1
            else if (pWinPos->hwndInsertAfter == HWND_BOTTOM) {
            }
            else {
                /* Check if this window is top of X windows. */
                HWND hWndAbove = NULL;
                DWORD dwCurrentProcessID = GetCurrentProcessId();
                DWORD dwWindowProcessID = 0;

                for (hWndAbove = pWinPos->hwndInsertAfter;
                     hWndAbove != NULL;
                     hWndAbove = GetNextWindow(hWndAbove, GW_HWNDPREV)) {
                    /* Ignore other XWin process's window */
                    GetWindowThreadProcessId(hWndAbove, &dwWindowProcessID);

                    if ((dwWindowProcessID == dwCurrentProcessID)
                        && GetProp(hWndAbove, WIN_WINDOW_PROP)
                        && !IsWindowVisible(hWndAbove)
                        && !IsIconic(hWndAbove))        /* ignore minimized windows */
                        break;
                }
                /* If this is top of X windows in Windows stack,
                   raise it in X stack. */
                if (hWndAbove == NULL) {
#if CYGMULTIWINDOW_DEBUG
                    winDebug("\traise to top\n");
#endif
                    /* Raise the window to the top in Z order */
                    wmMsg.msg = WM_WM_RAISE;
                    if (fWMMsgInitialized)
                        winSendMessageToWM(pScreenPriv->pWMInfo, &wmMsg);
                }
            }
#endif
        }

        if (!(pWinPos->flags & SWP_NOSIZE)) {
            if (IsIconic(hwnd)) {
#if CYGMULTIWINDOW_DEBUG
                winDebug("\tIconic -> MINIMIZED\n");
#endif
                if (winIsInternalWMRunning(pScreenInfo)) {
                    /* Raise the window to the top in Z order */
                    wmMsg.msg = WM_WM_LOWER;
                    if (fWMMsgInitialized)
                        winSendMessageToWM(pScreenPriv->pWMInfo, &wmMsg);
                }
                winWindowsWMSendEvent(WindowsWMControllerNotify,
                                      WindowsWMControllerNotifyMask,
                                      1,
                                      WindowsWMMinimizeWindow,
                                      pWin->drawable.id, 0, 0, 0, 0);
            }
            else if (IsZoomed(hwnd)) {
#if CYGMULTIWINDOW_DEBUG
                winDebug("\tZoomed -> MAXIMIZED\n");
#endif
                winWindowsWMSendEvent(WindowsWMControllerNotify,
                                      WindowsWMControllerNotifyMask,
                                      1,
                                      WindowsWMMaximizeWindow,
                                      pWin->drawable.id, 0, 0, 0, 0);
            }
            else {
#if CYGMULTIWINDOW_DEBUG
                winDebug("\tnone -> RESTORED\n");
#endif
                winWindowsWMSendEvent(WindowsWMControllerNotify,
                                      WindowsWMControllerNotifyMask,
                                      1,
                                      WindowsWMRestoreWindow,
                                      pWin->drawable.id, 0, 0, 0, 0);
            }
        }
        if (!g_fNoConfigureWindow) {

            if (!pRLWinPriv->fMovingOrSizing
                /*&& (pWinPos->flags & SWP_SHOWWINDOW) */ ) {
                GetClientRect(hwnd, &rcClient);
                MapWindowPoints(hwnd, HWND_DESKTOP, (LPPOINT) &rcClient, 2);

                if (!(pWinPos->flags & SWP_NOMOVE)
                    && !(pWinPos->flags & SWP_NOSIZE)) {
#if CYGMULTIWINDOW_DEBUG
                    winDebug("\tmove & resize\n");
#endif
                    if (winIsInternalWMRunning(pScreenInfo))
                        winAdjustXWindow(pWin, hwnd);

                    winMWExtWMMoveResizeXWindow(pWin,
                                                rcClient.left -
                                                wBorderWidth(pWin)
                                                -
                                                GetSystemMetrics
                                                (SM_XVIRTUALSCREEN),
                                                rcClient.top -
                                                wBorderWidth(pWin)
                                                -
                                                GetSystemMetrics
                                                (SM_YVIRTUALSCREEN),
                                                rcClient.right - rcClient.left -
                                                wBorderWidth(pWin) * 2,
                                                rcClient.bottom - rcClient.top -
                                                wBorderWidth(pWin) * 2);
                }
                else if (!(pWinPos->flags & SWP_NOMOVE)) {
#if CYGMULTIWINDOW_DEBUG
                    winDebug("\tmove\n");
#endif
                    if (winIsInternalWMRunning(pScreenInfo))
                        winAdjustXWindow(pWin, hwnd);

                    winMWExtWMMoveResizeXWindow(pWin,
                                                rcClient.left -
                                                wBorderWidth(pWin)
                                                -
                                                GetSystemMetrics
                                                (SM_XVIRTUALSCREEN),
                                                rcClient.top -
                                                wBorderWidth(pWin)
                                                -
                                                GetSystemMetrics
                                                (SM_YVIRTUALSCREEN),
                                                rcClient.right - rcClient.left -
                                                wBorderWidth(pWin) * 2,
                                                rcClient.bottom - rcClient.top -
                                                wBorderWidth(pWin) * 2);
                }
                else if (!(pWinPos->flags & SWP_NOMOVE)) {
#if CYGMULTIWINDOW_DEBUG
                    winDebug("\tmove\n");
#endif
                    if (winIsInternalWMRunning(pScreenInfo))
                        winAdjustXWindow(pWin, hwnd);

                    winMWExtWMMoveXWindow(pWin,
                                          rcClient.left - wBorderWidth(pWin)
                                          - GetSystemMetrics(SM_XVIRTUALSCREEN),
                                          rcClient.top - wBorderWidth(pWin)
                                          -
                                          GetSystemMetrics(SM_YVIRTUALSCREEN));
                }
                else if (!(pWinPos->flags & SWP_NOSIZE)) {
#if CYGMULTIWINDOW_DEBUG
                    winDebug("\tresize\n");
#endif
                    if (winIsInternalWMRunning(pScreenInfo))
                        winAdjustXWindow(pWin, hwnd);

                    winMWExtWMResizeXWindow(pWin,
                                            rcClient.right - rcClient.left
                                            - wBorderWidth(pWin) * 2,
                                            rcClient.bottom - rcClient.top
                                            - wBorderWidth(pWin) * 2);
                }
            }
        }
    }
#if CYGMULTIWINDOW_DEBUG
        winDebug("winMWExtWMWindowProc - WM_WINDOWPOSCHANGED - done.\n");
#endif
        return 0;

    case WM_SIZE:
        /* see dix/window.c */
        /* FIXME: Maximize/Restore? */
#if CYGMULTIWINDOW_DEBUG
        winDebug("winMWExtWMWindowProc - WM_SIZE - %d ms\n",
                 (unsigned int) GetTickCount());
#endif
#if CYGMULTIWINDOW_DEBUG
        winDebug("\t(%d, %d) %d\n", (short) LOWORD(lParam),
                 (short) HIWORD(lParam), g_fNoConfigureWindow);
#endif
        if (g_fNoConfigureWindow)
            break;

        /* Branch on type of resizing occurring */
        switch (wParam) {
        case SIZE_MINIMIZED:
#if CYGMULTIWINDOW_DEBUG
            winDebug("\tSIZE_MINIMIZED\n");
#endif
            if (winIsInternalWMRunning(pScreenInfo)) {
                /* Raise the window to the top in Z order */
                wmMsg.msg = WM_WM_LOWER;
                if (fWMMsgInitialized)
                    winSendMessageToWM(pScreenPriv->pWMInfo, &wmMsg);
            }
            winWindowsWMSendEvent(WindowsWMControllerNotify,
                                  WindowsWMControllerNotifyMask,
                                  1,
                                  WindowsWMMinimizeWindow,
                                  pWin->drawable.id,
                                  0, 0, LOWORD(lParam), HIWORD(lParam));
            break;

        case SIZE_RESTORED:
#if CYGMULTIWINDOW_DEBUG
            winDebug("\tSIZE_RESTORED\n");
#endif
            winWindowsWMSendEvent(WindowsWMControllerNotify,
                                  WindowsWMControllerNotifyMask,
                                  1,
                                  WindowsWMRestoreWindow,
                                  pWin->drawable.id,
                                  0, 0, LOWORD(lParam), HIWORD(lParam));
            break;

        case SIZE_MAXIMIZED:
#if CYGMULTIWINDOW_DEBUG
            winDebug("\tSIZE_MAXIMIZED\n");
#endif
            winWindowsWMSendEvent(WindowsWMControllerNotify,
                                  WindowsWMControllerNotifyMask,
                                  1,
                                  WindowsWMMaximizeWindow,
                                  pWin->drawable.id,
                                  0, 0, LOWORD(lParam), HIWORD(lParam));
            break;
        }

        /* Perform the resize and notify the X client */
        if (!pRLWinPriv->fMovingOrSizing) {
            if (winIsInternalWMRunning(pScreenInfo))
                winAdjustXWindow(pWin, hwnd);

            winMWExtWMResizeXWindow(pWin, (short) LOWORD(lParam)
                                    - wBorderWidth(pWin) * 2,
                                    (short) HIWORD(lParam)
                                    - wBorderWidth(pWin) * 2);
        }
        break;

    case WM_ACTIVATEAPP:
#if CYGMULTIWINDOW_DEBUG
        winDebug("winMWExtWMWindowProc - WM_ACTIVATEAPP - %d ms\n",
                 (unsigned int) GetTickCount());
#endif
        if (wParam) {
            if (winIsInternalWMRunning(pScreenInfo)) {
            }
            else {
            }
            winWindowsWMSendEvent(WindowsWMActivationNotify,
                                  WindowsWMActivationNotifyMask,
                                  1,
                                  WindowsWMIsActive,
                                  pWin->drawable.id, 0, 0, 0, 0);
        }
        else {
            winWindowsWMSendEvent(WindowsWMActivationNotify,
                                  WindowsWMActivationNotifyMask,
                                  1,
                                  WindowsWMIsInactive,
                                  pWin->drawable.id, 0, 0, 0, 0);
        }
        break;

    case WM_SETCURSOR:
        if (LOWORD(lParam) == HTCLIENT) {
            if (!g_fSoftwareCursor)
                SetCursor(pScreenPriv->cursor.handle);
            return TRUE;
        }
        break;

    case WM_ENTERSIZEMOVE:
#if CYGMULTIWINDOW_DEBUG
        winDebug("winMWExtWMWindowProc - WM_ENTERSIZEMOVE - %d ms\n",
                 (unsigned int) GetTickCount());
#endif
        pRLWinPriv->fMovingOrSizing = TRUE;
        break;

    case WM_EXITSIZEMOVE:
#if CYGMULTIWINDOW_DEBUG
        winDebug("winMWExtWMWindowProc - WM_EXITSIZEMOVE - %d ms\n",
                 (unsigned int) GetTickCount());
#endif
        pRLWinPriv->fMovingOrSizing = FALSE;

        GetClientRect(hwnd, &rcClient);

        MapWindowPoints(hwnd, HWND_DESKTOP, (LPPOINT) &rcClient, 2);

        if (winIsInternalWMRunning(pScreenInfo))
            winAdjustXWindow(pWin, hwnd);

        winMWExtWMMoveResizeXWindow(pWin, rcClient.left - wBorderWidth(pWin)
                                    - GetSystemMetrics(SM_XVIRTUALSCREEN),
                                    rcClient.top - wBorderWidth(pWin)
                                    - GetSystemMetrics(SM_YVIRTUALSCREEN),
                                    rcClient.right - rcClient.left
                                    - wBorderWidth(pWin) * 2,
                                    rcClient.bottom - rcClient.top
                                    - wBorderWidth(pWin) * 2);
        break;

    case WM_MANAGE:
        ErrorF("winMWExtWMWindowProc - WM_MANAGE\n");
        break;

    case WM_UNMANAGE:
        ErrorF("winMWExtWMWindowProc - WM_UNMANAGE\n");
        break;

    default:
        break;
    }

    return DefWindowProc(hwnd, message, wParam, lParam);
}