void
MFCSimpleTypeView::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	int			m_bClientWidthSel = TRUE;
	int			m_cxClient = 0;
	int			m_cxStateImageOffset = 0;
	COLORREF	m_clrText = ::GetSysColor(COLOR_WINDOWTEXT);
	COLORREF	m_clrTextBk = ::GetSysColor(COLOR_WINDOW);
	COLORREF	m_clrBkgnd = ::GetSysColor(COLOR_WINDOW);

	CListCtrl& listCtrl=GetListCtrl();
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	CRect rcItem(lpDrawItemStruct->rcItem);
	UINT uiFlags = ILD_TRANSPARENT;
	CImageList* pImageList;
	int nItem = lpDrawItemStruct->itemID;
	BOOL bFocus = (GetFocus() == this);
	COLORREF clrTextSave, clrBkSave;
	COLORREF clrImage = m_clrBkgnd;
	static _TCHAR szBuff[MAX_PATH];
	LPCTSTR pszText;

	StabEnt			*itemSym = SymForItem(nItem);
// get item data

	LV_ITEM lvi;
	lvi.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
	lvi.iItem = nItem;
	lvi.iSubItem = 0;
	lvi.pszText = szBuff;
	lvi.cchTextMax = sizeof(szBuff);
	lvi.stateMask = 0xFFFF;     // get all state flags
	listCtrl.GetItem(&lvi);

	BOOL bSelected = (bFocus || (GetStyle() & LVS_SHOWSELALWAYS)) && lvi.state & LVIS_SELECTED;
	bSelected = bSelected || (lvi.state & LVIS_DROPHILITED);

// set colors if item is selected

	CRect rcAllLabels;
	listCtrl.GetItemRect(nItem, rcAllLabels, LVIR_BOUNDS);

	CRect rcLabel;
	listCtrl.GetItemRect(nItem, rcLabel, LVIR_BOUNDS);
//	listCtrl.GetItemRect(nItem, rcLabel, LVIR_LABEL);

	rcAllLabels.left = rcLabel.left;
	if (m_bClientWidthSel && rcAllLabels.right<m_cxClient)
		rcAllLabels.right = m_cxClient;

	if (bSelected)	{
		clrTextSave = pDC->SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
		clrBkSave = pDC->SetBkColor(::GetSysColor(COLOR_HIGHLIGHT));

		pDC->FillRect(rcAllLabels, &CBrush(::GetSysColor(COLOR_HIGHLIGHT)));
	}
	else
		pDC->FillRect(rcAllLabels, &CBrush(m_clrTextBk));

// set color and mask for the icon

	if (lvi.state & LVIS_CUT)	{
		clrImage = m_clrBkgnd;
		uiFlags |= ILD_BLEND50;
	}	else if (bSelected) {
		clrImage = ::GetSysColor(COLOR_HIGHLIGHT);
		uiFlags |= ILD_BLEND50;
	}

// draw state icon

	UINT nStateImageMask = lvi.state & LVIS_STATEIMAGEMASK;
	if (nStateImageMask)	{
		int nImage = (nStateImageMask>>12) - 1;
		pImageList = listCtrl.GetImageList(LVSIL_STATE);
		if (pImageList)		{
			pImageList->Draw(pDC, nImage,
				CPoint(rcItem.left, rcItem.top), ILD_TRANSPARENT);
		}
	}

// draw normal and overlay icon

/*
	CRect rcIcon;
	ListCtrl.GetItemRect(nItem, rcIcon, LVIR_ICON);

	pImageList = listCtrl.GetImageList(LVSIL_SMALL);
	if (pImageList)	{
		UINT nOvlImageMask=lvi.state & LVIS_OVERLAYMASK;
		if (rcItem.left<rcItem.right-1)		{
			ImageList_DrawEx(pImageList->m_hImageList, lvi.iImage,
					pDC->m_hDC,rcIcon.left,rcIcon.top, 16, 16,
					m_clrBkgnd, clrImage, uiFlags | nOvlImageMask);
		}
	}
*/

// draw item label

//	listCtrl.GetItemRect(nItem, rcItem, LVIR_LABEL);
	LV_COLUMN lvc;
	lvc.mask = LVCF_FMT | LVCF_WIDTH;

	listCtrl.GetItemRect(nItem, rcItem, LVIR_BOUNDS);
	listCtrl.GetColumn(0, &lvc); 

	rcItem.right = lvc.cx;

//	pszText = MakeShortString(pDC, szBuff,
//				rcItem.right-rcItem.left, 2*OFFSET_FIRST);
	pszText = szBuff;

	rcLabel = rcItem;
	rcLabel.left += OFFSET_FIRST;
	rcLabel.right -= OFFSET_FIRST;


	pDC->SetTextColor(rgb_black);
	pDC->DrawText(pszText,-1,rcLabel,DT_LEFT | DT_SINGLELINE | DT_NOPREFIX | DT_NOCLIP | DT_VCENTER);

// draw labels for extra columns
	if (itemSym) {
		UINT nOvlImageMask=lvi.state & LVIS_OVERLAYMASK;
// type
		listCtrl.GetColumn(1, &lvc); 
		rcItem.left = rcItem.right;
		rcItem.right += lvc.cx;

		rcLabel = rcItem;
		rcLabel.left += OFFSET_OTHER;
		rcLabel.right -= OFFSET_OTHER;

		string tnm = findTypeName(itemSym->type);
		if (tnm.size()) {
			pDC->SetTextColor(rgb_blue);
			long h = pDC->DrawText(tnm.c_str() , -1, rcLabel, DT_SINGLELINE | DT_NOPREFIX | DT_NOCLIP | DT_VCENTER);
		}
// length
		listCtrl.GetColumn(2, &lvc); 
		rcItem.left = rcItem.right;
		rcItem.right += lvc.cx;
//		fprintf(stderr, "%d %d %d\n", pszText, itemSym->type, lvc.cx);

		rcLabel = rcItem;
		rcLabel.left += OFFSET_OTHER;
		rcLabel.right -= OFFSET_OTHER;

		if (itemSym->indirection > 0) {
			char	buf[120];
			buf[0] = 0;
			for (short i=1; i<itemSym->indirection; i++) {
				char	nbuf[10];
				sprintf(nbuf, "%s%d", i>1?",":"",itemSym->size[i]);
				strcat(buf, nbuf);
			}
			pDC->SetTextColor(rgb_blue);
			pDC->DrawText(buf, -1, rcLabel,
				DT_SINGLELINE | DT_NOPREFIX | DT_NOCLIP | DT_VCENTER);
		}
// controller
		listCtrl.GetColumn(3, &lvc); 
		rcItem.left = rcItem.right;
		rcItem.right += lvc.cx;
		if (itemSym->controlMode != StabEnt::DISPLAY_NOT) {
			ImageList_DrawEx(images,
					itemSym->controlMode == StabEnt::DISPLAY_CTL ? 0 :
						itemSym->controlMode == StabEnt::DISPLAY_DISP? 2 : 0,
					pDC->m_hDC,rcItem.left,rcItem.top, 16, 16,
					m_clrBkgnd, clrImage, uiFlags | nOvlImageMask);
		}
// envelope
		listCtrl.GetColumn(4, &lvc); 
		rcItem.left = rcItem.right;
		rcItem.right += lvc.cx;
		if (itemSym->isEnveloped) {
			ImageList_DrawEx(images, 1 /* which one */,
					pDC->m_hDC,rcItem.left,rcItem.top, 16, 16,
					m_clrBkgnd, clrImage, uiFlags | nOvlImageMask);
		}
	}
/*
	for(int nColumn = 1; listCtrl.GetColumn(nColumn, &lvc); nColumn++)	{
		rcItem.left = rcItem.right;
		rcItem.right += lvc.cx;

		int nRetLen = listCtrl.GetItemText(nItem, nColumn,	szBuff, sizeof(szBuff));
		if (nRetLen == 0)
			continue;

//		pszText = MakeShortString(pDC, szBuff,
//			rcItem.right - rcItem.left, 2*OFFSET_OTHER);

		pszText = szBuff;

		UINT nJustify = DT_LEFT;

		if(pszText == szBuff) {
			switch(lvc.fmt & LVCFMT_JUSTIFYMASK) {
			case LVCFMT_RIGHT:
				nJustify = DT_RIGHT;
				break;
			case LVCFMT_CENTER:
				nJustify = DT_CENTER;
				break;
			default:
				break;
			}
		}

		rcLabel = rcItem;
		rcLabel.left += OFFSET_OTHER;
		rcLabel.right -= OFFSET_OTHER;

		pDC->DrawText(pszText, -1, rcLabel,
			nJustify | DT_SINGLELINE | DT_NOPREFIX | DT_NOCLIP | DT_VCENTER);
	}*/

// draw focus rectangle if item has focus

	if (lvi.state & LVIS_FOCUSED && bFocus)
		pDC->DrawFocusRect(rcAllLabels);

// set original colors if item was selected

	if (bSelected) {
		pDC->SetTextColor(clrTextSave);
		pDC->SetBkColor(clrBkSave);
	}
}