BOOL CCustomRotateDialog::OnInitDialog() 
{
	BOOL fResult = CPmwDialog::OnInitDialog();
	
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_ROTATION);
	if (pEdit != NULL)
	{
		pEdit->LimitText(8); // -xxx.yyy
		pEdit->SetSel(0, -1);
		pEdit->SetFocus();
		fResult = FALSE;		// We set the focus.
	}

	return fResult;
}