BOOL PropSheetPage2_OnInitDialog(
    _In_ HWND hwndDlg,
    _In_ HWND hwndFocus,
    _Inout_ LPARAM lParam
    )
{
    // Set the fonts.
    InitializeFont(GetDlgItem(hwndDlg, IDC_MAINHEADER), -17, FW_SEMIBOLD);
   
    // Set the default radio button state to 'do not accept'.
    Button_SetCheck(GetDlgItem(hwndDlg, IDC_RADIO2), BST_CHECKED);
   
    LoadEulaText(hwndDlg);

    // Enable the themed dialog background texture.
    EnableThemeDialogTexture(hwndDlg, ETDT_ENABLETAB);

    return TRUE;
}