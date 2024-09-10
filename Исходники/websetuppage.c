INT_PTR CALLBACK SetupWebSetup_WndProc(
    _In_ HWND hwndDlg,
    _In_ UINT uMsg,
    _Inout_ WPARAM wParam,
    _Inout_ LPARAM lParam
    )
{
    PPH_SETUP_CONTEXT context = NULL;

    if (uMsg == WM_INITDIALOG)
    {
        context = GetProp(GetParent(hwndDlg), L"SetupContext");
        SetProp(hwndDlg, L"Context", (HANDLE)context);
    }
    else
    {
        context = (PPH_SETUP_CONTEXT)GetProp(hwndDlg, L"Context");
    }

    if (context == NULL)
        return FALSE;

    switch (uMsg)
    {
    case WM_INITDIALOG:
        {
            SetupLoadImage(GetDlgItem(hwndDlg, IDC_PROJECT_ICON), MAKEINTRESOURCE(IDB_PNG1));
            SetupInitializeFont(GetDlgItem(hwndDlg, IDC_MAINHEADER), -17, FW_SEMIBOLD);
            //SetupInitializeFont(GetDlgItem(hwndDlg, IDC_SUBHEADER), -12, FW_NORMAL);
            SetupInitializeFont(GetDlgItem(hwndDlg, IDC_INSTALL_STATUS), -12, FW_SEMIBOLD);
            SetupInitializeFont(GetDlgItem(hwndDlg, IDC_INSTALL_SUBSTATUS), -12, FW_NORMAL);

            EnableThemeDialogTexture(hwndDlg, ETDT_ENABLETAB);
        }
        break;
    case WM_NOTIFY:
        {
            LPNMHDR header = (LPNMHDR)lParam;
            LPPSHNOTIFY pageNotify = (LPPSHNOTIFY)header;

            switch (pageNotify->hdr.code)
            {
            case PSN_SETACTIVE:
                {
                    context->MainHeaderHandle = GetDlgItem(hwndDlg, IDC_MAINHEADER);
                    context->StatusHandle = GetDlgItem(hwndDlg, IDC_INSTALL_STATUS);
                    context->SubStatusHandle = GetDlgItem(hwndDlg, IDC_INSTALL_SUBSTATUS);
                    context->ProgressHandle = GetDlgItem(hwndDlg, IDC_INSTALL_PROGRESS);

                    SetWindowText(context->MainHeaderHandle, L"Checking for newer websetup version...");
                    SetWindowText(context->StatusHandle, L"Requesting latest version...");
                    SetWindowText(context->SubStatusHandle, L"");

                    // Disable Next/Back buttons
                    PropSheet_SetWizButtons(context->DialogHandle, 0);

                    PhCreateThread2(SetupDownloadWebSetupThread, context);
                }
                break;
            }
        }
        break;
    }

    return FALSE;
}