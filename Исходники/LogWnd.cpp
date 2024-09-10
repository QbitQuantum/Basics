void CLogWnd::OnScaleChanged()
{
	GETTHEMEFONT(&m_font, _T("LogWnd"), _T("Font"));
	m_edit.SetFont(m_font);

	MoveWindow(m_edit, 0, 0, 0, 0);
	Invalidate(m_hWnd);
	RECT rc;
	GetClientRect(m_hWnd, &rc);
	OnSize(0, (WORD)rc.right, (WORD)rc.bottom);
}