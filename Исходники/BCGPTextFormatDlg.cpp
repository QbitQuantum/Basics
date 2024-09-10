void CBCGPTextPreviewCtrl::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CBCGPMemDC memDC (dc, this);
	CDC* pDC = &memDC.GetDC ();

	CRect rect;
	GetClientRect(rect);

	pDC->FillRect (rect, &globalData.brWindow);

	if (m_pGM == NULL || m_pFormat == NULL)
	{
		return;
	}

	m_pGM->BindDC(pDC, rect);

	if (!m_pGM->BeginDraw())
	{
		return;
	}

	m_pGM->FillRectangle(rect, m_brFill);

	int nVertMargin = rect.Height() / 4;
	int nHorzMargin = rect.Width() / 4;

	switch (m_HorzAlign)
	{
	case CBCGPTextFormat::BCGP_TEXT_ALIGNMENT_LEADING:
		rect.right -= nHorzMargin;
		break;

	case CBCGPTextFormat::BCGP_TEXT_ALIGNMENT_TRAILING:
		rect.left += nHorzMargin;
		break;
	}

	switch (m_VertAlign)
	{
	case CBCGPTextFormat::BCGP_TEXT_ALIGNMENT_LEADING:
		rect.bottom -= nVertMargin;
		break;

	case CBCGPTextFormat::BCGP_TEXT_ALIGNMENT_TRAILING:
		rect.top += nVertMargin;
		break;
	}

	m_pGM->DrawText(m_strText, rect, *m_pFormat, m_brText);

	m_pGM->EndDraw();
}