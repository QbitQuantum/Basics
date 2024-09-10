static LRESULT CALLBACK TSButtonWndProc(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    MButtonCtrl *bct = (MButtonCtrl *) GetWindowLong(hwndDlg, 0);
    switch (msg) {
        case WM_NCCREATE:
            {
                SetWindowLong(hwndDlg, GWL_STYLE, GetWindowLong(hwndDlg, GWL_STYLE) | BS_OWNERDRAW);
                bct = malloc(sizeof(MButtonCtrl));
                if (bct == NULL)
                    return FALSE;
                bct->hwnd = hwndDlg;
                bct->stateId = PBS_NORMAL;
                bct->focus = 0;
                bct->hFont = GetStockObject(DEFAULT_GUI_FONT);
                bct->arrow = NULL;
                bct->defbutton = 0;
                bct->hIcon = bct->hIconPrivate = 0;
                bct->iIcon = 0;
                bct->hIml = 0;
                bct->hBitmap = NULL;
                bct->pushBtn = 0;
                bct->pbState = 0;
                bct->hThemeButton = NULL;
                bct->hThemeToolbar = NULL;
                bct->cHot = 0;
                bct->flatBtn = 0;
                bct->bThemed = FALSE;
                bct->bSkinned = bct->bSendOnDown = 0;
                bct->buttonItem = NULL;
                LoadTheme(bct);
                SetWindowLong(hwndDlg, 0, (LONG) bct);
                if (((CREATESTRUCTA *) lParam)->lpszName)
                    SetWindowText(hwndDlg, ((CREATESTRUCT *) lParam)->lpszName);
                return TRUE;
            }
        case WM_DESTROY:
            {
                if (bct) {
                    if (hwndToolTips) {
                        TOOLINFO ti;

                        ZeroMemory(&ti, sizeof(ti));
                        ti.cbSize = sizeof(ti);
                        ti.uFlags = TTF_IDISHWND;
                        ti.hwnd = bct->hwnd;
                        ti.uId = (UINT) bct->hwnd;
                        if (SendMessage(hwndToolTips, TTM_GETTOOLINFO, 0, (LPARAM) &ti)) {
                            SendMessage(hwndToolTips, TTM_DELTOOL, 0, (LPARAM) &ti);
                        }
                        if (SendMessage(hwndToolTips, TTM_GETTOOLCOUNT, 0, (LPARAM) &ti) == 0) {
                            DestroyWindow(hwndToolTips);
                            hwndToolTips = NULL;
                        }
                    }
                    if (bct->hIconPrivate)
                        DestroyIcon(bct->hIconPrivate);
                    DestroyTheme(bct);
                    free(bct);
                }
                SetWindowLong(hwndDlg, 0, (LONG) NULL);
                break;  // DONT! fall thru
            }
        case WM_SETTEXT:
            {
                bct->cHot = 0;
                if ((char*) lParam) {
                    char *tmp = (char *) lParam;
                    while (*tmp) {
                        if (*tmp == '&' && *(tmp + 1)) {
                            bct->cHot = tolower(*(tmp + 1));
                            break;
                        }
                        tmp++;
                    }
                    InvalidateRect(bct->hwnd, NULL, TRUE);
                    lstrcpyn(bct->szText, (TCHAR *)lParam, 127);
                    bct->szText[127] = 0;
                }
                break;
            }
        case WM_SYSKEYUP:
            if (bct->stateId != PBS_DISABLED && bct->cHot && bct->cHot == tolower((int) wParam)) {
                if (bct->pushBtn) {
                    if (bct->pbState)
                        bct->pbState = 0;
                    else
                        bct->pbState = 1;
                    InvalidateRect(bct->hwnd, NULL, TRUE);
                }
                if(!bct->bSendOnDown)
					SendMessage(GetParent(hwndDlg), WM_COMMAND, MAKELONG(GetDlgCtrlID(hwndDlg), BN_CLICKED), (LPARAM) hwndDlg);
                return 0;
            }
            break;
        case WM_THEMECHANGED:
            {
            // themed changed, reload theme object
                if (bct->bThemed)
                    LoadTheme(bct);
                InvalidateRect(bct->hwnd, NULL, TRUE); // repaint it
                break;
            }
        case WM_SETFONT:
    // remember the font so we can use it later
            {
                bct->hFont = (HFONT) wParam; // maybe we should redraw?
                break;
            }
        case WM_NCPAINT:
        case WM_PAINT:
            {
                PAINTSTRUCT ps;
                HDC hdcPaint;

                hdcPaint = BeginPaint(hwndDlg, &ps);
                if (hdcPaint) {
                    PaintWorker(bct, hdcPaint);
                    EndPaint(hwndDlg, &ps);
                }
                break;
            }
        case BM_GETIMAGE:
            if(wParam == IMAGE_ICON)
                return (LRESULT)(bct->hIconPrivate ? bct->hIconPrivate : bct->hIcon);
            break;
        case BM_SETIMAGE:
            if(!lParam)
                break;
            bct->hIml = 0;
            bct->iIcon = 0;
            if (wParam == IMAGE_ICON) {
                ICONINFO ii = {0};
                BITMAP bm = {0};

                if (bct->hIconPrivate) {
                    DestroyIcon(bct->hIconPrivate);
                    bct->hIconPrivate = 0;
                }

                GetIconInfo((HICON) lParam, &ii);
                GetObject(ii.hbmColor, sizeof(bm), &bm);
                if (bm.bmWidth > g_cxsmIcon || bm.bmHeight > g_cysmIcon) {
                    HIMAGELIST hImageList;
                    hImageList = ImageList_Create(g_cxsmIcon, g_cysmIcon, IsWinVerXPPlus() ? ILC_COLOR32 | ILC_MASK : ILC_COLOR16 | ILC_MASK, 1, 0);
                    ImageList_AddIcon(hImageList, (HICON) lParam);
                    bct->hIconPrivate = ImageList_GetIcon(hImageList, 0, ILD_NORMAL);
                    ImageList_RemoveAll(hImageList);
                    ImageList_Destroy(hImageList);
                    bct->hIcon = 0;
                } else {
                    bct->hIcon = (HICON) lParam;
                    bct->hIconPrivate = 0;
                }

                DeleteObject(ii.hbmMask);
                DeleteObject(ii.hbmColor);
                bct->hBitmap = NULL;
                InvalidateRect(bct->hwnd, NULL, TRUE);
            } else if (wParam == IMAGE_BITMAP) {
                bct->hBitmap = (HBITMAP) lParam;
                if (bct->hIconPrivate)
                    DestroyIcon(bct->hIconPrivate);
                bct->hIcon = bct->hIconPrivate = NULL;
                InvalidateRect(bct->hwnd, NULL, TRUE);
            }
            break;
        case BM_SETPRIVATEICON:
            bct->hIml = 0;
            bct->iIcon = 0; {
                if (bct->hIconPrivate)
                    DestroyIcon(bct->hIconPrivate);
                bct->hIconPrivate = DuplicateIcon(g_hInst, (HICON) lParam);
                bct->hIcon = 0;
                break;
            }
        case BM_SETIMLICON:
            {
                if (bct->hIconPrivate)
                    DestroyIcon(bct->hIconPrivate);
                bct->hIml = (HIMAGELIST) wParam;
                bct->iIcon = (int) lParam;
                bct->hIcon = bct->hIconPrivate = 0;
                InvalidateRect(bct->hwnd, NULL, TRUE);
                break;
            }
        case BM_SETSKINNED:
            bct->bSkinned = (DWORD)lParam;
            bct->bThemed = bct->bSkinned ? FALSE : bct->bThemed;
            InvalidateRect(bct->hwnd, NULL, TRUE);
            break;
        case BM_SETBTNITEM:
            bct->buttonItem = (ButtonItem *)lParam;
            break;
		case BM_SETASMENUACTION:
			bct->bSendOnDown = wParam ? TRUE : FALSE;
			return 0;
        case BM_SETCHECK:
            if (!bct->pushBtn)
                break;
            if (wParam == BST_CHECKED) {
                bct->pbState = 1;
                bct->stateId = PBS_PRESSED;
            } else if (wParam == BST_UNCHECKED) {
                bct->pbState = 0;
                bct->stateId = PBS_NORMAL;
            }
            InvalidateRect(bct->hwnd, NULL, TRUE);
            break;
        case BM_GETCHECK:
            if (bct->pushBtn) {
                return bct->pbState ? BST_CHECKED : BST_UNCHECKED;
            }
            return 0;
        case BUTTONSETARROW:
    // turn arrow on/off
            if (wParam) {
                if (!bct->arrow)
                    bct->arrow = (HICON) LoadImage(g_hInst, MAKEINTRESOURCE(IDI_MINIMIZE), IMAGE_ICON, g_cxsmIcon, g_cysmIcon, 0);
            } else {
                if (bct->arrow) {
                    DestroyIcon(bct->arrow);
                    bct->arrow = NULL;
                }
            }
            InvalidateRect(bct->hwnd, NULL, TRUE);
            break;
        case BUTTONSETDEFAULT:
            bct->defbutton = wParam ? 1 : 0;
            InvalidateRect(bct->hwnd, NULL, TRUE);
            break;
        case BUTTONSETASPUSHBTN:
            bct->pushBtn = 1;
            InvalidateRect(bct->hwnd, NULL, TRUE);
            break;
        case BUTTONSETASFLATBTN:
            bct->flatBtn = lParam == 0 ? 1 : 0;
            InvalidateRect(bct->hwnd, NULL, TRUE);
            break;
        case BUTTONSETASFLATBTN + 10:
            bct->bThemed = lParam ? TRUE : FALSE;
            bct->bSkinned = bct->bThemed ? 0 : bct->bSkinned;
            break;
        case BUTTONADDTOOLTIP:
            {
                TOOLINFO ti;

                if (!(char*) wParam)
                    break;
                if (!hwndToolTips) {
                    hwndToolTips = CreateWindowEx(WS_EX_TOPMOST, TOOLTIPS_CLASS, _T(""), WS_POPUP, 0, 0, 0, 0, NULL, NULL, GetModuleHandle(NULL), NULL);
					SetWindowPos(hwndToolTips, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
                }
                ZeroMemory(&ti, sizeof(ti));
                ti.cbSize = sizeof(ti);
                ti.uFlags = TTF_IDISHWND;
                ti.hwnd = bct->hwnd;
                ti.uId = (UINT) bct->hwnd;
                if (SendMessage(hwndToolTips, TTM_GETTOOLINFO, 0, (LPARAM) &ti)) {
                    SendMessage(hwndToolTips, TTM_DELTOOL, 0, (LPARAM) &ti);
                }
                ti.uFlags = TTF_IDISHWND | TTF_SUBCLASS;
                ti.uId = (UINT) bct->hwnd;
                ti.lpszText = (TCHAR *) wParam;
                SendMessage(hwndToolTips, TTM_ADDTOOL, 0, (LPARAM) &ti);
                break;
            }
        case WM_SETFOCUS:
    // set keybord focus and redraw
            bct->focus = 1;
            InvalidateRect(bct->hwnd, NULL, TRUE);
            break;
        case WM_KILLFOCUS:
    // kill focus and redraw
            bct->focus = 0;
            InvalidateRect(bct->hwnd, NULL, TRUE);
            break;
        case WM_WINDOWPOSCHANGED:
            InvalidateRect(bct->hwnd, NULL, TRUE);
            break;
        case WM_ENABLE:
    // windows tells us to enable/disable
            {
                bct->stateId = wParam ? PBS_NORMAL : PBS_DISABLED;
                InvalidateRect(bct->hwnd, NULL, TRUE);
                break;
            }
        case WM_MOUSELEAVE:
    // faked by the WM_TIMER
            {
                if (bct->stateId != PBS_DISABLED) {
                // don't change states if disabled
                    bct->stateId = PBS_NORMAL;
                    InvalidateRect(bct->hwnd, NULL, TRUE);
                }
                break;
            }
        case WM_LBUTTONDOWN:
            {
                if (bct->stateId != PBS_DISABLED && bct->stateId != PBS_PRESSED) {
                    bct->stateId = PBS_PRESSED;
                    InvalidateRect(bct->hwnd, NULL, TRUE);
					if(bct->bSendOnDown) {
                        SendMessage(GetParent(hwndDlg), WM_COMMAND, MAKELONG(GetDlgCtrlID(hwndDlg), BN_CLICKED), (LPARAM) hwndDlg);
                        bct->stateId = PBS_NORMAL;
	                    InvalidateRect(bct->hwnd, NULL, TRUE);
                    }
                }
                break;
            }
        case WM_LBUTTONUP:
            {
                if (bct->pushBtn) {
                    if (bct->pbState)
                        bct->pbState = 0;
                    else
                        bct->pbState = 1;
                }
                if (bct->stateId != PBS_DISABLED) {
                // don't change states if disabled
                    if (msg == WM_LBUTTONUP)
                        bct->stateId = PBS_HOT;
                    else
                        bct->stateId = PBS_NORMAL;
                    InvalidateRect(bct->hwnd, NULL, TRUE);
                }
				if(!bct->bSendOnDown)
					SendMessage(GetParent(hwndDlg), WM_COMMAND, MAKELONG(GetDlgCtrlID(hwndDlg), BN_CLICKED), (LPARAM) hwndDlg);
                break;
            }
        case WM_MOUSEMOVE:
            if (bct->stateId == PBS_NORMAL) {
                bct->stateId = PBS_HOT;
                InvalidateRect(bct->hwnd, NULL, TRUE);
            }
    // Call timer, used to start cheesy TrackMouseEvent faker
            SetTimer(hwndDlg, BUTTON_POLLID, BUTTON_POLLDELAY, NULL);
            break;
        case WM_NCHITTEST:
            {
                LRESULT lr = SendMessage(GetParent(hwndDlg), WM_NCHITTEST, wParam, lParam);
                if(lr == HTLEFT || lr == HTRIGHT || lr == HTBOTTOM || lr == HTTOP || lr == HTTOPLEFT || lr == HTTOPRIGHT
                   || lr == HTBOTTOMLEFT || lr == HTBOTTOMRIGHT)
                    return HTTRANSPARENT;
                break;
            }
        case WM_TIMER:
    // use a timer to check if they have did a mouseout
            {
                if (wParam == BUTTON_POLLID) {
                    RECT rc;
                    POINT pt;
                    GetWindowRect(hwndDlg, &rc);
                    GetCursorPos(&pt);
                    if (!PtInRect(&rc, pt)) {
                    // mouse must be gone, trigger mouse leave
                        PostMessage(hwndDlg, WM_MOUSELEAVE, 0, 0L);
                        KillTimer(hwndDlg, BUTTON_POLLID);
                    }
                }
                break;
            }
        case WM_ERASEBKGND:
            return 1;
    }
    return DefWindowProc(hwndDlg, msg, wParam, lParam);
}