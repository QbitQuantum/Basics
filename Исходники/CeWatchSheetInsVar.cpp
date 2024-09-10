BOOL CCeWatchSheetInsVar::OnInitDialog() 
{
	BOOL bResult = CPropertySheet::OnInitDialog();
	

	CWnd* pOk = GetDlgItem(IDOK);
	CWnd* pApply = GetDlgItem(ID_APPLY_NOW);
	CWnd* pCancel = GetDlgItem(IDCANCEL);
	
	ASSERT(pOk != NULL);
	ASSERT(pApply != NULL);
	ASSERT(pCancel != NULL);

	// hide OK buttton
	// rename Cancel and Apply button
	if (pOk && pCancel && pApply)
	{
		pOk->ShowWindow(SW_HIDE);

		CString str;
		str.LoadString(IDS_CLOSE);
		pCancel->SetWindowText(str);

		str.LoadString(IDS_ADD);
		pApply->SetWindowText(str);
	}

	return bResult;
}