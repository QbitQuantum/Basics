void cNewProject::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
		CEdit*	pEdit = NULL;

	if ( ( pEdit = ( CEdit* ) GetDlgItem ( IDC_EDIT_NEW ) ) == NULL )
		return;

	pEdit->SetFocus();
}