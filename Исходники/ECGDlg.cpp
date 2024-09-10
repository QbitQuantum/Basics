void CECGDlg::UpdateStatus(CString str, BOOL flag)
{
	if(CLEARSTATUS == flag)
		m_strStatus = "";
	this->m_strStatus += str;
	this->m_strStatus += "\r\n";
	CEdit * pRecvStrEdit = (CEdit *)this->GetDlgItem(IDC_EDIT_STATUS);
	pRecvStrEdit->SetWindowTextW(this->m_strStatus);
}