void CUISliderctrl::DoPaint(HDC hDC, const RECT& rcPaint)
{
   // Draw button
   UINT uState = m_uButtonState;
   if( IsFocused() ) uState |= UISTATE_FOCUSED;
   if( !IsEnabled() ) uState |= UISTATE_DISABLED;

	// Ìî³ä±³¾°ÑÕÉ«
   if (m_colorBk != INVALID__UICOLOR)
   {
		CUIBlueRenderEngine::DoFillRect(hDC, m_pManager, m_rcItem, m_colorBk);
   }
   

   // »­¿Ì¶È
   int nPageCount = (m_nPosMax - m_nPosMin) / m_nPageSize;
   int nButtonWidth = 0;
   if (m_pImageSlider != NULL)
   {
	   nButtonWidth = m_pImageSlider->GetWidth() / 4;
   }
   int nItemWidth = m_rcItem.right - m_rcItem.left - nButtonWidth;

	// »­¿Ì¶È
   if (m_colorScale != INVALID__UICOLOR)
   {
	   for (int i = 0; i <= nPageCount; i++)
	   {	  
		   POINT pt1 = {m_rcItem.left + i * ((double)nItemWidth / nPageCount) + nButtonWidth / 2, m_rcItem.top};
		   POINT pt2 = {m_rcItem.left + i * ((double)nItemWidth / nPageCount) + nButtonWidth / 2, m_rcItem.top + m_nScaleHeight};

		   CUIBlueRenderEngine::DoPaintLine(hDC, m_pManager, pt1, pt2, m_colorScale);
	   }
   }

   // »­Öá
   if (m_pImageShaft != NULL)
   {
	 int nShaftHeight = m_pImageShaft->GetHeight();

	 int nTop = m_rcItem.top + (m_rcItem.bottom - m_rcItem.top - nShaftHeight - m_nScaleHeight) / 2 + m_nScaleHeight;

	 RECT rcPadding = {m_rcItem.left + nButtonWidth / 2, nTop, m_rcItem.right - nButtonWidth / 2, nTop + nShaftHeight};

	 RECT rcImage= {0, 0, m_pImageShaft->GetWidth(), m_pImageShaft->GetHeight()};

	 CUIBlueRenderEngine::DoFillRect(hDC, m_pManager, rcPadding, rcImage, m_pImageShaft);
   }
  
   
   if (m_pImageSlider != NULL)
   {
	   int nWidth = m_pImageSlider->GetWidth() / 4;
	   int nHeight = m_pImageSlider->GetHeight();

	   int nIndex = 0;

	   // Draw frame and body
	   if( (uState & UISTATE_DISABLED) != 0 ) {
		   nIndex = 3;;
	   }
	   else if( (uState & UISTATE_PUSHED) != 0 ) {
		   nIndex = 2;
	   }
	   else if( (uState & UISTATE_HOT) != 0 ) {
		   nIndex = 1;
	   }
	   else {
		   nIndex = 0;
	   }

	   Graphics graph(hDC);
	   RECT rcImage = {nWidth *nIndex, 0, nWidth * (nIndex + 1), nHeight};

		double dblPos = (double)(m_nPos - m_nPosMin) / (double)(m_nPosMax - m_nPosMin);

		int nButtonPosX = m_rcItem.left  + (m_rcItem.right - m_rcItem.left - nWidth) * dblPos;
		if (nButtonPosX < m_rcItem.left)
		{
			nButtonPosX = m_rcItem.left;
		}

		if (nButtonPosX > m_rcItem.right - nWidth)
		{
			nButtonPosX = m_rcItem.right - nWidth;
		}

		int nButtonPosY = m_rcItem.top + ((m_rcItem.bottom - m_rcItem.top) - nHeight - m_nScaleHeight)/ 2 + m_nScaleHeight;

		m_rcButton.left = nButtonPosX;
		m_rcButton.right = m_rcButton.left + nWidth;

		m_rcButton.top = nButtonPosY;
		m_rcButton.bottom = m_rcButton.top + nHeight;

		RectF rfDest(PointF((REAL)nButtonPosX, (REAL)nButtonPosY), SizeF((REAL)nWidth, (REAL)nHeight));

		graph.DrawImage(m_pImageSlider, rfDest, (REAL)rcImage.left, (REAL)rcImage.top, (REAL)nWidth, (REAL)nHeight, UnitPixel, NULL);

   }
}