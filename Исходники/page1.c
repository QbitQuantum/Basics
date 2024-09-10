BOOL PropSheetPage1_OnInitDialog(
    _In_ HWND hwndDlg,
    _In_ HWND hwndFocus,
    _Inout_ LPARAM lParam
    )
{
    LoadSetupIcons(hwndDlg);
    LoadSetupImage(hwndDlg);

    // Center the dialog window on the desktop
    PhCenterWindow(GetParent(hwndDlg), NULL);
    SetForegroundWindow(GetParent(hwndDlg));

    // Set the fonts
    InitializeFont(GetDlgItem(hwndDlg, IDC_MAINHEADER), 24, FW_SEMIBOLD);
    InitializeFont(GetDlgItem(hwndDlg, IDC_SUBHEADER), 0, FW_NORMAL);

    // Enable the themed dialog background texture.
    EnableThemeDialogTexture(hwndDlg, ETDT_ENABLETAB);

    return TRUE;
}