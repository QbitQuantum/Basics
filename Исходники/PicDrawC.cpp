void CPicDrawC::DrawItem(LPDRAWITEMSTRUCT lpdis, bool bHasFocus)
{
	if (lpdis->itemID==(UINT)-1) return;

	CDC dc;
	CRect rect = lpdis->rcItem;
	
	
	ASSERT( lpdis->itemID >= 0 );
	const int nIndex = lpdis->itemID;

	dc.Attach(lpdis->hDC);

	// Save these value to restore them when done drawing.
	COLORREF crOldTextColor = dc.GetTextColor();
	COLORREF crOldBkColor = dc.GetBkColor();

	if ((lpdis->itemAction | ODA_SELECT) &&
	(lpdis->itemState  & ODS_SELECTED))	{
		dc.FillSolidRect(rect, ::GetSysColor(COLOR_HIGHLIGHT));
		if(bHasFocus) {
			dc.DrawFocusRect(rect);
		}	
	}
	else {      
		dc.FillSolidRect(rect, ::GetSysColor(COLOR_WINDOW));  
	}

	HBITMAP hbmp = (HBITMAP)lpdis->itemData;
	CDC MemDC;
	MemDC.CreateCompatibleDC(&dc);
	MemDC.SelectObject(hbmp);
	dc.BitBlt(rect.left+5, rect.top+1, PicSizeX, PicSizeY, &MemDC, 0, 0, SRCCOPY);
	
	// Reset the background color and the text color back to their
	// original values.
	dc.SetTextColor(crOldTextColor);
	dc.SetBkColor(crOldBkColor);	

	dc.Detach();

}