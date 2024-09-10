LRESULT CLrcMask::OnNCMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (!m_bTrace)
	{
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(tme);
		tme.hwndTrack = this->m_hWnd;
		tme.dwFlags = TME_LEAVE|TME_NONCLIENT;
		tme.dwHoverTime = 10;
		m_bTrace = _TrackMouseEvent(&tme)==0 ? false : true;
	}	
	DuiLib::CDuiRect rect;
	GetWindowRect(&rect);
	DuiLib::CPoint point = DuiLib::CPoint(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
	RECT sizebox;
	sizebox = GetPaintMgr()->GetSizeBox();
	rect.left+= sizebox.left;
	rect.top+=sizebox.top;
	rect.right-=sizebox.right;
	rect.bottom-=sizebox.bottom;
	if (::PtInRect(&rect,point))
	{
		SetCursor(LoadCursor(NULL,MAKEINTRESOURCE(32651)));
	}
	
	m_bMouseOn = true;
//	bHandled = false;
	
	YTrace_(m_bMouseOn?_T("CLrcMask::OnMouseMove:m_bMouseOn=true"):_T("CLrcMask::OnMouseMove:m_bMouseOn=false"));
	return 0;
}