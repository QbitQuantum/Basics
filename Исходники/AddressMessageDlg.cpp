void CAddressMessageDlg::OnStaticHazard() 
{
	// TODO: Add your control notification handler code here
	CWnd *pCBox;

	pCBox = (CComboBox *)GetDlgItem(IDC_STATIC_INITIALIZATION_CODE);
	pCBox->ShowWindow(SW_SHOW);
	pCBox = (CComboBox *)GetDlgItem(IDC_INITIALIZATION_CODE);
	pCBox->ShowWindow(SW_SHOW);
	pCBox = (CComboBox *)GetDlgItem(IDC_STATIC_TEMPORARY_KEY);
	pCBox->ShowWindow(SW_SHOW);
	pCBox = (CComboBox *)GetDlgItem(IDC_TEMPORARY_KEY);
	pCBox->ShowWindow(SW_SHOW);

	return;
}