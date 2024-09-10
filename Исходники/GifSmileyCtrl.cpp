HRESULT CGifSmileyCtrl::OnDrawSmiley(ATL_DRAWINFO& di, bool bCustom=false)
{
	USES_CONVERSION;
	if (di.dwDrawAspect != DVASPECT_CONTENT)
	{
		return E_FAIL;
	}
	if ( bCustom && !IsVisible(di))
	{
		return S_OK;
	}
	if (!m_pGifImage)
	{
		return E_FAIL;
	}
	RECT& rc = *(RECT*)di.prcBounds;

	HRGN hOldRgn, hNewRgn;

	if (!IsRectEmpty(&m_rectPos))
	{   //strange workaround for drawing zoom out smileys (look MS calculate it one pix larger than exactly)
		if (rc.bottom-rc.top-1 == m_rectPos.bottom-m_rectPos.top 
			&& rc.right-rc.left== m_rectPos.right-m_rectPos.left)
			rc.top+=1;
	}

	if ( bCustom )SelectSmileyClipRgn(di.hdcDraw, rc, hOldRgn, hNewRgn, TRUE);

	InflateRect(&rc,-1,0); //border offset to fix blinked cursor painting
	if ( (m_dwFlags&REO_INVERTEDSELECT) == 0 || !bCustom || m_bTransparent)
		DoDrawSmiley(di.hdcDraw, rc, rc.right-rc.left,rc.bottom-rc.top, m_nFrameSize.Width, m_nFrameSize.Height);
	else
	{
		Bitmap bmp(rc.right-rc.left,rc.bottom-rc.top, PixelFormat32bppARGB);
		Graphics g(&bmp);
		COLORREF col=(COLORREF)(m_clrBackColor);
		SolidBrush brush(Color(GetRValue(col),GetGValue(col),GetBValue(col)));
		g.FillRectangle( &brush, 0 ,0, rc.right-rc.left, rc.bottom-rc.top);
		HDC hdc=g.GetHDC();
		RECT mrc={0};
		mrc.right=rc.right-rc.left;
		mrc.bottom=rc.bottom-rc.top;
		DoDrawSmiley(hdc, mrc, mrc.right-mrc.left,mrc.bottom-mrc.top, m_nFrameSize.Width, m_nFrameSize.Height);
		InvertRect(hdc, &mrc);
		BitBlt(di.hdcDraw, rc.left, rc.top, rc.right-rc.left, rc.bottom-rc.top, hdc, 0, 0, SRCCOPY );
		g.ReleaseHDC(hdc);       
	}
	if ((m_dwFlags&REO_SELECTED) == REO_SELECTED && bCustom)
	{
		//Draw frame around
		HBRUSH oldBrush=(HBRUSH)SelectObject(di.hdcDraw, GetStockObject(NULL_BRUSH)); 
		HPEN oldPen=(HPEN)SelectObject(di.hdcDraw, GetStockObject(BLACK_PEN));
		::Rectangle(di.hdcDraw, rc.left, rc.top, rc.right, rc.bottom );
		SelectObject(di.hdcDraw, oldBrush);
		SelectObject(di.hdcDraw, oldPen);
	}
	AdvanceFrame();
	if (!bCustom) 
		m_bPaintValid=false;
	ResetClip(di.hdcDraw, hOldRgn, hNewRgn);

	return S_OK;
}