BOOL CreateSubdirDialog::OnInitDialog(void)
{
    /* do the DoDataExchange stuff */
    CDialog::OnInitDialog();

    /* select the default text and set the focus */
    CEdit* pEdit = (CEdit*) GetDlgItem(IDC_CREATESUBDIR_NEW);
    ASSERT(pEdit != NULL);
    pEdit->SetSel(0, -1);
    pEdit->SetFocus();

    return FALSE;   // we set the focus
}