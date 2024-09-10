static VOID
OnInitDialog(HWND hwndDlg)
{
    /* Initialize the list view control */
    SetListViewColumns(GetDlgItem(hwndDlg, IDC_USERPROFILE_LIST));

    AddUserProfiles(GetDlgItem(hwndDlg, IDC_USERPROFILE_LIST));

    /* Disable the "Delete" and "Copy To" buttons if the user is not an admin */
    if (!IsUserAnAdmin())
    {
         EnableWindow(GetDlgItem(hwndDlg, IDC_USERPROFILE_DELETE), FALSE);
         EnableWindow(GetDlgItem(hwndDlg, IDC_USERPROFILE_COPY), FALSE);
    }
}