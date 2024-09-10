HRESULT CDrawMenu::DoDraw(HDC hdcDest)
{
	if (m_bButtonDisplayed)
	{
		USES_CONVERSION;

		RECT rect;
		rect.left = ROUND(m_rcPosition.left);
		rect.top = ROUND(m_rcPosition.top);
		rect.right = ROUND(m_rcPosition.right);
		rect.bottom = ROUND(m_rcPosition.bottom);

		// 画边框
		if (m_enumButtonState == ButtonStateDown)
		{
			::DrawEdge(hdcDest, &rect, BDR_SUNKENOUTER, BF_RECT | BF_ADJUST);
		}
		else
		{
			if (m_bMouseOn || !ClientIsRunMode())
				::DrawEdge(hdcDest, &rect, BDR_RAISEDINNER, BF_RECT | BF_ADJUST);
		}

		COLORREF clrMenu = GetSysColor(COLOR_MENU);
		COLORREF clrMenuText = GetSysColor(COLOR_MENUTEXT);
			
		COLORREF clrOld = SetTextColor(hdcDest, clrMenuText);
		int iOldMode = SetBkMode(hdcDest, TRANSPARENT);
		
		if (m_fontMenu.m_hFont == NULL)
			GetSystemSettings();
		CFontHandle fontOld = (HFONT)SelectObject(hdcDest, m_fontMenu);

		LPTSTR szCaption = W2T(m_bstrButtonCaption);
		int cbCaption = lstrlen(szCaption);
			
		CBrush brushBack;
		brushBack.CreateSolidBrush(clrMenu);
		::FillRect(hdcDest, &rect, brushBack);

		::DrawText(hdcDest, szCaption, cbCaption, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

		SetTextColor(hdcDest, clrOld);
		SetBkMode(hdcDest, iOldMode);
		SelectObject(hdcDest, fontOld);
	}
	else
	{
		if (ClientIsRunMode())
			return S_OK;

		int nLeft = ROUND(m_rcPosition.left);
		int nTop = ROUND(m_rcPosition.top);
		int nRight = ROUND(m_rcPosition.right);
		int nBottom = ROUND(m_rcPosition.bottom);
		
		HBRUSH hOldBrush = (HBRUSH)::SelectObject(hdcDest, (HBRUSH)GetStockObject(BLACK_BRUSH));
		Rectangle(hdcDest, nLeft, nTop, nLeft + (nRight - nLeft) / 4, nBottom);
		
		RECT rect;
		rect.left = nLeft + (nRight - nLeft) / 4;
		rect.top = nTop;
		rect.right = nRight;
		rect.bottom = nBottom;
		
		::SelectObject(hdcDest, (HBRUSH)GetStockObject(WHITE_BRUSH));
		Rectangle(hdcDest, rect.left, nTop, nRight, nBottom);
		
		int iOldBkMode = SetBkMode(hdcDest, TRANSPARENT);
		HFONT hOldFont = (HFONT)::SelectObject(hdcDest, (HFONT)GetStockObject(DEFAULT_GUI_FONT));
		
		DrawText(hdcDest, _T("菜单"), -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		
		SetBkMode(hdcDest, iOldBkMode);
		::SelectObject(hdcDest, hOldBrush);
		::SelectObject(hdcDest, hOldFont);
	}
	
	
	return S_OK;
}