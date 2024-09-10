/*************************************************************************
 * FileMenu_DrawItem				[SHELL32.105]
 */
LRESULT WINAPI FileMenu_DrawItem(
	HWND			hWnd,
	LPDRAWITEMSTRUCT	lpdis)
{
	LPFMITEM pMyItem = (LPFMITEM)(lpdis->itemData);
	COLORREF clrPrevText, clrPrevBkgnd;
	int xi,yi,xt,yt;
	HIMAGELIST hImageList;
	RECT TextRect;
	LPFMINFO menuinfo;

	TRACE("%p %p %s\n", hWnd, lpdis, debugstr_w(pMyItem->szItemText));

	if (lpdis->itemState & ODS_SELECTED)
	{
	  clrPrevText = SetTextColor(lpdis->hDC, GetSysColor (COLOR_HIGHLIGHTTEXT));
	  clrPrevBkgnd = SetBkColor(lpdis->hDC, GetSysColor (COLOR_HIGHLIGHT));
	}
	else
	{
	  clrPrevText = SetTextColor(lpdis->hDC, GetSysColor (COLOR_MENUTEXT));
	  clrPrevBkgnd = SetBkColor(lpdis->hDC, GetSysColor (COLOR_MENU));
	}

	CopyRect(&TextRect, &(lpdis->rcItem));

	/* add the menubitmap */
	menuinfo = FM_GetMenuInfo(pMyItem->hMenu);
	if (menuinfo->nBorderWidth)
	  TextRect.left += menuinfo->nBorderWidth;

	TextRect.left += FM_LEFTBORDER;
	xi = TextRect.left + FM_SPACE1;
	yi = TextRect.top + FM_Y_SPACE/2;
	TextRect.bottom -= FM_Y_SPACE/2;

	xt = xi + FM_ICON_SIZE + FM_SPACE2;
	yt = yi;

	ExtTextOutW (lpdis->hDC, xt , yt, ETO_OPAQUE, &TextRect, pMyItem->szItemText, pMyItem->cchItemText, NULL);

	Shell_GetImageLists(0, &hImageList);
	ImageList_Draw(hImageList, pMyItem->iIconIndex, lpdis->hDC, xi, yi, ILD_NORMAL);

	TRACE("-- 0x%04x 0x%04x 0x%04x 0x%04x\n", TextRect.left, TextRect.top, TextRect.right, TextRect.bottom);

	SetTextColor(lpdis->hDC, clrPrevText);
	SetBkColor(lpdis->hDC, clrPrevBkgnd);

	return TRUE;
}