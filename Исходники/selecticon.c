/*------------------------------------------------
  WM_DRAWITEM message
--------------------------------------------------*/
void OnDrawItem(LPARAM lParam)
{
	LPDRAWITEMSTRUCT pDis;
	HBRUSH hbr;
	COLORREF col;
	RECT rc;
	int cxicon, cyicon;
	
	pDis = (LPDRAWITEMSTRUCT)lParam;
	
	switch(pDis->itemAction)
	{
		case ODA_DRAWENTIRE:
		case ODA_SELECT:
		{
			if(pDis->itemState & ODS_SELECTED)
				col = GetSysColor(COLOR_HIGHLIGHT);
			else col = GetSysColor(COLOR_WINDOW);
			hbr = CreateSolidBrush(col);
			FillRect(pDis->hDC, &pDis->rcItem, hbr);
			DeleteObject(hbr);
			if(!(pDis->itemState & ODS_FOCUS)) break;
		}
		case ODA_FOCUS:
		{
			if(pDis->itemState & ODS_FOCUS)
				col = GetSysColor(COLOR_WINDOWTEXT);
			else
				col = GetSysColor(COLOR_WINDOW);
			hbr = CreateSolidBrush(col);
			FrameRect(pDis->hDC, &pDis->rcItem, hbr);
			DeleteObject(hbr);
			break;
		}
	}
	
	if(pDis->itemData == 0) return;
	
	cxicon = GetSystemMetrics(SM_CXSMICON);
	cyicon = GetSystemMetrics(SM_CYSMICON);
	
	CopyRect(&rc, &(pDis->rcItem));
	DrawIconEx(pDis->hDC,
		rc.left + (rc.right - rc.left - cxicon)/2,
		rc.top + (rc.bottom - rc.top - cyicon)/2,
		(HICON)pDis->itemData,
		cxicon, cyicon, 0, NULL, DI_NORMAL);
}