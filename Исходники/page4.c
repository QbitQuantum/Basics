BOOL PropSheetPage4_OnInitDialog(
    _In_ HWND hwndDlg,
    _In_ HWND hwndFocus,
    _Inout_ LPARAM lParam
    )
{
    EnableThemeDialogTexture(hwndDlg, ETDT_ENABLETAB);

    InitializeFont(GetDlgItem(hwndDlg, IDC_MAINHEADER), -17, FW_SEMIBOLD);
    InitializeFont(GetDlgItem(hwndDlg, IDC_MAINHEADER1), -12, FW_SEMIBOLD);

    SetWindowSubclass(
        GetDlgItem(hwndDlg, IDC_PROGRESS1),
        SubclassWindowProc,
        IDC_PROGRESS1,
        0
        );

    return TRUE;
}