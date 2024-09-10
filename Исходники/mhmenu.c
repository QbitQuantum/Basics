LRESULT onDrawItem(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    LPDRAWITEMSTRUCT lpdis; 
	PNHMenuItem item;
	PNHMenuWindow data;
    TEXTMETRIC tm;
	HGDIOBJ saveFont;
	HDC tileDC;
	short ntile;
	int t_x, t_y;
	int x, y;
	TCHAR wbuf[BUFSZ];
	RECT drawRect;
	COLORREF OldBg, OldFg, NewBg;
	char *p, *p1;
	int column;

	lpdis = (LPDRAWITEMSTRUCT) lParam; 

    /* If there are no list box items, skip this message. */
    if (lpdis->itemID == -1) return FALSE;

	data = (PNHMenuWindow)GetWindowLong(hWnd, GWL_USERDATA);

    item = &data->menu.items[lpdis->itemID];

	tileDC = CreateCompatibleDC(lpdis->hDC);
	saveFont = SelectObject(lpdis->hDC, mswin_get_font(NHW_MENU, item->attr, lpdis->hDC, FALSE));
	NewBg = mswin_get_color(NHW_MENU, MSWIN_COLOR_BG);
	OldBg = SetBkColor(lpdis->hDC, NewBg);
	OldFg = SetTextColor(lpdis->hDC, mswin_get_color(NHW_MENU, MSWIN_COLOR_FG)); 

    GetTextMetrics(lpdis->hDC, &tm);

	x = lpdis->rcItem.left + 1;

	/* print check mark if it is a "selectable" menu */
	if( data->how!=PICK_NONE ) {
		if( NHMENU_IS_SELECTABLE(*item) ) {
			HGDIOBJ saveBrush;
			HBRUSH	hbrCheckMark;
			char buf[2];

			switch(item->count) {
			case -1: hbrCheckMark = CreatePatternBrush(data->bmpChecked); break;
			case 0: hbrCheckMark = CreatePatternBrush(data->bmpNotChecked); break;
			default: hbrCheckMark = CreatePatternBrush(data->bmpCheckedCount); break;
			}

			y = (lpdis->rcItem.bottom + lpdis->rcItem.top - TILE_Y) / 2; 
			SetBrushOrgEx(lpdis->hDC, x, y, NULL);
			saveBrush = SelectObject(lpdis->hDC, hbrCheckMark);
			PatBlt(lpdis->hDC, x, y, TILE_X, TILE_Y, PATCOPY);
			SelectObject(lpdis->hDC, saveBrush);
			DeleteObject(hbrCheckMark);

			x += TILE_X + 5;

			if(item->accelerator!=0) {
				buf[0] = item->accelerator;
				buf[1] = '\x0';

				SetRect( &drawRect, x, lpdis->rcItem.top, lpdis->rcItem.right, lpdis->rcItem.bottom );
/*JP
				DrawText(lpdis->hDC, NH_A2W(buf, wbuf, 2), 1, &drawRect, DT_LEFT | DT_VCENTER | DT_SINGLELINE | DT_NOPREFIX);
*/
				DrawText(lpdis->hDC, NH_A2W(buf, wbuf, 2), -1, &drawRect, DT_LEFT | DT_VCENTER | DT_SINGLELINE | DT_NOPREFIX);
			}
			x += tm.tmAveCharWidth + tm.tmOverhang + 5;
		} else {
			x += TILE_X + tm.tmAveCharWidth + tm.tmOverhang + 10;
		}
	}

	/* print glyph if present */
	if( item->glyph != NO_GLYPH ) {
		HGDIOBJ saveBmp;

		saveBmp = SelectObject(tileDC, GetNHApp()->bmpTiles);				
		ntile = glyph2tile[ item->glyph ];
		t_x = (ntile % TILES_PER_LINE)*TILE_X;
		t_y = (ntile / TILES_PER_LINE)*TILE_Y;

		y = (lpdis->rcItem.bottom + lpdis->rcItem.top - TILE_Y) / 2; 

		nhapply_image_transparent(
			lpdis->hDC, x, y, TILE_X, TILE_Y, 
			tileDC, t_x, t_y, TILE_X, TILE_Y, TILE_BK_COLOR );
		SelectObject(tileDC, saveBmp);
	}

	x += TILE_X + 5;

	/* draw item text */
	if( item->has_tab ) {
		p1 = item->str;
		p = strchr(item->str, '\t');
		column = 0;
		SetRect( &drawRect, x, lpdis->rcItem.top, min(x + data->menu.tab_stop_size[0], lpdis->rcItem.right),
			lpdis->rcItem.bottom );
		for (;;) {
			TCHAR wbuf[BUFSZ];
			if (p != NULL) *p = '\0'; /* for time being, view tab field as zstring */
			DrawText(lpdis->hDC,
				NH_A2W(p1, wbuf, BUFSZ),
/*JP
				strlen(p1),
*/
				-1,
				&drawRect,
				DT_LEFT | DT_VCENTER | DT_SINGLELINE
			);
			if (p != NULL) *p = '\t';
			else /* last string so, */ break;

			p1 = p + 1;
			p = strchr(p1, '\t');
			drawRect.left = drawRect.right + TAB_SEPARATION;
			++column;
			drawRect.right = min (drawRect.left + data->menu.tab_stop_size[column], lpdis->rcItem.right);
		}
	} else {
		TCHAR wbuf[BUFSZ];
		SetRect( &drawRect, x, lpdis->rcItem.top, lpdis->rcItem.right, lpdis->rcItem.bottom);
		DrawText(lpdis->hDC,
			NH_A2W(item->str, wbuf, BUFSZ),
/*JP
			strlen(item->str),
*/
			-1,
			&drawRect,
			DT_LEFT | DT_VCENTER | DT_SINGLELINE
		);
	}

	/* draw focused item */
	if( item->has_focus ) {
		RECT client_rt;
		HBRUSH bkBrush;

		GetClientRect(lpdis->hwndItem, &client_rt);
		if( NHMENU_IS_SELECTABLE(*item) && 
			data->menu.items[lpdis->itemID].count>0 &&
			item->glyph != NO_GLYPH ) {
			if( data->menu.items[lpdis->itemID].count==-1 ) {
				_stprintf(wbuf, TEXT("Count: All") );
			} else {
				_stprintf(wbuf, TEXT("Count: %d"), data->menu.items[lpdis->itemID].count );
			}

			SelectObject(lpdis->hDC, mswin_get_font(NHW_MENU, ATR_BLINK, lpdis->hDC, FALSE));

			/* calculate text rectangle */
			SetRect( &drawRect, client_rt.left, lpdis->rcItem.top, client_rt.right, lpdis->rcItem.bottom );
/*JP
			DrawText(lpdis->hDC, wbuf, _tcslen(wbuf), &drawRect, 
*/
			DrawText(lpdis->hDC, wbuf, -1, &drawRect, 
					 DT_CALCRECT | DT_RIGHT | DT_VCENTER | DT_SINGLELINE | DT_NOPREFIX );
			
			/* erase text rectangle */
			drawRect.left = max(client_rt.left+1, client_rt.right - (drawRect.right - drawRect.left) - 10);
			drawRect.right = client_rt.right-1;
			drawRect.top = lpdis->rcItem.top;
			drawRect.bottom = lpdis->rcItem.bottom;
			bkBrush = CreateSolidBrush( GetBkColor(lpdis->hDC) );
			FillRect(lpdis->hDC, &drawRect, bkBrush );
			DeleteObject( bkBrush );

			/* draw text */
/*JP
			DrawText(lpdis->hDC, wbuf, _tcslen(wbuf), &drawRect, 
*/
			DrawText(lpdis->hDC, wbuf, -1, &drawRect, 
					 DT_RIGHT | DT_VCENTER | DT_SINGLELINE | DT_NOPREFIX );
		}

		/* draw focus rect */
		SetRect( &drawRect, client_rt.left, lpdis->rcItem.top, client_rt.right, lpdis->rcItem.bottom );
		DrawFocusRect(lpdis->hDC, &drawRect);
	}

	SetTextColor (lpdis->hDC, OldFg);
	SetBkColor (lpdis->hDC, OldBg);
	SelectObject(lpdis->hDC, saveFont);
	DeleteDC(tileDC);
	return TRUE;
}