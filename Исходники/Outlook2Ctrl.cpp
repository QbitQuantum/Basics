void COutlook2Ctrl::OnInvertTracker(const CRect& rc)
{
	CFrameWnd* pParentFrame = GetParentFrame ();
	CDC* pDC = pParentFrame->GetDC();
	CRect rect(rc);
    ClientToScreen(rect);
	pParentFrame->ScreenToClient(rect);

	CBrush br;
	br.CreateSolidBrush(GetSysColor(COLOR_HIGHLIGHT));
	HBRUSH hOldBrush = NULL;
	hOldBrush = (HBRUSH)SelectObject(pDC->m_hDC, br.m_hObject);
	pDC->PatBlt(rect.left, rect.top, rect.Width(), rect.Height(), DSTINVERT);
	if (hOldBrush != NULL) SelectObject(pDC->m_hDC, hOldBrush);
	ReleaseDC(pDC);

}