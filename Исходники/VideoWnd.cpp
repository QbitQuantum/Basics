void CVideoWnd::OnPaint()
{
	CPaintDC dc(this);

	//WIDTHHEIGHT
	CRect clrect(m_rectWnd);
	clrect.right -= clrect.left;
	clrect.bottom -= clrect.top;
	clrect.left = 0;
	clrect.top = 0;

	int width = clrect.right - clrect.left;
	int height = clrect.bottom - clrect.top;

	CRect cRect(clrect);
	CDC memDC;
	memDC.CreateCompatibleDC(&dc);
	CDC *pDC = &memDC;
	CBitmap NewMemBmp;
	NewMemBmp.CreateCompatibleBitmap(&dc, width, height);
	CBitmap* pOldMemBmp = pDC->SelectObject(&NewMemBmp);
	if (!m_iStatus) {
		pDC->FillSolidRect(0, 0, clrect.Width(), clrect.Height(), RGB(255,255,255));
	} else if (m_ImageBitmap.GetSafeHandle()) {
		m_ImageBitmap.BitBlt(pDC, CPoint(0,0));
	}

	CFont dxfont;
	dxfont.CreateFontIndirect(&m_textfont);
	CFont* oldfont = (CFont *) pDC->SelectObject(&dxfont);

	//Draw Text
	int textlength = m_textstring.GetLength(); //get number of bytes
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(m_rgb);
	pDC->DrawText((char *)LPCTSTR(m_textstring), textlength, &m_tracker.m_rect, m_horzalign | DT_VCENTER | DT_WORDBREAK );

	pDC->SelectObject(oldfont);

	if ((m_bBorderYes) && (regionSHAPE == m_regionType)) {
		double rx = cRect.Width() * m_roundrectFactor;
		double ry = cRect.Height() * m_roundrectFactor;
		double rval = (rx > ry) ? ry : rx;

		CPen borderPen;
		borderPen.CreatePen( PS_SOLID , m_borderSize, m_borderColor );
		CPen* oldPen = (CPen *) pDC->SelectObject(&borderPen);

		LOGBRUSH logbrush;
		logbrush.lbStyle = BS_HOLLOW;
		CBrush borderBrush;
		borderBrush.CreateBrushIndirect(&logbrush);
		CBrush* oldBrush = (CBrush *) pDC->SelectObject(&borderBrush);

		int drawOffset = m_borderSize/2;

		if (m_regionPredefinedShape == regionROUNDRECT) {
			pDC->RoundRect(drawOffset-1, drawOffset-1, cRect.Width()-1-drawOffset, cRect.Height()-1-drawOffset, (int) rval, (int) rval);

		} else if (m_regionPredefinedShape == regionELLIPSE) {
			pDC->Ellipse(drawOffset-1,drawOffset-1, cRect.Width()-1-drawOffset, cRect.Height()-1-drawOffset);
		} else if (m_regionPredefinedShape == regionRECTANGLE) {
			pDC->Rectangle(drawOffset-1, drawOffset-1, cRect.Width()-1-drawOffset, cRect.Height()-1-drawOffset);
		}

		pDC->SelectObject(oldBrush);
		pDC->SelectObject(oldPen);
		borderPen.DeleteObject();
		borderBrush.DeleteObject();
	}

	CDC *pWinDC = &dc;
	pWinDC->BitBlt(0,0,clrect.Width(),clrect.Height(),pDC,0,0,SRCCOPY);

	pDC->SelectObject(pOldMemBmp);
	NewMemBmp.DeleteObject();
	memDC.DeleteDC();

	if (m_bTrackingOn) {
		m_tracker.Draw(pWinDC);
	}
}