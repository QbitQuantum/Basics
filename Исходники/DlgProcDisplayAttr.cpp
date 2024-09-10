INT_PTR CALLBACK DlgProcDisplayAttr(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam, int no)
{
    HWND hwnd;
    int x, y;
    RECT rect;
    POINT pt;
    CHOOSECOLORW cc;
    PAINTSTRUCT ps;
    HDC hdc;
    static COLORREF colCust[16];

    switch(message)
    {
    case WM_INITDIALOG:
        for(int i = 0; i < _countof(cbAttrID); i++)
        {
            for(int j = 0; j < _countof(cbAttrText); j++)
            {
                SendMessageW(GetDlgItem(hDlg, cbAttrID[i]), CB_ADDSTRING, 0, (LPARAM)cbAttrText[j]);
            }
        }
        for(int i = 0; i < _countof(cbULAttrID); i++)
        {
            for(int j = 0; j < _countof(cbULAttrText); j++)
            {
                SendMessageW(GetDlgItem(hDlg, cbULAttrID[i]), CB_ADDSTRING, 0, (LPARAM)cbULAttrText[j]);
            }
        }
        for(int i = 0; i < _countof(colCust); i++)
        {
            colCust[i] = RGB(0xFF, 0xFF, 0xFF);
        }

        LoadConfigDisplayAttr(no);

        for(int i = 0; i < _countof(displayAttr[no]); i++)
        {
            if(displayAttr[no][i].se)
            {
                CheckDlgButton(hDlg, displayAttrID[i][0], BST_CHECKED);
                DisplayAttrSeriesChecked(hDlg, displayAttrID[i][0]);
            }
            switch(displayAttr[no][i].da.crText.type)
            {
            case TF_CT_NONE:
                CheckDlgButton(hDlg, displayAttrID[i][1], BST_CHECKED);
                break;
            default:
                CheckDlgButton(hDlg, displayAttrID[i][2], BST_CHECKED);
                break;
            }
            switch(displayAttr[no][i].da.crBk.type)
            {
            case TF_CT_NONE:
                CheckDlgButton(hDlg, displayAttrID[i][4], BST_CHECKED);
                break;
            default:
                CheckDlgButton(hDlg, displayAttrID[i][5], BST_CHECKED);
                break;
            }
            SendMessageW(GetDlgItem(hDlg, displayAttrID[i][7]), CB_SETCURSEL, displayAttr[no][i].da.lsStyle, 0);
            CheckDlgButton(hDlg, displayAttrID[i][8], (displayAttr[no][i].da.fBoldLine ? BST_CHECKED : BST_UNCHECKED));
            switch(displayAttr[no][i].da.crLine.type)
            {
            case TF_CT_NONE:
                CheckDlgButton(hDlg, displayAttrID[i][9], BST_CHECKED);
                break;
            default:
                CheckDlgButton(hDlg, displayAttrID[i][10], BST_CHECKED);
                break;
            }
            SendMessageW(GetDlgItem(hDlg, displayAttrID[i][12]), CB_SETCURSEL, displayAttr[no][i].da.bAttr, 0);
        }

        return TRUE;

    case WM_COMMAND:
        switch(LOWORD(wParam))
        {
        case IDC_CHECKBOX_SERIES_MARK:
        case IDC_CHECKBOX_SERIES_TEXT:
        case IDC_CHECKBOX_SERIES_OKURI:
        case IDC_CHECKBOX_SERIES_ANNOT:
            DisplayAttrSeriesChecked(hDlg, LOWORD(wParam));
        //no break;
        case IDC_RADIO_FG_STD_MARK:
        case IDC_RADIO_FG_STD_TEXT:
        case IDC_RADIO_FG_STD_OKURI:
        case IDC_RADIO_FG_STD_ANNOT:
        case IDC_RADIO_FG_SEL_MARK:
        case IDC_RADIO_FG_SEL_TEXT:
        case IDC_RADIO_FG_SEL_OKURI:
        case IDC_RADIO_FG_SEL_ANNOT:
        case IDC_RADIO_BG_STD_MARK:
        case IDC_RADIO_BG_STD_TEXT:
        case IDC_RADIO_BG_STD_OKURI:
        case IDC_RADIO_BG_STD_ANNOT:
        case IDC_RADIO_BG_SEL_MARK:
        case IDC_RADIO_BG_SEL_TEXT:
        case IDC_RADIO_BG_SEL_OKURI:
        case IDC_RADIO_BG_SEL_ANNOT:
        case IDC_CHECKBOX_UL_BOLD_MARK:
        case IDC_CHECKBOX_UL_BOLD_TEXT:
        case IDC_CHECKBOX_UL_BOLD_OKURI:
        case IDC_CHECKBOX_UL_BOLD_ANNOT:
        case IDC_RADIO_UL_STD_MARK:
        case IDC_RADIO_UL_STD_TEXT:
        case IDC_RADIO_UL_STD_OKURI:
        case IDC_RADIO_UL_STD_ANNOT:
        case IDC_RADIO_UL_SEL_MARK:
        case IDC_RADIO_UL_SEL_TEXT:
        case IDC_RADIO_UL_SEL_OKURI:
        case IDC_RADIO_UL_SEL_ANNOT:
            PropSheet_Changed(GetParent(hDlg), hDlg);
            return TRUE;

        case IDC_COMBO_UL_ATTR_MARK:
        case IDC_COMBO_UL_ATTR_TEXT:
        case IDC_COMBO_UL_ATTR_OKURI:
        case IDC_COMBO_UL_ATTR_ANNOT:
        case IDC_COMBO_ATTR_MARK:
        case IDC_COMBO_ATTR_TEXT:
        case IDC_COMBO_ATTR_OKURI:
        case IDC_COMBO_ATTR_ANNOT:
            switch(HIWORD(wParam))
            {
            case CBN_SELCHANGE:
                PropSheet_Changed(GetParent(hDlg), hDlg);
                return TRUE;
            default:
                break;
            }
            break;

        default:
            break;
        }
        break;

    case WM_LBUTTONDOWN:
        for(int i = 0; i < _countof(displayAttrColor[no]); i++)
        {
            for(int j = 0; j < _countof(displayAttrColor[no][i]); j++)
            {
                hwnd = GetDlgItem(hDlg, displayAttrColor[no][i][j].id);
                if(!IsWindowEnabled(hwnd))
                {
                    continue;
                }
                GetWindowRect(hwnd, &rect);
                pt.x = x = GET_X_LPARAM(lParam);
                pt.y = y = GET_Y_LPARAM(lParam);
                ClientToScreen(hDlg, &pt);

                if(rect.left <= pt.x && pt.x <= rect.right &&
                        rect.top <= pt.y && pt.y <= rect.bottom)
                {
                    cc.lStructSize = sizeof(cc);
                    cc.hwndOwner = hDlg;
                    cc.hInstance = nullptr;
                    cc.rgbResult = *displayAttrColor[no][i][j].color;
                    cc.lpCustColors = colCust;
                    cc.Flags = CC_FULLOPEN | CC_RGBINIT;
                    cc.lCustData = 0;
                    cc.lpfnHook = nullptr;
                    cc.lpTemplateName = nullptr;
                    if(ChooseColorW(&cc))
                    {
                        DrawSelectColor(hDlg, displayAttrColor[no][i][j].id, cc.rgbResult);
                        *displayAttrColor[no][i][j].color = cc.rgbResult;
                        PropSheet_Changed(GetParent(hDlg), hDlg);
                        return TRUE;
                    }
                    break;
                }
            }
        }
        break;

    case WM_PAINT:
        hdc = BeginPaint(hDlg, &ps);
        for(int i = 0; i < _countof(displayAttrColor[no]); i++)
        {
            for(int j = 0; j < _countof(displayAttrColor[no][i]) && displayAttr[no][i].key != nullptr; j++)
            {
                DrawSelectColor(hDlg, displayAttrColor[no][i][j].id, *displayAttrColor[no][i][j].color);
            }
        }
        EndPaint(hDlg, &ps);

        return TRUE;

    case WM_NOTIFY:
        switch(((LPNMHDR)lParam)->code)
        {
        case PSN_APPLY:
            for(int i = 0; i < _countof(displayAttr[no]); i++)
            {
                displayAttr[no][i].se =
                    (IsDlgButtonChecked(hDlg, displayAttrID[i][0]) == BST_CHECKED ? TRUE : FALSE);
                displayAttr[no][i].da.crText.type =
                    (IsDlgButtonChecked(hDlg, displayAttrID[i][2]) == BST_CHECKED ? TF_CT_COLORREF : TF_CT_NONE);
                displayAttr[no][i].da.crBk.type =
                    (IsDlgButtonChecked(hDlg, displayAttrID[i][5]) == BST_CHECKED ? TF_CT_COLORREF : TF_CT_NONE);
                displayAttr[no][i].da.lsStyle =
                    (TF_DA_LINESTYLE)SendMessageW(GetDlgItem(hDlg, displayAttrID[i][7]), CB_GETCURSEL, 0, 0);
                displayAttr[no][i].da.fBoldLine =
                    (IsDlgButtonChecked(hDlg, displayAttrID[i][8]) == BST_CHECKED ? TRUE : FALSE);
                displayAttr[no][i].da.crLine.type =
                    (IsDlgButtonChecked(hDlg, displayAttrID[i][10]) == BST_CHECKED ? TF_CT_COLORREF : TF_CT_NONE);
                displayAttr[no][i].da.bAttr =
                    (TF_DA_ATTR_INFO)SendMessageW(GetDlgItem(hDlg, displayAttrID[i][12]), CB_GETCURSEL, 0, 0);
            }
            SaveConfigDisplayAttr(no);
            return TRUE;
        default:
            break;
        }
        break;

    default:
        break;
    }

    return FALSE;
}