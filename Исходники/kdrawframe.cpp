void KDrawFrame::Draw(CDCHandle& dc, CRect rct, COLORREF clrBk)
{
	CBrush brush;
	brush.CreateSolidBrush(clrBk);
	HBRUSH hOldBrush = dc.SelectBrush(brush);
	// 绘制背景
	dc.Rectangle(&rct);

	int left, top, right, botton;
	CSize size = GetBmpSize(m_bmpLeftTop);
	left = size.cx;
	top = size.cy;

	size = GetBmpSize(m_bmpRightBotton);
	right = size.cx;
	botton = size.cy;

	CDC hTmpDC;
	hTmpDC.CreateCompatibleDC(dc);

	HBITMAP bOldbmp = hTmpDC.SelectBitmap(m_bmpLeftTop);
	dc.BitBlt(0, 0, left, top, hTmpDC, 0, 0, SRCCOPY);
	
	size = GetBmpSize(m_bmpTopBoder);
	hTmpDC.SelectBitmap(m_bmpTopBoder);
	dc.StretchBlt(left, 0, rct.right-right, top, hTmpDC, 0, 0, size.cx, size.cy, SRCCOPY);

	hTmpDC.SelectBitmap(m_bmpRightTop);
	dc.BitBlt(rct.right-right, 0, rct.right, top, hTmpDC, 0, 0, SRCCOPY);

	size = GetBmpSize(m_bmpLeftBoder);
	hTmpDC.SelectBitmap(m_bmpLeftBoder);
	dc.StretchBlt(0, top, left, rct.bottom-botton-top, hTmpDC, 0, 0, size.cx, size.cy, SRCCOPY);
	
	size = GetBmpSize(m_bmpRightBoder);
	hTmpDC.SelectBitmap(m_bmpRightBoder);
	dc.StretchBlt(rct.right-right, top, right, rct.bottom-botton-top, hTmpDC, 0, 0, size.cx, size.cy, SRCCOPY);

	hTmpDC.SelectBitmap(m_bmpLeftBotton);
	dc.BitBlt(0, rct.bottom-botton, left, botton, hTmpDC, 0, 0, SRCCOPY);

	size = GetBmpSize(m_bmpBottonBoder);
	hTmpDC.SelectBitmap(m_bmpBottonBoder);
	dc.StretchBlt(left, rct.bottom-botton, rct.right-right, botton, hTmpDC, 0, 0, size.cx, size.cy, SRCCOPY);

	hTmpDC.SelectBitmap(m_bmpRightBotton);
	dc.BitBlt(rct.right-right, rct.bottom-botton, rct.right, botton, hTmpDC, 0, 0, SRCCOPY);
	
	hTmpDC.SelectBitmap(bOldbmp);
	dc.SelectBrush(hOldBrush);
}