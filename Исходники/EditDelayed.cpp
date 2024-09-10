void CEditDelayed::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_pctrlColumnHeader != NULL)
	{
		if (point.x <= ICON_LEFTSPACE)
		{
			// construct a popup menu out of the columnheader for the filter setting
			// ==> XP Style Menu [Xanatos] - Stulle
			/*
			CMenu menu;
			menu.CreatePopupMenu();
			*/
			CTitleMenu menu;
			menu.CreatePopupMenu();
			menu.AddMenuTitle(GetResString(IDS_FILTER));
			// <== XP Style Menu [Xanatos] - Stulle

			HDITEM hdi;
			TCHAR szBuffer[256];
			hdi.mask = HDI_TEXT | HDI_WIDTH;
			hdi.pszText = szBuffer;
			hdi.cchTextMax = _countof(szBuffer);
			int nCount = m_pctrlColumnHeader->GetItemCount();
			int nIdx;
			for (int i = 0; i < nCount ;i++) {
				nIdx = m_pctrlColumnHeader->OrderToIndex(i);
				m_pctrlColumnHeader->GetItem(nIdx, &hdi);
				szBuffer[_countof(szBuffer) - 1] = _T('\0');
				bool bIgnored = false;
				for (int i = 0; i < m_aIgnoredColums.GetCount(); i++){
					if (m_aIgnoredColums[i] == nIdx){
						bIgnored = true;
						break;
					}
				}
				if (hdi.cxy > 0 && !bIgnored) // ignore hidden columns
					menu.AppendMenu(MF_STRING | ((m_nCurrentColumnIdx == nIdx) ? MF_CHECKED : MF_UNCHECKED), MP_FILTERCOLUMNS + nIdx, hdi.pszText);
			}

			// draw the menu on a fixed position so it doesnt hides the inputtext
			CRect editRect;
			GetClientRect(&editRect);
			CPoint pointMenu(2, editRect.bottom);
			ClientToScreen(&pointMenu);
			menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pointMenu.x, pointMenu.y, this);
			VERIFY( menu.DestroyMenu() ); // XP Style Menu [Xanatos] - Stulle
			return;
		}
	}

	CRect editRect;
	GetClientRect(&editRect);
	if (m_pointMousePos.x > editRect.right - ICON_LEFTSPACE && m_bShowResetButton) {
		m_iwReset.ShowIcon(1);
		SetCapture();
		return;
	}

	CEdit::OnLButtonDown(nFlags, point);
}