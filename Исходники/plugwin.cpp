LRESULT CALLBACK mypluginwindow1proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	RECT rect;
	MEASUREITEMSTRUCT *mis;
	LPDRAWITEMSTRUCT dis;
	LISTITEM *pItemData;
	SIZE textSize;
	RECT r;
	LPARAM lp;
	int sel;
	HFONT oldFont;
	//PAINTSTRUCT ps;

	switch(msg)
	{
		
	case WM_MEASUREITEM:
		{
			mis = (MEASUREITEMSTRUCT *)lParam;
			mis->itemWidth = 100;
			mis->itemHeight = DBGetContactSettingWord(NULL, "WorldTime", "RowHeight",GetSystemMetrics(SM_CYSMICON));
			return TRUE;
		}
		
	case WM_DRAWITEM:
		dis = (LPDRAWITEMSTRUCT)lParam;
		//pItemData = (LISTITEM *)dis->itemData;
		if(dis->hwndItem == label) {
			HBRUSH ttbrush = 0;
			RECT r;
			COLORREF tcol;
			//GetClientRect(dis->hwndItem, &r);
			GetClientRect(hwnd, &r);
			if(dis->itemID != -1) {

				oldFont = (HFONT)SelectObject(dis->hDC, ContactFont);
				GetTextExtentPoint32(dis->hDC,_T("X"),1,&textSize);
				SendMessage(label, LB_SETITEMHEIGHT, 0, (LPARAM)DBGetContactSettingWord(NULL, "WorldTime", "RowHeight",GetSystemMetrics(SM_CYSMICON)));
				// stop full list erase
				//dis->rcItem.bottom = dis->rcItem.top + DBGetContactSettingWord(NULL, "WorldTime", "RowHeight",GetSystemMetrics(SM_CYSMICON));

				if(dis->itemState & ODS_SELECTED && dis->itemState & ODS_FOCUS) {

					if(ServiceExists(MS_SKIN_DRAWGLYPH)) {
						if(FrameIsFloating()) {
							//SkinDrawGlyph(dis->hDC, &r, &dis->rcItem, "Main Window/Backgrnd");
							SkinDrawGlyph(dis->hDC, &r, &dis->rcItem, "World Time/Selection Background");
						} else {
							//SkinDrawWindowBack(label, dis->hDC, &dis->rcItem, "Main Window/Backgrnd");
							SkinDrawGlyph(dis->hDC, &r, &dis->rcItem, "World Time/Selection Background");
						}
					} else {
						tcol = DBGetContactSettingDword(NULL,"CLC","SelBkColour", CLCDEFAULT_SELBKCOLOUR);
						SetBkColor(dis->hDC, tcol);
						FillRect(dis->hDC, &dis->rcItem, (ttbrush = CreateSolidBrush(tcol)));
					}
					
					tcol = DBGetContactSettingDword(NULL,"CLC","SelTextColour", CLCDEFAULT_SELTEXTCOLOUR);
					SetTextColor(dis->hDC, tcol);
				} else {
					
					if(ServiceExists(MS_SKIN_DRAWGLYPH)) {
						
						if(FrameIsFloating()) {
							//SkinDrawGlyph(dis->hDC, &r, &dis->rcItem, "Main Window/Backgrnd");
							SkinDrawGlyph(dis->hDC, &r, &dis->rcItem, "World Time/Background");
						} else {
							//SkinDrawWindowBack(label, dis->hDC, &dis->rcItem, "Main Window/Backgrnd");
							SkinDrawGlyph(dis->hDC, &r, &dis->rcItem, "World Time/Background");
						}
						
					} else {
						//tcol = DBGetContactSettingDword(NULL,"CLC","BkColour", CLCDEFAULT_BKCOLOUR);
						tcol = DBGetContactSettingDword(NULL, "WorldTime", "BgColour", GetSysColor(COLOR_3DFACE));
						SetBkColor(dis->hDC, tcol);
						FillRect(dis->hDC, &dis->rcItem, (ttbrush = CreateSolidBrush(tcol)));
					}
					
					//SendMessage(label, LB_GETITEMRECT, (WPARAM)dis->itemID, (LPARAM)&r);
					//FillRect(dis->hDC, &r, (ttbrush = CreateSolidBrush(tcol)));

					tcol = ContactFontColour;					
					SetTextColor(dis->hDC, tcol);
				}				
				
				SetBkMode(dis->hDC, TRANSPARENT);
				pItemData = &listbox_items[dis->itemID];
				{

					dis->rcItem.left += DBGetContactSettingWord(NULL, "WorldTime", "Indent", 0);
					if(show_icons) {
						//DrawIconEx(dis->hDC,dis->rcItem.left,(dis->rcItem.top+dis->rcItem.bottom-GetSystemMetrics(SM_CYSMICON))>>1, pItemData->icon, GetSystemMetrics(SM_CXSMICON),GetSystemMetrics(SM_CYSMICON),0,NULL,DI_NORMAL);
						DrawIconEx(dis->hDC,dis->rcItem.left,(dis->rcItem.top+dis->rcItem.bottom-16)>>1, pItemData->icon, 0, 0, 0, NULL, DI_NORMAL);
			
						GetTextExtentPoint32(dis->hDC,pItemData->pszText,lstrlen(pItemData->pszText),&textSize);
						TextOut(dis->hDC,dis->rcItem.left + 16 + 4,(dis->rcItem.top+dis->rcItem.bottom-textSize.cy)>>1,pItemData->pszText,lstrlen(pItemData->pszText));
					} else {
						GetTextExtentPoint32(dis->hDC,pItemData->pszText,lstrlen(pItemData->pszText),&textSize);
						TextOut(dis->hDC,dis->rcItem.left,(dis->rcItem.top+dis->rcItem.bottom-textSize.cy)>>1,pItemData->pszText,lstrlen(pItemData->pszText));
					}

					GetTextExtentPoint32(dis->hDC,pItemData->pszTimeText,lstrlen(pItemData->pszTimeText),&textSize);
					TextOut(dis->hDC,dis->rcItem.right - textSize.cx - 2,(dis->rcItem.top+dis->rcItem.bottom-textSize.cy)>>1,pItemData->pszTimeText,lstrlen(pItemData->pszTimeText));

					if(set_format) {
						int xSave = textSize.cx;

						GetTextExtentPoint32(dis->hDC,pItemData->pszDateText,lstrlen(pItemData->pszDateText),&textSize);
						TextOut(dis->hDC,dis->rcItem.right - textSize.cx - xSave - 4,(dis->rcItem.top+dis->rcItem.bottom-textSize.cy)>>1,pItemData->pszDateText,lstrlen(pItemData->pszDateText));
					}
				}

				SetBkMode(dis->hDC, OPAQUE);
				SelectObject(dis->hDC, oldFont);
			} else {