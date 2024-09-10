LRESULT CALLBACK PropsTabWndWndProc(HWND hwnd, UINT iMessage, WPARAM wParam,
    LPARAM lParam)
{
    static int selected, sizingbottom;
    static HIMAGELIST tabIml;
    static int ilProps, ilToolbox;
    RECT r;
    TC_ITEM tie;
    NMHDR *h;
    DRAWITEMSTRUCT *dr;
    HFONT font;
    HBITMAP hbmp;
    HDC hMemDC;
    PAINTSTRUCT paint;
    HDC dc;
    switch (iMessage)
    {
        case WM_SYSCOMMAND:
            if (wParam == SC_CLOSE)
            {
                PostMessage(hwnd, WM_CLOSE, 0, 0);
                return 0;
            }
            break;
        case WM_NOTIFY:
            h = (NMHDR*)lParam;
            switch (h->code)
            {
            case TCN_SELCHANGE:
                switch (selected = TabCtrl_GetCurSel(hwndPropsTabCtrl))
                {
                case 0:
                    ShowWindow(hwndToolbox, SW_HIDE) ;
                    ShowWindow(hwndProps, SW_SHOW) ;
                    break;
                case 1:
                    ShowWindow(hwndProps, SW_HIDE) ;
                    ShowWindow(hwndToolbox, SW_SHOW) ;
                    break;
                }
            }
            break;
        case WM_SETTEXT:
            return SendMessage(hwndPropsTabCtrl, iMessage, wParam, lParam);
        case WM_DRAWITEM:
            dr = (DRAWITEMSTRUCT*)lParam;
            hMemDC = CreateCompatibleDC(dr->hDC);
            hbmp = SelectObject(hMemDC,  *bitmaps[dr->itemID]);
            BitBlt(dr->hDC, dr->rcItem.left + 2, dr->rcItem.bottom - 18, 16, 16,
                hMemDC, 0, 0, SRCCOPY);
            font = SelectObject(dr->hDC, font);
            TextOut(dr->hDC, dr->rcItem.left + 18, dr->rcItem.bottom - 16,
                nameTags[dr->itemID], strlen(nameTags[dr->itemID]));
            font = SelectObject(dr->hDC, font);
            SelectObject(dr->hDC, hbmp);
            DeleteDC(hMemDC);
            break;
        case WM_CREATE:
            hwndPropsTab = hwnd;
            GetClientRect(hwnd, &r);
            hwndPropsTabCtrl = CreateWindow(WC_TABCONTROL, 0, WS_CHILD +
                WS_CLIPSIBLINGS + WS_VISIBLE + TCS_FLATBUTTONS /*+ TCS_OWNERDRAWFIXED */
                + TCS_FOCUSNEVER /*+ TCS_FIXEDWIDTH*/ + TCS_BOTTOM, r.left, r.top,
                r.right - r.left, r.bottom - r.top, hwnd, 0, hInstance, 0);
            ApplyDialogFont(hwndPropsTabCtrl);
            propsBitMap = LoadImage(hInstance, "ID_PROPSBMP", IMAGE_BITMAP,0,0,LR_DEFAULTSIZE | LR_LOADMAP3DCOLORS);
            toolsBitMap = LoadImage(hInstance, "ID_TOOLBOXBMP", IMAGE_BITMAP,0,0,LR_DEFAULTSIZE | LR_LOADMAP3DCOLORS);
            tabIml = ImageList_Create(16, 16, ILC_COLOR32, 1, 0);
            ilProps = ImageList_Add(tabIml, propsBitMap, 0);
            ilToolbox = ImageList_Add(tabIml, toolsBitMap, 0);
            TabCtrl_SetImageList(hwndPropsTabCtrl, tabIml);

            CreatePropsWindow();
            CreateCtlTbWindow();
            tie.mask = TCIF_TEXT | TCIF_IMAGE;
            tie.iImage = ilProps;
            tie.pszText = nameTags[0];
            TabCtrl_InsertItem(hwndPropsTabCtrl, 0, &tie);
            tie.mask = TCIF_TEXT | TCIF_IMAGE ;
            tie.iImage = ilToolbox ;
            tie.pszText  = nameTags[1] ;
            TabCtrl_InsertItem(hwndPropsTabCtrl,1, &tie) ;
            ShowWindow(hwndToolbox,SW_HIDE) ;
            return 0;
        case WM_COMMAND:
            break;
		case WM_SELERRWINDOW:
			{
				NMHDR xx;
				memset(&xx, 0, sizeof(xx));
				xx.code = TCN_SELCHANGE;
				TabCtrl_SetCurSel(hwndPropsTabCtrl, lParam);
				SendMessage(hwnd, WM_NOTIFY, 0, (LPARAM)&xx);
			}
			break;
        case WM_PAINT:
            dc = BeginPaint(hwnd, &paint);
            EndPaint(hwnd, &paint);
            break;
        case WM_DESTROY:
            DestroyWindow(hwndToolbox) ;
            DestroyWindow(hwndProps);
            DestroyWindow(hwndPropsTabCtrl);
            DeleteObject(propsBitMap);
            DeleteObject(toolsBitMap);
            hwndPropsTab = 0;
            break;
        case WM_SIZE:
            r.right = LOWORD(lParam);
            r.bottom = HIWORD(lParam);
            r.left = r.top = 0;
            MoveWindow(hwndPropsTabCtrl, r.left, r.top, r.right - r.left, r.bottom -
                r.top, 1);
            GetPropsTabRect(&r);
            MoveWindow(hwndProps, r.left, r.top, r.right - r.left, r.bottom -
                r.top, 1);
            MoveWindow( hwndToolbox,r.left,r.top,r.right-r.left,r.bottom-r.top,TRUE) ;
            break;
        case WM_CLOSE:
            break;
    }
    return DefWindowProc(hwnd, iMessage, wParam, lParam);
}