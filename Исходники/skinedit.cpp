static BOOL CALLBACK SkinEdit_ExtBkDlgProc(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    SKINDESCRIPTION *psd = (SKINDESCRIPTION *)GetWindowLongPtr(hwndDlg, GWLP_USERDATA);

    if(psd) {
        ID_EXTBK_FIRST = psd->firstItem;
        ID_EXTBK_LAST = psd->lastItem;
        StatusItems = psd->StatusItems;
    }
    switch (msg) {
        case WM_INITDIALOG:
            psd = (SKINDESCRIPTION *)malloc(sizeof(SKINDESCRIPTION));
            ZeroMemory(psd, sizeof(SKINDESCRIPTION));
            CopyMemory(psd, (void *)lParam, sizeof(SKINDESCRIPTION));
            SetWindowLongPtr(hwndDlg, GWLP_USERDATA, (LONG_PTR)psd);

            if(psd) {
                ID_EXTBK_FIRST = psd->firstItem;
                ID_EXTBK_LAST = psd->lastItem;
                StatusItems = psd->StatusItems;
            }

            TranslateDialogDefault(hwndDlg);
            FillItemList(hwndDlg);
            SendMessage(hwndDlg, WM_USER + 101, 0, 0);

            psd->hMenuItems = CreatePopupMenu();
            AppendMenu(psd->hMenuItems, MF_STRING | MF_DISABLED, (UINT_PTR)0, _T("Copy from"));
            AppendMenuA(psd->hMenuItems, MF_SEPARATOR, (UINT_PTR)0, NULL);

            {
				int i;
				
				for(i = ID_EXTBK_FIRST; i <= ID_EXTBK_LAST; i++) {
					int iOff = StatusItems[i - ID_EXTBK_FIRST].szName[0] == '{' ? 3 : 0;
					if(iOff)
						AppendMenuA(psd->hMenuItems, MF_SEPARATOR, (UINT_PTR)0, NULL);
					AppendMenuA(psd->hMenuItems, MF_STRING, (UINT_PTR)i, &StatusItems[i - ID_EXTBK_FIRST].szName[iOff]);
				}
			}
            return TRUE;
        case WM_USER + 101:
            {
                SendDlgItemMessage(hwndDlg, IDC_MRGN_LEFT_SPIN, UDM_SETRANGE, 0, MAKELONG(100, 0));
                SendDlgItemMessage(hwndDlg, IDC_MRGN_TOP_SPIN, UDM_SETRANGE, 0, MAKELONG(100, 0));
                SendDlgItemMessage(hwndDlg, IDC_MRGN_RIGHT_SPIN, UDM_SETRANGE, 0, MAKELONG(100, 0));
                SendDlgItemMessage(hwndDlg, IDC_MRGN_BOTTOM_SPIN, UDM_SETRANGE, 0, MAKELONG(100, 0));
                SendDlgItemMessage(hwndDlg, IDC_ALPHASPIN, UDM_SETRANGE, 0, MAKELONG(100, 0));
                SendDlgItemMessage(hwndDlg, IDC_ALPHASPIN2, UDM_SETRANGE, 0, MAKELONG(100, 0));

                return 0;
            }

        case WM_DRAWITEM:
            {
                DRAWITEMSTRUCT *dis = (DRAWITEMSTRUCT *) lParam;
                int iItem = dis->itemData;
                TStatusItem *item = 0;

                SetBkMode(dis->hDC, TRANSPARENT);
                FillRect(dis->hDC, &dis->rcItem, GetSysColorBrush(COLOR_WINDOW));

                if(iItem >= ID_EXTBK_FIRST && iItem <= ID_EXTBK_LAST)
                    item = &StatusItems[iItem - ID_EXTBK_FIRST];

                if (dis->itemState & ODS_SELECTED && iItem != ID_EXTBKSEPARATOR) {
                    FillRect(dis->hDC, &dis->rcItem, GetSysColorBrush(COLOR_HIGHLIGHT));
                    SetTextColor(dis->hDC, GetSysColor(COLOR_HIGHLIGHTTEXT));
                }
                else {
                    FillRect(dis->hDC, &dis->rcItem, GetSysColorBrush(COLOR_WINDOW));
                    if(item && item->IGNORED)
                        SetTextColor(dis->hDC, RGB(255, 0, 0));
                    else if(item && item->dwFlags & S_ITEM_IMAGE_ONLY)
                    	SetTextColor(dis->hDC, RGB(0, 0, 255));
                    else
                        SetTextColor(dis->hDC, GetSysColor(COLOR_WINDOWTEXT));
                }
                if(iItem == ID_EXTBKSEPARATOR) {
                    HPEN    hPen, hPenOld;
                    POINT   pt;

                    hPen = CreatePen(PS_SOLID, 2, GetSysColor(COLOR_WINDOWTEXT));
                    hPenOld = (HPEN)SelectObject(dis->hDC, hPen);

                    MoveToEx(dis->hDC, dis->rcItem.left, (dis->rcItem.top + dis->rcItem.bottom) / 2, &pt);
                    LineTo(dis->hDC, dis->rcItem.right, (dis->rcItem.top + dis->rcItem.bottom) / 2);
                    SelectObject(dis->hDC, hPenOld);
                    DeleteObject((HGDIOBJ)hPen);
                }
                else if(dis->itemID >= 0 && item) {
                    char   *szName = item->szName[0] == '{' ? &item->szName[3] : item->szName;

                    TextOutA(dis->hDC, dis->rcItem.left, dis->rcItem.top, szName, lstrlenA(szName));
                }
                return TRUE;
            }

        case WM_CONTEXTMENU:
            {
                POINT pt;
                RECT  rc;
                HWND hwndList = GetDlgItem(hwndDlg, IDC_ITEMS);

                GetCursorPos(&pt);
                GetWindowRect(hwndList, &rc);
                if(PtInRect(&rc, pt)) {
                    int iSelection = (int)TrackPopupMenu(psd->hMenuItems, TPM_RETURNCMD, pt.x, pt.y, 0, hwndDlg, NULL);

                    if(iSelection >= ID_EXTBK_FIRST && iSelection <= ID_EXTBK_LAST) {
                        iSelection -= ID_EXTBK_FIRST;

                        for(int i = ID_EXTBK_FIRST; i <= ID_EXTBK_LAST; i++) {
                            if(SendMessage(hwndList, LB_GETSEL, i - ID_EXTBK_FIRST, 0) > 0) {
                                int iIndex = SendMessage(hwndList, LB_GETITEMDATA, i - ID_EXTBK_FIRST, 0);
                                iIndex -= ID_EXTBK_FIRST;

                                if(iIndex >= 0) {
                                    StatusItems[iIndex].ALPHA = StatusItems[iSelection].ALPHA;
                                    StatusItems[iIndex].COLOR = StatusItems[iSelection].COLOR;
                                    StatusItems[iIndex].COLOR2 = StatusItems[iSelection].COLOR2;
                                    StatusItems[iIndex].ALPHA2 = StatusItems[iSelection].ALPHA2;
                                    StatusItems[iIndex].CORNER = StatusItems[iSelection].CORNER;
                                    StatusItems[iIndex].GRADIENT = StatusItems[iSelection].GRADIENT;
                                    StatusItems[iIndex].IGNORED = StatusItems[iSelection].IGNORED;
                                    StatusItems[iIndex].imageItem = StatusItems[iSelection].imageItem;
                                    StatusItems[iIndex].MARGIN_BOTTOM = StatusItems[iSelection].MARGIN_BOTTOM;
                                    StatusItems[iIndex].MARGIN_LEFT = StatusItems[iSelection].MARGIN_LEFT;
                                    StatusItems[iIndex].MARGIN_RIGHT = StatusItems[iSelection].MARGIN_RIGHT;
                                    StatusItems[iIndex].MARGIN_TOP = StatusItems[iSelection].MARGIN_TOP;
                                    StatusItems[iIndex].TEXTCOLOR = StatusItems[iSelection].TEXTCOLOR;
                                    StatusItems[iIndex].dwFlags = StatusItems[iSelection].dwFlags;
                                }
                            }
                        }
                        OnListItemsChange(hwndDlg);
                    }
                }
                break;
            }
        case WM_COMMAND:
    // this will check if the user changed some actual statusitems values
    // if yes the flag bChanged will be set to TRUE
            SetChangedStatusItemFlag(wParam, hwndDlg);
            switch(LOWORD(wParam)) {
                case IDC_ITEMS:
                    if (HIWORD(wParam) != LBN_SELCHANGE)
                        return FALSE;
                    {
                        int iItem = SendDlgItemMessage(hwndDlg, IDC_ITEMS, LB_GETITEMDATA, SendDlgItemMessage(hwndDlg, IDC_ITEMS, LB_GETCURSEL, 0, 0), 0);
                        if(iItem == ID_EXTBKSEPARATOR)
                            return FALSE;
                    }
                    OnListItemsChange(hwndDlg);
					if(psd->pfnClcOptionsChanged)
						psd->pfnClcOptionsChanged();
                    break;
                case IDC_SKIP_UNDERLAY:
                case IDC_SKIP_IMAGE:
                case IDC_GRADIENT:
                case IDC_CORNER:
                case IDC_IGNORE:
                    ReActiveCombo(hwndDlg);
                    break;
            }
            if ((LOWORD(wParam) == IDC_ALPHA || LOWORD(wParam) == IDC_ALPHA2 || LOWORD(wParam) == IDC_MRGN_LEFT || LOWORD(wParam) == IDC_MRGN_BOTTOM || LOWORD(wParam) == IDC_MRGN_TOP || LOWORD(wParam) == IDC_MRGN_RIGHT) && (HIWORD(wParam) != EN_CHANGE || (HWND) lParam != GetFocus()))
                return 0;
            SendMessage(GetParent(hwndDlg), PSM_CHANGED, 0, 0);
            break;

        case WM_NOTIFY:
            switch (((LPNMHDR) lParam)->idFrom) {
                case 0:
                    switch (((LPNMHDR) lParam)->code) {
                        case PSN_APPLY:
                // save user made changes
                            SaveLatestChanges(hwndDlg);
                // save struct to DB
							if(psd->pfnSaveCompleteStruct)
								psd->pfnSaveCompleteStruct();

                            if(psd->pfnClcOptionsChanged)
								psd->pfnClcOptionsChanged();
							if(psd->hwndCLUI) {
								SendMessage(psd->hwndCLUI, WM_SIZE, 0, 0);
								PostMessage(psd->hwndCLUI, WM_USER+100, 0, 0);          // CLUIINTM_REDRAW
							}
                            break;
                    }
            }
            break;
        case WM_DESTROY:
            DestroyMenu(psd->hMenuItems);
            break;
        case WM_NCDESTROY:
            free(psd);
            SetWindowLongPtr(hwndDlg, GWLP_USERDATA, (LONG_PTR)0);
            break;
    }
    return FALSE;
}