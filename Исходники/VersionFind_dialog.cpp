BOOL CALLBACK VF_DlgMain(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
    case WM_INITDIALOG:
    {
        g_shared_hwnd=hwndDlg;
        EnableWin(IDC_BTN_CALCFROMRAW, 0);
        CheckDlgButton(hwndDlg, IDC_CHK_LOG, log_version);
    }
    return TRUE;

    case WM_CLOSE:
    {
        EndDialog(hwndDlg, 0);
    }
    return TRUE;

    case WM_HELP:
    {
        char id[10]="";
        sprintf(id, "%d", IDS_HELPVERSION);
        SetEnvironmentVariableA("HELPID", id);
        SetEnvironmentVariableA("HELPTITLE", "Version Help");
        DialogBox(hInst, MAKEINTRESOURCE(DLG_HELP), hwndDlg, DlgHelp);
    }
    return TRUE;

    case WM_BROWSE:
    {
        strcpy(g_szFileName, (const char*)wParam);
        CreateThread(0, 0, VF_DebugThread, 0, 0, 0);
    }
    return TRUE;

    case WM_DROPFILES:
    {
        DragQueryFileA((HDROP)wParam, 0, g_szFileName, 256);
        CreateThread(0, 0, VF_DebugThread, 0, 0, 0);
    }
    return TRUE;

    case WM_COMMAND:
    {
        switch(LOWORD(wParam))
        {
        case IDC_CHK_LOG:
        {
            NoFocus();
            log_version=!!IsDlgButtonChecked(hwndDlg, LOWORD(wParam));
        }
        return TRUE;

        case IDC_BTN_CALCFROMRAW:
        {
            NoFocus();
            ResetContent(false);
            ARMA_OPTIONS op= {0};
            EXTRA_OPTIONS eo= {0};
            if(g_extra_options)
            {
                FillArmaExtraOptionsStruct(g_extra_options, &eo);
                FillArmaOptionsStruct(g_raw_options, g_version, &op, &eo, g_minimal);
            }
            else
                FillArmaOptionsStruct(g_raw_options, g_version, &op, 0, g_minimal);
            PrintArmaOptionsStruct(&op, 0, g_raw_options, g_extra_options);
        }
        return TRUE;

        case IDC_EDT_RAWOPTIONS:
        {
            char str[11]="";
            if(GetDlgItemTextA(hwndDlg, IDC_EDT_RAWOPTIONS, str, 10))
            {
                EnableWin(IDC_BTN_CALCFROMRAW, 1);
                sscanf(str, "%X", &g_raw_options);
            }
        }
        return TRUE;

        case IDC_EDT_EXTRAOPTIONS:
        {
            char str[11]="";
            if(GetDlgItemTextA(hwndDlg, IDC_EDT_EXTRAOPTIONS, str, 10))
            {
                EnableWin(IDC_BTN_CALCFROMRAW, 1);
                sscanf(str, "%X", &g_extra_options);
            }
        }
        return TRUE;
        }
    }
    return TRUE;
    }
    return FALSE;
}