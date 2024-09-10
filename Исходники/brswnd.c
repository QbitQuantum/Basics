LRESULT CALLBACK BrowseProc(HWND hwnd, UINT iMessage, WPARAM
    wParam, LPARAM lParam)
{
    static HFONT font;
    LV_ITEM item;
    POINT pt;
    LV_COLUMN lvC;
    RECT r;
    int i;
    LPNMHDR nmh;
    static LVITEM pressed;
    switch (iMessage)
    {
        case WM_USER+1:
        {
            DWINFO info;
            char *q;
            memset(&info,0, sizeof(info));
            strcpy(info.dwName, browselist[pressed.lParam]->file);
            q = strrchr(info.dwName, '\\');
            if (q)
                strcpy(info.dwTitle, q + 1);
            else
                strcpy(info.dwTitle, info.dwName);
            info.dwLineNo = TagNewLine(browselist[pressed.lParam]->file, browselist[pressed.lParam]->line);
            info.logMRU = FALSE;
            info.newFile = FALSE;
            CreateDrawWindow(&info, TRUE);
            break;
        }
        case WM_CTLCOLORSTATIC:
        {
            return (LRESULT)(HBRUSH)(COLOR_INACTIVECAPTION + 1);
        }
        case WM_CTLCOLORBTN:
        {
            return (LRESULT)GetStockObject(NULL_BRUSH);
        }

        case WM_NOTIFY:
            nmh = (LPNMHDR)lParam;
            if (nmh->code == NM_SETFOCUS)
            {
                PostMessage(hwndFrame, WM_REDRAWTOOLBAR, 0, 0);
                SendMessage(GetParent(hwnd), WM_ACTIVATEME, 0, 0);
            }
            else if (nmh->code == LVN_GETDISPINFO)
            {
                LV_DISPINFO *p = (LV_DISPINFO *)lParam;
                char name[512] = "", *q;
                switch (p->item.iSubItem)
                {
                    case 1: /* id*/
                        sprintf(name,"%d", p->item.lParam +1);
                        break;
                    case 2: /*name*/
                        strcpy(name, browselist[p->item.lParam]->name);
                        break;
                    case 3: /* browse */
                        sprintf(name, "%d", browselist[p->item.lParam]->line);
                        break;
                    case 4: /*file*/
                        q = strrchr(browselist[p->item.lParam]->file, '\\');
                        if (!q)
                            q = browselist[p->item.lParam]->file;
                        else
                            q++;
                        strcpy(name, q);
                        break;
                }
                if (name[0])
                {
                    p->item.mask |= LVIF_TEXT | LVIF_DI_SETITEM;
                    p->item.mask &= ~LVIF_STATE;
                    p->item.pszText = name;
                }
            }
            else if (((LPNMHDR)lParam)->code == NM_DBLCLK)
            {
                LVHITTESTINFO hittest;
                GetCursorPos(&hittest.pt);
                ScreenToClient(hwndLV, &hittest.pt);
                if (ListView_SubItemHitTest(hwndLV, &hittest) >= 0)
                {
                    LVITEM lvitem;
                    lvitem.iItem = hittest.iItem;
                    lvitem.iSubItem = 0;
                    lvitem.mask = LVIF_PARAM;
                    ListView_GetItem(hwndLV, &lvitem);
                    memcpy(&pressed, &lvitem, sizeof(pressed));
                    SendMessage(hwnd, WM_USER + 1, 0, 0);
                }
            }
            else if (nmh->code == LVN_KEYDOWN)
            {
                switch (((LPNMLVKEYDOWN)lParam)->wVKey)
                {
                    case 'C':
                        if (GetKeyState(VK_CONTROL) &0x80000000)
                        {
                            CopyText(hwnd);
                        }
                        break;
                    case VK_UP:
                        if (curSel > 0)
                            SendMessage(hwnd, WM_USER, curSel-1, 0);
                        break;
                    case VK_DOWN:
                        if (curSel < ListView_GetItemCount(hwndLV) - 1)
                            SendMessage(hwnd, WM_USER, curSel + 1, 0);
                        break;
                }
            }
            break;
        case WM_COMMAND:
            switch(wParam)
            {
                case IDC_RETURN:
                    GetWindowText(hwndEdit, brsName, sizeof(brsName));
                    SendMessage(hwndCombo, WM_SAVEHISTORY, 0, 0);
                    CreateUsageList();
                    return 0;
                case IDC_ESCAPE:
                    SendMessage(hwndEdit, WM_SETTEXT, 0, (LPARAM)brsName);
                    return 0;
                default:
                    if (HIWORD(wParam) == BN_CLICKED && LOWORD(wParam) == 300)
                    {
                        displayFull = !displayFull;
                        PostMessage(hwnd, WM_USER, 0, 0);
                    }
                    if (HIWORD(wParam) == CBN_SELENDOK && LOWORD(wParam) == 500)
                    {
                        PostMessage(hwnd, WM_COMMAND, IDC_RETURN, 0);
                    }
                    break;
            }
            break;
            
        case WM_USER:
        {
            int k = 0;
            char buf[40];
            sprintf(buf, "%d Usages", browsecount);
            SetWindowText(hwndButton, buf);
            
            ListView_DeleteAllItems(hwndLV);
            memset(&item, 0, sizeof(item));
            for (i=0; i < browsecount; i++)
            {
                if (displayFull || browselist[i]->definition || browselist[i]->declaration)
                {
                    item.iItem = k++;
                    item.iSubItem = 0;
                    item.mask = LVIF_IMAGE | LVIF_PARAM;
                    item.lParam = i;
                    item.iImage = browselist[i]->definition ? 0 : browselist[i]->declaration ? 1 : 2;
                    ListView_InsertItem(hwndLV, &item);
                }            
            }
        }
            break;
        case WM_DRAWITEM:
        {
            LPDRAWITEMSTRUCT pDis = (LPDRAWITEMSTRUCT)lParam;
            HDC memdc;
            char staticText[256];
            BOOL state = !! displayFull;
            int len = SendMessage(pDis->hwndItem, WM_GETTEXT, 
                sizeof(staticText), (LPARAM)staticText);
            SIZE sz;
            RECT r;
            POINT textpos, iconpos;
            GetClientRect(pDis->hwndItem, &r);
            GetTextExtentPoint32(pDis->hDC, staticText, len, &sz);
            SetBkMode(pDis->hDC, TRANSPARENT);   
            iconpos.x = 4;
            iconpos.y = (r.bottom - r.top - 16)/2;
            textpos.x = r.right - 4 - sz.cx;
            textpos.y = (r.bottom - r.top - sz.cy)/2;
            DrawFrameControl(pDis->hDC, &pDis->rcItem, DFC_BUTTON, DFCS_BUTTONPUSH | (state ? DFCS_PUSHED : 0));
            TextOut(pDis->hDC, pDis->rcItem.left+ textpos.x, pDis->rcItem.top+textpos.y, staticText, len);
            memdc = CreateCompatibleDC(pDis->hDC);
            SelectObject(memdc, buttonbmp);
            TransparentBlt(pDis->hDC, pDis->rcItem.left+ iconpos.x, pDis->rcItem.top+iconpos.y, 16, 16, memdc, 0, 0, 16, 16, 0xc0c0c0);
            DeleteDC(memdc);
        }
        return 0;
        case WM_CREATE:
            hwndBrowse = hwnd;
            GetClientRect(hwnd, &r);
            hwndBackground = CreateWindow("static", "", WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS,
                                                0,0, r.right - r.bottom, BUTTONHEIGHT + 4, hwnd, 0, hInstance, 0);
            hwndButton = CreateWindow("button", "0 Usages",  WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
                                         2,2,BUTTONWIDTH,BUTTONHEIGHT, hwnd, (HMENU)300, hInstance, 0);
            ApplyDialogFont(hwndButton);
            hwndCombo = CreateWindow("COMBOBOX", "", WS_CHILD + WS_CLIPSIBLINGS +
                WS_BORDER + WS_VISIBLE + CBS_DROPDOWN + CBS_AUTOHSCROLL, 
                                BUTTONWIDTH + 10, 4, 200, 100, hwnd, (HMENU)500, hInstance, 0);
            ApplyDialogFont(hwndCombo);
            SubClassHistoryCombo(hwndCombo);
            SendMessage(hwndCombo, WM_SETHISTORY, 0, (LPARAM)varinfohist);
            pt.x = pt.y = 5;
            hwndEdit = ChildWindowFromPoint(hwndCombo, pt);
            oldproc = (WNDPROC)SetWindowLong(hwndEdit, GWL_WNDPROC, (int)EditHook);
            BringWindowToTop(hwndButton);
            BringWindowToTop(hwndCombo);
            font = CreateFontIndirect(&systemDialogFont);
            SendMessage(hwndErrButton, WM_SETFONT, (WPARAM)font, 0);
            SendMessage(hwndWarnButton, WM_SETFONT, (WPARAM)font, 0);
            hwndLV = CreateWindowEx(0, WC_LISTVIEW, "", 
                           LVS_REPORT | LVS_SINGLESEL | WS_CHILD | WS_VISIBLE | WS_BORDER,
                           0,BUTTONHEIGHT + 4,r.right-r.left, r.bottom - r.top-BUTTONHEIGHT-4, hwnd, 0, hInstance, 0);
            ListView_SetExtendedListViewStyle(hwndLV, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_DOUBLEBUFFER);
            ApplyDialogFont(hwndLV);
            GetWindowRect(hwndLV, &r);
            lvC.mask = LVCF_WIDTH;
            lvC.cx = 50;
            lvC.iSubItem = 0;
            ListView_InsertColumn(hwndLV, 0, &lvC);
            lvC.mask = LVCF_WIDTH | LVCF_SUBITEM | LVCF_TEXT;
            lvC.cx = 50;            lvC.iSubItem = 1;
            lvC.pszText = "Id";
            ListView_InsertColumn(hwndLV, 1, &lvC);
            lvC.mask = LVCF_WIDTH | LVCF_SUBITEM | LVCF_TEXT;
            lvC.cx = 250;
            lvC.iSubItem = 2;
            lvC.pszText = "Name";
            ListView_InsertColumn(hwndLV, 2, &lvC);
            lvC.mask = LVCF_WIDTH | LVCF_SUBITEM | LVCF_TEXT;
            lvC.cx = 50;
            lvC.iSubItem = 3;
            lvC.pszText = "Line";
            ListView_InsertColumn(hwndLV, 3, &lvC);
            lvC.mask = LVCF_WIDTH | LVCF_SUBITEM | LVCF_TEXT;
            lvC.cx = r.right - r.left - 375;
            lvC.iSubItem = 4;
            lvC.pszText = "File";
            ListView_InsertColumn(hwndLV, 4, &lvC);
            ListView_SetImageList(hwndLV, tagImageList, LVSIL_SMALL);
            break;
        case WM_RESETHISTORY:
            SendMessage(hwndCombo, WM_SETHISTORY, 0, (LPARAM)varinfohist);
            break;
        case WM_SIZE:
            r.left = r.top = 0;
            r.right = LOWORD(lParam);
            r.bottom = HIWORD(lParam);
            MoveWindow(hwndLV, r.left, r.top+BUTTONHEIGHT + 4, r.right - r.left,
                r.bottom - r.top-BUTTONHEIGHT - 4, 1);
            MoveWindow(hwndBackground, r.left, r.top, r.right - r.left, BUTTONHEIGHT + 4, 1);
            lvC.mask = LVCF_WIDTH;
            lvC.cx = r.right - r.left - 375;
            ListView_SetColumn(hwndLV, 4, &lvC);
            break;
        case WM_DESTROY:
            hwndBrowse = 0;
            break;
        case WM_SETFOCUS:
            break;
        case WM_KILLFOCUS:
            break;
    }
    return DefWindowProc(hwnd, iMessage, wParam, lParam);
}