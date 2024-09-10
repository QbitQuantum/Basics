LRESULT CWebWindow::_windowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch(message)
    {
    case WM_CREATE:
        {
            DragAcceptFiles(hwnd, TRUE);
            //SetTimer(hwnd, 100, 20, NULL);
        }
        return 0;

    case WM_CLOSE:
        if (m_windowClosingCallback)
        {
            if (!m_windowClosingCallback(this, m_windowClosingCallbackParam))
                return 0;
        }

        ShowWindow(hwnd, SW_HIDE);
        DestroyWindow(hwnd);
        return 0;

    case WM_DESTROY:
        {
            //KillTimer(hwnd, 100);
            RemovePropW(hwnd, L"wkeWebWindow");
            m_hwnd = NULL;

            if (m_windowDestroyCallback)
                m_windowDestroyCallback(this, m_windowDestroyCallbackParam);

            wkeDestroyWebView(this);
        }
        return 0;

    //case WM_TIMER:
    //    {
    //        wkeRepaintIfNeeded(this);
    //    }
    //    return 0;

    case WM_PAINT:
        {
            PAINTSTRUCT ps = { 0 };
            HDC hdc = BeginPaint(hwnd, &ps);
            _paintDC(hdc, (HDC)wkeGetViewDC(this));
            EndPaint(hwnd, &ps);
        }
        return 0;

    case WM_ERASEBKGND:
        return TRUE;

    case WM_SIZE:
        {
            RECT rc = { 0 };
            GetClientRect(hwnd, &rc);
            int width = rc.right - rc.left;
            int height = rc.bottom - rc.top;

            CWebView::resize(width, height);
            wkeRepaintIfNeeded(this);
        }
        return 0;

    case WM_DROPFILES:
        {
            wchar_t szFile[MAX_PATH + 8] = {0};
            wcscpy(szFile, L"file:///");

            HDROP hDrop = reinterpret_cast<HDROP>(wParam);

            UINT uFilesCount = DragQueryFileW(hDrop, 0xFFFFFFFF, szFile, MAX_PATH);
            if (uFilesCount != 0)
            {
                UINT uRet = DragQueryFileW(hDrop, 0, (wchar_t*)szFile + 8, MAX_PATH);
                if ( uRet != 0)
                {
                    wkeLoadURLW(this, szFile);
                    SetWindowTextW(hwnd, szFile);
                }
            }
            DragFinish(hDrop);
        }
        return 0;


    //case WM_NCHITTEST:
    //    if (IsWindow(m_hwnd) && flagsOff(GetWindowLong(m_hwnd, GWL_STYLE), WS_CAPTION))
    //    {
    //        IWebkitObserverPtr observer = m_observer.lock();
    //        if (!observer)
    //            break;

    //        QPoint cursor(LOWORD(lParam), HIWORD(lParam));
    //        ScreenToClient(m_hwnd, &cursor);

    //        QRect clientRect;
    //        QSize clientSize;
    //        GetClientRect(hwnd, &clientRect);
    //        clientSize.cx = clientRect.width();
    //        clientSize.cy = clientRect.height();

    //        EWebkitHitTest hit = observer->onHitTest(QWebkitView(thisView), clientSize, cursor);
    //        switch (hit)
    //        {
    //        case eWebkitHitLeftTop:     return HTTOPLEFT;
    //        case eWebkitHitLeft:        return HTLEFT;
    //        case eWebkitHitLeftBottom:  return HTBOTTOMLEFT;
    //        case eWebkitHitRightTop:    return HTTOPRIGHT;
    //        case eWebkitHitRight:       return HTRIGHT;
    //        case eWebkitHitRightBottom: return HTBOTTOMRIGHT;
    //        case eWebkitHitTop:         return HTTOP;
    //        case eWebkitHitBottom:      return HTBOTTOM;
    //        case eWebkitHitCaption:     return HTCAPTION;
    //        case eWebkitHitClient:      return HTCLIENT;
    //        case eWebkitHitNone:        return HTCLIENT;
    //        }
    //    }
    //    break;

    //case WM_SETCURSOR:
    //    if (IsWindow(m_hwnd) && flagsOff(GetWindowLong(m_hwnd, GWL_STYLE), WS_CAPTION))
    //    {
    //        WORD hit = LOWORD(lParam);
    //        switch (hit)
    //        {
    //        case HTCAPTION:
    //        case HTSYSMENU:
    //        case HTMENU:
    //        case HTCLIENT:
    //            SetCursor(LoadCursor(NULL, MAKEINTRESOURCE(IDC_ARROW)));
    //            return TRUE;

    //        case HTTOP:
    //        case HTBOTTOM:
    //            SetCursor(LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZENS)));
    //            return TRUE;

    //        case HTLEFT:
    //        case HTRIGHT:
    //            SetCursor(LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZEWE)));
    //            return TRUE;

    //        case HTTOPLEFT:
    //        case HTBOTTOMRIGHT:
    //            SetCursor(LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZENWSE)));
    //            return TRUE;

    //        case HTTOPRIGHT:
    //        case HTBOTTOMLEFT:
    //            SetCursor(LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZENESW)));
    //            return TRUE;

    //        default:
    //            SetCursor(LoadCursor(NULL, MAKEINTRESOURCE(IDC_ARROW)));
    //            return TRUE;
    //        }
    //    }
    //    break;

    //case WM_NCLBUTTONDOWN:
    //    if (IsWindow(m_hwnd) && flagsOff(GetWindowLong(m_hwnd, GWL_STYLE), WS_CAPTION))
    //    {
    //        int hit = wParam;
    //        switch (hit)
    //        {
    //        case HTTOP:         SendMessageW(m_hwnd, WM_SYSCOMMAND, SC_SIZE|WMSZ_TOP, lParam); return 0;
    //        case HTBOTTOM:      SendMessageW(m_hwnd, WM_SYSCOMMAND, SC_SIZE|WMSZ_BOTTOM, lParam); return 0;
    //        case HTLEFT:        SendMessageW(m_hwnd, WM_SYSCOMMAND, SC_SIZE|WMSZ_LEFT, lParam); return 0;
    //        case HTRIGHT:       SendMessageW(m_hwnd, WM_SYSCOMMAND, SC_SIZE|WMSZ_RIGHT, lParam); return 0;
    //        case HTTOPLEFT:     SendMessageW(m_hwnd, WM_SYSCOMMAND, SC_SIZE|WMSZ_TOPLEFT, lParam); return 0;
    //        case HTTOPRIGHT:    SendMessageW(m_hwnd, WM_SYSCOMMAND, SC_SIZE|WMSZ_TOPRIGHT, lParam); return 0;
    //        case HTBOTTOMLEFT:  SendMessageW(m_hwnd, WM_SYSCOMMAND, SC_SIZE|WMSZ_BOTTOMLEFT, lParam); return 0;
    //        case HTBOTTOMRIGHT: SendMessageW(m_hwnd, WM_SYSCOMMAND, SC_SIZE|WMSZ_BOTTOMRIGHT, lParam); return 0;
    //        case HTCAPTION:     SendMessageW(m_hwnd, WM_SYSCOMMAND, SC_MOVE|4, lParam); return 0;
    //        }
    //    }
    //    break;

    //case WM_NCLBUTTONDBLCLK:
    //    if (IsWindow(m_hwnd) && flagsOff(GetWindowLong(m_hwnd, GWL_STYLE), WS_CAPTION))
    //    {
    //        int hit = wParam;
    //        if (hit == HTCAPTION)
    //        {
    //            if (IsZoomed(m_hwnd))
    //                SendMessageW(m_hwnd, WM_SYSCOMMAND, SC_RESTORE, lParam);
    //            else
    //                SendMessageW(m_hwnd, WM_SYSCOMMAND, SC_MAXIMIZE, lParam);
    //            return 0;
    //        }
    //    }
    //    break;

    case WM_KEYDOWN:
        {
            unsigned int virtualKeyCode = wParam;
            unsigned int flags = 0;
            if (HIWORD(lParam) & KF_REPEAT)
                flags |= WKE_REPEAT;
            if (HIWORD(lParam) & KF_EXTENDED)
                flags |= WKE_EXTENDED;

            if (wkeFireKeyDownEvent(this, virtualKeyCode, flags, false))
                return 0;
        }
        break;

    case WM_KEYUP:
        {
            unsigned int virtualKeyCode = wParam;
            unsigned int flags = 0;
            if (HIWORD(lParam) & KF_REPEAT)
                flags |= WKE_REPEAT;
            if (HIWORD(lParam) & KF_EXTENDED)
                flags |= WKE_EXTENDED;

            if (wkeFireKeyUpEvent(this, virtualKeyCode, flags, false))
                return 0;
        }
        break;

    case WM_CHAR:
        {
            unsigned int charCode = wParam;
            unsigned int flags = 0;
            if (HIWORD(lParam) & KF_REPEAT)
                flags |= WKE_REPEAT;
            if (HIWORD(lParam) & KF_EXTENDED)
                flags |= WKE_EXTENDED;

            if (wkeFireKeyPressEvent(this, charCode, flags, false))
                return 0;
        }
        break;

    case WM_LBUTTONDOWN:
    case WM_MBUTTONDOWN:
    case WM_RBUTTONDOWN:
    case WM_LBUTTONDBLCLK:
    case WM_MBUTTONDBLCLK:
    case WM_RBUTTONDBLCLK:
    case WM_LBUTTONUP:
    case WM_MBUTTONUP:
    case WM_RBUTTONUP:
    case WM_MOUSEMOVE:
        {
            if (message == WM_LBUTTONDOWN || message == WM_MBUTTONDOWN || message == WM_RBUTTONDOWN)
            {
                SetFocus(hwnd);
                SetCapture(hwnd);
            }
            else if (message == WM_LBUTTONUP || message == WM_MBUTTONUP || message == WM_RBUTTONUP)
            {
                ReleaseCapture();
            }

            int x = LOWORD(lParam);
            int y = HIWORD(lParam);

            unsigned int flags = 0;

            if (wParam & MK_CONTROL)
                flags |= WKE_CONTROL;
            if (wParam & MK_SHIFT)
                flags |= WKE_SHIFT;

            if (wParam & MK_LBUTTON)
                flags |= WKE_LBUTTON;
            if (wParam & MK_MBUTTON)
                flags |= WKE_MBUTTON;
            if (wParam & MK_RBUTTON)
                flags |= WKE_RBUTTON;

            if (wkeFireMouseEvent(this, message, x, y, flags))
                return 0;
        }
        break;

    case WM_CONTEXTMENU:
        {
            POINT pt;
            pt.x = LOWORD(lParam);
            pt.y = HIWORD(lParam);

            if (pt.x != -1 && pt.y != -1)
                ScreenToClient(hwnd, &pt);

            unsigned int flags = 0;

            if (wParam & MK_CONTROL)
                flags |= WKE_CONTROL;
            if (wParam & MK_SHIFT)
                flags |= WKE_SHIFT;

            if (wParam & MK_LBUTTON)
                flags |= WKE_LBUTTON;
            if (wParam & MK_MBUTTON)
                flags |= WKE_MBUTTON;
            if (wParam & MK_RBUTTON)
                flags |= WKE_RBUTTON;

            if (wkeFireContextMenuEvent(this, pt.x, pt.y, flags))
                return 0;
        }
        break;

    case WM_MOUSEWHEEL:
        {
            POINT pt;
            pt.x = LOWORD(lParam);
            pt.y = HIWORD(lParam);
            ScreenToClient(hwnd, &pt);

            int delta = GET_WHEEL_DELTA_WPARAM(wParam);

            unsigned int flags = 0;

            if (wParam & MK_CONTROL)
                flags |= WKE_CONTROL;
            if (wParam & MK_SHIFT)
                flags |= WKE_SHIFT;

            if (wParam & MK_LBUTTON)
                flags |= WKE_LBUTTON;
            if (wParam & MK_MBUTTON)
                flags |= WKE_MBUTTON;
            if (wParam & MK_RBUTTON)
                flags |= WKE_RBUTTON;

            if (wkeFireMouseWheelEvent(this, pt.x, pt.y, delta, flags))
                return 0;
        }
        break;

    case WM_SETFOCUS:
        wkeSetFocus(this);
        return 0;

    case WM_KILLFOCUS:
        wkeKillFocus(this);
        return 0;

    case WM_IME_STARTCOMPOSITION:
        {
            wkeRect caret = wkeGetCaretRect(this);

            CANDIDATEFORM form;
            form.dwIndex = 0;
            form.dwStyle = CFS_EXCLUDE;
            form.ptCurrentPos.x = caret.x;
            form.ptCurrentPos.y = caret.y + caret.h;
            form.rcArea.top = caret.y;
            form.rcArea.bottom = caret.y + caret.h;
            form.rcArea.left = caret.x;
            form.rcArea.right = caret.x + caret.w;

            COMPOSITIONFORM compForm;
            compForm.ptCurrentPos = form.ptCurrentPos;
            compForm.rcArea = form.rcArea;
            compForm.dwStyle = CFS_POINT;

            HIMC hIMC = ImmGetContext(hwnd);
            ImmSetCandidateWindow(hIMC, &form);
            ImmSetCompositionWindow(hIMC, &compForm);
            ImmReleaseContext(hwnd, hIMC);
        }
        return 0;
    }

    return DefWindowProcW(hwnd, message, wParam, lParam);
}