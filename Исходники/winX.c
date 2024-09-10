LRESULT CALLBACK WinXwindowProc(HWND hwnd, UINT uMsg, WPARAM wParam,
                                LPARAM lParam)
{
    switch (uMsg) {
    case WM_CREATE:
    {
        LPCREATESTRUCT lpcs = (LPCREATESTRUCT) lParam;
        int xidno = (int) lpcs->lpCreateParams;

        Trace("WM_CREATE %d %d/%d %s:%d\n", xidno, lpcs->cx, lpcs->cy,
              xid[xidno].any.file, xid[xidno].any.line);
        WinXCreateBitmapForXid(hwnd, xidno, lpcs->cx, lpcs->cy);
        SetWindowWord(hwnd, 0, (WORD) xidno);
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    case WM_DESTROY:
    {
        XID xidno = (int) GetWindowWord(hwnd, 0);

        if (Widget_window(motd_viewer) == xidno)
            Motd_destroy();
        if (Widget_window(keys_viewer) == xidno)
            Keys_destroy();
        WinXDeleteDraw(xidno);
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    case WM_SIZE:
    {
        int xidno = (int) GetWindowWord(hwnd, 0);
        if (xidno > 0 && xidno < MAX_XIDS && xid[xidno].hwnd.hBmp) {
            int width = LOWORD(lParam);
            int height = HIWORD(lParam);
            Trace("WM_SIZE   %d %d/%d %s:%d\n", xidno, width, height,
                  xid[xidno].any.file, xid[xidno].any.line);
            WinXCreateBitmapForXid(hwnd, xidno, width, height);
        }
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    case WM_LBUTTONDOWN:
    {
        int xidno = (int) GetWindowWord(hwnd, 0);
        if (xid[xidno].hwnd.event_mask & ButtonPressMask) {
            XEvent event;
            XButtonEvent *button = (XButtonEvent *) & event;
            POINT pt;

            pt.x = LOWORD(lParam);
            pt.y = HIWORD(lParam);
            MapWindowPoints(xid[xidno].hwnd.hWnd, xid[topWindow].hwnd.hWnd,
                            &pt, 1);
            button->type = ButtonPress;
            button->window = xidno;
            button->x = LOWORD(lParam);
            button->y = HIWORD(lParam);
            button->x_root = pt.x;
            button->y_root = pt.y;
            button->button = Button1;
            win_xevent(event);
        }
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    case WM_LBUTTONUP:
    {
        int xidno = (int) GetWindowWord(hwnd, 0);

        if (xid[xidno].hwnd.event_mask & ButtonReleaseMask) {
            XEvent event;
            XButtonEvent *button = (XButtonEvent *) & event;

            Trace("ButtonUp in %d %s:%d\n", xidno, xid[xidno].any.file,
                  xid[xidno].any.line);
            button->type = ButtonRelease;
            button->window = xidno;
            button->x = LOWORD(lParam);
            button->y = HIWORD(lParam);
            button->button = Button1;
            if (win_xevent(event) == -1) {
                WinXExit();
            }
            return (0);
        }
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    case WM_MBUTTONDOWN:
    {
        int xidno = (int) GetWindowWord(hwnd, 0);
        if (xid[xidno].hwnd.event_mask & ButtonPressMask) {
            XEvent event;
            XButtonEvent *button = (XButtonEvent *) & event;
            POINT pt;

            pt.x = LOWORD(lParam);
            pt.y = HIWORD(lParam);
            MapWindowPoints(xid[xidno].hwnd.hWnd, xid[topWindow].hwnd.hWnd,
                            &pt, 1);
            button->type = ButtonPress;
            button->window = xidno;
            button->x = LOWORD(lParam);
            button->y = HIWORD(lParam);
            button->x_root = pt.x;
            button->y_root = pt.y;
            button->button = Button2;
            win_xevent(event);
        }
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    case WM_MBUTTONUP:
    {
        int xidno = (int) GetWindowWord(hwnd, 0);

        if (xid[xidno].hwnd.event_mask & ButtonReleaseMask) {
            XEvent event;
            XButtonEvent *button = (XButtonEvent *) & event;

            Trace("ButtonUp in %d %s:%d\n", xidno, xid[xidno].any.file,
                  xid[xidno].any.line);
            button->type = ButtonRelease;
            button->window = xidno;
            button->x = LOWORD(lParam);
            button->y = HIWORD(lParam);
            button->button = Button2;
            if (win_xevent(event) == -1) {
                WinXExit();
            }
            return (0);
        }
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    case WM_RBUTTONDOWN:
    {
        int xidno = (int) GetWindowWord(hwnd, 0);
        if (xid[xidno].hwnd.event_mask & ButtonPressMask) {
            XEvent event;
            XButtonEvent *button = (XButtonEvent *) & event;
            POINT pt;

            pt.x = LOWORD(lParam);
            pt.y = HIWORD(lParam);
            MapWindowPoints(xid[xidno].hwnd.hWnd, xid[topWindow].hwnd.hWnd,
                            &pt, 1);
            button->type = ButtonPress;
            button->window = xidno;
            button->x = LOWORD(lParam);
            button->y = HIWORD(lParam);
            button->x_root = pt.x;
            button->y_root = pt.y;
            button->button = Button3;
            win_xevent(event);
        }
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    case WM_RBUTTONUP:
    {
        int xidno = (int) GetWindowWord(hwnd, 0);

        if (xid[xidno].hwnd.event_mask & ButtonReleaseMask) {
            XEvent event;
            XButtonEvent *button = (XButtonEvent *) & event;

            Trace("ButtonUp in %d %s:%d\n", xidno, xid[xidno].any.file,
                  xid[xidno].any.line);
            button->type = ButtonRelease;
            button->window = xidno;
            button->x = LOWORD(lParam);
            button->y = HIWORD(lParam);
            button->button = Button3;
            if (win_xevent(event) == -1) {
                WinXExit();
            }
            return (0);
        }
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    case WM_MOUSEMOVE:
    {
        XID xidno = (int) GetWindowWord(hwnd, 0);
        XEvent event;
        XID i;
        XAnyEvent *enter = (XAnyEvent *) & event;

        /* Trace("MouseMove in %d %d/%d %s:%d\n", xidno,
           LOWORD(lParam), HIWORD(lParam), xid[xidno].any.file, xid[xidno].any.line); */

        enter->type = LeaveNotify;
        for (i = 0; i < MAX_XIDS; i++) {
            if (i != xidno && xid[i].type == XIDTYPE_HWND
                    && xid[i].hwnd.mouseover
                    && xid[i].hwnd.event_mask & LeaveWindowMask) {
                Trace("LeaveNotify %d %s:%d\n", xidno,
                      xid[xidno].any.file, xid[xidno].any.line);
                enter->window = i;
                win_xevent(event);
                xid[i].hwnd.mouseover = FALSE;
            }
        }
        if (xid[xidno].hwnd.event_mask & PointerMotionMask) {
            XMotionEvent *me = (XMotionEvent *) & event;
            me->type = MotionNotify;
            me->window = xidno;
            me->x = LOWORD(lParam);
            me->y = HIWORD(lParam);
//                      if (me->x != draw_width/2 && me->y != draw_height/2)
            {
                win_xevent(event);
//                              SetCursorPos(draw_width/2, draw_height/2);
            }
            //      return(0);
        } else if (!xid[xidno].hwnd.mouseover) {
            /* PointerMotionMask is only on captured window *//* so don't do the mouseover event */
            if (xid[xidno].hwnd.event_mask & EnterWindowMask) {
                Trace("EnterNotify %d %s:%d\n", xidno,
                      xid[xidno].any.file, xid[xidno].any.line);
                enter->type = EnterNotify;
                enter->window = xidno;
                win_xevent(event);
            }
            xid[xidno].hwnd.mouseover = TRUE;
        }

        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    case WM_ERASEBKGND:
    {
        RECT rect;
        if (GetClientRect(hwnd, &rect)) {
            HDC hBmpDC;
            XID xidno = (int) GetWindowWord(hwnd, 0);
            hBmpDC = xid[xidno].hwnd.hBmpDC;
            if (hBmpDC) {
                Trace("WM_ERASEBKGND %d color=%d %d/%d %d/%d\n", xidno,
                      xid[xidno].hwnd.bgcolor, rect.left, rect.top,
                      rect.right, rect.bottom);
                FillRect(hBmpDC, &rect,
                         (HBRUSH) WinXGetBrush(xid[xidno].hwnd.
                                               bgcolor));
            }
        }
        return (0);
    }
    case WM_PAINT:
    {
        RECT rect;
        if (GetUpdateRect(hwnd, &rect, FALSE)) {
            XID xidno = (int) GetWindowWord(hwnd, 0);
//                      if (xidno == draw)
//                              return DefWindowProc(hwnd, uMsg, wParam, lParam);
            if (xidno >= 0 && xidno < MAX_XIDS) {
                HDC hBmpDC;

                hBmpDC = xid[xidno].hwnd.hBmpDC;
                if (hBmpDC) {
                    PAINTSTRUCT ps;
                    HDC hDC;
                    XEvent event;
                    XExposeEvent *expose = (XExposeEvent *) & event;

                    if (ThreadedDraw && xidno == (int) drawWindow) {
                        ValidateRect(hwnd, &rect);
                        winXTDraw(NULL, xidno, &rect);
                    } else {
                        hDC = BeginPaint(hwnd, &ps);

                        if (xid[xidno].hwnd.event_mask & ExposureMask) {
                            expose->type = Expose;
                            expose->window = xidno;
                            expose->x = rect.left;
                            expose->y = rect.top;
                            expose->width = rect.right - rect.left;
                            expose->height = rect.bottom - rect.top;
                            expose->count = 0;
                            Trace("Expose %d %s:%d\n", xidno,
                                  xid[xidno].any.file,
                                  xid[xidno].any.line);
                            win_xevent(event);
                        }

                        SelectPalette(hDC, myPal, FALSE);
                        RealizePalette(hDC);

                        if (xidno == (int) drawWindow) {
                            //      RECT r;
                            //      WinXUnscaled(hBmpDC);
                            if (ThreadedDraw) {
                                ValidateRect(hwnd, &rect);
                                winXTDraw(hDC, xidno, &rect);
                            } else {
                                BitBlt(hDC, rect.left, rect.top,
                                       rect.right, rect.bottom, hBmpDC,
                                       rect.left, rect.top, SRCCOPY);
                            }
                            //      GetClientRect(hwnd, &r);
                            //      WinXScaled(hBmpDC, r.right - r.left, r.bottom - r.top);
                            drawPending = FALSE;
                        } else {	/* not the main playfield window */
                            BitBlt(hDC, rect.left, rect.top,
                                   rect.right, rect.bottom, hBmpDC,
                                   rect.left, rect.top, SRCCOPY);
                        }
                        EndPaint(hwnd, &ps);
                    }
                    return 0;
                }
            }
        }
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}