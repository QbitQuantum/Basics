INT_PTR CALLBACK dlgfunc (HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    int id, f, option;
    TCHAR buffer[MAX_PATH], temp[2000];

    switch( msg ) {
    case WM_DESTROY:
        g_hDlg = NULL;
        return 0;

    case WM_INITDIALOG:
        g_hDlg = hDlg;
        option = 0;

        Init ();
        if (0 == is_usingNT)
        {
            EnableWindow(GetDlgItem(hDlg, IDC_CHK1), FALSE);
        }
        else if (0 == is_admin)
        {
            /* if not admin, see if a shell is set for this user */
            is_per_user = rw_reg(A_RD|A_SZ, HKEY_CURRENT_USER, logonstr, TEXT("Shell"), buffer);
            SetDlgItemText(hDlg, IDC_CHK1, TEXT("Set shell for this user &individually"));
        }

        CheckDlgButton(hDlg, IDC_CHK1, is_per_user ? BST_CHECKED : BST_UNCHECKED);

display:
        if (is_usingNT) {
            if (0 == is_per_user) {
                _tcscpy(buffer, TEXT("Shell for all users"));
                if (0 == is_admin)
                    _tcscat(buffer, TEXT(" (run as admin to change)"));

            } else {
                DWORD result = sizeof temp;
                temp[0] = 0;
                GetUserName(temp, &result);
                _stprintf(buffer, TEXT("Shell for the current user (%s)"), temp);
            }

            SetDlgItemText(hDlg, IDC_GRP1, buffer);
        }

        if (2 == option)
            _tcscpy(buffer, szBlackbox);
        else
        if (1 == option)
            _tcscpy(buffer, szExplorer);
        else
            get_shell(buffer);

        _tcslwr(_tcscpy(temp, buffer));

        if (0 == _tcsicmp(temp, szBlackbox)) {
            id = IDC_RBN1;
        }
        else if (_tcsstr(temp, TEXT("explorer"))) {
            id = IDC_RBN2;
        } else if (temp[0]) {
            id = IDC_RBN3;
        } else {
            _tcscpy(buffer, TEXT("<not set>"));
            id = 0;
        }

        CheckRadioButton(hDlg, IDC_RBN1, IDC_RBN3, id);
        for (f = IDC_RBN1; f <= IDC_RBN3; ++f)
            EnableWindow(GetDlgItem(hDlg, f), is_admin || is_per_user);

set_line:
        {
            HWND hLine = GetDlgItem(hDlg, IDC_EDT1);
            SetWindowText(hLine, buffer);
            SendMessage(hLine, EM_SETREADONLY, id != IDC_RBN3, 0);
        }
        return 1;


    case WM_COMMAND:
        id = LOWORD( wParam );
        switch(id) {
        case IDC_CHK1:
            is_per_user = 0 != IsDlgButtonChecked(hDlg, id);
            option = 0;
            goto display;

        case IDC_RBN1:
            option = 2;
            goto display;

        case IDC_RBN2:
            option = 1;
            goto display;

        case IDC_RBN3:
            buffer[0] = 0;
            goto set_line;

        case IDCANCEL:
            EndDialog(hDlg, 0);
            return 1;

        case IDOK:
        case IDC_LOG1:
            GetDlgItemText(hDlg, IDC_EDT1, shellpath, sizeof shellpath);
            if (SetAsShell(shellpath) == 1)
              return 1;
            if (0 == is_admin && is_per_user && 0 == get_per_user()) {
                id = 1;
            } else if (id == IDC_LOG1) {
                id = 2;
            } else if (0 == is_admin && 0 == is_per_user) {
                id = 3;
            } else {
                id = 4;
            }

            EndDialog(hDlg, id);
            return 1;
        }
    }
    return 0;
}