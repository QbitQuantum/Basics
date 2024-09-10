LRESULT CALLBACK FrameWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	RECT rect;
	MEASUREITEMSTRUCT *mis;
	LPDRAWITEMSTRUCT dis;
	SIZE textSize;
	RECT r;
	LPARAM lp;
	int sel;

	switch (msg) {

	case WM_MEASUREITEM:
		mis = (MEASUREITEMSTRUCT *)lParam;
		mis->itemWidth = 100;
		mis->itemHeight = options.row_height;
		return TRUE;

	case WM_DRAWITEM:
		dis = (LPDRAWITEMSTRUCT)lParam;
		if (dis->hwndItem == list_hwnd) {
			HBRUSH ttbrush = 0;
			COLORREF tcol;
			if (dis->itemID != -1) {
				PINGADDRESS itemData;
				{
					mir_cslock lck(data_list_cs);
					itemData = *(PINGADDRESS *)dis->itemData;
				}
				SendMessage(list_hwnd, LB_SETITEMHEIGHT, 0, (LPARAM)options.row_height);

				LONG x, y;
				if (context_point_valid) {
					GetWindowRect(list_hwnd, &r);
					x = LOWORD(context_point) - r.left;
					y = HIWORD(context_point) - r.top;
				}
				else x = y = 0;

				GetClientRect(hwnd, &r);

				if ((dis->itemState & ODS_SELECTED && dis->itemState & ODS_FOCUS)
					|| (context_point_valid && (x >= dis->rcItem.left && x <= dis->rcItem.right) && (y >= dis->rcItem.top && y <= dis->rcItem.bottom))) {
					tcol = db_get_dw(NULL, "CLC", "SelBkColour", GetSysColor(COLOR_HIGHLIGHT));
					SetBkColor(dis->hDC, tcol);
					FillRect(dis->hDC, &dis->rcItem, (ttbrush = CreateSolidBrush(tcol)));

					tcol = db_get_dw(NULL, "CLC", "SelTextColour", GetSysColor(COLOR_HIGHLIGHTTEXT));
					SetTextColor(dis->hDC, tcol);
				}
				else {
					tcol = bk_col;
					SetBkColor(dis->hDC, tcol);
					FillRect(dis->hDC, &dis->rcItem, (ttbrush = CreateSolidBrush(tcol)));

					tcol = db_get_dw(NULL, PLUG, "FontCol", GetSysColor(COLOR_WINDOWTEXT));
					SetTextColor(dis->hDC, tcol);
				}

				SetBkMode(dis->hDC, TRANSPARENT);
				HICON hIcon = (itemData.status != PS_DISABLED ? (itemData.status == PS_TESTING ? hIconTesting : (itemData.status == PS_RESPONDING ? hIconResponding : hIconNotResponding)) : hIconDisabled);
				dis->rcItem.left += options.indent;
				DrawIconEx(dis->hDC, dis->rcItem.left, dis->rcItem.top + ((options.row_height - 16) >> 1), hIcon, 0, 0, 0, NULL, DI_NORMAL);

				GetTextExtentPoint32(dis->hDC, itemData.pszLabel, (int)mir_tstrlen(itemData.pszLabel), &textSize);
				TextOut(dis->hDC, dis->rcItem.left + 16 + 4, (dis->rcItem.top + dis->rcItem.bottom - textSize.cy) >> 1, itemData.pszLabel, (int)mir_tstrlen(itemData.pszLabel));

				if (itemData.status != PS_DISABLED) {
					TCHAR buf[256];
					if (itemData.responding) {
						mir_sntprintf(buf, TranslateT("%d ms"), itemData.round_trip_time);
						GetTextExtentPoint32(dis->hDC, buf, (int)mir_tstrlen(buf), &textSize);
						TextOut(dis->hDC, dis->rcItem.right - textSize.cx - 2, (dis->rcItem.top + dis->rcItem.bottom - textSize.cy) >> 1, buf, (int)mir_tstrlen(buf));
					}
					else if (itemData.miss_count > 0) {