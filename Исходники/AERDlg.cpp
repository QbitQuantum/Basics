void CAERDlg::OnStop() 
{
	m_enAER = AER_STOP;
	m_bDontAskAgain = IsDlgButtonChecked (IDC_DONTASKAGAIN) == BST_CHECKED;
	EndDialog (IDOK);	
}