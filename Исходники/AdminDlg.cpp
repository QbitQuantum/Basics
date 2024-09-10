void CAdminDlg::OnDblclkTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CButton *Btn = (CButton *)GetDlgItem(IDEDIT);
	if (Btn->IsWindowEnabled())	OnEdit();
	*pResult = 0;
}