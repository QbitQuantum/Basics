/* on WM_PAINT */
void onPaint(HWND hWnd) 
{
	PNHMapWindow data;
	PAINTSTRUCT ps;
	HDC hDC;
	HDC tileDC;
	HGDIOBJ saveBmp;
	RECT paint_rt;
	int i, j;

	/* get window data */
	data = (PNHMapWindow)GetWindowLong(hWnd, GWL_USERDATA);

	hDC = BeginPaint(hWnd, &ps);

	/* calculate paint rectangle */
	if( !IsRectEmpty(&ps.rcPaint) ) {
		/* calculate paint rectangle */
		paint_rt.left = max(data->xPos + (ps.rcPaint.left - data->map_orig.x)/data->xScrTile, 0);
		paint_rt.top = max(data->yPos + (ps.rcPaint.top - data->map_orig.y)/data->yScrTile, 0);
		paint_rt.right = min(data->xPos + (ps.rcPaint.right - data->map_orig.x)/data->xScrTile+1, COLNO);
		paint_rt.bottom = min(data->yPos + (ps.rcPaint.bottom - data->map_orig.y)/data->yScrTile+1, ROWNO);

		if( data->bAsciiMode
#ifdef REINCARNATION
		    || Is_rogue_level(&u.uz) 
			/* You enter a VERY primitive world! */
#endif
			) {
			HGDIOBJ oldFont;

			oldFont = SelectObject(hDC, data->hMapFont);
			SetBkMode(hDC, TRANSPARENT);

			/* draw the map */
			for(i=paint_rt.left; i<paint_rt.right; i++) 
			for(j=paint_rt.top; j<paint_rt.bottom; j++) 
			if(data->map[i][j]>=0) {
				char ch;
				TCHAR wch;
				RECT  glyph_rect;
				int   color;
				unsigned special;
				int mgch;
				HBRUSH back_brush;
				COLORREF OldFg;

				nhcoord2display(data, i, j, &glyph_rect);

#if (VERSION_MAJOR < 4) && (VERSION_MINOR < 4) && (PATCHLEVEL < 2)
				nhglyph2charcolor(data->map[i][j], &ch, &color);
				OldFg = SetTextColor (hDC, nhcolor_to_RGB(color) );
#else
				/* rely on NetHack core helper routine */
				mapglyph(data->map[i][j], &mgch, &color,
						&special, i, j);
				ch = (char)mgch;
				if (((special & MG_PET) && iflags.hilite_pet) ||
				    ((special & MG_DETECT) && iflags.use_inverse)) {
					back_brush = CreateSolidBrush(nhcolor_to_RGB(CLR_GRAY));
					FillRect (hDC, &glyph_rect, back_brush);
					DeleteObject (back_brush);
					switch (color)
					{
					case CLR_GRAY:
					case CLR_WHITE:
						OldFg = SetTextColor( hDC,  nhcolor_to_RGB(CLR_BLACK));
						break;
					default:
						OldFg = SetTextColor (hDC, nhcolor_to_RGB(color) );
					}
				} else {
					OldFg = SetTextColor (hDC, nhcolor_to_RGB(color) );
				}
#endif

				DrawText(hDC, 
						 NH_A2W(&ch, &wch, 1),
						 1,
						 &glyph_rect,
						 DT_CENTER | DT_VCENTER | DT_NOPREFIX
						 );
				SetTextColor (hDC, OldFg);
			}
			SelectObject(hDC, oldFont);
		} else {
			/* prepare tiles DC for mapping */
			tileDC = CreateCompatibleDC(hDC);
			saveBmp = SelectObject(tileDC, GetNHApp()->bmpMapTiles);

			/* draw the map */
			for(i=paint_rt.left; i<paint_rt.right; i++) 
			for(j=paint_rt.top; j<paint_rt.bottom; j++) 
				if(data->map[i][j]>=0) {
					short ntile;
					int t_x, t_y;
					RECT glyph_rect;

					ntile = glyph2tile[ data->map[i][j] ];
					t_x = (ntile % GetNHApp()->mapTilesPerLine)*GetNHApp()->mapTile_X;
					t_y = (ntile / GetNHApp()->mapTilesPerLine)*GetNHApp()->mapTile_Y;
					
					nhcoord2display(data, i, j, &glyph_rect);

					StretchBlt( 
						hDC, 
						glyph_rect.left,
						glyph_rect.top, 
						data->xScrTile,
						data->yScrTile,
						tileDC,
						t_x,
						t_y,
						GetNHApp()->mapTile_X, 
						GetNHApp()->mapTile_Y, 
						SRCCOPY 
					);
					if( glyph_is_pet(data->map[i][j]) && iflags.wc_hilite_pet ) {
						/* apply pet mark transparently over 
						   pet image */
						HDC hdcPetMark;
						HBITMAP    bmPetMarkOld;

						/* this is DC for petmark bitmap */
						hdcPetMark = CreateCompatibleDC(hDC);
						bmPetMarkOld = SelectObject(hdcPetMark, GetNHApp()->bmpPetMark);

						nhapply_image_transparent( 
							hDC,
							glyph_rect.left,
							glyph_rect.top, 
							data->xScrTile,
							data->yScrTile,
							hdcPetMark,
							0,
							0,
							TILE_X, 
							TILE_Y,
							TILE_BK_COLOR 
						);
						SelectObject(hdcPetMark, bmPetMarkOld);
						DeleteDC(hdcPetMark);
					}
				}
			SelectObject(tileDC, saveBmp);
			DeleteDC(tileDC);
		}

		/* draw focus rect */
		nhcoord2display(data, data->xCur, data->yCur, &paint_rt);
		if( data->bAsciiMode ) {
			PatBlt( hDC, 
				    paint_rt.left, paint_rt.top, 
				    paint_rt.right-paint_rt.left, paint_rt.bottom-paint_rt.top, 
				    DSTINVERT );	
		} else {
			DrawFocusRect(hDC, &paint_rt);
		}
	}
	EndPaint(hWnd, &ps);
}