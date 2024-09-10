//*******************************************************************************
void CBCGPTextGaugeImpl::OnDraw(CBCGPGraphicsManager* pGM, const CBCGPRect& /*rectClip*/, DWORD dwFlags)
{
	ASSERT_VALID(pGM);

	if (m_rect.IsRectEmpty() || !m_bIsVisible || m_strText.IsEmpty())
	{
		return;
	}

	if ((dwFlags & m_DefaultDrawFlags) == 0)
	{
		return;
	}

	CBCGPRect rect = m_rect;
	if (m_bIsSubGauge)
	{
		rect.OffsetRect(-m_ptScrollOffset);
	}

	pGM->FillRectangle(rect, GetFillBrush ());

	const CBCGPBrush& br = m_bOff ? m_brTextLight : m_brText;

	CreateResources(CBCGPBrush(), FALSE);
	pGM->DrawText(m_strText, rect, m_textFormat, br);

	pGM->DrawRectangle(rect, GetOutlineBrush (), GetScaleRatioMid());
	
	SetDirty(FALSE);
}