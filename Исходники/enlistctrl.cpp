void CEnListCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	CDC* pDC;
	CRect rText, rItem, rClient, rHeader;
	COLORREF crOldText, crOldBack;
	CSize sizeText;
	LV_COLUMN lvc = { 0 };
//	CPen* pOldPen;
	CImageList* pImageList;
	CImageList* pStateList;
	int nImage = -1;
	BOOL bItemFocused, bListFocused, bSelected, bDropHighlighted, bSelAlways;
	UINT uStyle, uState;
	CSize sizeState(0, 0), sizeImage(0, 0);
	int nIndent = 0;

	// get and prepare device context
	pDC = CDC::FromHandle(lpDrawItemStruct->hDC);//GetDC(); 
	pDC->SelectObject(GetFont());
	pDC->SetROP2(R2_COPYPEN);

	// init helper variables
	int nItem = lpDrawItemStruct->itemID;
	GetItemRect(nItem, rItem, LVIR_BOUNDS);//lpDrawItemStruct->rcItem;
	GetClientRect(&rClient);

	// some problems with drophiliting items during drag and drop
	// so we need to make sure drawing is clipped to client area
	// this fixes it admirably!
	if (GetHeader())
	{
		GetHeader()->GetWindowRect(rHeader);
		ScreenToClient(rHeader);
		rClient.top = max(0, rHeader.bottom);
		pDC->IntersectClipRect(rClient);
	}

	rText = rItem;

	uStyle = GetStyle();
	uState = GetItemState(nItem, LVIS_DROPHILITED | LVIS_SELECTED);
	bDropHighlighted = (uState & LVIS_DROPHILITED);
	bItemFocused = (GetFocusedItem() == nItem);
	bListFocused = (GetFocus() == this);
	bSelected = (uState & LVIS_SELECTED);
	bSelAlways = ((uStyle & LVS_SHOWSELALWAYS) == LVS_SHOWSELALWAYS);
	bSelected = bSelected && (bListFocused || bSelAlways);

	crOldText = pDC->SetTextColor(COLORREF(0)); // this will be overwritten on a per subitem basis
	crOldBack = pDC->SetBkColor(GetItemBackColor(nItem, bSelected, bDropHighlighted, bListFocused));

	// images and indentation
	pImageList = GetImageList(LVSIL_SMALL);

	if (pImageList)
	{
		nImage = GetImageIndex(nItem, 0); 
		ImageList_GetIconSize(pImageList->m_hImageList, (int*)&sizeImage.cx, (int*)&sizeImage.cy);

		nIndent = GetItemIndent(nItem) * sizeImage.cx;

		rText.left += nIndent;
		rItem.left += nIndent;

//		if (pImageList == &s_ilIndent)
//			pImageList = NULL;
	}

	// state
	pStateList = GetImageList(LVSIL_STATE);

	if (pStateList)
		ImageList_GetIconSize(pStateList->m_hImageList, (int*)&sizeState.cx, (int*)&sizeState.cy);

	if (lpDrawItemStruct->itemAction & (ODA_DRAWENTIRE | ODA_SELECT))
	{
		// setup colors and pens
		int nImageStyle = GetImageStyle(bSelected, bDropHighlighted, bListFocused);

		// draw item images if required
		int nImageWidth = 0;

		// make sure there is enough space
		lvc.mask = LVCF_WIDTH | LVCF_FMT;
		int nCol = 0;
		BOOL bRes = GetColumn(nCol, &lvc);
		
		// must paint the background of column 0 before the icons
		if (bRes && (pStateList || pImageList))
			pDC->ExtTextOut(0, rItem.top, ETO_CLIPPED | ETO_OPAQUE, CRect(0, rItem.top, lvc.cx, rItem.bottom), _T(""), NULL);

		// state
		if (pStateList && bRes)
		{
			int nState = (GetItemState(nItem, LVIS_STATEIMAGEMASK) & LVIS_STATEIMAGEMASK);
			nState = nState >> 12;

			if (lvc.cx > sizeState.cx)
				pStateList->Draw(pDC, nState, CPoint(rText.left + 1, rText.top), ILD_TRANSPARENT); 

			nImageWidth = sizeState.cx + 2; // 1 pixel border either side
		}