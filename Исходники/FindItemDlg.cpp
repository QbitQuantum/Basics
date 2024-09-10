void CFindItemDlg::OnEnChangeEditKeyword()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CEdit* e = (CEdit*)GetDlgItem(IDC_EDIT_KEYWORD);
	if(e)
	{
		e->GetWindowTextW(m_KeywordStringValue);
		std::wstring wstr(m_KeywordStringValue);
		CSettingsSM::GetInstance()->SetUserString(wstr);
	}
}