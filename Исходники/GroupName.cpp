BOOL CGroupName::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CWnd *pWnd = GetDlgItem(IDC_NAME);
	if(pWnd)
		pWnd->SetFocus();
		
	return FALSE;
}