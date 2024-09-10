void	CToolBarPropertyPage::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	if (lpDrawItemStruct->CtlID == IDC_LIST_ICON) {
		CDCHandle dc = lpDrawItemStruct->hDC;

		// Save these value to restore them when done drawing.
		COLORREF crOldTextColor = dc.GetTextColor();
		COLORREF crOldBkColor = dc.GetBkColor();

		// If this item is selected, set the background color 
		// and the text color to appropriate values. Also, erase
		// rect by filling it with the background color.
		if ((lpDrawItemStruct->itemAction | ODA_SELECT) &&
			(lpDrawItemStruct->itemState & ODS_SELECTED))
		{
			dc.SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
			dc.SetBkColor(::GetSysColor(COLOR_HIGHLIGHT));
			dc.FillSolidRect(&lpDrawItemStruct->rcItem, 
				::GetSysColor(COLOR_HIGHLIGHT));
		} else
			dc.FillSolidRect(&lpDrawItemStruct->rcItem, crOldBkColor);
#if 0
		// If this item has the focus, draw a red frame around the
		// item's rect.
		if ((lpDrawItemStruct->itemAction | ODA_FOCUS) &&
			(lpDrawItemStruct->itemState & ODS_FOCUS))
		{
			CBrush br;
			br.CreateSolidBrush(RGB(255, 0, 0));
			dc.FrameRect(&lpDrawItemStruct->rcItem, br);
		}
#endif
		IconListData* pData = (IconListData*)lpDrawItemStruct->itemData;
		if (pData) {
			CIconHandle icon = m_imgList.GetIcon(pData->nIndex);
			if (icon.m_hIcon)
				icon.DrawIconEx(dc, lpDrawItemStruct->rcItem.left + cxMargin, lpDrawItemStruct->rcItem.top + cyMargin, m_iconSize.cx, m_iconSize.cy);

			lpDrawItemStruct->rcItem.left += m_iconSize.cx + cxMargin + IconTextMargin;
			// Draw the text.
			dc.DrawText(
				pData->strText,
				pData->strText.GetLength(),
				&lpDrawItemStruct->rcItem,
				DT_SINGLELINE | DT_VCENTER);
		}

		// Reset the background color and the text color back to their
		// original values.
		dc.SetTextColor(crOldTextColor);
		dc.SetBkColor(crOldBkColor);
	}
}