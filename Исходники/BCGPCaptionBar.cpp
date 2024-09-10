//*****************************************************************************
void CBCGPCaptionBar::OnPaint() 
{
	CPaintDC dcPaint (this);
	CBCGPMemDC memDC (dcPaint, this);
	CDC& dc = memDC.GetDC ();

	CRect rectClient;
	GetClientRect(rectClient);

	OnDrawBackground (&dc, rectClient);

	int nOldBkMode = dc.SetBkMode (TRANSPARENT);
	COLORREF clrOldText = 
		dc.SetTextColor (m_clrBarText != (COLORREF) -1 ? m_clrBarText : 
		CBCGPVisualManager::GetInstance ()->GetCaptionBarTextColor (this));

	CFont* pOldFont = dc.SelectObject (
		m_hFont == NULL ? &globalData.fontRegular : CFont::FromHandle (m_hFont));

	CRect rectButton = m_rectButton;
	rectButton.top = max(rectClient.top + 1, rectButton.top);
	rectButton.bottom = min(rectClient.bottom - 1, rectButton.bottom);

	OnDrawButton (&dc, rectButton, m_strBtnText, m_bBtnEnabled);
	OnDrawText (&dc, m_rectDrawText, m_strText);

	if (!m_rectImage.IsRectEmpty ())
	{
		OnDrawImage (&dc, m_rectImage);
	}

	if (!m_rectClose.IsRectEmpty ())
	{
		COLORREF clrText = CBCGPVisualManager::GetInstance ()->OnFillCaptionBarButton (&dc, this,
			m_rectClose, m_bIsCloseBtnPressed, m_bIsCloseBtnHighlighted, FALSE,
			FALSE, TRUE);

		CBCGPVisualManager::GetInstance ()->OnDrawCaptionBarCloseButton(&dc, this, 
			m_rectClose, m_bIsCloseBtnPressed, m_bIsCloseBtnHighlighted, clrText);

		CBCGPVisualManager::GetInstance ()->OnDrawCaptionBarButtonBorder (&dc, this,
			m_rectClose, m_bIsCloseBtnPressed, m_bIsCloseBtnHighlighted, FALSE,
			FALSE, TRUE);
	}

	dc.SelectObject (pOldFont);
	dc.SetTextColor (clrOldText);
	dc.SetBkMode (nOldBkMode);
}