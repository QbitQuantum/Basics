/**
* Responsible for drawing each list item.
*/
void ToggleListView::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) {

	CListCtrl& ListCtrl=GetListCtrl();
	int nItem = lpDrawItemStruct->itemID;
	
	// get item data
	LV_ITEM lvi;
	_TCHAR szBuff[MAX_PATH];
	
	memset(&lvi, 0, sizeof(LV_ITEM));
	lvi.mask = LVIF_TEXT;
	lvi.iItem = nItem;
	lvi.pszText = szBuff;
	lvi.cchTextMax = sizeof(szBuff);
	ListCtrl.GetItem(&lvi);

	RECT rDraw;
	
	
	CopyRect ( &rDraw, &lpDrawItemStruct->rcItem );
	rDraw.right = rDraw.left + TOGGLELIST_ITEMHEIGHT;
	rDraw.top ++;

	rDraw.right ++;
	FrameRect ( lpDrawItemStruct->hDC, &rDraw, (HBRUSH)GetStockObject ( BLACK_BRUSH ) );
	rDraw.right --;

	FillRect ( lpDrawItemStruct->hDC, &rDraw, GetSysColorBrush ( COLOR_3DFACE ) );

	Draw3dRect ( lpDrawItemStruct->hDC, &rDraw, GetSysColorBrush ( COLOR_3DHILIGHT ), GetSysColorBrush ( COLOR_3DSHADOW ) );

	InflateRect ( &rDraw, -3, -3 );
	Draw3dRect ( lpDrawItemStruct->hDC, &rDraw, GetSysColorBrush ( COLOR_3DSHADOW ), GetSysColorBrush ( COLOR_3DHILIGHT ) );

	switch(GetToggleState(lvi.iItem)) {
		case TOGGLE_STATE_DISABLED:
			if(disabledIcon) {
				DrawIconEx ( lpDrawItemStruct->hDC, rDraw.left, rDraw.top, disabledIcon, 16, 16,0, NULL, DI_NORMAL );
			}
			break;
		case TOGGLE_STATE_ON:
			if(onIcon) {
				DrawIconEx ( lpDrawItemStruct->hDC, rDraw.left, rDraw.top, onIcon, 16, 16,0, NULL, DI_NORMAL );
			}
			break;
		case TOGGLE_STATE_OFF:
			if(offIcon) {
				DrawIconEx ( lpDrawItemStruct->hDC, rDraw.left, rDraw.top, offIcon, 16, 16,0, NULL, DI_NORMAL );
			}
			break;
	};
	
	CopyRect ( &rDraw, &lpDrawItemStruct->rcItem );
	rDraw.left += TOGGLELIST_ITEMHEIGHT;
	rDraw.left += 1;

	if ( lpDrawItemStruct->itemState & ODS_SELECTED ) {
		FillRect ( lpDrawItemStruct->hDC, &rDraw, GetSysColorBrush ( COLOR_HIGHLIGHT ) );			
	} else {
		FillRect ( lpDrawItemStruct->hDC, &rDraw, GetSysColorBrush ( COLOR_WINDOW ) ); 
	}

	rDraw.left += TEXT_OFFSET;

	int colorIndex = ( (lpDrawItemStruct->itemState & ODS_SELECTED ) ? COLOR_HIGHLIGHTTEXT : COLOR_WINDOWTEXT );
	SetTextColor ( lpDrawItemStruct->hDC, GetSysColor ( colorIndex ) );
	DrawText ( lpDrawItemStruct->hDC, szBuff, strlen(szBuff), &rDraw, DT_LEFT|DT_VCENTER|DT_SINGLELINE );

}