void CRemoteProfileLoginDlg::OnSelchangeAcctname() 
{
	UpdateData(TRUE);
	// Save the previous stuff?
	CString csKey;
	// Populate the fields with the values of the new selection
	m_iSel = m_ccbName.GetCurSel();
	if ( m_iSel == -1 )
	{
		m_cePassword.SetWindowText("");
		UpdateData(FALSE);
		return;
	}
	m_ccbName.GetLBText(m_iSel, m_csAccountName);
	csKey.Format("%s\\%s", REGKEY_REMOTELOGIN, m_csAccountName);
	m_cePassword.SetWindowText(Encrypt(Main->GetRegistryString("Password", "", hRegLocation, csKey)));

	// Update the last account setting
	Main->PutRegistryString("LastRemoteProfileAccount", m_csAccountName);
	UpdateData(FALSE);
}