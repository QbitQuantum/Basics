void CRunMacroDlg::OnSelchangeMacrolist() 
{
	// The user selected a macro, so enable the buttons
	CWnd* pButton = GetDlgItem(IDOK);
	pButton->EnableWindow(TRUE);
	pButton = GetDlgItem(IDC_EDIT);
	pButton->EnableWindow(TRUE);
	
}