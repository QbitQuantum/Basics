void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{	
	if (songlist.quit)
		return;

	UINT n = lpDrawItemStruct->itemID;
	HDC* mdc = &lpDrawItemStruct->hDC;
	HWND* hWnd = &songlist.hWnd;	
	HDC* bdc = &songlist.bdc;
	IMGINFO* imgplay = &songlist.imgplay;
	IMGINFO* imgpause = &songlist.imgpause;
	PLAYERINFO* playerinfo = GetPlayerInfo(n);
	if (playerinfo == NULL)	
		return;
	
	HFONT font = (HFONT)GetCurrentObject(*mdc, OBJ_FONT);
	SelectObject(*bdc, font);		

	RECT r = {0};
	LONG x = lpDrawItemStruct->rcItem.left;
	LONG y = lpDrawItemStruct->rcItem.top;
	LONG w = lpDrawItemStruct->rcItem.right - lpDrawItemStruct->rcItem.left;
	LONG h = lpDrawItemStruct->rcItem.bottom - lpDrawItemStruct->rcItem.top;
	r.left = lpDrawItemStruct->rcItem.left;
	r.right = lpDrawItemStruct->rcItem.right - lpDrawItemStruct->rcItem.left;
	r.top = 0;
	r.bottom = lpDrawItemStruct->rcItem.bottom - lpDrawItemStruct->rcItem.top;

	COLORREF color = RGB(0, 0, 0);

	if ((lpDrawItemStruct->itemAction | ODA_SELECT) && (lpDrawItemStruct->itemState & ODS_SELECTED))  
	{
		SetTextColor(*bdc, RGB(0, 0, 0));
		color = RGB(192, 192, 192);		
	}
	else
		SetTextColor(*bdc, RGB(255, 255, 255));	

	SetBkColor(*bdc, color);
	HBRUSH brush = CreateSolidBrush(color);	
	ExtTextOut(*bdc, 0, 0, ETO_OPAQUE, &r, NULL, 0, NULL);
	DeleteObject(brush);

	RECT rect = {0};
	if (playerinfo != NULL)
	{
		Gdiplus::Graphics graphics(*bdc);
		ListView_GetSubItemRect(*hWnd, n, 0, LVIR_LABEL, &rect);	
		Gdiplus::PointF point;

		if (playerinfo->playing)
		{
			point.X = (Gdiplus::REAL)(rect.right - rect.left - imgplay->image->GetWidth()) / 2.0F;
			point.Y = (Gdiplus::REAL)(rect.bottom - rect.top - imgplay->image->GetHeight()) / 2.0F;
			Gdiplus::Status s = graphics.DrawImage(imgplay->image, point);
		}

		if (playerinfo->pause)
		{
			point.X = (Gdiplus::REAL)(rect.right - rect.left - imgpause->image->GetWidth()) / 2.0F;
			point.Y = (Gdiplus::REAL)(rect.bottom - rect.top - imgpause->image->GetHeight()) / 2.0F;
			Gdiplus::Status s = graphics.DrawImage(imgpause->image, point);
		}
	}
	
	for (int i = 1;i < 4;i++)
	{
		wchar_t text[256] = {0};		
		ListView_GetItemText(*hWnd, n, i, text, sizeof(text) / sizeof(wchar_t));
		ListView_GetSubItemRect(*hWnd, n, i, LVIR_LABEL, &rect);
		r.left = rect.left;
		r.right = rect.right;
		r.top = 0;
		r.bottom = rect.bottom - rect.top;
		DrawText(*bdc, text, wcslen(text), &r, DT_LEFT | DT_SINGLELINE | DT_VCENTER);		
	}

	BitBlt(*mdc, x, y, w, h, *bdc, 0, 0, SRCCOPY);	
}