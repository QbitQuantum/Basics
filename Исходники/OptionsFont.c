//
//	Fontlist owner-draw 
//
BOOL FontCombo_DrawItem(HWND hwnd, DRAWITEMSTRUCT *dis)
{
	TCHAR		szText[100];
	
	BOOL		fFixed		= LOWORD(dis->itemData);
	BOOL		fTrueType	= HIWORD(dis->itemData);

	TEXTMETRIC	tm;
	int			xpos, ypos;
	HANDLE		hOldFont;

	if(dis->itemAction & ODA_FOCUS && !(dis->itemState & ODS_NOFOCUSRECT))
	{
		DrawFocusRect(dis->hDC, &dis->rcItem);
		return TRUE;
	}

	/*{
		HTHEME hTheme = 	OpenThemeData(hwnd, L"combobox");
		RECT rc;
		HDC hdc=GetDC(GetParent(hwnd));
		CopyRect(&rc, &dis->rcItem);
		InflateRect(&rc, 3, 3);
		//GetClientRect(hwnd, &rc);
		//rc.bottom = rc.top + 22;

		//DrawThemeBackground(
		//	hTheme, 
		//	dis->hDC, 
		//	4,//CP_DROPDOWNBUTTON, 
		//	CBXS_HOT,//CBXS_NORMAL, 
		//	&rc, 
		//	&rc);

		CloseThemeData(hTheme);
		ReleaseDC(GetParent(hwnd),hdc);
		return TRUE;
	}*/

	//
	//	Get the item text
	//
	if(dis->itemID == -1)
		SendMessage(dis->hwndItem, WM_GETTEXT, 0, (LONG)szText);
	else
		SendMessage(dis->hwndItem, CB_GETLBTEXT, dis->itemID, (LONG)szText);
	
	//
	//	Set text colour and background based on current state
	//
	DrawItem_DefaultColours(dis);

	// set the font: BOLD for fixed-width, NORMAL for 'normal'
	hOldFont = SelectObject(dis->hDC, fFixed ? g_hBoldFont : g_hNormalFont);
	GetTextMetrics(dis->hDC, &tm);

	ypos = dis->rcItem.top  + (dis->rcItem.bottom-dis->rcItem.top-tm.tmHeight)/2;
	xpos = dis->rcItem.left + 20;
	
	// draw the text
	ExtTextOut(dis->hDC, xpos, ypos,
		ETO_CLIPPED|ETO_OPAQUE, &dis->rcItem, szText, _tcslen(szText), 0);

	// draw a 'TT' icon if the font is TRUETYPE
	if(fTrueType)
		DrawIconEx(dis->hDC, dis->rcItem.left+2, dis->rcItem.top, g_hIcon2,16, 16, 0, 0, DI_NORMAL);
	//else if(fTrueType == 2)
	//	DrawIconEx(dis->hDC, dis->rcItem.left+2, dis->rcItem.top, g_hIcon3,16, 16, 0, 0, DI_NORMAL);

	SelectObject(dis->hDC, hOldFont);

	// draw the focus rectangle
	if((dis->itemState & ODS_FOCUS) && !(dis->itemState & ODS_NOFOCUSRECT))
	{
		DrawFocusRect(dis->hDC, &dis->rcItem);
	}

	return TRUE;
}