void CDlgLog::OnBnClickedOk()
{
	m_running = FALSE;
	CWnd * frm = ::AfxGetMainWnd();
	frm->BringWindowToTop();
	OnOK();
}