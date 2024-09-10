void ThumbInfo::UpdateContent()
{
	bmpContent.allocate(szSize.cx, szSize.cy);

	HFONT hOldFont;
	SIZE  size;
	RECT  rc, rcText;
	DWORD oldColor;
	int   oldBkMode, index = 0;// nStatus;
	UINT	fStyle = ILD_NORMAL;

	HDC		hdcDraw = bmpContent.getDC();
	SetRect(&rc, 0, 0, szSize.cx, szSize.cy);

	if (nullptr != hBmpBackground) {
		RECT rcBkgnd;
		SetRect(&rcBkgnd, 0, 0, szSize.cx, szSize.cy);
		if (nullptr != hLTEdgesPen)
			InflateRect(&rcBkgnd, -1, -1);
		int width = rcBkgnd.right - rcBkgnd.left;
		int height = rcBkgnd.bottom - rcBkgnd.top;

		BITMAP bmp;
		GetObject(hBmpBackground, sizeof(bmp), &bmp);
		HDC hdcBmp = CreateCompatibleDC(hdcDraw);
		HBITMAP hbmTmp = (HBITMAP)SelectObject(hdcBmp, hBmpBackground);

		int maxx = (0 != (nBackgroundBmpUse & CLBF_TILEH) ? rcBkgnd.right : rcBkgnd.left + 1);
		int maxy = (0 != (nBackgroundBmpUse & CLBF_TILEV) ? rcBkgnd.bottom : rcBkgnd.top + 1);
		int destw, desth;
		switch (nBackgroundBmpUse & CLBM_TYPE) {
		case CLB_STRETCH:
			if (0 != (nBackgroundBmpUse & CLBF_PROPORTIONAL)) {
				if (width * bmp.bmHeight < height * bmp.bmWidth) {
					desth = height;
					destw = desth * bmp.bmWidth / bmp.bmHeight;
				}
				else {
					destw = width;
					desth = destw * bmp.bmHeight / bmp.bmWidth;
				}
			}
			else {
				destw = width;
				desth = height;
			}
			break;

		case CLB_STRETCHH:
			destw = width;
			if (0 != (nBackgroundBmpUse & CLBF_PROPORTIONAL))
				desth = destw * bmp.bmHeight / bmp.bmWidth;
			else
				desth = bmp.bmHeight;
			break;

		case CLB_STRETCHV:
			desth = height;
			if (0 != (nBackgroundBmpUse & CLBF_PROPORTIONAL))
				destw = desth * bmp.bmWidth / bmp.bmHeight;
			else
				destw = bmp.bmWidth;
			break;

		default:    //clb_topleft
			destw = bmp.bmWidth;
			desth = bmp.bmHeight;
			break;
		}
		SetStretchBltMode(hdcBmp, STRETCH_HALFTONE);

		for (int x = rcBkgnd.left; x < maxx; x += destw)
			for (int y = rcBkgnd.top; y < maxy; y += desth)
				StretchBlt(hdcDraw, x, y, destw, desth, hdcBmp, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);

		SelectObject(hdcBmp, hbmTmp);
		DeleteDC(hdcBmp);
	}
	else FillRect(hdcDraw, &rc, hBkBrush);

	if (nullptr != hLTEdgesPen) {
		HPEN  hOldPen = (HPEN)SelectObject(hdcDraw, hLTEdgesPen);

		MoveToEx(hdcDraw, 0, 0, nullptr);
		LineTo(hdcDraw, szSize.cx, 0);
		MoveToEx(hdcDraw, 0, 0, nullptr);
		LineTo(hdcDraw, 0, szSize.cy);

		SelectObject(hdcDraw, hRBEdgesPen);

		MoveToEx(hdcDraw, 0, szSize.cy - 1, nullptr);
		LineTo(hdcDraw, szSize.cx - 1, szSize.cy - 1);
		MoveToEx(hdcDraw, szSize.cx - 1, szSize.cy - 1, nullptr);
		LineTo(hdcDraw, szSize.cx - 1, 0);

		SelectObject(hdcDraw, hOldPen);
	}

	bmpContent.setAlpha(btAlpha);

	ImageList_GetIconSize_my(himlMiranda, size);

	oldBkMode = SetBkMode(hdcDraw, TRANSPARENT);

	if (!db_get_b(hContact, "CList", "NotOnList", 0)) {
		char *szProto = GetContactProto(hContact);
		if (nullptr != szProto) {
			int nStatus = Proto_GetStatus(szProto);
			int nContactStatus = db_get_w(hContact, szProto, "Status", ID_STATUS_OFFLINE);
			int nApparentMode = db_get_w(hContact, szProto, "ApparentMode", 0);

			if ((nStatus == ID_STATUS_INVISIBLE && nApparentMode == ID_STATUS_ONLINE) ||
				(nStatus != ID_STATUS_INVISIBLE && nApparentMode == ID_STATUS_OFFLINE)) {
				if (ID_STATUS_OFFLINE == nContactStatus)
					index = FLT_FONTID_OFFINVIS;
				else {
					index = FLT_FONTID_INVIS;
					if (fcOpt.bShowIdle && db_get_dw(hContact, szProto, "IdleTS", 0))
						fStyle |= ILD_BLEND50;
				}
			}
			else if (ID_STATUS_OFFLINE == nContactStatus) {
				index = FLT_FONTID_OFFLINE;
			}
			else {
				index = FLT_FONTID_CONTACTS;
				if (fcOpt.bShowIdle && db_get_dw(hContact, szProto, "IdleTS", 0))
					fStyle |= ILD_BLEND50;
			}
		}
	}
	else {
		index = FLT_FONTID_NOTONLIST;
		fStyle |= ILD_BLEND50;
	}

	oldColor = SetTextColor(hdcDraw, tColor[index]);

	HICON icon = ImageList_GetIcon(himlMiranda, iIcon, ILD_NORMAL);
	MyBitmap bmptmp(size.cx, size.cy);
	bmptmp.DrawIcon(icon, 0, 0);//bmpContent
	BLENDFUNCTION blend;
	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;
	blend.SourceConstantAlpha = (fStyle&ILD_BLEND50) ? 128 : 255;
	blend.AlphaFormat = AC_SRC_ALPHA;
	AlphaBlend(hdcDraw, 2, (szSize.cy - size.cx) / 2, bmptmp.getWidth(), bmptmp.getHeight(), bmptmp.getDC(), 0, 0, bmptmp.getWidth(), bmptmp.getHeight(), blend);
	DestroyIcon(icon);

	SetRect(&rcText, 0, 0, szSize.cx, szSize.cy);
	rcText.left += size.cx + 4;

	hOldFont = (HFONT)SelectObject(hdcDraw, hFont[index]);

	SIZE szText;
	GetTextExtentPoint32(hdcDraw, ptszName, (int)mir_wstrlen(ptszName), &szText);
	SetTextColor(hdcDraw, bkColor);

	// simple border
	bmpContent.DrawText(ptszName, rcText.left - 1, (rcText.top + rcText.bottom - szText.cy) / 2);
	bmpContent.DrawText(ptszName, rcText.left + 1, (rcText.top + rcText.bottom - szText.cy) / 2);
	bmpContent.DrawText(ptszName, rcText.left, (rcText.top + rcText.bottom - szText.cy) / 2 - 1);
	bmpContent.DrawText(ptszName, rcText.left, (rcText.top + rcText.bottom - szText.cy) / 2 + 1);

	// blurred border
	// bmpContent.DrawText(ptszName, rcText.left, (rcText.top + rcText.bottom - szText.cy)/2, 3);

	// text itself
	SetTextColor(hdcDraw, tColor[index]);
	bmpContent.DrawText(ptszName, rcText.left, (rcText.top + rcText.bottom - szText.cy) / 2);

	SelectObject(hdcDraw, hOldFont);

	SetTextColor(hdcDraw, oldColor);
	SetBkMode(hdcDraw, oldBkMode);

	SetWindowLongPtr(hwnd, GWL_EXSTYLE, GetWindowLongPtr(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED);

	GetWindowRect(hwnd, &rc);
	POINT ptDst = { rc.left, rc.top };
	POINT ptSrc = { 0, 0 };

	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;
	blend.SourceConstantAlpha = 255;
	blend.AlphaFormat = AC_SRC_ALPHA;

	UpdateLayeredWindow(hwnd, nullptr, &ptDst, &szSize, bmpContent.getDC(), &ptSrc, 0xffffffff, &blend, ULW_ALPHA);
}