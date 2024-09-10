void CGrammarBuilderComplxConDlg::HidePopup()
{
	CWnd* pWnd;

	pWnd=&m_recPopup;
	pWnd->ShowWindow(SW_HIDE);
	m_bPopupVisible=FALSE;
	pWnd=&m_datatblComplexConcepts;
	pWnd->RedrawWindow();
}