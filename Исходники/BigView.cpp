BOOL CBigScrollView::OnScroll(UINT nScrollCode, UINT nPos, BOOL bDoScroll)
{
	// calc new x position
	int x = GetScrollPos(SB_HORZ);
	int xOrig = x;

	switch (LOBYTE(nScrollCode))
	{
		case SB_TOP:
			x = 0;
			break;
		case SB_BOTTOM:
			x = INT_MAX;
			break;
		case SB_LINEUP:
			x -= m_lineDev.cx;
			break;
		case SB_LINEDOWN:
			x += m_lineDev.cx;
			break;
		case SB_PAGEUP:
			x -= m_pageDev.cx;
			break;
		case SB_PAGEDOWN:
			x += m_pageDev.cx;
			break;
		case SB_THUMBTRACK:
		{
			SCROLLINFO si;
			si.fMask = SIF_TRACKPOS;
			si.cbSize = sizeof(SCROLLINFO);
			GetScrollInfo(SB_HORZ,&si,SIF_TRACKPOS);
			x = si.nTrackPos;
			break;
		}
	}

	// calc new y position
	int y = GetScrollPos(SB_VERT);
	int yOrig = y;

	switch (HIBYTE(nScrollCode))
	{
		case SB_TOP:
			y = 0;
			break;
		case SB_BOTTOM:
			y = INT_MAX;
			break;
		case SB_LINEUP:
			y -= m_lineDev.cy;
			break;
		case SB_LINEDOWN:
			y += m_lineDev.cy;
			break;
		case SB_PAGEUP:
			y -= m_pageDev.cy;
			break;
		case SB_PAGEDOWN:
			y += m_pageDev.cy;
			break;
		case SB_THUMBTRACK:
		{
			SCROLLINFO si;
			si.fMask = SIF_TRACKPOS;
			si.cbSize = sizeof(SCROLLINFO);
			GetScrollInfo(SB_VERT,&si,SIF_TRACKPOS);
			y = si.nTrackPos;
			break;
		}
	}

	BOOL bResult = OnScrollBy(wxSize(x - xOrig, y - yOrig), bDoScroll);
	if (bResult && bDoScroll)
		UpdateWindow();

	return bResult;
}