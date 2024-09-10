void CRasterPropShowPage::OnBnClickedCheckSet()
{
	CButton* pCheck =(CButton*)GetDlgItem(IDC_CHECK_SET);

	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_INVALIDVAL);

	if(BST_UNCHECKED == pCheck->GetCheck())
	{
		pEdit->EnableWindow(false);		                              
	}
	else
		pEdit->EnableWindow(true);

	UpdateChannelStaticInfo(m_comboBand.GetCurSel()+1);
}