static BOOL CALLBACK AddCheatCallB(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    static int lbfocus;
    static HWND hwndLB;

    switch (uMsg) {
    case WM_VSCROLL:
        if (scrollnum > (CSTOD - 1)) {
            switch ((int)LOWORD(wParam)) {
            case SB_TOP:
                scrollindex = -32768;
                SendDlgItemMessage(hwndDlg, 120, SBM_SETPOS, scrollindex, 1);
                SendDlgItemMessage(hwndDlg, 108, LB_RESETCONTENT, (CSTOD - 1), 0);
                FCEUI_CheatSearchGetRange(scrollindex + 32768, scrollindex + 32768 + (CSTOD - 1), cfcallb);
                break;
            case SB_BOTTOM:
                scrollindex = scrollmax;
                SendDlgItemMessage(hwndDlg, 120, SBM_SETPOS, scrollindex, 1);
                SendDlgItemMessage(hwndDlg, 108, LB_RESETCONTENT, (CSTOD - 1), 0);
                FCEUI_CheatSearchGetRange(scrollindex + 32768, scrollindex + 32768 + (CSTOD - 1), cfcallb);
                break;
            case SB_LINEUP:
                if (scrollindex > -32768) {
                    scrollindex--;
                    SendDlgItemMessage(hwndDlg, 120, SBM_SETPOS, scrollindex, 1);
                    SendDlgItemMessage(hwndDlg, 108, LB_DELETESTRING, (CSTOD - 1), 0);
                    FCEUI_CheatSearchGetRange(scrollindex + 32768, scrollindex + 32768, cfcallbinsertt);
                }
                break;

            case SB_PAGEUP:
                scrollindex -= CSTOD;
                if (scrollindex < -32768) scrollindex = -32768;
                SendDlgItemMessage(hwndDlg, 120, SBM_SETPOS, scrollindex, 1);
                SendDlgItemMessage(hwndDlg, 108, LB_RESETCONTENT, (CSTOD - 1), 0);
                FCEUI_CheatSearchGetRange(scrollindex + 32768, scrollindex + 32768 + (CSTOD - 1), cfcallb);
                break;

            case SB_LINEDOWN:
                if (scrollindex < scrollmax) {
                    scrollindex++;
                    SendDlgItemMessage(hwndDlg, 120, SBM_SETPOS, scrollindex, 1);
                    SendDlgItemMessage(hwndDlg, 108, LB_DELETESTRING, 0, 0);
                    FCEUI_CheatSearchGetRange(scrollindex + 32768 + (CSTOD - 1), scrollindex + 32768 + (CSTOD - 1), cfcallbinsert);
                }
                break;

            case SB_PAGEDOWN:
                scrollindex += CSTOD;
                if (scrollindex > scrollmax)
                    scrollindex = scrollmax;
                SendDlgItemMessage(hwndDlg, 120, SBM_SETPOS, scrollindex, 1);
                SendDlgItemMessage(hwndDlg, 108, LB_RESETCONTENT, 0, 0);
                FCEUI_CheatSearchGetRange(scrollindex + 32768, scrollindex + 32768 + (CSTOD - 1), cfcallb);
                break;

            case SB_THUMBPOSITION:
            case SB_THUMBTRACK:
                scrollindex = (short int)HIWORD(wParam);
                SendDlgItemMessage(hwndDlg, 120, SBM_SETPOS, scrollindex, 1);
                SendDlgItemMessage(hwndDlg, 108, LB_RESETCONTENT, 0, 0);
                FCEUI_CheatSearchGetRange(32768 + scrollindex, 32768 + scrollindex + (CSTOD - 1), cfcallb);
                break;
            }
        }
        break;

    case WM_INITDIALOG:
        selcheat = -1;
        FixCheatSelButtons(hwndDlg, 0);
        acwin = hwndDlg;
        SetDlgItemText(hwndDlg, 110, (LPTSTR)U8ToStr(cheatval1));
        SetDlgItemText(hwndDlg, 111, (LPTSTR)U8ToStr(cheatval2));
        DoGet();
        CheckRadioButton(hwndDlg, 115, 120, scheatmethod + 115);
        lbfocus = 0;
        hwndLB = 0;

        RedoCheatsLB(hwndDlg);
        break;

    case WM_VKEYTOITEM:
        if (lbfocus) {
            int real;

            real = SendDlgItemMessage(hwndDlg, 108, LB_GETCURSEL, 0, (LPARAM)(LPSTR)0);
            switch ((int)LOWORD(wParam)) {
            case VK_UP:
                /* mmmm....recursive goodness */
                if (!real)
                    SendMessage(hwndDlg, WM_VSCROLL, SB_LINEUP, 0);
                return(-1);
                break;
            case VK_DOWN:
                if (real == (CSTOD - 1))
                    SendMessage(hwndDlg, WM_VSCROLL, SB_LINEDOWN, 0);
                return(-1);
                break;
            case VK_PRIOR:
                SendMessage(hwndDlg, WM_VSCROLL, SB_PAGEUP, 0);
                break;
            case VK_NEXT:
                SendMessage(hwndDlg, WM_VSCROLL, SB_PAGEDOWN, 0);
                break;
            case VK_HOME:
                SendMessage(hwndDlg, WM_VSCROLL, SB_TOP, 0);
                break;
            case VK_END:
                SendMessage(hwndDlg, WM_VSCROLL, SB_BOTTOM, 0);
                break;
            }
            return(-2);
        }
        break;

    case WM_CLOSE:
    case WM_QUIT:
        goto gornk;
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case 300:               /* List box selection changed. */
            if (HIWORD(wParam) == LBN_SELCHANGE) {
                char *s;
                uint32 a;
                uint8 v;
                int status;
                int c, type;

                selcheat = SendDlgItemMessage(hwndDlg, 300, LB_GETCURSEL, 0, (LPARAM)(LPSTR)0);
                if (selcheat < 0) {
                    FixCheatSelButtons(hwndDlg, 0);
                    break;
                }
                FixCheatSelButtons(hwndDlg, 1);

                FCEUI_GetCheat(selcheat, &s, &a, &v, &c, &status, &type);
                SetDlgItemText(hwndDlg, 200, (LPTSTR)s);
                SetDlgItemText(hwndDlg, 201, (LPTSTR)U16ToStr(a));
                SetDlgItemText(hwndDlg, 202, (LPTSTR)U8ToStr(v));
                SetDlgItemText(hwndDlg, 203, (c == -1) ? (LPTSTR)"" : (LPTSTR)IToStr(c));
                CheckDlgButton(hwndDlg, 204, type ? BST_CHECKED : BST_UNCHECKED);
            }
            break;
        case 108:
            switch (HIWORD(wParam)) {
            case LBN_SELCHANGE:
            {
                char TempArray[32];
                SendDlgItemMessage(hwndDlg, 108, LB_GETTEXT, SendDlgItemMessage(hwndDlg, 108, LB_GETCURSEL, 0, (LPARAM)(LPSTR)0), (LPARAM)(LPCTSTR)TempArray);
                TempArray[4] = 0;
                SetDlgItemText(hwndDlg, 201, (LPTSTR)TempArray);
            }
            break;
            case LBN_SETFOCUS:
                lbfocus = 1;
                break;
            case LBN_KILLFOCUS:
                lbfocus = 0;
                break;
            }
            break;
        }

        switch (HIWORD(wParam)) {
        case LBN_DBLCLK:
            if (selcheat >= 0) {
                if (LOWORD(wParam) == 300)
                    FCEUI_ToggleCheat(selcheat);
                RedoCheatsLB(hwndDlg);
                SendDlgItemMessage(hwndDlg, 300, LB_SETCURSEL, selcheat, 0);
            }
            break;

        case BN_CLICKED:
            if (LOWORD(wParam) >= 115 && LOWORD(wParam) <= 120)
                scheatmethod = LOWORD(wParam) - 115;
            else switch (LOWORD(wParam)) {
                case 112:
                    FCEUI_CheatSearchBegin();
                    DoGet();
                    break;
                case 113:
                    FCEUI_CheatSearchEnd(scheatmethod, cheatval1, cheatval2);
                    DoGet();
                    break;
                case 114:
                    FCEUI_CheatSearchSetCurrentAsOriginal();
                    DoGet();
                    break;
                case 107:
                    FCEUI_CheatSearchShowExcluded();
                    DoGet();
                    break;
                case 250:               /* Add Cheat Button */
                {
                    int a, v, c, t;
                    char name[257];
                    char temp[16];

                    GetDlgItemText(hwndDlg, 200, name, 256 + 1);
                    GetDlgItemText(hwndDlg, 201, temp, 4 + 1);
                    a = StrToU16(temp);
                    GetDlgItemText(hwndDlg, 202, temp, 3 + 1);
                    v = StrToU8(temp);
                    GetDlgItemText(hwndDlg, 203, temp, 3 + 1);
                    if (temp[0] == 0)
                        c = -1;
                    else
                        c = StrToI(temp);
                    t = (IsDlgButtonChecked(hwndDlg, 204) == BST_CHECKED) ? 1 : 0;
                    FCEUI_AddCheat(name, a, v, c, t);
                    RedoCheatsLB(hwndDlg);
                    SendDlgItemMessage(hwndDlg, 300, LB_SETCURSEL, selcheat, 0);
                }
                break;
                case 253:               /* Add GG Cheat Button */
                {
                    uint16 a;
                    int c;
                    uint8 v;
                    char name[257];

                    GetDlgItemText(hwndDlg, 200, name, 256 + 1);

                    if (FCEUI_DecodeGG(name, &a, &v, &c)) {
                        FCEUI_AddCheat(name, a, v, c, 1);
                        RedoCheatsLB(hwndDlg);
                        SendDlgItemMessage(hwndDlg, 300, LB_SETCURSEL, selcheat, 0);
                    }
                }
                break;

                case 251:               /* Update Cheat Button */
                    if (selcheat >= 0) {
                        int a, v, c, t;
                        char name[257];
                        char temp[16];

                        GetDlgItemText(hwndDlg, 200, name, 256 + 1);
                        GetDlgItemText(hwndDlg, 201, temp, 4 + 1);
                        a = StrToU16(temp);
                        GetDlgItemText(hwndDlg, 202, temp, 3 + 1);
                        v = StrToU8(temp);
                        GetDlgItemText(hwndDlg, 203, temp, 3 + 1);
                        if (temp[0] == 0)
                            c = -1;
                        else
                            c = StrToI(temp);
                        t = (IsDlgButtonChecked(hwndDlg, 204) == BST_CHECKED) ? 1 : 0;
                        FCEUI_SetCheat(selcheat, name, a, v, c, -1, t);
                        RedoCheatsLB(hwndDlg);
                        SendDlgItemMessage(hwndDlg, 300, LB_SETCURSEL, selcheat, 0);
                    }
                    break;
                case 252:               /* Delete cheat button */
                    if (selcheat >= 0) {
                        FCEUI_DelCheat(selcheat);
                        SendDlgItemMessage(hwndDlg, 300, LB_DELETESTRING, selcheat, 0);
                        FixCheatSelButtons(hwndDlg, 0);
                        selcheat = -1;
                        SetDlgItemText(hwndDlg, 200, (LPTSTR)"");
                        SetDlgItemText(hwndDlg, 201, (LPTSTR)"");
                        SetDlgItemText(hwndDlg, 202, (LPTSTR)"");
                        SetDlgItemText(hwndDlg, 203, (LPTSTR)"");
                        CheckDlgButton(hwndDlg, 204, BST_UNCHECKED);
                    }
                    break;
                case 106:
gornk:
                    EndDialog(hwndDlg, 0);
                    acwin = 0;
                    break;
                }
            break;
        case EN_CHANGE:
        {
            char TempArray[256];
            GetDlgItemText(hwndDlg, LOWORD(wParam), TempArray, 256);
            switch (LOWORD(wParam)) {
            case 110:
                cheatval1 = StrToU8(TempArray);
                break;
            case 111:
                cheatval2 = StrToU8(TempArray);
                break;
            }
        }
        break;
        }
    }
    return 0;
}