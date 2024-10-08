LRESULT CALLBACK
winTopLevelWindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    POINT ptMouse;
    HDC hdcUpdate;
    PAINTSTRUCT ps;
    WindowPtr pWin = NULL;
    winPrivWinPtr pWinPriv = NULL;
    ScreenPtr s_pScreen = NULL;
    winPrivScreenPtr s_pScreenPriv = NULL;
    winScreenInfo *s_pScreenInfo = NULL;
    HWND hwndScreen = NULL;
    DrawablePtr pDraw = NULL;
    winWMMessageRec wmMsg;
    Bool fWMMsgInitialized = FALSE;
    static Bool s_fTracking = FALSE;
    Bool needRestack = FALSE;
    LRESULT ret;
    static Bool	hasEnteredSizeMove = FALSE;

    winDebugWin32Message("winTopLevelWindowProc", hwnd, message, wParam,
                         lParam);

    /* Check if the Windows window property for our X window pointer is valid */
    if ((pWin = GetProp(hwnd, WIN_WINDOW_PROP)) != NULL) {
        /* Our X window pointer is valid */

        /* Get pointers to the drawable and the screen */
        pDraw = &pWin->drawable;
        s_pScreen = pWin->drawable.pScreen;

        /* Get a pointer to our window privates */
        pWinPriv = winGetWindowPriv(pWin);

        /* Get pointers to our screen privates and screen info */
        s_pScreenPriv = pWinPriv->pScreenPriv;
        s_pScreenInfo = s_pScreenPriv->pScreenInfo;

        /* Get the handle for our screen-sized window */
        hwndScreen = s_pScreenPriv->hwndScreen;

        /* */
        wmMsg.msg = 0;
        wmMsg.hwndWindow = hwnd;
        wmMsg.iWindow = (Window) GetProp(hwnd, WIN_WID_PROP);

        wmMsg.iX = pDraw->x;
        wmMsg.iY = pDraw->y;
        wmMsg.iWidth = pDraw->width;
        wmMsg.iHeight = pDraw->height;

        fWMMsgInitialized = TRUE;

    }
#ifdef _DEBUG
    else if (message!=WM_CREATE)
    {
        winDebug("Warning: message 0x%x received when WIN_WINDOW_PROP NULL\n",message);
    }
#endif

    /* Branch on message type */
    switch (message) {
    case WM_CREATE:

        /* */
        SetProp(hwnd,
                WIN_WINDOW_PROP,
                (HANDLE) ((LPCREATESTRUCT) lParam)->lpCreateParams);

        /* */
        SetProp(hwnd,
                WIN_WID_PROP,
                (HANDLE) winGetWindowID(((LPCREATESTRUCT) lParam)->
                                        lpCreateParams));

        /*
         * Make X windows' Z orders sync with Windows windows because
         * there can be AlwaysOnTop windows overlapped on the window
         * currently being created.
         */
        winReorderWindowsMultiWindow();

        /* Fix a 'round title bar corner background should be transparent not black' problem when first painted */
        {
            RECT rWindow;
            HRGN hRgnWindow;

            GetWindowRect(hwnd, &rWindow);
            hRgnWindow = CreateRectRgnIndirect(&rWindow);
            SetWindowRgn(hwnd, hRgnWindow, TRUE);
        }

        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)VCXSRV_SIGNATURE);

        return 0;

    case WM_INIT_SYS_MENU:
        /*
         * Add whatever the setup file wants to for this window
         */
        SetupSysMenu((unsigned long) hwnd);
        return 0;

    case WM_SYSCOMMAND:
        /*
         * Any window menu items go through here
         */
        if (HandleCustomWM_COMMAND((unsigned long) hwnd, LOWORD(wParam))) {
            /* Don't pass customized menus to DefWindowProc */
            return 0;
        }
        if (wParam == SC_RESTORE || wParam == SC_MAXIMIZE) {
            WINDOWPLACEMENT wndpl;

            wndpl.length = sizeof(wndpl);
            if (GetWindowPlacement(hwnd, &wndpl) &&
                    wndpl.showCmd == SW_SHOWMINIMIZED)
                needRestack = TRUE;
        }
        break;

    case WM_INITMENU:
        /* Checks/Unchecks any menu items before they are displayed */
        HandleCustomWM_INITMENU((unsigned long) hwnd, wParam);
        break;

    case WM_ERASEBKGND:
        /*
         * Pretend that we did erase the background but we don't care,
         * since we repaint the entire region anyhow
         * This avoids some flickering when resizing.
         */
        return TRUE;

    case WM_PAINT:
        /* Only paint if our window handle is valid */
        if (hwndScreen == NULL)
            break;

        /* BeginPaint gives us an hdc that clips to the invalidated region */
        hdcUpdate = BeginPaint(hwnd, &ps);
        /* Avoid the BitBlt's if the PAINTSTRUCT is bogus */
        if (ps.rcPaint.right == 0 && ps.rcPaint.bottom == 0 &&
                ps.rcPaint.left == 0 && ps.rcPaint.top == 0) {
            EndPaint(hwnd, &ps);
            return 0;
        }

#ifdef XWIN_GLX_WINDOWS
        if (pWinPriv->fWglUsed) {
            /*
               For regions which are being drawn by GL, the shadow framebuffer doesn't have the
               correct bits, so don't bitblt from the shadow framebuffer

               XXX: For now, just leave it alone, but ideally we want to send an expose event to
               the window so it really redraws the affected region...
             */
            ValidateRect(hwnd, &(ps.rcPaint));
        }
        else
#endif
            /* Try to copy from the shadow buffer */
            if (!BitBlt(hdcUpdate,
                        ps.rcPaint.left, ps.rcPaint.top,
                        ps.rcPaint.right - ps.rcPaint.left,
                        ps.rcPaint.bottom - ps.rcPaint.top,
                        s_pScreenPriv->hdcShadow,
                        ps.rcPaint.left + pWin->drawable.x,
                        ps.rcPaint.top + pWin->drawable.y, SRCCOPY)) {
                LPVOID lpMsgBuf;

                /* Display a fancy error message */
                FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
                              FORMAT_MESSAGE_FROM_SYSTEM |
                              FORMAT_MESSAGE_IGNORE_INSERTS,
                              NULL,
                              GetLastError(),
                              MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                              (LPTSTR) &lpMsgBuf, 0, NULL);

                ErrorF("winTopLevelWindowProc - BitBlt failed: %s\n",
                       (LPSTR) lpMsgBuf);
                LocalFree(lpMsgBuf);
            }

        /* EndPaint frees the DC */
        EndPaint(hwnd, &ps);
        return 0;

    case WM_MOUSEMOVE:
        /* Unpack the client area mouse coordinates */
        ptMouse.x = GET_X_LPARAM(lParam);
        ptMouse.y = GET_Y_LPARAM(lParam);

        /* Translate the client area mouse coordinates to screen coordinates */
        ClientToScreen(hwnd, &ptMouse);

        /* Screen Coords from (-X, -Y) -> Root Window (0, 0) */
        ptMouse.x -= GetSystemMetrics(SM_XVIRTUALSCREEN);
        ptMouse.y -= GetSystemMetrics(SM_YVIRTUALSCREEN);

        /* We can't do anything without privates */
        if (s_pScreenPriv == NULL || s_pScreenInfo->fIgnoreInput)
            break;

        /* Has the mouse pointer crossed screens? */
        if (s_pScreen != miPointerGetScreen(g_pwinPointer))
            miPointerSetScreen(g_pwinPointer, s_pScreenInfo->dwScreen,
                               ptMouse.x - s_pScreenInfo->dwXOffset,
                               ptMouse.y - s_pScreenInfo->dwYOffset);

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
                ErrorF("winTopLevelWindowProc - TrackMouseEvent failed\n");

            /* Flag that we are tracking now */
            s_fTracking = TRUE;
        }

        /* Hide or show the Windows mouse cursor */
        if (g_fSoftwareCursor && g_fCursor) {
            /* Hide Windows cursor */
            g_fCursor = FALSE;
            ShowCursor(FALSE);
        }

        /* Kill the timer used to poll mouse events */
        if (g_uipMousePollingTimerID != 0) {
            KillTimer(s_pScreenPriv->hwndScreen, WIN_POLLING_MOUSE_TIMER_ID);
            g_uipMousePollingTimerID = 0;
        }

        /* Deliver absolute cursor position to X Server */
        winEnqueueMotion(ptMouse.x - s_pScreenInfo->dwXOffset,
                         ptMouse.y - s_pScreenInfo->dwYOffset);

        return 0;

    case WM_NCMOUSEMOVE:
        /*
         * We break instead of returning 0 since we need to call
         * DefWindowProc to get the mouse cursor changes
         * and min/max/close button highlighting in Windows XP.
         * The Platform SDK says that you should return 0 if you
         * process this message, but it fails to mention that you
         * will give up any default functionality if you do return 0.
         */

        /* We can't do anything without privates */
        if (s_pScreenPriv == NULL || s_pScreenInfo->fIgnoreInput)
            break;

        /* Non-client mouse movement, show Windows cursor */
        if (g_fSoftwareCursor && !g_fCursor) {
            g_fCursor = TRUE;
            ShowCursor(TRUE);
        }

        winStartMousePolling(s_pScreenPriv);

        break;

    case WM_MOUSELEAVE:
        /* We can't do anything without privates */
        if (s_pScreenPriv == NULL || s_pScreenInfo->fIgnoreInput)
            break;
        /* Mouse has left our client area */

        /* Flag that we are no longer tracking */
        s_fTracking = FALSE;

        /* Show the mouse cursor, if necessary */
        if (g_fSoftwareCursor && !g_fCursor) {
            g_fCursor = TRUE;
            ShowCursor(TRUE);
        }

        winStartMousePolling(s_pScreenPriv);

        return 0;

    case WM_LBUTTONDBLCLK:
    case WM_LBUTTONDOWN:
        if (s_pScreenPriv == NULL || s_pScreenInfo->fIgnoreInput)
            break;
        g_fButton[0] = TRUE;
        SetCapture(hwnd);
        return winMouseButtonsHandle(s_pScreen, ButtonPress, Button1, wParam);

    case WM_LBUTTONUP:
        if (s_pScreenPriv == NULL || s_pScreenInfo->fIgnoreInput)
            break;
        g_fButton[0] = FALSE;
        ReleaseCapture();
        winStartMousePolling(s_pScreenPriv);
        return winMouseButtonsHandle(s_pScreen, ButtonRelease, Button1, wParam);

    case WM_MBUTTONDBLCLK:
    case WM_MBUTTONDOWN:
        if (s_pScreenPriv == NULL || s_pScreenInfo->fIgnoreInput)
            break;
        g_fButton[1] = TRUE;
        SetCapture(hwnd);
        return winMouseButtonsHandle(s_pScreen, ButtonPress, Button2, wParam);

    case WM_MBUTTONUP:
        if (s_pScreenPriv == NULL || s_pScreenInfo->fIgnoreInput)
            break;
        g_fButton[1] = FALSE;
        ReleaseCapture();
        winStartMousePolling(s_pScreenPriv);
        return winMouseButtonsHandle(s_pScreen, ButtonRelease, Button2, wParam);

    case WM_RBUTTONDBLCLK:
    case WM_RBUTTONDOWN:
        if (s_pScreenPriv == NULL || s_pScreenInfo->fIgnoreInput)
            break;
        g_fButton[2] = TRUE;
        SetCapture(hwnd);
        return winMouseButtonsHandle(s_pScreen, ButtonPress, Button3, wParam);

    case WM_RBUTTONUP:
        if (s_pScreenPriv == NULL || s_pScreenInfo->fIgnoreInput)
            break;
        g_fButton[2] = FALSE;
        ReleaseCapture();
        winStartMousePolling(s_pScreenPriv);
        return winMouseButtonsHandle(s_pScreen, ButtonRelease, Button3, wParam);

    case WM_XBUTTONDBLCLK:
    case WM_XBUTTONDOWN:
        if (s_pScreenPriv == NULL || s_pScreenInfo->fIgnoreInput)
            break;
        SetCapture(hwnd);
        return winMouseButtonsHandle(s_pScreen, ButtonPress, HIWORD(wParam) + 5,
                                     wParam);

    case WM_XBUTTONUP:
        if (s_pScreenPriv == NULL || s_pScreenInfo->fIgnoreInput)
            break;
        ReleaseCapture();
        winStartMousePolling(s_pScreenPriv);
        return winMouseButtonsHandle(s_pScreen, ButtonRelease,
                                     HIWORD(wParam) + 5, wParam);

    case WM_MOUSEWHEEL:
        if (SendMessage
                (hwnd, WM_NCHITTEST, 0,
                 MAKELONG(GET_X_LPARAM(lParam),
                          GET_Y_LPARAM(lParam))) == HTCLIENT) {
            /* Pass the message to the root window */
            SendMessage(hwndScreen, message, wParam, lParam);
            return 0;
        }
        else
            break;

    case WM_SETFOCUS:
        if (s_pScreenPriv == NULL || s_pScreenInfo->fIgnoreInput)
            break;

        {
            /* Get the parent window for transient handling */
            HWND hParent = GetParent(hwnd);

            if (hParent && IsIconic(hParent))
                ShowWindow(hParent, SW_RESTORE);
        }

        winRestoreModeKeyStates();

        /* Add the keyboard hook if possible */
        if (g_fKeyboardHookLL)
            g_fKeyboardHookLL = winInstallKeyboardHookLL();
        return 0;

    case WM_KILLFOCUS:
        /* Pop any pressed keys since we are losing keyboard focus */
        winKeybdReleaseKeys();

        /* Remove our keyboard hook if it is installed */
        winRemoveKeyboardHookLL();

        /* Revert the X focus as well, but only if the Windows focus is going to another window */
        if (!wParam && pWin)
            DeleteWindowFromAnyEvents(pWin, FALSE);

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

#ifdef WINDBG
        if (wParam == VK_ESCAPE) {
            /* Place for debug: put any tests and dumps here */
            WINDOWPLACEMENT windPlace;
            RECT rc;
            LPRECT pRect;

            windPlace.length = sizeof(WINDOWPLACEMENT);
            GetWindowPlacement(hwnd, &windPlace);
            pRect = &windPlace.rcNormalPosition;
            winDebug ("\nCYGWINDOWING Dump:\n"
                      "\tdrawable: (%hd, %hd) - %hdx%hd\n", pDraw->x,
                      pDraw->y, pDraw->width, pDraw->height);
            winDebug ("\twindPlace: (%ld, %ld) - %ldx%ld\n", pRect->left,
                      pRect->top, pRect->right - pRect->left,
                      pRect->bottom - pRect->top);
            if (GetClientRect(hwnd, &rc)) {
                pRect = &rc;
                winDebug ("\tClientRect: (%ld, %ld) - %ldx%ld\n", pRect->left,
                          pRect->top, pRect->right - pRect->left,
                          pRect->bottom - pRect->top);
            }
            if (GetWindowRect(hwnd, &rc)) {
                pRect = &rc;
                winDebug ("\tWindowRect: (%ld, %ld) - %ldx%ld\n", pRect->left,
                          pRect->top, pRect->right - pRect->left,
                          pRect->bottom - pRect->top);
            }
            winDebug ("\n");
        }
#endif

        /* Pass the message to the root window */
        return winWindowProc(hwndScreen, message, wParam, lParam);

    case WM_SYSKEYUP:
    case WM_KEYUP:

        /* Pass the message to the root window */
        return winWindowProc(hwndScreen, message, wParam, lParam);

    case WM_HOTKEY:

        /* Pass the message to the root window */
        SendMessage(hwndScreen, message, wParam, lParam);
        return 0;

    case WM_ACTIVATE:

        /* Pass the message to the root window */
        SendMessage(hwndScreen, message, wParam, lParam);

        if (LOWORD(wParam) != WA_INACTIVE) {
            /* Raise the window to the top in Z order */
            /* ago: Activate does not mean putting it to front! */
            /*
               wmMsg.msg = WM_WM_RAISE;
               if (fWMMsgInitialized)
               winSendMessageToWM (s_pScreenPriv->pWMInfo, &wmMsg);
             */

            /* Tell our Window Manager thread to activate the window */
            wmMsg.msg = WM_WM_ACTIVATE;
            if (fWMMsgInitialized && pWin->realized && !pWin->overrideRedirect /* for OOo menus */)
                winSendMessageToWM (s_pScreenPriv->pWMInfo, &wmMsg);
        }
        /* Prevent the mouse wheel from stalling when another window is minimized */
        if (HIWORD(wParam) == 0 && LOWORD(wParam) == WA_ACTIVE &&
                (HWND) lParam != NULL && (HWND) lParam != (HWND) GetParent(hwnd))
            SetFocus(hwnd);
        return 0;

    case WM_ACTIVATEAPP:
        /*
         * This message is also sent to the root window
         * so we do nothing for individual multiwindow windows
         */
        break;

    case WM_CLOSE:
        /* Removep AppUserModelID property */
        winSetAppUserModelID(hwnd, NULL);
        /* Branch on if the window was killed in X already */
        if (pWinPriv->fXKilled) {
            /* Window was killed, go ahead and destroy the window */
            DestroyWindow(hwnd);
        }
        else {
            /* Tell our Window Manager thread to kill the window */
            wmMsg.msg = WM_WM_KILL;
            if (fWMMsgInitialized)
                winSendMessageToWM(s_pScreenPriv->pWMInfo, &wmMsg);
        }
        return 0;

    case WM_DESTROY:

        /* Branch on if the window was killed in X already */
        if (pWinPriv && !pWinPriv->fXKilled) {
            winDebug ("winTopLevelWindowProc - WM_DESTROY - WM_WM_KILL\n");

            /* Tell our Window Manager thread to kill the window */
            wmMsg.msg = WM_WM_KILL;
            if (fWMMsgInitialized)
                winSendMessageToWM(s_pScreenPriv->pWMInfo, &wmMsg);
        }

        RemoveProp(hwnd, WIN_WINDOW_PROP);
        RemoveProp(hwnd, WIN_WID_PROP);
        RemoveProp(hwnd, WIN_NEEDMANAGE_PROP);

        break;

    case WM_MOVE:
        /* Adjust the X Window to the moved Windows window */
        if (!hasEnteredSizeMove) winAdjustXWindow (pWin, hwnd);
        /* else: Wait for WM_EXITSIZEMOVE */
        return 0;

    case WM_SHOWWINDOW:
        /* Bail out if the window is being hidden */
        if (!wParam)
            return 0;

        /* */
        if (!pWin->overrideRedirect) {
            HWND zstyle = HWND_NOTOPMOST;

            /* Flag that this window needs to be made active when clicked */
            SetProp(hwnd, WIN_NEEDMANAGE_PROP, (HANDLE) 1);

            /* Set the transient style flags */
            if (GetParent(hwnd))
                SetWindowLongPtr(hwnd, GWL_STYLE,
                                 WS_POPUP | WS_OVERLAPPED | WS_SYSMENU |
                                 WS_CLIPCHILDREN | WS_CLIPSIBLINGS);
            /* Set the window standard style flags */
            else
                SetWindowLongPtr(hwnd, GWL_STYLE,
                                 (WS_POPUP | WS_OVERLAPPEDWINDOW |
                                  WS_CLIPCHILDREN | WS_CLIPSIBLINGS)
                                 & ~WS_CAPTION & ~WS_SIZEBOX);

            winUpdateWindowPosition(hwnd, &zstyle);

            {
                WinXWMHints hints;

                if (winMultiWindowGetWMHints(pWin, &hints)) {
                    /*
                       Give the window focus, unless it has an InputHint
                       which is FALSE (this is used by e.g. glean to
                       avoid every test window grabbing the focus)
                     */
                    if (!((hints.flags & InputHint) && (!hints.input))) {
                        SetForegroundWindow(hwnd);
                    }
                }
            }
            wmMsg.msg = WM_WM_MAP3;
        }
        else {                  /* It is an overridden window so make it top of Z stack */

            HWND forHwnd = GetForegroundWindow();
            winDebug ("overridden window is shown\n");
            if (forHwnd != NULL) {
                if (GetWindowLongPtr(forHwnd, GWLP_USERDATA) & (LONG_PTR)
                        VCXSRV_SIGNATURE) {
                    if (GetWindowLongPtr(forHwnd, GWL_EXSTYLE) & WS_EX_TOPMOST)
                        SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0,
                                     SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
                    else
                        SetWindowPos(hwnd, HWND_NOTOPMOST, 0, 0, 0, 0,
                                     SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
                }
            }
            wmMsg.msg = WM_WM_MAP2;
        }

        /* Tell our Window Manager thread to map the window */
        if (fWMMsgInitialized)
            winSendMessageToWM(s_pScreenPriv->pWMInfo, &wmMsg);

        winStartMousePolling(s_pScreenPriv);

        return 0;

    case WM_SIZING:
        /* Need to legalize the size according to WM_NORMAL_HINTS */
        /* for applications like xterm */
        return ValidateSizing(hwnd, pWin, wParam, lParam);

    case WM_WINDOWPOSCHANGING:
    {
        /*
          When window is moved or resized, force it to be redrawn, so that
          any OpenGL content is re-drawn correctly, rather than copying bits
          (which seem to be wrong, either because we are copying the wrong
          window in the window heirarchy, or because we don't have the bits
          drawn by OpenGL at all)

          XXX: really this should check if any child has fWglUsed set, but
          that might be expensive to check....
         */
        if (g_fNativeGl)
        {
            LPWINDOWPOS pWinPos = (LPWINDOWPOS)lParam;
            pWinPos->flags |= SWP_NOCOPYBITS;
        }
    }
    break;

    case WM_WINDOWPOSCHANGED:
    {
        LPWINDOWPOS pWinPos = (LPWINDOWPOS) lParam;

        if (!(pWinPos->flags & SWP_NOZORDER)) {
#if CYGWINDOWING_DEBUG
            winDebug("\twindow z order was changed\n");
#endif
            if (pWinPos->hwndInsertAfter == HWND_TOP
                    || pWinPos->hwndInsertAfter == HWND_TOPMOST
                    || pWinPos->hwndInsertAfter == HWND_NOTOPMOST) {
#if CYGWINDOWING_DEBUG
                winDebug("\traise to top\n");
#endif
                /* Raise the window to the top in Z order */
                winRaiseWindow(pWin);
            }
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
#if CYGWINDOWING_DEBUG
                    winDebug("\traise to top\n");
#endif
                    winRaiseWindow(pWin);
                }
            }
        }
    }
        /*
         * Pass the message to DefWindowProc to let the function
         * break down WM_WINDOWPOSCHANGED to WM_MOVE and WM_SIZE.
         */
    break;

    case WM_ENTERSIZEMOVE:
        hasEnteredSizeMove = TRUE;
        return 0;

    case WM_EXITSIZEMOVE:
        /* Adjust the X Window to the moved Windows window */
        hasEnteredSizeMove = FALSE;
        winAdjustXWindow (pWin, hwnd);
        return 0;

    case WM_SIZE:
        /* see dix/window.c */
#ifdef WINDBG
    {
        char buf[64];

        switch (wParam) {
        case SIZE_MINIMIZED:
            strcpy(buf, "SIZE_MINIMIZED");
            break;
        case SIZE_MAXIMIZED:
            strcpy(buf, "SIZE_MAXIMIZED");
            break;
        case SIZE_RESTORED:
            strcpy(buf, "SIZE_RESTORED");
            break;
        default:
            strcpy(buf, "UNKNOWN_FLAG");
        }
        winDebug ("winTopLevelWindowProc - WM_SIZE to %dx%d (%s) - %d ms\n",
                  (int) LOWORD(lParam), (int) HIWORD(lParam), buf,
                  (int) (GetTickCount()));
    }
#endif
    if (!hasEnteredSizeMove)
    {
        /* Adjust the X Window to the moved Windows window */
        winAdjustXWindow (pWin, hwnd);
        if (wParam == SIZE_MINIMIZED) winReorderWindowsMultiWindow();
    }
        /* else: wait for WM_EXITSIZEMOVE */
        return 0; /* end of WM_SIZE handler */

    case WM_STYLECHANGED:
        /* when the style changes, adjust the window size so the client area remains the same */
    {
        LONG x,y;
        DrawablePtr pDraw = &pWin->drawable;
        x =  pDraw->x - wBorderWidth(pWin);
        y = pDraw->y - wBorderWidth(pWin);
        winPositionWindowMultiWindow(pWin, x, y);
    }
    return 0;

    case WM_MOUSEACTIVATE:

        /* Check if this window needs to be made active when clicked */
        if (!GetProp(pWinPriv->hWnd, WIN_NEEDMANAGE_PROP)) {
            winDebug ("winTopLevelWindowProc - WM_MOUSEACTIVATE - "
                      "MA_NOACTIVATE\n");

            /* */
            return MA_NOACTIVATE;
        }
        break;

    case WM_SETCURSOR:
        if (LOWORD(lParam) == HTCLIENT) {
            if (!g_fSoftwareCursor)
                SetCursor(s_pScreenPriv->cursor.handle);
            return TRUE;
        }
        break;

    default:
        break;
    }

    ret = DefWindowProc(hwnd, message, wParam, lParam);
    /*
     * If the window was minized we get the stack change before the window is restored
     * and so it gets lost. Ensure there stacking order is correct.
     */
    if (needRestack)
        winReorderWindowsMultiWindow();
    return ret;
}