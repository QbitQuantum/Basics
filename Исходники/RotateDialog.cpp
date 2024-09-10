BOOL CRotateDialog::OnInitDialog()
{
  CDialog::OnInitDialog();

  CWnd*	firstEdit = GetDlgItem(IDC_ROTATEANGLE);
  if (firstEdit) {
    firstEdit->SetFocus();
  }

  return FALSE;  // return TRUE unless you set the focus to a control
                // EXCEPTION: OCX Property Pages should return FALSE
}