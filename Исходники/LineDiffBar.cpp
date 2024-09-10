void CLineDiffBar::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CRect rect;
	GetClientRect(rect);
	int height = rect.Height();
	int width = rect.Width();

	CDC cacheDC;
	VERIFY(cacheDC.CreateCompatibleDC(&dc));
	cacheDC.FillSolidRect(&rect, ::GetSysColor(COLOR_WINDOW));
	if (m_pCacheBitmap == NULL)
	{
		m_pCacheBitmap = new CBitmap;
		VERIFY(m_pCacheBitmap->CreateCompatibleBitmap(&dc, width, height));
	}
	CBitmap *pOldBitmap = cacheDC.SelectObject(m_pCacheBitmap);

	CRect upperrect = CRect(rect.left, rect.top, rect.right, rect.bottom/2);
	CRect lowerrect = CRect(rect.left, rect.bottom/2, rect.right, rect.bottom);

	if ((m_pMainFrm)&&(m_pMainFrm->m_pwndLeftView)&&(m_pMainFrm->m_pwndRightView))
	{
		CLeftView* leftView = m_pMainFrm->m_pwndLeftView;
		CRightView* rightView = m_pMainFrm->m_pwndRightView;
		if ((leftView->IsWindowVisible())&&(rightView->IsWindowVisible()))
		{
			BOOL bViewWhiteSpace = leftView->m_bViewWhitespace;
			BOOL bInlineDiffs = leftView->m_bShowInlineDiff;
			
			leftView->m_bViewWhitespace = TRUE;
			leftView->m_bShowInlineDiff = TRUE;
			leftView->m_bShowSelection = false;
			rightView->m_bViewWhitespace = TRUE;
			rightView->m_bShowInlineDiff = TRUE;
			rightView->m_bShowSelection = false;

			// Use left and right view to display lines next to each other
			leftView->DrawSingleLine(&cacheDC, &upperrect, m_nLineIndex);
			rightView->DrawSingleLine(&cacheDC, &lowerrect, m_nLineIndex);

			leftView->m_bViewWhitespace = bViewWhiteSpace;
			leftView->m_bShowInlineDiff = bInlineDiffs;
			leftView->m_bShowSelection = true;
			rightView->m_bViewWhitespace = bViewWhiteSpace;
			rightView->m_bShowInlineDiff = bInlineDiffs;
			rightView->m_bShowSelection = true;
		}
	} 

	VERIFY(dc.BitBlt(rect.left, rect.top, width, height, &cacheDC, 0, 0, SRCCOPY));

	cacheDC.SelectObject(pOldBitmap);
	cacheDC.DeleteDC();
}