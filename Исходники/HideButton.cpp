void CHideButton::DrawControl(CDC &dc, CRect rcUpdate)
{
	int nWidth = m_rc.Width();
	int nHeight = m_rc.Height();

	if(!m_bUpdate)
	{		
		UpdateMemDC(dc, nWidth * 5, nHeight);
		
		for(int i = 0; i < 4; i++)
		{
			m_memDC.BitBlt(i * nWidth, 0, nWidth, nHeight, &dc, m_rc.left ,m_rc.top, SRCCOPY);
		}
		
		Color clrText[4] = {m_clrTextNormal, m_clrTextHover, m_clrTextDown, m_clrTextDisable};

		Graphics graphics(m_memDC);
		BSTR bsFont = m_strFont.AllocSysString();
		FontFamily fontFamily(bsFont);
		Font font(&fontFamily, (REAL)m_nFontWidth, m_fontStyle, UnitPixel);
		graphics.SetTextRenderingHint( TextRenderingHintClearTypeGridFit );
		::SysFreeString(bsFont);

		// 设置水平和垂直对齐方式
		DUI_STRING_ALIGN_DEFINE();

		strFormat.SetFormatFlags( StringFormatFlagsNoWrap | StringFormatFlagsMeasureTrailingSpaces);
		Size sizeTip = GetTextBounds(font, strFormat, m_strTip);
		Size sizeText = GetTextBounds(font, strFormat, m_strTitle);
		
		m_rcText.SetRect(m_rc.left + sizeTip.Width + 10, m_rc.top, m_rc.left + sizeTip.Width + 10 + sizeText.Width, m_rc.top + sizeText.Height);
		
		SolidBrush solidBrushTip(m_clrTip);

		for(int i = 0; i < 4; i++)
		{
			RectF rect((Gdiplus::REAL)(i * nWidth), (Gdiplus::REAL)0, (Gdiplus::REAL)(sizeTip.Width + 10), (Gdiplus::REAL)sizeTip.Height);

			BSTR bsTip = m_strTip.AllocSysString();
			graphics.DrawString(bsTip, (INT)wcslen(bsTip), &font, rect, &strFormat, &solidBrushTip);
			::SysFreeString(bsTip);

			if(i > 0)
			{
				SolidBrush solidBrush(clrText[i - 1]);	
				RectF rect((Gdiplus::REAL)(sizeTip.Width + 10 + i * nWidth), (Gdiplus::REAL)0, (Gdiplus::REAL)(nWidth - (sizeTip.Width + 10)), (Gdiplus::REAL)sizeText.Height);
				BSTR bsTitle = m_strTitle.AllocSysString();
				graphics.DrawString(bsTitle, (INT)wcslen(bsTitle), &font, rect, &strFormat, &solidBrush);
				::SysFreeString(bsTitle);
			}
		}
	}

	dc.BitBlt(m_rc.left,m_rc.top, m_rc.Width(), m_rc.Height(), &m_memDC, m_bShowButton ? (1 + m_enButtonState) * nWidth : 0, 0, SRCCOPY);
}