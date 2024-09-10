//退出监控
void CKillGamesDlg::OnButton5() 
{
	BOOL m_isKeyRegistered = UnregisterHotKey(GetSafeHwnd(),m_nHotKeyID);
	ASSERT(m_isKeyRegistered != FALSE);
	CDialog::OnClose();
	CDialog::OnCancel();
}