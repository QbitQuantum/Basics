static
INT_PTR CALLBACK
SettingsDlgProc(HWND hDlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    switch (Msg)
    {
    case WM_INITDIALOG:
    {
        NewSettingsInfo = SettingsInfo;
        InitSettingsControls(hDlg, &SettingsInfo);
    }
    break;

    case WM_COMMAND:
    {
        switch (LOWORD(wParam))
        {
        case IDC_CHOOSE:
            ChooseFolder(hDlg);
            break;

        case IDC_SAVE_WINDOW_POS:
            IS_CHECKED(NewSettingsInfo.bSaveWndPos, IDC_SAVE_WINDOW_POS);
            break;

        case IDC_UPDATE_AVLIST:
            IS_CHECKED(NewSettingsInfo.bUpdateAtStart, IDC_UPDATE_AVLIST);
            break;

        case IDC_LOG_ENABLED:
            IS_CHECKED(NewSettingsInfo.bLogEnabled, IDC_LOG_ENABLED);
            break;

        case IDC_DEL_AFTER_INSTALL:
            IS_CHECKED(NewSettingsInfo.bDelInstaller, IDC_DEL_AFTER_INSTALL);
            break;

        case IDC_PROXY_DEFAULT:
            NewSettingsInfo.Proxy = 0;
            EnableWindow(GetDlgItem(hDlg, IDC_PROXY_SERVER), FALSE);
            EnableWindow(GetDlgItem(hDlg, IDC_NO_PROXY_FOR), FALSE);
            break;

        case IDC_NO_PROXY:
            NewSettingsInfo.Proxy = 1;
            EnableWindow(GetDlgItem(hDlg, IDC_PROXY_SERVER), FALSE);
            EnableWindow(GetDlgItem(hDlg, IDC_NO_PROXY_FOR), FALSE);
            break;

        case IDC_USE_PROXY:
            NewSettingsInfo.Proxy = 2;
            EnableWindow(GetDlgItem(hDlg, IDC_PROXY_SERVER), TRUE);
            EnableWindow(GetDlgItem(hDlg, IDC_NO_PROXY_FOR), TRUE);
            break;

        case IDC_DEFAULT_SETTINGS:
            FillDefaultSettings(&NewSettingsInfo);
            InitSettingsControls(hDlg, &NewSettingsInfo);
            break;

        case IDOK:
        {
            WCHAR szDir[MAX_PATH];
            WCHAR szProxy[MAX_PATH];
            WCHAR szNoProxy[MAX_PATH];
            DWORD dwAttr;

            GetWindowTextW(GetDlgItem(hDlg, IDC_DOWNLOAD_DIR_EDIT),
                           szDir, MAX_PATH);

            GetWindowTextW(GetDlgItem(hDlg, IDC_PROXY_SERVER),
                           szProxy, MAX_PATH);
            StringCbCopyW(NewSettingsInfo.szProxyServer, sizeof(NewSettingsInfo.szProxyServer), szProxy);

            GetWindowTextW(GetDlgItem(hDlg, IDC_NO_PROXY_FOR),
                           szNoProxy, MAX_PATH);
            StringCbCopyW(NewSettingsInfo.szNoProxyFor, sizeof(NewSettingsInfo.szNoProxyFor), szNoProxy);

            dwAttr = GetFileAttributesW(szDir);
            if (dwAttr != INVALID_FILE_ATTRIBUTES &&
                    (dwAttr & FILE_ATTRIBUTE_DIRECTORY))
            {
                StringCbCopyW(NewSettingsInfo.szDownloadDir,
                              sizeof(NewSettingsInfo.szDownloadDir),
                              szDir);
            }
            else
            {
                WCHAR szMsgText[MAX_STR_LEN];

                LoadStringW(hInst,
                            IDS_CHOOSE_FOLDER_ERROR,
                            szMsgText, sizeof(szMsgText) / sizeof(WCHAR));

                if (MessageBoxW(hDlg, szMsgText, NULL, MB_YESNO) == IDYES)
                {
                    if (CreateDirectoryW(szDir, NULL))
                    {
                        EndDialog(hDlg, LOWORD(wParam));
                    }
                }
                else
                {
                    SetFocus(GetDlgItem(hDlg, IDC_DOWNLOAD_DIR_EDIT));
                    break;
                }
            }

            SettingsInfo = NewSettingsInfo;
            SaveSettings(GetParent(hDlg));
            EndDialog(hDlg, LOWORD(wParam));
        }
        break;

        case IDCANCEL:
            EndDialog(hDlg, LOWORD(wParam));
            break;
        }
    }
    break;
    }

    return FALSE;
}