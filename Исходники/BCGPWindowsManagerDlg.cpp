//**************************************************************************************
BOOL CBCGPWindowsManagerDlg::OnInitDialog() 
{
	CBCGPDialog::OnInitDialog();
	
	if (AfxGetMainWnd () != NULL && 
		(AfxGetMainWnd ()->GetExStyle () & WS_EX_LAYOUTRTL))
	{
		ModifyStyleEx (0, WS_EX_LAYOUTRTL);
	}

	FillWindowList();

	// If no MDI actions are availible, hide all MDI-related buttons:

	if (!m_bMDIActions)
	{
		GetDlgItem(IDC_BCGBARRES_TILEHORZ)->ShowWindow (SW_HIDE);
		GetDlgItem(IDC_BCGBARRES_TILEVERT)->ShowWindow (SW_HIDE);
		GetDlgItem(IDC_BCGBARRES_CASCADE)->ShowWindow (SW_HIDE);
		GetDlgItem(IDC_BCGBARRES_MINIMIZE)->ShowWindow (SW_HIDE);
	}

	SelActive();
	UpdateButtons();

	CWnd* pBtnHelp = GetDlgItem (ID_HELP);
	if (pBtnHelp != NULL)
	{
		pBtnHelp->ShowWindow (m_bHelpButton ? SW_SHOW : SW_HIDE);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}