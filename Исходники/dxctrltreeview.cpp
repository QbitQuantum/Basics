VOID CDXCtrlTreeview::DrawText()
{
	TEXTMETRIC tm;
	LPD3DXFONT pFont;
	RECT rect, irect;
	PLISTITEM pItem;
	D3DCOLOR Color;
	DWORD dwIndex;
	DWORD dwIndexTextSize;
	SIZE size;
	char szBuff[8];
	if(m_pManager)
	{

		GetRect(&rect);
		pFont = m_pManager->GetFixedWidthFont();
		pFont->GetTextMetrics(&tm);
		
		GetTextExtentPoint32(pFont->GetDC(), "999", 3, &size);
		
		if(m_bShowIndex)
			dwIndexTextSize = size.cx;
		else
			dwIndexTextSize = 0;

		pItem = m_pList;
		for(dwIndex = 0; dwIndex < m_dwTopIndex; dwIndex++)
			pItem = pItem->link;
		rect.left += (5 * m_dwFrameWidth / 8) + tm.tmHeight;
		rect.top += (5 * m_dwFrameWidth / 8);
		rect.bottom -= (5 * m_dwFrameWidth / 8);
		rect.right -= ((5 * m_dwFrameWidth / 8) + 16 + dwIndexTextSize);
		for(; rect.top <= rect.bottom - tm.tmHeight && pItem; dwIndex++)
		{
			if(pItem->bGroup || pItem->bVisible)
			{
				if(dwIndex == m_dwSelectedIndex)
				{
					Color = m_SelectedColor;
				}
				else
				{
					if(pItem->bGroup)
						Color = m_GroupColor;
					else
						Color = m_ItemColor;
				}
				pFont->DrawTextA(m_pManager->GetFontSprite(), pItem->szText, -1, &rect, DT_TOP | DT_LEFT, Color);
				if(m_bShowIndex && pItem->bGroup == FALSE)
				{
					irect = rect;
					irect.left = irect.right;
					irect.right = irect.left + dwIndexTextSize;
					pFont->DrawTextA(m_pManager->GetFontSprite(), itoa(dwIndex, szBuff, 10), -1, &irect, DT_TOP | DT_RIGHT, Color);
				}
				rect.top += tm.tmHeight;
			}
			pItem = pItem->link;
		}
	}
}