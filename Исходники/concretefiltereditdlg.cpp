LRESULT CLogTIDFilterEditDlg::OnOK(WORD , WORD , HWND , BOOL& )
{
	CStringW text;
	GetDlgItemText(IDC_EDIT_LOGTID, text);
	unsigned int tid;
	swscanf_s((LPCWSTR)text, L"%u", &tid);
	m_filter->setfilter(tid);
	EndDialog(IDOK);
	return 0;
}