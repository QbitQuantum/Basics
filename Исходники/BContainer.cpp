void BContainer::OnVScroll(UINT nSBCode,UINT nPos, CScrollBar* pScrollBar)
{
	// Handle vertical scrollbar messages
	// These can be tweaked to better fit the implementation
	int nInc;
	int yPos;
	SCROLLINFO si;


	GetScrollInfo(SB_VERT,&si,SIF_POS | SIF_RANGE | SIF_PAGE);
	yPos = si.nPos;
	nInc = 0;
	switch (nSBCode)
	{
	case SB_TOP: nInc = -si.nPos; break;
	case SB_BOTTOM: nInc = si.nMax-si.nPos; break;
	case SB_LINEUP: 
		if(si.nPos > 0)
			nInc = -1; 
		else 
			nInc = 0;
		break;
	case SB_LINEDOWN:
		if(si.nPage+si.nPos < si.nMax+1)
			nInc = 1; 
		else
			nInc = 0;
		break;
//	case SB_PAGEUP: nInc = min(-1, -m_nVertInc); break;
//	case SB_PAGEDOWN: nInc = max(1, m_nVertInc); break;
	case SB_THUMBTRACK: nInc = nPos - si.nPos; break;
	default: nInc = 0;
	}

//	nInc = max(-si.nPos, min(nInc, si.nMax - si.nPos));

	if (nInc)
	{
		si.nPos += nInc;
		int iMove = (yPos - si.nPos)*(ELEMENT_HEIGHT+ELEMENT_SIZE_BETWEEN);

		si.cbSize = sizeof(SCROLLINFO);
		si.fMask = SIF_POS ;
		SetScrollInfo(SB_VERT,&si,true);

		ScrollWindow(0, iMove, NULL, NULL);
	//	CWnd::UpdateWindow();
		//SetScrollPos(SB_VERT, m_nVscrollPos, TRUE);
		
	}
	

	
	CWnd::OnVScroll(nSBCode, nPos, pScrollBar);

}