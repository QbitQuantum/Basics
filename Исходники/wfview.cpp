void CWFView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CBTEditDoc* pDoc = GetDocument();
	int	MinPos,MaxPos;
	SCROLLINFO ScrollInfo;

	CPoint ScrollPos = GetScrollPosition();
	m_ScrollX = ScrollPos.x;
	m_ScrollY = ScrollPos.y;
//	pDoc->GetScrollPosition((SLONG*)&m_ScrollX,(SLONG*)&m_ScrollY);

	GetScrollInfo( SB_HORZ, &ScrollInfo, SIF_ALL );
	MinPos = ScrollInfo.nMin;
	MaxPos = ScrollInfo.nMax-ScrollInfo.nPage;

	switch(nSBCode) {
		case	SB_THUMBPOSITION:
		case	SB_THUMBTRACK:
			m_ScrollX = nPos;
			break;
		case	SB_LINELEFT:
			m_ScrollX -= pDoc->GetTextureWidth();
			if(m_ScrollX < MinPos) m_ScrollX = MinPos;
			break;
		case	SB_LINERIGHT:
			m_ScrollX += pDoc->GetTextureWidth();
			if(m_ScrollX > MaxPos) m_ScrollX = MaxPos;
			break;
		case	SB_PAGELEFT:
			m_ScrollX -= ScrollInfo.nPage;
			if(m_ScrollX < MinPos) m_ScrollX = MinPos;
			break;
		case	SB_PAGERIGHT:
			m_ScrollX += ScrollInfo.nPage;
			if(m_ScrollX > MaxPos) m_ScrollX = MaxPos;
			break;
	}

	m_ScrollX /= pDoc->GetTextureWidth();
	m_ScrollX *= pDoc->GetTextureWidth();

	pDoc->RegisterScrollPosition(m_ScrollX-pDoc->GetTextureWidth()*OVERSCAN,m_ScrollY-pDoc->GetTextureHeight()*OVERSCAN);
  	UpdateAndValidate();

	if(pDoc->Get2DMode() == M2D_WORLD) {
		if(pDoc->GetAutoSync()) {
			pDoc->Set3DViewPos();	// Bind views.
  			pDoc->Invalidate3D();
		}
	}


	SetScrollPos( SB_HORZ, m_ScrollX, TRUE );
}