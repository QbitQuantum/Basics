void CCJSizeDockBar::DrawBorders(CDC *pDC, CRect &rect)
{
	int cxBorderLeft	= 0;
	int cxBorderRight	= 0;
	int cyBorderTop		= 0;
	int cyBorderBottom	= 0;
	
	CRect rc;
	rc.CopyRect(&rect);
	
	if (m_dwStyle & CBRS_BORDER_TOP) {
		pDC->FillSolidRect(rc.left,rc.top,rc.Width(),1,m_clrBtnShadow);
		pDC->FillSolidRect(rc.left,rc.top+1,rc.Width(),1,m_clrBtnHilite);
		cyBorderTop+=2;
	}
	
	if (m_dwStyle & CBRS_BORDER_BOTTOM) {
		pDC->FillSolidRect(rc.left,rc.bottom-1,rc.Width(),1,m_clrBtnHilite);
		pDC->FillSolidRect(rc.left,rc.bottom-2,rc.Width(),1,m_clrBtnShadow);
		cyBorderBottom+=2;
	}
	
	if (m_dwStyle & CBRS_BORDER_LEFT) {
		pDC->FillSolidRect(rc.left,rc.top,1,rc.Height(),m_clrBtnShadow);
		pDC->FillSolidRect(rc.left+1,rc.top,1,rc.Height(),m_clrBtnHilite);
		cxBorderLeft+=2;
	}
	
	if (m_dwStyle & CBRS_BORDER_RIGHT) {
		pDC->FillSolidRect(rc.right-2,rc.top,1,rc.Height(),m_clrBtnShadow);
		pDC->FillSolidRect(rc.right-1,rc.top,1,rc.Height(),m_clrBtnHilite);
		cxBorderRight+=2;
	}
	
	UINT nID = ((UINT)(WORD)::GetDlgCtrlID(m_hWnd));
	
	CRect rcTrack;
	rcTrack.CopyRect(&rc);
	
	if (nID == AFX_IDW_SIZEBAR_LEFT) {
		rcTrack.left    = rc.right-m_iTrackBorderSize;
		rcTrack.right  += 1;
		rcTrack.top    += 1;
		rcTrack.bottom -= 1;
		pDC->FillSolidRect(rcTrack,m_clrBtnFace);
		pDC->Draw3dRect(rcTrack,m_clrBtnHilite,m_clrBtnShadow);
		cxBorderRight = m_iTrackBorderSize;
	}
	
	else if (nID == AFX_IDW_SIZEBAR_TOP) {
		rcTrack.top = rc.bottom-m_iTrackBorderSize;
		rcTrack.bottom+=1;
		pDC->FillSolidRect(rcTrack,m_clrBtnFace);
		pDC->Draw3dRect(rcTrack,m_clrBtnHilite,m_clrBtnShadow);
		cyBorderBottom = m_iTrackBorderSize;	
	}
	
	else if (nID == AFX_IDW_SIZEBAR_RIGHT) {
		rcTrack.right   = rc.left+m_iTrackBorderSize;
		rcTrack.left   -= 1;
		rcTrack.top    += 1;
		rcTrack.bottom -= 1;
		pDC->FillSolidRect(rcTrack,m_clrBtnFace);
		pDC->Draw3dRect(rcTrack,m_clrBtnHilite,m_clrBtnShadow);
		cxBorderLeft = m_iTrackBorderSize;		
	}
	
	else if (nID == AFX_IDW_SIZEBAR_BOTTOM) {
		rcTrack.bottom = rc.top+m_iTrackBorderSize;
		rcTrack.top-=1;
		pDC->FillSolidRect(rcTrack,m_clrBtnFace);
		pDC->Draw3dRect(rcTrack,m_clrBtnHilite,m_clrBtnShadow);
		cyBorderTop = m_iTrackBorderSize;	
	}
	
	rect.left	+= cxBorderLeft;
	rect.right	-= cxBorderRight;
	rect.top	+= cyBorderTop;
	rect.bottom	-= cyBorderBottom;
}