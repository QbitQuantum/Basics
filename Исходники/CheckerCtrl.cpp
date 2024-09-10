void CCheckerCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	SetFocus();

	DWORD dwPos = GetMessagePos();
	CPoint clickedPoint((int)(short)LOWORD(dwPos), (int)(short)HIWORD(dwPos));
	ScreenToClient(&clickedPoint);
	
	{
		CRect cRect;
		GetWindowRect(&cRect);
		ScreenToClient(&cRect);

		UINT nY = UINT(((float)clickedPoint.y / (float(cRect.Height())/float(m_nBlocksPerColumn)))+.3);

		UINT nX = UINT(((float)clickedPoint.x / (float(cRect.Width())/float(m_nBlocksPerRow)))+.3);

		UINT nIndex = nY * m_nBlocksPerRow + nX + m_nyPos * m_nBlocksPerRow;

		if(nIndex < m_nNumberofBlocks && nX < m_nBlocksPerRow)
		{

			CString strNumber;
//			strNumber.Format("%d", nIndex + m_nStartIndex+1);
			strNumber = (m_crText.GetAt(nIndex + m_nStartIndex));

			if (strNumber.GetLength())
			{
				SetCapture();
				CreateSafeTooltipRect(clickedPoint.x, clickedPoint.y, strNumber);

				GetParent()->PostMessage(9876,(WPARAM)(nIndex+m_nStartIndex+1), 0);
			
				CClientDC dc(this);
				CBrush brush;
				brush.CreateSolidBrush(GetSysColor(COLOR_INFOBK));
				dc.Rectangle(tooltipRect);
				
				tooltipRect.left++;
				tooltipRect.top++;
				tooltipRect.bottom--;
				tooltipRect.right--;
				
				dc.FillRect(tooltipRect, &brush);
				
				CFont font;
				LOGFONT logFont;
				strcpy(logFont.lfFaceName, "Verdana");
				logFont.lfHeight = -MulDiv(12, GetDeviceCaps(dc.m_hDC, LOGPIXELSY), 72);
				logFont.lfWidth = 0;
				logFont.lfEscapement = 0;
				logFont.lfItalic = FALSE;
				logFont.lfStrikeOut = FALSE;
				logFont.lfUnderline = FALSE;
				logFont.lfWeight = FW_BOLD;
				
				font.CreateFontIndirect(&logFont);
				
				dc.SelectObject(font);
				
				dc.SetTextColor(GetSysColor(COLOR_INFOTEXT));
				dc.SetBkColor(GetSysColor(COLOR_INFOBK));
				dc.DrawText(strNumber, tooltipRect, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
				
				tooltipRect.left--;
				tooltipRect.top--;
				tooltipRect.bottom++;
				tooltipRect.right++;

				m_bShouldUpdated = TRUE;
			}
		}
	}

	CWnd::OnLButtonDown(nFlags, point);
}