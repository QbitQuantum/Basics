BOOL CWSPrintDialog::OnInitDialog()
{
	bool bShowPrintRedlineOptions = Workshare::OptionApi::GetBool( L"ShowPrintRedlineOptions");
	CButton *pButton;
	pButton = (CButton*)GetDlgItem(IDC_CHECK_BW);
	if( bShowPrintRedlineOptions)
	{
		pButton->SetCheck(m_bBlackAndWhite);
	}
	else
	{
		pButton->ShowWindow( SW_HIDE);
	}

	pButton = (CButton*)GetDlgItem(IDC_CHECK_CHANGES);
	if( bShowPrintRedlineOptions)
	{
		pButton->SetCheck(m_bChangesOnly);
	}
	else
	{
		pButton->ShowWindow(SW_HIDE);
	}

	// resize the control to 3 times the width
	CRect rcIcon;
	GetDlgItem(1086)->GetWindowRect(rcIcon);

	GetDlgItem(1086)->SetWindowPos(&wndTop, 0, 0, 2+rcIcon.Width()*3, 2+rcIcon.Height(), SWP_NOMOVE);

	CEdit *pEdit = (CEdit *)GetDlgItem(1154);
	pEdit->EnableWindow(TRUE);	

	CButton *pCheck = (CButton *)GetDlgItem( 1041 );
	m_bCollate = pCheck->GetCheck();

	CButton *pCheckPrintToFile = (CButton *)GetDlgItem( 1040 );
	pCheckPrintToFile->SetCheck(FALSE);

	return TRUE;
}