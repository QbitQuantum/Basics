void CThhylDlg::OnAutocomp() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	
	SHAutoComplete( ((CEdit*)GetDlgItem(IDC_RPYFILE))->GetSafeHwnd(),
		m_bAutocomp ? 0x10000043 : 0x20000043 );
}