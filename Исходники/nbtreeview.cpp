void 
CNBTreeListView::DrawTreeItem(LPNMTVCUSTOMDRAW lptvcd, UINT iState, const RECT& rcItem)
{
	CDCHandle dc = lptvcd->nmcd.hdc;
	HTREEITEM hItem = (HTREEITEM) lptvcd->nmcd.dwItemSpec;

	tMapItem* pVal = m_mapItems.Lookup(hItem);
	if( pVal == NULL ) return;

	// NOTE: Having an ImageList attached to the TreeView control seems
	//       to produce some extra WM_ERASEBKGND msgs, which we can use to
	//       optimize the painting...
	CImageList il = m_ctrlTree.GetImageList(TVSIL_NORMAL);

	// If the item had focus then draw it
	// NOTE: Only when images are used (see note above)
	// FIX-BY-PATRIA: DrawFocusRect should be done later
	//if( (iState & CDIS_FOCUS) != 0 && !il.IsNull() ) {
	//	RECT rcFocus = rcItem;
	//	rcFocus.left = 1;
	//	dc.SetTextColor(::GetSysColor(COLOR_BTNTEXT));
	//	dc.DrawFocusRect(&rcFocus);
	//}

	// If it's selected, paint the selection background
	if( iState & CDIS_SELECTED  && iState & CDIS_FOCUS) {
		RECT rcHigh = rcItem;
		dc.FillSolidRect(&rcHigh, ::GetSysColor(COLOR_HIGHLIGHT));
	}
	else if( il.IsNull() ) {
		RECT rcHigh = rcItem;
		dc.FillSolidRect(&rcHigh, lptvcd->clrTextBk);
	}

	// Always write text with background
	dc.SetBkMode(OPAQUE);
	dc.SetBkColor(::GetSysColor((iState & CDIS_SELECTED) != 0 ? COLOR_HIGHLIGHT : COLOR_WINDOW));

	// Draw all columns of the item
	RECT rc = rcItem;
	int cnt = pVal->GetSize();
	for( int i = 0; i < cnt; i++ ) {
		LPTLVITEM pItem = (*pVal)[i];
		ATLASSERT(pItem);

		if( i != 0 ) rc.left = m_rcColumns[i].left;
		rc.right = m_rcColumns[i].right;

		if( pItem->mask & TLVIF_IMAGE ) {
			ATLASSERT(!il.IsNull());
			int cx, cy;
			il.GetIconSize(cx, cy);
			il.DrawEx(
				pItem->iImage, 
				dc, 
				rc.left, rc.top, 
				MIN(cx, rc.right - rc.left), cy,
				CLR_NONE, CLR_NONE,
				ILD_TRANSPARENT);
			rc.left += cx;
		}

		if( pItem->mask & TLVIF_TEXT ) {

			rc.left += 2;

			COLORREF clrText = lptvcd->clrText;
			if( pItem->mask & TLVIF_TEXTCOLOR ) clrText = pItem->clrText;
			if( iState & CDIS_SELECTED ) clrText = ::GetSysColor(COLOR_HIGHLIGHTTEXT);
			dc.SetTextColor(clrText);

			CFont font;
			HFONT hOldFont = NULL;
			if( pItem->mask & TLVIF_STATE ) {
				LOGFONT lf;
				::GetObject(m_ctrlTree.GetFont(), sizeof(LOGFONT), &lf);
				if( pItem->state & TLVIS_BOLD ) lf.lfWeight += FW_BOLD - FW_NORMAL;
				if( pItem->state & TLVIS_ITALIC ) lf.lfItalic = TRUE;
				if( pItem->state & TLVIS_UNDERLINE ) lf.lfUnderline = TRUE;
				if( pItem->state & TLVIS_STRIKEOUT ) lf.lfStrikeOut = TRUE;
				font.CreateFontIndirect(&lf);
				ATLASSERT(!font.IsNull());
				hOldFont = dc.SelectFont(font);
			}

			UINT format = pItem->mask & TLVIF_FORMAT ? pItem->format : 0;

			if (0 == i)
			{
				CNBDevice* pDevice = (CNBDevice*) m_ctrlTree.GetItemData(hItem);
				if (NULL != pDevice && pDevice->GetIDString(_T('*')).GetLength() > 0)
				{
					CString strBottom = pDevice->GetIDString(m_chHidden);

					CRect rcTop = rc; rcTop.DeflateRect(0, 0, 0, rcTop.Height() / 2);
					CRect rcBottom = rc; rcBottom.top = rcTop.bottom;
					
					dc.FillSolidRect(&rc, lptvcd->clrTextBk);

					LOGFONT lf;
					CFontHandle fontHandle = dc.GetCurrentFont();
					fontHandle.GetLogFont(&lf);
					lf.lfWeight = FW_BOLD;
					CFont font; 
					font.CreateFontIndirect(&lf);
					ATLASSERT(!font.IsNull());

					HFONT hOldFont = dc.SelectFont(font);
					dc.DrawText(pItem->pszText, -1, &rcTop, DT_VCENTER | DT_SINGLELINE | DT_WORD_ELLIPSIS | format);
					dc.SelectFont(hOldFont);

					COLORREF clrText = dc.GetTextColor();
					clrText = RGB(
						(GetRValue(clrText) + 0x40) & 0xFF, 
						(GetGValue(clrText) + 0x40) & 0xFF,
						(GetBValue(clrText) + 0x40) & 0xFF);
					clrText = dc.SetTextColor(clrText);
					dc.DrawText(strBottom, -1, &rcBottom, DT_VCENTER | DT_SINGLELINE | DT_WORD_ELLIPSIS | format);
					dc.SetTextColor(clrText);
				}
				else
				{
					dc.FillSolidRect(&rc, lptvcd->clrTextBk);

					LOGFONT lf;
					CFontHandle fontHandle = dc.GetCurrentFont();
					fontHandle.GetLogFont(&lf);
					lf.lfWeight = FW_BOLD;
					CFont font; 
					font.CreateFontIndirect(&lf);
					ATLASSERT(!font.IsNull());
					HFONT hOldFont = dc.SelectFont(font);
					dc.DrawText(pItem->pszText, 
						-1, 
						&rc, 
						DT_VCENTER | DT_SINGLELINE | DT_WORD_ELLIPSIS | format);
					dc.SelectFont(hOldFont);
				}
			}
			else
			{
				dc.DrawText(pItem->pszText, 
					-1, 
					&rc, 
					DT_VCENTER | DT_SINGLELINE | DT_WORD_ELLIPSIS | format);
			}

			if( pItem->mask & TLVIF_STATE ) dc.SelectFont(hOldFont);
		}
	}
	// FIX-BY-PATRIA: DrawFocusRect should be done here
	if( (iState & CDIS_FOCUS) != 0 && !il.IsNull() ) {
		RECT rcFocus = rcItem;
		rcFocus.left = 1;
		dc.SetTextColor(::GetSysColor(COLOR_BTNTEXT));
		dc.DrawFocusRect(&rcFocus);
	}

}