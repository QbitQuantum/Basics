/*******************************************************************************
 *
 *  FUNCTION: ChildWndProc(HWND, unsigned, WORD, LONG)
 *
 *  PURPOSE:  Processes messages for the child windows.
 *
 *  WM_COMMAND  - process the application menu
 *  WM_PAINT    - Paint the main window
 *  WM_DESTROY  - post a quit message and return
 *
 */
LRESULT CALLBACK ChildWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
    case WM_CREATE:
        g_pChildWnd = HeapAlloc(GetProcessHeap(), 0, sizeof(ChildWnd));
        if (!g_pChildWnd) return 0;
        LoadStringW(hInst, IDS_REGISTRY_ROOT_NAME, g_pChildWnd->szPath, MAX_PATH);
        g_pChildWnd->nSplitPos = 250;
        g_pChildWnd->hWnd = hWnd;
        g_pChildWnd->hTreeWnd = CreateTreeView(hWnd, g_pChildWnd->szPath, TREE_WINDOW);
        g_pChildWnd->hListWnd = CreateListView(hWnd, LIST_WINDOW/*, g_pChildWnd->szPath*/);
        g_pChildWnd->nFocusPanel = 1;
        SetFocus(g_pChildWnd->hTreeWnd);
        get_last_key(g_pChildWnd->hTreeWnd);
        break;
    case WM_COMMAND:
        if (!_CmdWndProc(hWnd, message, wParam, lParam)) {
            goto def;
        }
        break;
    case WM_PAINT:
        OnPaint(hWnd);
        return 0;
    case WM_SETCURSOR:
        if (LOWORD(lParam) == HTCLIENT) {
            POINT pt;
            GetCursorPos(&pt);
            ScreenToClient(hWnd, &pt);
            if (pt.x>=g_pChildWnd->nSplitPos-SPLIT_WIDTH/2 && pt.x<g_pChildWnd->nSplitPos+SPLIT_WIDTH/2+1) {
                SetCursor(LoadCursorW(0, (LPCWSTR)IDC_SIZEWE));
                return TRUE;
            }
        }
        goto def;
    case WM_DESTROY:
        set_last_key(g_pChildWnd->hTreeWnd);
        HeapFree(GetProcessHeap(), 0, g_pChildWnd);
        g_pChildWnd = NULL;
        PostQuitMessage(0);
        break;
    case WM_LBUTTONDOWN: {
            RECT rt;
            int x = (short)LOWORD(lParam);
            GetClientRect(hWnd, &rt);
            if (x>=g_pChildWnd->nSplitPos-SPLIT_WIDTH/2 && x<g_pChildWnd->nSplitPos+SPLIT_WIDTH/2+1) {
                last_split = g_pChildWnd->nSplitPos;
                draw_splitbar(hWnd, last_split);
                SetCapture(hWnd);
            }
            break;
        }

    /* WM_RBUTTONDOWN sets the splitbar the same way as WM_LBUTTONUP */
    case WM_LBUTTONUP:
    case WM_RBUTTONDOWN:
        if (GetCapture() == hWnd) {
            finish_splitbar(hWnd, LOWORD(lParam));
        }
        break;

    case WM_CAPTURECHANGED:
        if (GetCapture()==hWnd && last_split>=0)
            draw_splitbar(hWnd, last_split);
        break;

    case WM_KEYDOWN:
        if (wParam == VK_ESCAPE)
            if (GetCapture() == hWnd) {
                RECT rt;
                draw_splitbar(hWnd, last_split);
                GetClientRect(hWnd, &rt);
                ResizeWnd(rt.right, rt.bottom);
                last_split = -1;
                ReleaseCapture();
                SetCursor(LoadCursorW(0, (LPCWSTR)IDC_ARROW));
            }
        break;

    case WM_MOUSEMOVE:
        if (GetCapture() == hWnd) {
            RECT rt;
            int x = LOWORD(lParam);
            HDC hdc = GetDC(hWnd);
            GetClientRect(hWnd, &rt);
            rt.left = last_split-SPLIT_WIDTH/2;
            rt.right = last_split+SPLIT_WIDTH/2+1;
            InvertRect(hdc, &rt);
            last_split = x;
            rt.left = x-SPLIT_WIDTH/2;
            rt.right = x+SPLIT_WIDTH/2+1;
            InvertRect(hdc, &rt);
            ReleaseDC(hWnd, hdc);
        }
        break;

    case WM_SETFOCUS:
        if (g_pChildWnd != NULL) {
            SetFocus(g_pChildWnd->nFocusPanel? g_pChildWnd->hListWnd: g_pChildWnd->hTreeWnd);
        }
        break;

    case WM_TIMER:
        break;

    case WM_NOTIFY:
        if (((int)wParam == TREE_WINDOW) && (g_pChildWnd != NULL)) {
            switch (((LPNMHDR)lParam)->code) {
            case TVN_ITEMEXPANDINGW:
                return !OnTreeExpanding(g_pChildWnd->hTreeWnd, (NMTREEVIEWW*)lParam);
            case TVN_SELCHANGEDW:
                OnTreeSelectionChanged(g_pChildWnd->hTreeWnd, g_pChildWnd->hListWnd,
                    ((NMTREEVIEWW *)lParam)->itemNew.hItem, TRUE);
                break;
	    case NM_SETFOCUS:
		g_pChildWnd->nFocusPanel = 0;
		break;
            case NM_RCLICK: {
		POINT pt;
                GetCursorPos(&pt);
		TrackPopupMenu(GetSubMenu(hPopupMenus, PM_NEW),
			       TPM_RIGHTBUTTON, pt.x, pt.y, 0, hFrameWnd, NULL);
		break;
            }
            case TVN_BEGINLABELEDITW: {
                HKEY hRootKey;
                LPWSTR path = GetItemPath(g_pChildWnd->hTreeWnd, 0, &hRootKey);
                if (!path || !*path) return 1;
                return 0;
            }
	    case TVN_ENDLABELEDITW: {
		HKEY hRootKey;
	        LPNMTVDISPINFOW dispInfo = (LPNMTVDISPINFOW)lParam;
		LPWSTR path = GetItemPath(g_pChildWnd->hTreeWnd, 0, &hRootKey);
	        BOOL res = RenameKey(hWnd, hRootKey, path, dispInfo->item.pszText);
		if (res) {
		    TVITEMEXW item;
                    LPWSTR fullPath = GetPathFullPath(g_pChildWnd->hTreeWnd,
                     dispInfo->item.pszText);
		    item.mask = TVIF_HANDLE | TVIF_TEXT;
		    item.hItem = (HTREEITEM)SendMessageW(g_pChildWnd->hTreeWnd, TVM_GETNEXTITEM, TVGN_CARET, 0);
		    item.pszText = dispInfo->item.pszText;
                    SendMessageW( g_pChildWnd->hTreeWnd, TVM_SETITEMW, 0, (LPARAM)&item );
                    SendMessageW(hStatusBar, SB_SETTEXTW, 0, (LPARAM)fullPath);
                    HeapFree(GetProcessHeap(), 0, fullPath);
		}
                HeapFree(GetProcessHeap(), 0, path);
		return res;
	    }
            default:
                return 0; /* goto def; */
            }
        } else
            if (((int)wParam == LIST_WINDOW) && (g_pChildWnd != NULL)) {
		if (((LPNMHDR)lParam)->code == NM_SETFOCUS) {
		    g_pChildWnd->nFocusPanel = 1;
		} else if (!SendMessageW(g_pChildWnd->hListWnd, WM_NOTIFY_REFLECT, wParam, lParam)) {
                    goto def;
                }
            }
        break;

    case WM_SIZE:
        if (wParam != SIZE_MINIMIZED && g_pChildWnd != NULL) {
            ResizeWnd(LOWORD(lParam), HIWORD(lParam));
        }
        /* fall through */
default: def:
        return DefWindowProcW(hWnd, message, wParam, lParam);
    }
    return 0;
}