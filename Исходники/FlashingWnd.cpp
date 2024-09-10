// Create the "4 corner" region surrounding cRect
void CFlashingWnd::MakeFixedRegion(CRgn &wndRgn, CRgn &rgnTemp, CRgn &rgnTemp2, CRgn &rgnTemp3)
{
	CRect rectWnd(0, 0, m_cRect.Width() + THICKNESS + THICKNESS, m_cRect.Height() + THICKNESS + THICKNESS);
	CRect rectTemp(THICKNESS, THICKNESS, m_cRect.Width() + THICKNESS + 1, m_cRect.Height() + THICKNESS + 1);
	CRect rectTemp2(0, SIDELEN2, m_cRect.Width() + THICKNESS + THICKNESS, m_cRect.Height() - SIDELEN + 1);
	CRect rectTemp3(SIDELEN2, 0, m_cRect.Width() - SIDELEN + 1, m_cRect.Height() + THICKNESS + THICKNESS);

	VERIFY(wndRgn.CreateRectRgnIndirect(rectWnd));
	VERIFY(rgnTemp.CreateRectRgnIndirect(rectTemp));
	VERIFY(rgnTemp2.CreateRectRgnIndirect(rectTemp2));
	VERIFY(rgnTemp3.CreateRectRgnIndirect(rectTemp3));

	VERIFY(ERROR != wndRgn.CombineRgn(&wndRgn, &rgnTemp, RGN_DIFF));
	VERIFY(ERROR != wndRgn.CombineRgn(&wndRgn, &rgnTemp2, RGN_DIFF));
	VERIFY(ERROR != wndRgn.CombineRgn(&wndRgn, &rgnTemp3, RGN_DIFF));

	VERIFY(ERROR != wndRgn.OffsetRgn(m_cRect.left - THICKNESS, m_cRect.top - THICKNESS));
}