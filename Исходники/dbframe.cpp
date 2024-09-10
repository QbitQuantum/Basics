void CDBFrame::OnSetWndRgn()
{
	/*
	//创建凸出的部分区域
	CRgn rgnAdd;
	CRect rcRgnAdd;
	GetTitleRect(rcRgnAdd);
	rcRgnAdd.bottom = rcRgnAdd.top + 3;
	rgnAdd.CreateRectRgnIndirect(rcRgnAdd);
	*/

	CRect rcRgn;
	GetWindowRect(&rcRgn);
	rcRgn.OffsetRect(-rcRgn.left, -rcRgn.top);
	rcRgn.top;
	m_rgnWnd.DeleteObject();
	m_rgnWnd.CreateRoundRectRgn(rcRgn.left, rcRgn.top, rcRgn.right,
		rcRgn.bottom, m_szRoundCorner.cx, m_szRoundCorner.cy);
	
	/*
	//合并区域
	m_rgnWnd.CombineRgn(&m_rgnWnd, &rgnAdd, RGN_OR);
	*/

	SetWindowRgn(m_rgnWnd, TRUE);

}