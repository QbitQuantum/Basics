void CXInfoTip::OnPaint() 
{
	CPaintDC dc( this ); 

	CRect	rc;
	CBrush	WindowBrush;
	CBrush	FrameBrush;
	CBrush	InnerFrameBrush;
	HRGN	hRegion;
	CRgn	*pRegion;
	CFont	*pSysFont;

	
	GetClientRect(rc);

	
	InnerFrameBrush.CreateSolidBrush(::GetSysColor(COLOR_SCROLLBAR));
	FrameBrush.CreateSolidBrush(::GetSysColor(COLOR_WINDOWTEXT));
	WindowBrush.CreateSolidBrush(::GetSysColor(COLOR_WINDOW));

	
	GetWindowRegion(&dc, &hRegion);
	pRegion = CRgn::FromHandle(hRegion);

	
	dc.FillRgn(pRegion, &WindowBrush);
	dc.FrameRgn(pRegion, &InnerFrameBrush, 3, 3);
	dc.FrameRgn(pRegion, &FrameBrush, 1, 1);

	
	rc.DeflateRect(CX_ROUNDED, CY_ROUNDED, 0, 0);
	if (m_hIcon != NULL)
		rc.left = rc.left + m_IconSize.cx + CX_ICON_MARGIN;
	
	
	pSysFont = (CFont *)dc.SelectObject(&m_fntBold);
	
	dc.SetBkMode( TRANSPARENT );

	dc.DrawText (m_strCaption, &rc, DT_TOP | DT_LEFT);

	dc.SelectObject(m_pFont);

	CRect rc2 = rc;
	rc2.top += m_nCaptionHeight;
	dc.DrawText(m_szText, &rc2, DT_TOP | DT_LEFT);

	if (m_bShowDSA && m_bPlaced == false)
	{
		m_bPlaced = true;
		m_btnDSA.MoveWindow (rc.left, m_yDSA, m_cxDSA + 10 + 20, 20);
	}

	
	if (m_hIcon != NULL)
		DrawIconEx(dc.m_hDC, CX_ROUNDED, CY_ROUNDED, m_hIcon, m_IconSize.cx, m_IconSize.cy, 0, NULL, DI_NORMAL);

	
	::DeleteObject(hRegion);
	dc.SelectObject(pSysFont);

}                                        