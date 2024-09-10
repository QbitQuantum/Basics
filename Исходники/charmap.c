static
INT_PTR
CALLBACK
CharMapDlgProc(HWND hDlg,
               UINT Message,
               WPARAM wParam,
               LPARAM lParam)
{
    switch(Message)
    {
        case WM_INITDIALOG:
        {
            DWORD evMask;
#ifdef REMOVE_ADVANCED
            HWND hAdv;
#endif

            FillFontStyleComboList(GetDlgItem(hDlg,
                                              IDC_FONTCOMBO));

            ChangeMapFont(hDlg);

            // Configure Richedit control for sending notification changes.
            evMask = SendDlgItemMessage(hDlg, IDC_TEXTBOX, EM_GETEVENTMASK, 0, 0);
            evMask |= ENM_CHANGE;
            SendDlgItemMessage(hDlg, IDC_TEXTBOX, EM_SETEVENTMASK, 0, (LPARAM)evMask);
#ifdef REMOVE_ADVANCED
            hAdv = GetDlgItem(hDlg, IDC_CHECK_ADVANCED);
            ShowWindow(hAdv, SW_HIDE);
#endif
            return TRUE;
        }

        case WM_COMMAND:
        {
            switch(LOWORD(wParam))
            {
                case IDC_FONTMAP:
                    switch (HIWORD(wParam))
                    {
                        case FM_SETCHAR:
                            AddCharToSelection(hDlg, LOWORD(lParam));
                            break;
                    }
                    break;

                case IDC_FONTCOMBO:
                    if (HIWORD(wParam) == CBN_SELCHANGE)
                    {
                        ChangeMapFont(hDlg);
                    }
                    break;

                case IDC_SELECT:
                    AddCharToSelection(hDlg, 0);
                    break;

                case IDC_TEXTBOX:
                    switch (HIWORD(wParam)) {
                    case EN_CHANGE:
                        if (GetWindowTextLength(GetDlgItem(hDlg, IDC_TEXTBOX)) == 0)
                            EnableWindow(GetDlgItem(hDlg, IDC_COPY), FALSE);
                        else
                            EnableWindow(GetDlgItem(hDlg, IDC_COPY), TRUE);
                        break;
                    }
                    break;

                case IDC_COPY:
                    CopyCharacters(hDlg);
                    break;
#ifndef REMOVE_ADVANCED
                case IDC_CHECK_ADVANCED:
                    UpdateSettings(hDlg);
                    ChangeView(GetParent(hDlg));
                    break;
#endif
            }
        }
        break;

        default:
            break;
    }

    return FALSE;
}