//************************************************************************
// CLCDInput::Draw
//************************************************************************
bool CLCDInput::Draw(CLCDGfx *pGfx)
{
	if(!CLCDTextObject::Draw(pGfx))
		return false;
	
	
	SelectObject(pGfx->GetHDC(),m_hFont);
				
	RECT rBoundary = { 0, 0,0 + GetWidth(), 0 + GetHeight() }; 
	int iLine = m_iLinePosition;
	int iEndLine = m_iLinePosition + m_iLineCount;
	int iLen = 0;
	TCHAR *pcOffset = NULL;
	while(iLine <  iEndLine && iLine < m_vLineOffsets.size())
	{
		// Calculate the text length
		if(iLine < m_vLineOffsets.size() -1)
		{
			iLen = m_vLineOffsets[iLine+1].iOffset - m_vLineOffsets[iLine].iOffset;
			// Draw the linebreak marker
			if(m_bShowSymbols && m_vLineOffsets[iLine+1].bLineBreak)
				pGfx->DrawFilledRect(m_vLineOffsets[iLine].iWidth+1,rBoundary.top+m_iFontHeight/3,m_iFontHeight/3,m_iFontHeight/3);
		}
		else iLen = (int)m_strText.length() - m_vLineOffsets[iLine].iOffset;
		
		// Draw the text
		pcOffset = (TCHAR*)m_strText.c_str() + m_vLineOffsets[iLine].iOffset;
		DrawTextEx(pGfx->GetHDC(),
					(LPTSTR)pcOffset,
					iLen,
					&rBoundary,
					m_iTextFormat,
					&m_dtp);

		// Draw the input cursor
		if(m_pInput && m_bShowMarker && m_Marker[0].iLine == iLine)
		{
			// insert-mode cursor
			if(m_bInsert ||m_Marker[0].iXWidth == 1)
			{
				pGfx->DrawFilledRect(m_Marker[0].iXLine,
				m_iFontHeight*(iLine-m_iLinePosition),
				1,
				m_iFontHeight);
			}
			// replace-mode cursor
			else
			{
				RECT rMarker = {m_Marker[0].iXLine,
								m_iFontHeight*(iLine-m_iLinePosition),
								m_Marker[0].iXLine+m_Marker[0].iXWidth,
								m_iFontHeight*(iLine-m_iLinePosition+1)};
				InvertRect(pGfx->GetHDC(),&rMarker);
			}
		}

		rBoundary.top += m_iFontHeight;
		rBoundary.bottom += m_iFontHeight;

		iLine++;
	}
	return true;
}