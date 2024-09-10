BOOL CScreenPropertiesDlg::OnInitDialog() 
{
	// Set up the name field.	
	CEdit *pEdit;
	
	pEdit = (CEdit *)GetDlgItem(IDC_EDIT1);
	
	SetDlgItemText(IDC_EDIT1, screenName);

	pEdit->LimitText(255);

	pEdit->SetFocus();
	pEdit->SetSel(0, -1);

	// Set up the width.
	pEdit = (CEdit *)GetDlgItem(IDC_EDIT2);

	SetDlgItemInt(IDC_EDIT2, screenWidth, FALSE);
	
	pEdit->LimitText(4);

	// Set up the height.
	pEdit = (CEdit *)GetDlgItem(IDC_EDIT3);
	
	SetDlgItemInt(IDC_EDIT3, screenHeight, FALSE);
	
	pEdit->LimitText(4);

	SetDlgItemText(IDC_EDIT10, userInfo);
	
	return FALSE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}