void CBCGPRibbonKeyTip::OnPaint() 
{
	ASSERT_VALID (m_pElement);

	CPaintDC dc(this); // device context for painting

	CBCGPMemDC memDC (dc, this);
	CDC* pDC = &memDC.GetDC ();

	CFont* pOldFont = pDC->SelectObject (&globalData.fontRegular);
	ASSERT (pOldFont != NULL);

	pDC->SetBkMode (TRANSPARENT);

	CRect rect;
	GetClientRect (rect);

	m_pElement->OnDrawKeyTip (pDC, rect, m_bIsMenu);

	pDC->SelectObject (pOldFont);
}