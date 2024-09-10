static void PaintWorker(MButtonCtrl *ctl, HDC hdcPaint)
{
	if(hdcPaint) {
		HDC 	hdcMem;
		RECT 	rcClient, rcBp;
		HFONT 	hOldFont = 0;
		int 	xOffset = 0;
		HANDLE	hbp = 0;
		GetClientRect(ctl->hwnd, &rcClient);
#ifndef _USE_D2D
		rcBp = rcClient;
		INIT_PAINT(hdcPaint, rcBp, hdcMem);
#else
		hdcMem = cfg::dat.hdcBg;
		MapWindowPoints(ctl->hwnd, pcli->hwndContactList, reinterpret_cast<POINT *>(&rcClient), 2);
#endif

		hOldFont = reinterpret_cast<HFONT>(SelectObject(hdcMem, ctl->hFont));
		// If its a push button, check to see if it should stay pressed
		if(ctl->pushBtn && ctl->pbState)
			ctl->stateId = PBS_PRESSED;

		// Draw the flat button
		if(ctl->flatBtn) {
			if(ctl->hThemeToolbar && ctl->bThemed) {
				RECT rc = rcClient;
				int state = IsWindowEnabled(ctl->hwnd) ? (ctl->stateId == PBS_NORMAL && ctl->defbutton ? PBS_DEFAULTED : ctl->stateId) : PBS_DISABLED;
				Gfx::drawBGFromSurface(ctl->hwnd, rc, hdcMem);
				if(Api::pfnIsThemeBackgroundPartiallyTransparent(ctl->hThemeToolbar, TP_BUTTON, TBStateConvert2Flat(state))) {
					Api::pfnDrawThemeParentBackground(ctl->hwnd, hdcMem, &rc);
				}
				Api::pfnDrawThemeBackground(ctl->hThemeToolbar, hdcMem, TP_BUTTON, TBStateConvert2Flat(state), &rc, &rc);
			} else {
				HBRUSH hbr;
				RECT rc = rcClient;

				if(ctl->buttonItem) {
					RECT rcParent;
					POINT pt;
					TImageItem *imgItem = ctl->stateId == PBS_HOT ? ctl->buttonItem->imgHover : (ctl->stateId == PBS_PRESSED ? ctl->buttonItem->imgPressed : ctl->buttonItem->imgNormal);
					LONG *glyphMetrics = ctl->stateId == PBS_HOT ? ctl->buttonItem->hoverGlyphMetrics : (ctl->stateId == PBS_PRESSED ? ctl->buttonItem->pressedGlyphMetrics : ctl->buttonItem->normalGlyphMetrics);
#ifndef _USE_D2D
					GetWindowRect(ctl->hwnd, &rcParent);
					pt.x = rcParent.left;
					pt.y = rcParent.top;
					ScreenToClient(pcli->hwndContactList, &pt);
					Gfx::drawBGFromSurface(ctl->hwnd, rc, hdcMem);
#endif
					if(imgItem)
						Gfx::renderSkinItem(hdcMem, &rc, imgItem);
					if(Skin::glyphItem) {
						Api::pfnAlphaBlend(hdcMem, (rc.right - glyphMetrics[2]) / 2, (rc.bottom - glyphMetrics[3]) / 2,
										   glyphMetrics[2], glyphMetrics[3], Skin::glyphItem->hdc,
										   glyphMetrics[0], glyphMetrics[1], glyphMetrics[2],
										   glyphMetrics[3], Skin::glyphItem->bf);
					}
				} else if(ctl->bSkinned) {    // skinned
					RECT rcParent;
					TStatusItem *item;
					int item_id;

					GetWindowRect(ctl->hwnd, &rcParent);

					Gfx::drawBGFromSurface(ctl->hwnd, rc, hdcMem);
					item_id = ctl->stateId == PBS_HOT ? ID_EXTBKBUTTONSMOUSEOVER : (ctl->stateId == PBS_PRESSED ? ID_EXTBKBUTTONSPRESSED : ID_EXTBKBUTTONSNPRESSED);
					item = &Skin::statusItems[item_id];
					Gfx::setTextColor(item->TEXTCOLOR);
					if(item->IGNORED)
						FillRect(hdcMem, &rc, GetSysColorBrush(COLOR_3DFACE));
					else {
						rc.top += item->MARGIN_TOP;
						rc.bottom -= item->MARGIN_BOTTOM;
						rc.left += item->MARGIN_LEFT;
						rc.right -= item->MARGIN_RIGHT;
						Gfx::renderSkinItem(hdcMem, &rc, item->imageItem);
					}
				} else {
					if(ctl->stateId == PBS_PRESSED || ctl->stateId == PBS_HOT)
						hbr = GetSysColorBrush(COLOR_3DFACE);
					else {
						HDC dc;
						HWND hwndParent;

						hwndParent = GetParent(ctl->hwnd);
						dc = GetDC(hwndParent);
						hbr = (HBRUSH) SendMessage(hwndParent, WM_CTLCOLORDLG, (WPARAM) dc, (LPARAM) hwndParent);
						ReleaseDC(hwndParent, dc);
					}
					if(hbr) {
						FillRect(hdcMem, &rc, hbr);
						DeleteObject(hbr);
					}
				}
				if(!ctl->bSkinned && ctl->buttonItem == 0) {
					if(ctl->stateId == PBS_HOT || ctl->focus) {
						if(ctl->pbState)
							DrawEdge(hdcMem, &rc, EDGE_ETCHED, BF_RECT | BF_SOFT);
						else
							DrawEdge(hdcMem, &rc, BDR_RAISEDOUTER, BF_RECT | BF_SOFT);
					} else if(ctl->stateId == PBS_PRESSED)
						DrawEdge(hdcMem, &rc, BDR_SUNKENOUTER, BF_RECT | BF_SOFT);
				}
			}
		} else {
			// Draw background/border
			if(ctl->hThemeButton && ctl->bThemed) {
				int state = IsWindowEnabled(ctl->hwnd) ? (ctl->stateId == PBS_NORMAL && ctl->defbutton ? PBS_DEFAULTED : ctl->stateId) : PBS_DISABLED;
				POINT pt;
				RECT rcParent;

				GetWindowRect(ctl->hwnd, &rcParent);
				pt.x = rcParent.left;
				pt.y = rcParent.top;
				ScreenToClient(pcli->hwndContactList, &pt);
				BitBlt(hdcMem, 0, 0, rcClient.right, rcClient.bottom, cfg::dat.hdcBg, pt.x, pt.y, SRCCOPY);

				if(Api::pfnIsThemeBackgroundPartiallyTransparent(ctl->hThemeButton, BP_PUSHBUTTON, state)) {
					Api::pfnDrawThemeParentBackground(ctl->hwnd, hdcMem, &rcClient);
				}
				Api::pfnDrawThemeBackground(ctl->hThemeButton, hdcMem, BP_PUSHBUTTON, state, &rcClient, &rcClient);
			} else {
				UINT uState = DFCS_BUTTONPUSH | ((ctl->stateId == PBS_HOT) ? DFCS_HOT : 0) | ((ctl->stateId == PBS_PRESSED) ? DFCS_PUSHED : 0);
				if(ctl->defbutton && ctl->stateId == PBS_NORMAL)
					uState |= DLGC_DEFPUSHBUTTON;
				DrawFrameControl(hdcMem, &rcClient, DFC_BUTTON, uState);
			}

			// Draw focus rectangle if button has focus
			if(ctl->focus) {
				RECT focusRect = rcClient;
				InflateRect(&focusRect, -3, -3);
				DrawFocusRect(hdcMem, &focusRect);
			}
		}

		// If we have an icon or a bitmap, ignore text and only draw the image on the button
		if(ctl->hIcon || ctl->hIconPrivate || ctl->iIcon) {
			int ix = (rcClient.right - rcClient.left) / 2 - (CXSMICON / 2);
			int iy = (rcClient.bottom - rcClient.top) / 2 - (CXSMICON / 2);
			HICON hIconNew = ctl->hIconPrivate != 0 ? ctl->hIconPrivate : ctl->hIcon;
			if(lstrlen(ctl->szText) == 0) {
				if(ctl->iIcon)
					ImageList_DrawEx(ctl->hIml, ctl->iIcon, hdcMem, ix, iy, CXSMICON, CYSMICON, CLR_NONE, CLR_NONE, ILD_NORMAL);
				else
					DrawState(hdcMem, NULL, NULL, (LPARAM) hIconNew, 0, ix, iy, CXSMICON, CYSMICON, IsWindowEnabled(ctl->hwnd) ? DST_ICON | DSS_NORMAL : DST_ICON | DSS_DISABLED);
				ctl->sLabel.cx = ctl->sLabel.cy = 0;
			} else {
				GetTextExtentPoint32(hdcMem, ctl->szText, lstrlen(ctl->szText), &ctl->sLabel);

				if(CXSMICON + ctl->sLabel.cx + 8 > rcClient.right - rcClient.left)
					ctl->sLabel.cx = (rcClient.right - rcClient.left) - CXSMICON - 8;
				else
					ctl->sLabel.cx += 4;

				ix = (rcClient.right - rcClient.left) / 2 - ((CXSMICON + ctl->sLabel.cx) / 2);
				if(ctl->iIcon)
					ImageList_DrawEx(ctl->hIml, ctl->iIcon, hdcMem, ix, iy, CXSMICON, CYSMICON, CLR_NONE, CLR_NONE, ILD_NORMAL);
				else
					DrawState(hdcMem, NULL, NULL, (LPARAM) hIconNew, 0, ix, iy, CXSMICON, CYSMICON, IsWindowEnabled(ctl->hwnd) ? DST_ICON | DSS_NORMAL : DST_ICON | DSS_DISABLED);
				xOffset = ix + CXSMICON + 4;
			}
		} else if(ctl->hBitmap) {
			BITMAP bminfo;
			int ix, iy;

			GetObject(ctl->hBitmap, sizeof(bminfo), &bminfo);
			ix = (rcClient.right - rcClient.left) / 2 - (bminfo.bmWidth / 2);
			iy = (rcClient.bottom - rcClient.top) / 2 - (bminfo.bmHeight / 2);
			if(ctl->stateId == PBS_PRESSED) {
				ix++;
				iy++;
			}
			DrawState(hdcMem, NULL, NULL, (LPARAM) ctl->hBitmap, 0, ix, iy, bminfo.bmWidth, bminfo.bmHeight, IsWindowEnabled(ctl->hwnd) ? DST_BITMAP : DST_BITMAP | DSS_DISABLED);
		}
		if(GetWindowTextLength(ctl->hwnd)) {
			// Draw the text and optinally the arrow
			RECT rcText;

			CopyRect(&rcText, &rcClient);
			SetBkMode(hdcMem, TRANSPARENT);
			if(!ctl->bSkinned)
				Gfx::setTextColor(IsWindowEnabled(ctl->hwnd) || !ctl->hThemeButton ? GetSysColor(COLOR_BTNTEXT) : GetSysColor(COLOR_GRAYTEXT));
			if(ctl->arrow) {
				DrawState(hdcMem, NULL, NULL, (LPARAM) ctl->arrow, 0, rcClient.right - rcClient.left - 5 - CXSMICON + (!ctl->hThemeButton && ctl->stateId == PBS_PRESSED ? 1 : 0), (rcClient.bottom - rcClient.top) / 2 - CYSMICON / 2 + (!ctl->hThemeButton && ctl->stateId == PBS_PRESSED ? 1 : 0), CXSMICON, CYSMICON, IsWindowEnabled(ctl->hwnd) ? DST_ICON : DST_ICON | DSS_DISABLED);
				rcText.left += (4 + CXSMICON);
			}
			if(xOffset)
				rcText.left += (4 + CXSMICON);
			Gfx::renderText(hdcMem, ctl->hThemeButton, ctl->szText, &rcText, DT_VCENTER | DT_CENTER | DT_SINGLELINE, 0);
		}
		if(hOldFont)
			SelectObject(hdcMem, hOldFont);
#ifndef _USE_D2D
		FINALIZE_PAINT(hbp, &rcBp, 0);
#endif
	}
}