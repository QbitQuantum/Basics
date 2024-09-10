void CValueAxis::DoDraw(HDC hdcDest)
{
	USES_CONVERSION;

	if (!m_bShowAxis)
		return;

	double dViewMinValue = fabs(m_dViewMinVal - DBL_MAX) < 1E-6 ? m_dMinVal : m_dViewMinVal;
	double dViewMaxValue = fabs(m_dViewMaxVal + DBL_MAX) < 1E-6 ? m_dMaxVal : m_dViewMaxVal;

	if (::IsRectEmpty(&m_rect))
		return;

	COLORREF clrAxis;
	OleTranslateColor(m_clrAxis, NULL, &clrAxis);
	COLORREF clrOldText = ::SetTextColor(hdcDest, clrAxis);
	
	HFONT hFont;
	HFONT hOldFont;
	if (m_spTickFont != NULL)
	{
		CComPtr<IFont> pFont;
		m_spTickFont->QueryInterface(IID_IFont, (void**)&pFont);
		pFont->get_hFont(&hFont);
	}
	else
	{
		hFont = (HFONT)::GetStockObject(DEFAULT_GUI_FONT);
	}
	hOldFont = (HFONT)::SelectObject(hdcDest, hFont);

	TEXTMETRIC tm;
	::GetTextMetrics(hdcDest, &tm);
	int nHalfTickHeight = (tm.tmHeight + tm.tmExternalLeading) / 2;
		
	HPEN hPen = ::CreatePen(PS_SOLID, 1, clrAxis);
	HGDIOBJ hOldPen = ::SelectObject(hdcDest, hPen);

	TCHAR szBuf[16];

	::MoveToEx(hdcDest, m_rect.right, m_rect.top, NULL);
	::LineTo(hdcDest, m_rect.right, m_rect.bottom);

	int nX = m_rect.right;
	int nY;
	float fDY = float(m_rect.bottom - m_rect.top) / (m_lNumTicks - 1);
	
	double dDY = (dViewMaxValue - dViewMinValue) / (m_lNumTicks - 1); 
	
	RECT rect;
	rect.left = m_rect.left;
	rect.right = m_rect.right - 8;

	for (int i = 0; i < m_lNumTicks; i++)
	{
		nY = ROUND(m_rect.bottom - fDY * i);
		rect.top = nY - nHalfTickHeight;
		rect.bottom = nY + nHalfTickHeight;

		::MoveToEx(hdcDest, nX, nY, NULL);
		::LineTo(hdcDest, max(nX - (i % 2 == 0 ? 7 : 5), m_rect.left), nY);

		double dY = dViewMinValue + i * dDY;

		sprintf(szBuf, OLE2T(m_bstrDisplayFormat), dY);
		::DrawText(hdcDest, szBuf, strlen(szBuf), &rect, DT_SINGLELINE | DT_RIGHT | DT_VCENTER);
	}

	if (m_bShowTitle)
	{
		COLORREF clrTitle;
		OleTranslateColor(m_clrTitle, NULL, &clrTitle);
		::SetTextColor(hdcDest, clrTitle);
		
		if (m_spTitleFont != NULL)
		{
			CComPtr<IFont> pFont;
			m_spTitleFont->QueryInterface(IID_IFont, (void**)&pFont);
			pFont->get_hFont(&hFont);
		}
		else
		{
			hFont = (HFONT)::GetStockObject(DEFAULT_GUI_FONT);
		}
		::SelectObject(hdcDest, hFont);

		rect = m_rect;
		rect.bottom = rect.top - nHalfTickHeight;
		rect.top = m_pChart->m_rect.top;
				
		::DrawText(hdcDest, W2T(m_bstrTitle), -1, &rect, DT_SINGLELINE | DT_RIGHT| DT_BOTTOM);
	}
	
	::SelectObject(hdcDest, hOldPen);
	::DeleteObject(hPen);

	::SetTextColor(hdcDest, clrOldText);
	::SelectObject(hdcDest, hOldFont);
}