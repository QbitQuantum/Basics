void PaintClc(HWND hwnd, struct ClcData *dat, HDC hdc, RECT * rcPaint)
{
	RECT clRect;
	int indent, index, fontHeight;
	struct ClcGroup *group;
	HFONT hOldFont;
	LONG_PTR style = GetWindowLongPtr(hwnd, GWL_STYLE);
	int status = GetGeneralisedStatus();
	int grey = 0, groupCountsFontTopShift;
	HBRUSH hBrushAlternateGrey = NULL;
	// yes I know about GetSysColorBrush()
	COLORREF tmpbkcolour = style & CLS_CONTACTLIST ? (dat->useWindowsColours ? GetSysColor(COLOR_3DFACE) : dat->bkColour) : dat->bkColour;

	if (dat->greyoutFlags & pcli->pfnClcStatusToPf2(status) || style & WS_DISABLED)
		grey = 1;
	else if (GetFocus() != hwnd && dat->greyoutFlags & GREYF_UNFOCUS)
		grey = 1;
	GetClientRect(hwnd, &clRect);
	if (rcPaint == NULL)
		rcPaint = &clRect;
	if (IsRectEmpty(rcPaint))
		return;

	HDC hdcMem = CreateCompatibleDC(hdc);
	HBITMAP hBmpOsb = CreateBitmap(clRect.right, clRect.bottom, 1, GetDeviceCaps(hdc, BITSPIXEL), NULL);
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(hdcMem, hBmpOsb);
	{
		TEXTMETRIC tm;
		hOldFont = (HFONT)SelectObject(hdcMem, dat->fontInfo[FONTID_GROUPS].hFont);
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
		HBRUSH hBrush = CreateSolidBrush(tmpbkcolour);
		FillRect(hdcMem, rcPaint, hBrush);
		DeleteObject(hBrush);
		if (dat->hBmpBackground) {
			// XXX: Halftone isnt supported on 9x, however the scretch problems dont happen on 98.
			SetStretchBltMode(hdcMem, HALFTONE);

			BITMAP bmp;
			GetObject(dat->hBmpBackground, sizeof(bmp), &bmp);
			HDC hdcBmp = CreateCompatibleDC(hdcMem);
			SelectObject(hdcBmp, dat->hBmpBackground);
			int y = dat->backgroundBmpUse & CLBF_SCROLL ? -dat->yScroll : 0;
			int maxx = dat->backgroundBmpUse & CLBF_TILEH ? clRect.right : 1;
			int maxy = dat->backgroundBmpUse & CLBF_TILEV ? rcPaint->bottom : y + 1;
			int destw, desth;
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
				for (int x = 0; x < maxx; x += destw)
					StretchBlt(hdcMem, x, y, destw, desth, hdcBmp, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);
			}
			DeleteDC(hdcBmp);
		}
	}

	int y = -dat->yScroll;
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

		ClcContact *cc = group->cl.items[group->scanIndex];
		if (y > rcPaint->top - dat->rowHeight) {
			int iImage = -1;
			int selected = index == dat->selection && (dat->showSelAlways || dat->exStyle & CLS_EX_SHOWSELALWAYS || GetFocus() == hwnd) && cc->type != CLCIT_DIVIDER;
			int hottrack = dat->exStyle & CLS_EX_TRACKSELECT && cc->type != CLCIT_DIVIDER && dat->iHotTrack == index;
			SIZE textSize, countsSize = { 0 }, spaceSize = { 0 };
			int width, checkboxWidth;
			TCHAR *szCounts = NULL;

			// alternating grey
			if (style & CLS_GREYALTERNATE && index & 1) {
				RECT rc;
				rc.top = y;
				rc.bottom = rc.top + dat->rowHeight;
				rc.left = 0;
				rc.right = clRect.right;
				FillRect(hdcMem, &rc, hBrushAlternateGrey);
			}

			// setup
			if (cc->type == CLCIT_GROUP)
				ChangeToFont(hdcMem, dat, FONTID_GROUPS, &fontHeight);
			else if (cc->type == CLCIT_INFO) {
				if (cc->flags & CLCIIF_GROUPFONT)
					ChangeToFont(hdcMem, dat, FONTID_GROUPS, &fontHeight);
				else
					ChangeToFont(hdcMem, dat, FONTID_CONTACTS, &fontHeight);
			}
			else if (cc->type == CLCIT_DIVIDER)
				ChangeToFont(hdcMem, dat, FONTID_DIVIDERS, &fontHeight);
			else if (cc->type == CLCIT_CONTACT && cc->flags & CONTACTF_NOTONLIST)
				ChangeToFont(hdcMem, dat, FONTID_NOTONLIST, &fontHeight);
			else if (cc->type == CLCIT_CONTACT &&
				((cc->flags & CONTACTF_INVISTO && GetRealStatus(cc, status) != ID_STATUS_INVISIBLE) || (cc->flags & CONTACTF_VISTO && GetRealStatus(cc, status) == ID_STATUS_INVISIBLE))) {
				// the contact is in the always visible list and the proto is invisible
				// the contact is in the always invisible and the proto is in any other mode
				ChangeToFont(hdcMem, dat, cc->flags & CONTACTF_ONLINE ? FONTID_INVIS : FONTID_OFFINVIS, &fontHeight);
			}
			else if (cc->type == CLCIT_CONTACT && !(cc->flags & CONTACTF_ONLINE))
				ChangeToFont(hdcMem, dat, FONTID_OFFLINE, &fontHeight);
			else
				ChangeToFont(hdcMem, dat, FONTID_CONTACTS, &fontHeight);
			GetTextExtentPoint32(hdcMem, cc->szText, (int)mir_tstrlen(cc->szText), &textSize);
			width = textSize.cx;
			if (cc->type == CLCIT_GROUP) {
				szCounts = pcli->pfnGetGroupCountsText(dat, cc);
				if (szCounts[0]) {
					GetTextExtentPoint32(hdcMem, _T(" "), 1, &spaceSize);
					ChangeToFont(hdcMem, dat, FONTID_GROUPCOUNTS, &fontHeight);
					GetTextExtentPoint32(hdcMem, szCounts, (int)mir_tstrlen(szCounts), &countsSize);
					width += spaceSize.cx + countsSize.cx;
				}
			}

			if ((style & CLS_CHECKBOXES && cc->type == CLCIT_CONTACT) || (style & CLS_GROUPCHECKBOXES && cc->type == CLCIT_GROUP) || (cc->type == CLCIT_INFO && cc->flags & CLCIIF_CHECKBOX))
				checkboxWidth = dat->checkboxSize + 2;
			else
				checkboxWidth = 0;

			// background
			if (selected) {
				int x = dat->leftMargin + indent * dat->groupIndent + checkboxWidth + dat->iconXSpace - 2;
				ImageList_DrawEx(dat->himlHighlight, 0, hdcMem, x, y, min(width + 5, clRect.right - x), dat->rowHeight, CLR_NONE, CLR_NONE,
					dat->exStyle & CLS_EX_NOTRANSLUCENTSEL ? ILD_NORMAL : ILD_BLEND25);
				SetTextColor(hdcMem, dat->selTextColour);
			}
			else if (hottrack)
				SetHotTrackColour(hdcMem, dat);

			// checkboxes
			if (checkboxWidth) {
				RECT rc;
				HANDLE hTheme = OpenThemeData(hwnd, L"BUTTON");
				rc.left = dat->leftMargin + indent * dat->groupIndent;
				rc.right = rc.left + dat->checkboxSize;
				rc.top = y + ((dat->rowHeight - dat->checkboxSize) >> 1);
				rc.bottom = rc.top + dat->checkboxSize;
				DrawThemeBackground(hTheme, hdcMem, BP_CHECKBOX, cc->flags & CONTACTF_CHECKED ? (hottrack ? CBS_CHECKEDHOT : CBS_CHECKEDNORMAL) : (hottrack ? CBS_UNCHECKEDHOT : CBS_UNCHECKEDNORMAL), &rc, &rc);
				CloseThemeData(hTheme);
			}

			// icon
			if (cc->type == CLCIT_GROUP)
				iImage = cc->group->expanded ? IMAGE_GROUPOPEN : IMAGE_GROUPSHUT;
			else if (cc->type == CLCIT_CONTACT)
				iImage = cc->iImage;
			if (iImage != -1) {
				// this doesnt use CLS_CONTACTLIST since the colour prolly wont match anyway
				COLORREF colourFg = dat->selBkColour;
				int mode = ILD_NORMAL;
				if (hottrack) {
					colourFg = dat->hotTextColour;
				}
				else if (cc->type == CLCIT_CONTACT && cc->flags & CONTACTF_NOTONLIST) {
					colourFg = dat->fontInfo[FONTID_NOTONLIST].colour;
					mode = ILD_BLEND50;
				}
				if (cc->type == CLCIT_CONTACT && dat->showIdle
					&& (cc->flags & CONTACTF_IDLE)
					&& GetRealStatus(cc, ID_STATUS_OFFLINE) != ID_STATUS_OFFLINE)
					mode = ILD_SELECTED;
				ImageList_DrawEx(himlCListClc, iImage, hdcMem, dat->leftMargin + indent * dat->groupIndent + checkboxWidth,
					y + ((dat->rowHeight - 16) >> 1), 0, 0, CLR_NONE, colourFg, mode);
			}

			// text
			if (cc->type == CLCIT_DIVIDER) {
				RECT rc;
				rc.top = y + (dat->rowHeight >> 1);
				rc.bottom = rc.top + 2;
				rc.left = dat->leftMargin + indent * dat->groupIndent;
				rc.right = rc.left + ((clRect.right - rc.left - textSize.cx) >> 1) - 3;
				DrawEdge(hdcMem, &rc, BDR_SUNKENOUTER, BF_RECT);
				TextOut(hdcMem, rc.right + 3, y + ((dat->rowHeight - fontHeight) >> 1), cc->szText,
					(int)mir_tstrlen(cc->szText));
				rc.left = rc.right + 6 + textSize.cx;
				rc.right = clRect.right;
				DrawEdge(hdcMem, &rc, BDR_SUNKENOUTER, BF_RECT);
			}