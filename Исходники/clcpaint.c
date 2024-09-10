void PaintClc(HWND hwnd, struct ClcData *dat, HDC hdc, RECT * rcPaint)
{
	HDC hdcMem;
	RECT clRect;
	int i, y, indent, index, fontHeight;
	struct ClcGroup *group;
	HBITMAP hBmpOsb, hOldBitmap;
	HFONT hOldFont;
	DWORD style = GetWindowLong(hwnd, GWL_STYLE);
	int status = GetGeneralisedStatus();
	int grey = 0, groupCountsFontTopShift;
	HBRUSH hBrushAlternateGrey = NULL;
	// yes I know about GetSysColorBrush()
	COLORREF tmpbkcolour = style & CLS_CONTACTLIST ? (dat->useWindowsColours ? GetSysColor(COLOR_3DFACE) : dat->bkColour) : dat->bkColour;
	int minHeight = 16;
	for (i = 0; i < FONTID_LAST; i++) {
		if (minHeight < dat->fontInfo[i].fontHeight) {
			minHeight = dat->fontInfo[i].fontHeight;
		}
	}
	if (dat->rowHeight < minHeight) {
		dat->rowHeight = minHeight;
	}

	if (dat->greyoutFlags & pcli->pfnClcStatusToPf2(status) || style & WS_DISABLED)
		grey = 1;
	else if (GetFocus() != hwnd && dat->greyoutFlags & GREYF_UNFOCUS)
		grey = 1;
	GetClientRect(hwnd, &clRect);
	if (rcPaint == NULL)
		rcPaint = &clRect;
	if (IsRectEmpty(rcPaint))
		return;
	y = -dat->yScroll;
	hdcMem = CreateCompatibleDC(hdc);
	hBmpOsb = CreateBitmap(clRect.right, clRect.bottom, 1, GetDeviceCaps(hdc, BITSPIXEL), NULL);
	hOldBitmap = SelectObject(hdcMem, hBmpOsb);
	{
		TEXTMETRIC tm;
		hOldFont = SelectObject(hdcMem, dat->fontInfo[FONTID_GROUPS].hFont);
		GetTextMetrics(hdcMem, &tm);
		groupCountsFontTopShift = tm.tmAscent;
		SelectObject(hdcMem, dat->fontInfo[FONTID_GROUPCOUNTS].hFont);
		GetTextMetrics(hdcMem, &tm);
		groupCountsFontTopShift -= tm.tmAscent;
	}
	if (style & CLS_GREYALTERNATE)
		hBrushAlternateGrey =
		CreateSolidBrush(GetNearestColor(hdcMem, RGB(GetRValue(tmpbkcolour) - 10, GetGValue(tmpbkcolour) - 10, GetBValue(tmpbkcolour) - 10)));

	ChangeToFont(hdcMem, dat, FONTID_CONTACTS, &fontHeight);
	SetBkMode(hdcMem, TRANSPARENT);
	{
		HBRUSH hBrush;

		hBrush = CreateSolidBrush(tmpbkcolour);
		FillRect(hdcMem, rcPaint, hBrush);
		DeleteObject(hBrush);
		if (dat->hBmpBackground) {
			BITMAP bmp;
			HDC hdcBmp;
			int x, y;
			int maxx, maxy;
			int destw, desth;

			// XXX: Halftone isnt supported on 9x, however the scretch problems dont happen on 98.
			SetStretchBltMode(hdcMem, HALFTONE);

			GetObject(dat->hBmpBackground, sizeof(bmp), &bmp);
			hdcBmp = CreateCompatibleDC(hdcMem);
			SelectObject(hdcBmp, dat->hBmpBackground);
			y = dat->backgroundBmpUse & CLBF_SCROLL ? -dat->yScroll : 0;
			maxx = dat->backgroundBmpUse & CLBF_TILEH ? clRect.right : 1;
			maxy = dat->backgroundBmpUse & CLBF_TILEV ? maxy = rcPaint->bottom : y + 1;
			switch (dat->backgroundBmpUse & CLBM_TYPE) {
			case CLB_STRETCH:
				if (dat->backgroundBmpUse & CLBF_PROPORTIONAL) {
					if (clRect.right * bmp.bmHeight < clRect.bottom * bmp.bmWidth) {
						desth = clRect.bottom;
						destw = desth * bmp.bmWidth / bmp.bmHeight;
					}
					else {
						destw = clRect.right;
						desth = destw * bmp.bmHeight / bmp.bmWidth;
					}
				}
				else {
					destw = clRect.right;
					desth = clRect.bottom;
				}
				break;
			case CLB_STRETCHH:
				if (dat->backgroundBmpUse & CLBF_PROPORTIONAL) {
					destw = clRect.right;
					desth = destw * bmp.bmHeight / bmp.bmWidth;
				}
				else {
					destw = clRect.right;
					desth = bmp.bmHeight;
				}
				break;
			case CLB_STRETCHV:
				if (dat->backgroundBmpUse & CLBF_PROPORTIONAL) {
					desth = clRect.bottom;
					destw = desth * bmp.bmWidth / bmp.bmHeight;
				}
				else {
					destw = bmp.bmWidth;
					desth = clRect.bottom;
				}
				break;
			default:       //clb_topleft
				destw = bmp.bmWidth;
				desth = bmp.bmHeight;
				break;
			}
			for (; y < maxy; y += desth) {
				if (y < rcPaint->top - desth)
					continue;
				for (x = 0; x < maxx; x += destw)
					StretchBlt(hdcMem, x, y, destw, desth, hdcBmp, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);
			}
			DeleteDC(hdcBmp);
		}
	}
	group = &dat->list;
	group->scanIndex = 0;
	indent = 0;
	for (index = 0; y < rcPaint->bottom;) {
		if (group->scanIndex == group->cl.count) {
			group = group->parent;
			indent--;
			if (group == NULL)
				break;
			group->scanIndex++;
			continue;
		}
		if (y > rcPaint->top - dat->rowHeight) {
			int iImage = -1;
			int selected = index == dat->selection && (dat->showSelAlways || dat->exStyle & CLS_EX_SHOWSELALWAYS || GetFocus() == hwnd)
				&& group->cl.items[group->scanIndex]->type != CLCIT_DIVIDER;
			int hottrack = dat->exStyle & CLS_EX_TRACKSELECT && group->cl.items[group->scanIndex]->type != CLCIT_DIVIDER && dat->iHotTrack == index;
			SIZE textSize, countsSize, spaceSize;
			int width, checkboxWidth;
			char *szCounts;

			//alternating grey
			if (style & CLS_GREYALTERNATE && index & 1) {
				RECT rc;
				rc.top = y;
				rc.bottom = rc.top + dat->rowHeight;
				rc.left = 0;
				rc.right = clRect.right;
				FillRect(hdcMem, &rc, hBrushAlternateGrey);
			}

			//setup
			if (group->cl.items[group->scanIndex]->type == CLCIT_GROUP)
				ChangeToFont(hdcMem, dat, FONTID_GROUPS, &fontHeight);
			else if (group->cl.items[group->scanIndex]->type == CLCIT_INFO) {
				if (group->cl.items[group->scanIndex]->flags & CLCIIF_GROUPFONT)
					ChangeToFont(hdcMem, dat, FONTID_GROUPS, &fontHeight);
				else
					ChangeToFont(hdcMem, dat, FONTID_CONTACTS, &fontHeight);
			}
			else if (group->cl.items[group->scanIndex]->type == CLCIT_DIVIDER)
				ChangeToFont(hdcMem, dat, FONTID_DIVIDERS, &fontHeight);
			else if (group->cl.items[group->scanIndex]->type == CLCIT_CONTACT && group->cl.items[group->scanIndex]->flags & CONTACTF_NOTONLIST)
				ChangeToFont(hdcMem, dat, FONTID_NOTONLIST, &fontHeight);
			else if (group->cl.items[group->scanIndex]->type == CLCIT_CONTACT &&
				((group->cl.items[group->scanIndex]->flags & CONTACTF_INVISTO
				&& GetRealStatus(group->cl.items[group->scanIndex], status) != ID_STATUS_INVISIBLE)
				|| (group->cl.items[group->scanIndex]->flags & CONTACTF_VISTO
				&& GetRealStatus(group->cl.items[group->scanIndex], status) == ID_STATUS_INVISIBLE)
				)
				) {
					// the contact is in the always visible list and the proto is invisible
					// the contact is in the always invisible and the proto is in any other mode
					ChangeToFont(hdcMem, dat, group->cl.items[group->scanIndex]->flags & CONTACTF_ONLINE ? FONTID_INVIS : FONTID_OFFINVIS, &fontHeight);
				}
			else if (group->cl.items[group->scanIndex]->type == CLCIT_CONTACT && !(group->cl.items[group->scanIndex]->flags & CONTACTF_ONLINE))
				ChangeToFont(hdcMem, dat, FONTID_OFFLINE, &fontHeight);
			else
				ChangeToFont(hdcMem, dat, FONTID_CONTACTS, &fontHeight);
			GetTextExtentPoint32(hdcMem, group->cl.items[group->scanIndex]->szText, lstrlen(group->cl.items[group->scanIndex]->szText), &textSize);
			width = textSize.cx;
			if (group->cl.items[group->scanIndex]->type == CLCIT_GROUP) {
				szCounts = pcli->pfnGetGroupCountsText(dat, group->cl.items[group->scanIndex]);
				if (szCounts[0]) {
					GetTextExtentPoint32A(hdcMem, " ", 1, &spaceSize);
					ChangeToFont(hdcMem, dat, FONTID_GROUPCOUNTS, &fontHeight);
					GetTextExtentPoint32A(hdcMem, szCounts, lstrlenA(szCounts), &countsSize);
					width += spaceSize.cx + countsSize.cx;
				}
			}

			if ((style & CLS_CHECKBOXES && group->cl.items[group->scanIndex]->type == CLCIT_CONTACT) ||
				(style & CLS_GROUPCHECKBOXES && group->cl.items[group->scanIndex]->type == CLCIT_GROUP) ||
				(group->cl.items[group->scanIndex]->type == CLCIT_INFO && group->cl.items[group->scanIndex]->flags & CLCIIF_CHECKBOX))
				checkboxWidth = dat->checkboxSize + 2;
			else
				checkboxWidth = 0;

			//background
			if (selected) {
				int x = dat->leftMargin + indent * dat->groupIndent + checkboxWidth + dat->iconXSpace - 2;
				ImageList_DrawEx(dat->himlHighlight, 0, hdcMem, x, y, min(width + 5, clRect.right - x), dat->rowHeight, CLR_NONE, CLR_NONE,
					dat->exStyle & CLS_EX_NOTRANSLUCENTSEL ? ILD_NORMAL : ILD_BLEND25);
				SetTextColor(hdcMem, dat->selTextColour);
			}
			else if (hottrack)
				SetHotTrackColour(hdcMem, dat);

			//checkboxes
			if (checkboxWidth) {
				RECT rc;
				HANDLE hTheme = NULL;

				// THEME
				if (IsWinVerXPPlus()) {
					if (!themeAPIHandle) {
						themeAPIHandle = GetModuleHandleA("uxtheme");
						if (themeAPIHandle) {
							MyOpenThemeData = (HANDLE(WINAPI *) (HWND, LPCWSTR)) MGPROC("OpenThemeData");
							MyCloseThemeData = (HRESULT(WINAPI *) (HANDLE)) MGPROC("CloseThemeData");
							MyDrawThemeBackground =
								(HRESULT(WINAPI *) (HANDLE, HDC, int, int, const RECT *, const RECT *)) MGPROC("DrawThemeBackground");
						}
					}
					// Make sure all of these methods are valid (i would hope either all or none work)
					if (MyOpenThemeData && MyCloseThemeData && MyDrawThemeBackground) {
						hTheme = MyOpenThemeData(hwnd, L"BUTTON");
					}
				}
				rc.left = dat->leftMargin + indent * dat->groupIndent;
				rc.right = rc.left + dat->checkboxSize;
				rc.top = y + ((dat->rowHeight - dat->checkboxSize) >> 1);
				rc.bottom = rc.top + dat->checkboxSize;
				if (hTheme) {
					MyDrawThemeBackground(hTheme, hdcMem, BP_CHECKBOX, group->cl.items[group->scanIndex]->flags & CONTACTF_CHECKED ? (hottrack ? CBS_CHECKEDHOT : CBS_CHECKEDNORMAL) : (hottrack ? CBS_UNCHECKEDHOT : CBS_UNCHECKEDNORMAL), &rc, &rc);
				}
				else
					DrawFrameControl(hdcMem, &rc, DFC_BUTTON, DFCS_BUTTONCHECK | DFCS_FLAT | (group->cl.items[group->scanIndex]->flags & CONTACTF_CHECKED ? DFCS_CHECKED : 0) | (hottrack ? DFCS_HOT : 0));
				if (hTheme && MyCloseThemeData) {
					MyCloseThemeData(hTheme);
					hTheme = NULL;
				}
			}

			//icon
			if (group->cl.items[group->scanIndex]->type == CLCIT_GROUP)
				iImage = group->cl.items[group->scanIndex]->group->expanded ? IMAGE_GROUPOPEN : IMAGE_GROUPSHUT;
			else if (group->cl.items[group->scanIndex]->type == CLCIT_CONTACT)
				iImage = group->cl.items[group->scanIndex]->iImage;
			if (iImage != -1) {
				/*COLORREF colourFg=dat->selBkColour;
				int mode=ILD_NORMAL;
				if(selected) mode=ILD_SELECTED;
				else if(hottrack) {mode=ILD_FOCUS; colourFg=dat->hotTextColour;}
				else if(group->cl.items[group->scanIndex]->type==CLCIT_CONTACT && group->cl.items[group->scanIndex]->flags&CONTACTF_NOTONLIST) {colourFg=dat->fontInfo[FONTID_NOTONLIST].colour; mode=ILD_BLEND50;}
				ImageList_DrawEx(himlCListClc,iImage,hdcMem,dat->leftMargin+indent*dat->groupIndent+checkboxWidth,y+((dat->rowHeight-16)>>1),0,0,CLR_NONE,colourFg,mode);
				*/
				// this doesnt use CLS_CONTACTLIST since the colour prolly wont match anyway
				COLORREF colourFg = dat->selBkColour;
				int mode = ILD_NORMAL;
				if (hottrack) {
					colourFg = dat->hotTextColour;
				}
				else if (group->cl.items[group->scanIndex]->type == CLCIT_CONTACT && group->cl.items[group->scanIndex]->flags & CONTACTF_NOTONLIST) {
					colourFg = dat->fontInfo[FONTID_NOTONLIST].colour;
					mode = ILD_BLEND50;
				}
				if (group->cl.items[group->scanIndex]->type == CLCIT_CONTACT && dat->showIdle
					&& (group->cl.items[group->scanIndex]->flags & CONTACTF_IDLE)
					&& GetRealStatus(group->cl.items[group->scanIndex], ID_STATUS_OFFLINE) != ID_STATUS_OFFLINE)
					mode = ILD_SELECTED;
				ImageList_DrawEx(himlCListClc, iImage, hdcMem, dat->leftMargin + indent * dat->groupIndent + checkboxWidth,
					y + ((dat->rowHeight - 16) >> 1), 0, 0, CLR_NONE, colourFg, mode);
			}

			//text
			if (group->cl.items[group->scanIndex]->type == CLCIT_DIVIDER) {
				RECT rc;
				rc.top = y + (dat->rowHeight >> 1);
				rc.bottom = rc.top + 2;
				rc.left = dat->leftMargin + indent * dat->groupIndent;
				rc.right = rc.left + ((clRect.right - rc.left - textSize.cx) >> 1) - 3;
				DrawEdge(hdcMem, &rc, BDR_SUNKENOUTER, BF_RECT);
				TextOut(hdcMem, rc.right + 3, y + ((dat->rowHeight - fontHeight) >> 1), group->cl.items[group->scanIndex]->szText,
					lstrlen(group->cl.items[group->scanIndex]->szText));
				rc.left = rc.right + 6 + textSize.cx;
				rc.right = clRect.right;
				DrawEdge(hdcMem, &rc, BDR_SUNKENOUTER, BF_RECT);
			}