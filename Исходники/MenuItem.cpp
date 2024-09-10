void MenuItem::Paint(HDC hDC)
{
	RECT rect;

	COLORREF cr0 = (COLORREF)-1;
	bool lit = false;
	StyleItem *pSI = &mStyle.MenuFrame;

	if (m_bActive && 0 == (m_isNOP & (MI_NOP_TEXT | MI_NOP_SEP)) && (0 == (m_isNOP & MI_NOP_DISABLED) || m_pSubMenu))
	{
		// draw hilite bar
		GetItemRect(&rect);
		pSI = &mStyle.MenuHilite;
		MakeStyleGradient(hDC, &rect, pSI, pSI->bordered);
		cr0 = SetTextColor(hDC, pSI->TextColor);
		lit = true;
	}
	else
		if (m_isNOP & MI_NOP_DISABLED)
		{
			cr0 = SetTextColor(hDC, mStyle.MenuFrame.disabledColor);
		}

	//dbg_printf("Menu separator style is: %s",Settings_menuSeparatorStyle);

	// draw separator
	if (m_isNOP & MI_NOP_LINE)
	{
		int x, y = m_nTop + m_nHeight / 2;
		// Noccy: Looks like we have to remove some pixels here to prevent it from overwriting the right border.
		int left  = m_nLeft + ((Settings_menuFullSeparatorWidth)?1:mStyle.MenuSepMargin) - 1;
		int right = m_nLeft + m_nWidth - ((Settings_menuFullSeparatorWidth)?1:mStyle.MenuSepMargin);
		// int dist = (m_nWidth + 1) / 2 - ((Settings_menuFullSeparatorWidth==true)?mStyle.MenuFrame.borderWidth:mStyle.MenuSepMargin);
		int dist = (m_nWidth+1) / 2 - ((Settings_menuFullSeparatorWidth)?1:mStyle.MenuSepMargin);
		COLORREF c = mStyle.MenuSepColor;
		COLORREF cs = pSI->ShadowColor;

		if (pSI->ShadowXY)
		{
			int yS = y + pSI->ShadowY;
			int leftS  = left + pSI->ShadowX;
			int rightS = right + pSI->ShadowX;
			if (0 == stricmp(Settings_menuSeparatorStyle,"gradient"))
			{
				// Gradient shadow
				for (x = 0; x <= dist; ++x)
				{
					int pos, hue = x * 255 / dist;
					pos = leftS + x;
					SetPixel(hDC, pos, yS, mixcolors(cs, GetPixel(hDC, pos, y), hue));
					pos = rightS - x;
					SetPixel(hDC, pos, yS, mixcolors(cs, GetPixel(hDC, pos, y), hue));
				}
			}
			else
				if (0 == stricmp(Settings_menuSeparatorStyle,"flat"))
				{
					// Flat shadow
					for (x = 0; x <= dist; ++x)
					{
						int pos;
						pos = leftS + x;
						SetPixel(hDC, pos, yS, cs);
						pos = rightS - x;
						SetPixel(hDC, pos, yS, cs);
					}
				}
				else
					if (0 == stricmp(Settings_menuSeparatorStyle,"bevel"))
					{
						// Bevel shadow is simply none...
					}
		}
		if (0 == stricmp(Settings_menuSeparatorStyle,"gradient"))
		{
			for (x = 0; x <= dist; ++x)
			{
				int pos, hue = x * 255 / dist;
				pos = left + x;
				SetPixel(hDC, pos, y, mixcolors(c, GetPixel(hDC, pos, y), hue));
				pos = right - x;
				SetPixel(hDC, pos, y, mixcolors(c, GetPixel(hDC, pos, y), hue));
			}
		}
		else
			if (0 == stricmp(Settings_menuSeparatorStyle,"flat"))
			{
				for (x = 0; x <= dist; ++x)
				{
					int pos; //, hue = x * 255 / dist;
					pos = left + x;
					SetPixel(hDC, pos, y, c);
					pos = right - x;
					SetPixel(hDC, pos, y, c);
				}
			}
			else
				if (0 == stricmp(Settings_menuSeparatorStyle,"bevel"))
				{
					for (x = 0; x <= dist; ++x)
					{
						int pos;
						pos = left + x;
						SetPixel(hDC, pos, y, mixcolors(0x00000000, GetPixel(hDC, pos, y), 160));
						pos = right - x;
						SetPixel(hDC, pos, y, mixcolors(0x00000000, GetPixel(hDC, pos, y), 160));
						pos = left + x;
						SetPixel(hDC, pos, y+1, mixcolors(0x00FFFFFF, GetPixel(hDC, pos, y+1), 160));
						pos = right - x;
						SetPixel(hDC, pos, y+1, mixcolors(0x00FFFFFF, GetPixel(hDC, pos, y+1), 160));
					}
				}
	}

	int iconSize = m_pMenu->m_iconSize;
	if (-2 == iconSize) iconSize = MenuInfo.nIconSize;
	GetTextRect(&rect, iconSize);

	// [load and ]draw menu item icon
	if (iconSize)
	{
		bool bSmallIcon = (16 >= iconSize);
		// load menu item icon
		if (NULL == m_hIcon || bSmallIcon != m_bSmallIcon)
		{
			DestroyIcon(m_hIcon), m_hIcon = NULL;
			m_bSmallIcon = bSmallIcon;
			switch (m_iconMode)
			{
			case IM_PIDL:
			{
				const _ITEMIDLIST *pidl = (MENUITEM_ID_SF == m_ItemID) ?
										  ((SpecialFolderItem*)this)->check_pidl() : m_pidl;

				if (pidl)
				{
					SHFILEINFO sfi;
					HIMAGELIST sysimgl = (HIMAGELIST)SHGetFileInfo((LPCSTR)pidl, 0, &sfi, sizeof(SHFILEINFO), SHGFI_PIDL | SHGFI_SYSICONINDEX | (bSmallIcon ? SHGFI_SMALLICON : SHGFI_LARGEICON));
					if (sysimgl) m_hIcon = ImageList_GetIcon(sysimgl, sfi.iIcon, ILD_NORMAL);
				}
			}
			break;

			case IM_TASK:
			{
				const struct tasklist *tl = (struct tasklist *)m_im_stuff;
				m_hIcon = CopyIcon(bSmallIcon ? tl->icon : tl->icon_big);
			}
			break;

			case IM_PATH:
				char *icon = (char *)m_im_stuff;
				char *path = strrchr(icon, ',');
				int idx;
				if (path)
					idx = atoi(path + 1), *path = 0;
				else
					idx = 0;
				if (bSmallIcon)
					ExtractIconEx(icon, idx, NULL, &m_hIcon, 1);
				else
					ExtractIconEx(icon, idx, &m_hIcon, NULL, 1);
				if (path) *path = ',';
				break;
			}
		}

		// draw menu item icon
		if (m_hIcon)
		{
			int top = rect.top + (m_nHeight - iconSize) / 2;
			int adjust = (MenuInfo.nItemIndent[iconSize] - iconSize) / 2;
			int left = ((DT_LEFT == FolderItem::m_nBulletPosition) ? rect.right : m_nLeft) + adjust;
			drawIco(left, top, iconSize, m_hIcon, hDC, !m_bActive, Settings_menuIconSaturation, Settings_menuIconHue);
		}
	}


	/*
		Noccy: Added DT_NOPREFIX to BBDrawText to prevent ampersand (&) to be interpreted as
		a hotkey.
		Note: Reverted.
	*/

	// draw menu item text
	const char *title = GetDisplayString();

	if (0 == (m_ItemID & (~MENUITEM_ID_CI & (MENUITEM_ID_CIInt|MENUITEM_ID_CIStr))) || Settings_menusBroamMode)
		BBDrawText(hDC, title, -1, &rect, mStyle.MenuFrame.Justify | DT_MENU_STANDARD, pSI);
	else
		if (m_ItemID != MENUITEM_ID_CIStr)
			BBDrawText(hDC, title, -1, &rect, DT_CENTER | DT_MENU_STANDARD, pSI);

	// set back previous textColor
	if ((COLORREF)-1 != cr0) SetTextColor(hDC, cr0);

	if (m_isChecked) // draw check-mark
	{
		pSI = &mStyle.MenuHilite;
		bool pr = pSI->parentRelative;
		if (lit != pr) pSI = &mStyle.MenuFrame;

		int x, y = m_nTop + m_nHeight / 2;
		if ((FolderItem::m_nBulletPosition == DT_RIGHT) == (0 == (MENUITEM_ID_FOLDER & m_ItemID)))
			x = m_nLeft + m_nWidth - MenuInfo.nItemIndent[iconSize] / 2 - 1;
		else
			x = m_nLeft + MenuInfo.nItemIndent[iconSize] / 2;

		const int r = 3;
		rect.left   = x - r;
		rect.right  = x + r;
		rect.top    = y - r;
		rect.bottom = y + r;

		if (pr) MakeGradient(hDC, rect, B_SOLID, pSI->TextColor, 0, false, BEVEL_FLAT, 0, 0, 0, 0);
		else MakeStyleGradient(hDC, &rect, pSI, false);
	}
}