void CBEdit::OnDraw(const CEspRect& rect)
{
	IAwsGc* pGc = GetGc();
	CEspSize size = *GetSize();
	CEspRect rt, rtTemp;

	// ÓÃ±³¾°Ìî³äÇøÓò
	DrawBK(pGc, rect);

	// »æÖÆ±ß¿ò
	if ( 0 == rect.m_ptLT.m_nX || 0 == rect.m_ptLT.m_nY || size.m_nWidth == rect.m_ptRB.m_nX || size.m_nHeight == rect.m_ptRB.m_nY )
	{
		if ( m_bIsFocus )
		{
			pGc->SetPenColor(m_oFocusBorderColor);
		}
		else
		{
			pGc->SetPenColor(m_oBorderColor);
		}
		CEspRect rtTemp(0, 0, size.m_nWidth, size.m_nHeight);
		pGc->DrawRect(rtTemp);
	}

	// »æÖÆÎÄ×Ö
//	rt = rect;
	rt.m_ptLT.m_nX = 3;
	rt.m_ptLT.m_nY = 3;
	rt.m_ptRB.m_nX = size.m_nWidth - 2;
	rt.m_ptRB.m_nY = size.m_nHeight - 2;
	pGc->SetTextColor(m_oTextColor);
	pGc->SetTextAlignment(AWS_TAM_Left);
	m_oFont.CreateFont(0, m_nFontSize);
	pGc->UseFont(m_oFont);

//	CAwsString strSub;
	m_strDrawText.Reset();
	m_strText.GetSubString(m_strDrawText, m_nStartDrawCharIndex, -1);
	pGc->DrawText(m_strDrawText, rt);

	pGc->DiscardFont();

	// »æÖÆ²åÈë·û
	rt.m_ptLT = m_oCaretPos;
	rt.m_ptRB.m_nX = rt.m_ptLT.m_nX + m_oCaretSize.m_nWidth;
	rt.m_ptRB.m_nY = rt.m_ptLT.m_nY + m_oCaretSize.m_nHeight;
	if ( rect.InterRect(rt, rtTemp) )
	{
		if ( m_bCaretIsVisible )
		{
			pGc->SetPenColor(m_oCaretColor);
			pGc->SetBrushColor(m_oCaretColor);

			pGc->DrawFillRect(rt);
		}
	}
}