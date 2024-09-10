void QnSkinDialog::OnThemeNcPaint()
{
	CDC* pDc = GetWindowDC();
	CDC memDc;
	memDc.CreateCompatibleDC(pDc);

	CBitmap* bitmap = m_pThemeDialog->m_pBmpActiveBorder;
	if (bitmap == 0)
		return;

	BITMAP bm;
	bitmap->GetBitmap(&bm);

	CRect rcBmp;
	rcBmp.left = 0;
	rcBmp.right = bm.bmWidth;
	rcBmp.top = 0;
	rcBmp.bottom = bm.bmHeight;

	CRect rcWin;
	GetWindowRect(&rcWin);
	rcWin -= CPoint(rcWin.left, rcWin.top);

	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDc, rcWin.Width(),m_pThemeDialog->m_nToTop);
	
	CBitmap* pOldBmp = memDc.SelectObject(&bmp);
	DrawBorder(pDc, rcWin, rcBmp, TRUE);
	rcWin.bottom = rcWin.top + m_pThemeDialog->m_nToTop;
	DrawCaption(&memDc, rcWin, rcBmp, TRUE);
	pDc->BitBlt(0, 0, rcWin.Width(), rcWin.Height(), &memDc, 0, 0, SRCCOPY);
	memDc.SelectObject(pOldBmp);

	memDc.DeleteDC();
	ReleaseDC(pDc);
}