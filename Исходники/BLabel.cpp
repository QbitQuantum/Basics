void CBLabel::OnDraw(const CEspRect& rect)
{
	IAwsGc* pGc = GetGc();

	if ( !m_bIsBKTransparent )
	{
		pGc->SetPenColor(m_oBKColor);
		pGc->SetBrushColor(m_oBKColor);
		pGc->DrawFillRect(rect);
	}

	m_oFont.CreateFont(0, m_nTextSize);
	pGc->UseFont(m_oFont);

	pGc->SetTextColor(m_oTextColor);
	pGc->SetTextAlignment(m_eAlignMode);
	pGc->SetTextBKMode(AWS_TSM_Transparent);

	DrawText(pGc, rect);
}