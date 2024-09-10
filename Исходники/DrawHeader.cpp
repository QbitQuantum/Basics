void CDrawHeader::DoDraw(HDC hdc)
{
	int iOldMode = ::SetBkMode(hdc, TRANSPARENT);
	COLORREF clrFore;
	OleTranslateColor(m_pAlmSum->m_clrHeaderFore, 0, &clrFore);
	COLORREF clrOldColor = ::SetTextColor(hdc, clrFore);
	
	HFONT hFont;
	HFONT hOldFont;
	if (m_pAlmSum->m_spHeaderFont != NULL)
	{
		CComPtr<IFont> pFont;
		m_pAlmSum->m_spHeaderFont->QueryInterface(IID_IFont, (void**)&pFont);
		pFont->get_hFont(&hFont);
	}
	else
	{
		hFont = (HFONT)::GetStockObject(DEFAULT_GUI_FONT);
	}
	hOldFont = (HFONT)::SelectObject(hdc, hFont);

	//Ìî³äÇ°¾°
	COLORREF clrFill;
	OleTranslateColor(m_pAlmSum->m_clrHeaderBack, 0, &clrFill);
	HBRUSH brush = ::CreateSolidBrush(clrFill);
	::FillRect(hdc, &m_rect, brush);
	::DeleteObject((HGDIOBJ)brush);

	CSimpleValArray<CColumn *>& apColumns = m_pAlmSum->m_apColumns;

	int nFirstColumn = m_pAlmSum->GetFirstVisibleColumn();
	int nCount = apColumns.GetSize();
	RECT rect = m_rect;
	
	BOOL bBreak = FALSE;
	for (int i = nFirstColumn; i < nCount; i++)
	{
		rect.right = rect.left + apColumns[i]->m_nWidth;
		if (rect.right > m_rect.right)
		{
			rect.right = m_rect.right;
			bBreak = TRUE;
		}
			
		apColumns[i]->Draw(hdc, rect, m_nColumnCatpture == i);
		
		if (bBreak)
			break;
		rect.left = rect.right;
	}

	rect.left = rect.right;
	rect.right = m_rect.right;
	DrawEdge(hdc, &rect, BDR_RAISEDINNER, BF_RECT);

	::SetBkMode(hdc, iOldMode);
	::SetTextColor(hdc, clrOldColor);
	::SelectObject(hdc, hOldFont);
}