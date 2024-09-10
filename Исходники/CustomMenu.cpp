BOOL CCustomMenu::OnDrawItem(WPARAM wParam,LPARAM lParam)
{
	DRAWITEMSTRUCT	*pDrawItem = NULL;
	HBRUSH			hBrush;
	MENUITEMINFO	mi;
	TCHAR			szMenuString[64];
	RECT			rcText;
	RECT			rcShortcut;
	UINT			MenuState;
	TCHAR			szMenuName[64];
	TCHAR			szMenuShortcut[64];
	TCHAR			*ptr = NULL;
	DWORD			dwPrefixState;
	int				i = 0;

	pDrawItem = (DRAWITEMSTRUCT *)lParam;

	/* Is this item actually a menu? */
	if(pDrawItem->CtlType == ODT_MENU)
	{
		if(pDrawItem->itemAction & ODA_DRAWENTIRE ||
		(pDrawItem->itemAction & ODA_SELECT))
		{
			if(pDrawItem->itemState & ODS_SELECTED)
			{
				/* <---- Item been selected ----> */
				COLORREF	BorderColorBase;
				RECT		rcSelection;

				BorderColorBase = GetSysColor(COLOR_MENUHILIGHT);

				hBrush = CreateSolidBrush(BORDER_SELECTION_COLOUR);

				/* Draw the frame around the menu. */
				FrameRect(pDrawItem->hDC,&pDrawItem->rcItem,hBrush);

				DeleteObject(hBrush);

				rcSelection = pDrawItem->rcItem;

				/* Decrease the width and height of the shaded
				rectangle so that the border will be seen
				around the shading. */
				InflateRect(&rcSelection,-1,-1);

				Gdiplus::SolidBrush SemiTransBrush(Gdiplus::Color(100,GetRValue(BorderColorBase),
					GetGValue(BorderColorBase),GetBValue(BorderColorBase)));

				Gdiplus::Graphics graphics(pDrawItem->hDC);
				graphics.FillRectangle(&SemiTransBrush,rcSelection.left,rcSelection.top,
					rcSelection.right - rcSelection.left,rcSelection.bottom - rcSelection.top);
			}
			else if(!(pDrawItem->itemState & ODS_SELECTED))
			{
				COLORREF	MenuBackColor;

				MenuBackColor = GetSysColor(COLOR_MENU);

				/* <---- Item been deselected ----> */
				hBrush = CreateSolidBrush(MenuBackColor);

				/* Fill the menu item with the backing colour. */
				FillRect(pDrawItem->hDC,&pDrawItem->rcItem,hBrush);

				DeleteObject(hBrush);
			}

			SetBkMode(pDrawItem->hDC,TRANSPARENT);

			MenuState = GetMenuState((HMENU)pDrawItem->hwndItem,pDrawItem->itemID,MF_BYCOMMAND);

			/* A different colour is used for all text on the menu
			when it is disabled. */
			if(MenuState & MF_GRAYED)
				SetTextColor(pDrawItem->hDC,GetSysColor(COLOR_GRAYTEXT));

			/* If this item is a separator, draw in the separator line. */
			if((MenuState & MF_SEPARATOR) && !(MenuState & MF_POPUP)
				|| MenuState == (UINT)-1)
			{
				RECT rcSeparator;

				rcSeparator = pDrawItem->rcItem;

				OffsetRect(&rcSeparator,0,(rcSeparator.bottom - rcSeparator.top) / 2);
				//OffsetRect(&rcSeparator,MENU_TEXT_INDENT_LEFT,(rcSeparator.bottom - rcSeparator.top) / 2);

				DrawEdge(pDrawItem->hDC,&rcSeparator,EDGE_ETCHED,BF_TOP);
			}

			/* If the item is checked, draw a checkmark to the
			left of the menu text. */
			if(MenuState & MF_CHECKED)
			{
				/* Draw a check mark next to the menu. */
				/* SHELLIMAGES_MENUCHECKMARK - Defined within Explorer++ project. */
				ImageList_Draw(himlMenu,21,pDrawItem->hDC,
					pDrawItem->rcItem.left + MENU_ICON_INDENT_LEFT,
					pDrawItem->rcItem.top + MENU_ICON_INDENT_TOP,ILD_NORMAL);
			}

			mi.cbSize	= sizeof(mi);
			mi.fMask	= MIIM_DATA;
			GetMenuItemInfo((HMENU)pDrawItem->hwndItem,pDrawItem->itemID,FALSE,&mi);

			CustomMenuInfo_t *pcmi = NULL;

			pcmi = (CustomMenuInfo_t *)mi.dwItemData;

			if(pcmi->bUseImage)
			{
				ImageList_Draw(himlMenu,pcmi->iImage,pDrawItem->hDC,
					pDrawItem->rcItem.left + MENU_ICON_INDENT_LEFT,
					pDrawItem->rcItem.top + MENU_ICON_INDENT_TOP,ILD_NORMAL);
			}

			GetMenuString((HMENU)pDrawItem->hwndItem,pDrawItem->itemID,
			szMenuString,SIZEOF_ARRAY(szMenuString),MF_BYCOMMAND);

			ptr = szMenuString;

			/* Read out the main part of the menu text. This
			will either be until the end of the string, or until
			a tab character is reached (depending on whether or not
			there is a shortcut string in the menu text). */
			while(*ptr != '\0' && *ptr != '\t')
			{
				szMenuName[i] = *ptr;

				i++;
				ptr++;
			}

			szMenuName[i] = '\0';

			i = 0;

			/* Now, read out the menu shortcut
			text (if any). */
			if(*ptr == '\t')
			{
				ptr++;

				while(*ptr != '\0')
				{
					szMenuShortcut[i] = *ptr;

					i++;
					ptr++;
				}
			}

			szMenuShortcut[i] = '\0';

			/* Check whether or not the accelerator
			mnemonics need to be underlined. */
			if(pDrawItem->itemState & ODS_NOACCEL)
				dwPrefixState = DT_HIDEPREFIX;
			else
				dwPrefixState = 0;

			rcText = pDrawItem->rcItem;
			OffsetRect(&rcText,MENU_TEXT_INDENT_LEFT,0);

			/* Draw the main menu text. */
			DrawText(pDrawItem->hDC,szMenuName,lstrlen(szMenuName),&rcText,
				DT_LEFT|DT_VCENTER|DT_SINGLELINE|DT_EXPANDTABS|dwPrefixState);

			/* The menu text bounding rectangle does not
			extend the full width of the menu. There is a
			small clearance on the right edge to ensure
			all text is drawn well before the end of the menu. */
			rcShortcut = pDrawItem->rcItem;
			InflateRect(&rcShortcut,MENU_TEXT_INDENT_RIGHT,0);

			/* Now draw the menu shortcut text (if any). */
			DrawText(pDrawItem->hDC,szMenuShortcut,lstrlen(szMenuShortcut),&rcShortcut,
				DT_RIGHT|DT_VCENTER|DT_SINGLELINE|DT_HIDEPREFIX);
		}
	}

	return TRUE;
}