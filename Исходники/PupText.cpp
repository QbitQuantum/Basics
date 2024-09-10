//////////////////
// text changed: resize window to fit
//
LRESULT CPopupText::OnSetText(WPARAM wp, LPARAM lp)
{
	UNREFERENCED_PARAMETER (wp);

	CClientDC dc = this;
	CFont* pOldFont = dc.SelectObject(&m_font);
	CRect rc;
	GetWindowRect(&rc);
	int x = (m_nStyle & JUSTIFYRIGHT) ? rc.right : rc.left;
	int y = rc.top;
	dc.DrawText(CString((LPCTSTR)lp), &rc, DT_CALCRECT);
	rc.InflateRect(m_szMargins);
	if (m_nStyle & JUSTIFYRIGHT)
		x -= rc.Width();
	SetWindowPos(NULL,x,y,rc.Width(),rc.Height(), SWP_NOZORDER|SWP_NOACTIVATE);
	dc.SelectObject (pOldFont);

	return Default();
}