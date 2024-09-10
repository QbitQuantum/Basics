///////////////////////////////////////////////////////////////////////////////
// OnTimer
void CXTipListBox::OnTimer(UINT nIDEvent) 
{
	CPoint point;
	::GetCursorPos(&point);
	ScreenToClient(&point);

	CRect rectClient;
	GetClientRect(&rectClient);

	DWORD dwStyle = GetStyle();
	if ((!rectClient.PtInRect(point)) || ((dwStyle & WS_VISIBLE) == 0))
	{
		TRACE(_T("not in listbox =====\n"));
		KillTimer(nIDEvent);
		::SendMessage(m_hWndToolTip, TTM_TRACKACTIVATE, FALSE, (LPARAM)(LPTOOLINFO) &m_ToolInfo);
	}
}