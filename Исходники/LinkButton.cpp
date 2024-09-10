void CLinkButton::DrawControl(CDC &dc, CRect rcUpdate)
{
	int nWidth = m_rc.Width();
	int nHeight = m_rc.Height();

	if(!m_bUpdate)
	{		
		UpdateMemDC(dc, nWidth * 4, nHeight);

		m_memDC.SetBkMode(TRANSPARENT);
		//CFont *pOldFont = m_memDC.SelectObject(&m_font);

		COLORREF clrText[4] = {m_clrTextNormal, m_clrTextHover, m_clrTextDown, m_clrTextDisable};
		CRect rcText = m_rcText;
		rcText.OffsetRect(-m_rc.left, -m_rc.top);
		COLORREF clrOld = m_memDC.SetTextColor(clrText[0]);

		for(int i = 0; i < 4; i++)
		{
			m_memDC.BitBlt(i * nWidth, 0, nWidth, nHeight, &dc, m_rc.left ,m_rc.top, SRCCOPY);

			m_memDC.SetTextColor(clrText[i]);
			
			//m_memDC.DrawText(m_strTitle, &rcText, DT_VCENTER | DT_CENTER | DT_SINGLELINE | DT_WORD_ELLIPSIS);	

			// ÏÂ»®Ïß
			if(i == 1 || i == 2)
			{
				CPen pen;
				pen.CreatePen(PS_SOLID, 1, clrText[i]);
				CPen *pOldPen = m_memDC.SelectObject(&pen); 	
				m_memDC.MoveTo(rcText.left, rcText.bottom);
				m_memDC.LineTo(rcText.right, rcText.bottom);
				m_memDC.SelectObject(pOldPen);
				pen.DeleteObject();
			}

			rcText.OffsetRect(nWidth, 0);
		}

		//m_memDC.SelectObject(pOldFont);
		m_memDC.SetTextColor(clrOld);
	}

	dc.BitBlt(m_rc.left,m_rc.top, m_rc.Width(), m_rc.Height(), &m_memDC, m_enButtonState * nWidth, 0, SRCCOPY);
}