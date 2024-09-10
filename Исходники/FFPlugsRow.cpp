void CFFPlugsRow::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	m_ParmSlider.SetFocus();
	if (point.x == -1 && point.y == -1) {	// if menu triggered via keyboard
		CRect	r;
		m_ParmSlider.GetWindowRect(r);	// position menu over slider
		point = r.TopLeft() + CSize(10, 10);	// offset looks nicer
	}
	CMenu	menu;
	menu.LoadMenu(IDR_VIEW_ROW_CTX);
	CMenu	*mp = menu.GetSubMenu(0);
	CWnd	*NotifyWnd = GetNotifyWnd();
	theApp.UpdateMenu(NotifyWnd, &menu);
	mp->TrackPopupMenu(0, point.x, point.y, NotifyWnd);
}