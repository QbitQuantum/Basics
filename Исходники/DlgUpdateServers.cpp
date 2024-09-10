void CUpdateServersDlg::OnChangeURL()
{
	UpdateData();

	m_wndOK.EnableWindow( IsValidURL() );
}