void CBCGPMSMCaptionBar::DoPaint (CDC* pDCPaint)
{
	ASSERT_VALID(this);
	ASSERT_VALID(pDCPaint);

	CRect rectClip;
	pDCPaint->GetClipBox (rectClip);

	CRect rect;
	GetClientRect(rect);

	CBCGPMemDC memDC (*pDCPaint, this);
	CDC* pDC = &memDC.GetDC ();

	CBCGPVisualManager::GetInstance ()->OnFillBarBackground (pDC, this,
		rect, rectClip);

	HGDIOBJ  hOldFont    = pDC->SelectObject (GetCaptionFont());

	int      nOldMode    = pDC->SetBkMode    (TRANSPARENT);
	COLORREF crTextColor = pDC->SetTextColor (GetCaptionTextColor());
	COLORREF crBkColor   = pDC->SetBkColor   (globalData.clrBtnFace);

	if (m_hIcon != NULL && m_szIcon != CSize (0, 0))
	{
		CRect rectIcon (0, 0, m_SystemHeight, rect.Height ());

		int x = max (0, (rectIcon.Width ()  - m_szIcon.cx) / 2);
		int y = max (0, (rectIcon.Height () - m_szIcon.cy) / 2);

		::DrawIconEx (pDC->GetSafeHdc (), x, y, m_hIcon, m_szIcon.cx, m_szIcon.cy,
					  0, NULL, DI_NORMAL);

		rect.left  += m_SystemHeight;

		CRect rt;
		m_BtnMinimize.GetWindowRect (rt);
		ScreenToClient (rt);

		rect.right = rt.left - 1;
	}

	if (!m_strCaption.IsEmpty ())
	{
		pDC->DrawText (m_strCaption, rect, DT_END_ELLIPSIS | DT_SINGLELINE | DT_VCENTER);
	}

	pDC->SetTextColor (crTextColor);
	pDC->SetBkColor   (crBkColor);
	pDC->SetBkMode    (nOldMode);

	pDC->SelectObject (hOldFont);
}