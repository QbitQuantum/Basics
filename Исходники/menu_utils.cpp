static HMENU BuildRecursiveMenu(HMENU hMenu, TMO_IntMenuItem *pRootMenu, WPARAM wParam, LPARAM lParam)
{
	if (pRootMenu == NULL)
		return NULL;

	TIntMenuObject *pmo = pRootMenu->parent;

	if (pRootMenu->mi.root == NULL)
		while (GetMenuItemCount(hMenu) > 0)
			DeleteMenu(hMenu, 0, MF_BYPOSITION);

	for (TMO_IntMenuItem *pmi = pRootMenu; pmi != NULL; pmi = pmi->next) {
		TMO_MenuItem *mi = &pmi->mi;
		if (mi->flags & CMIF_HIDDEN)
			continue;

		if (pmo->CheckService != NULL) {
			TCheckProcParam CheckParam;
			CheckParam.wParam = wParam;
			CheckParam.lParam = lParam;
			CheckParam.MenuItemOwnerData = pmi->pUserData;
			CheckParam.MenuItemHandle = pmi;
			if (CallService(pmo->CheckService, (WPARAM)&CheckParam, 0) == false)
				continue;
		}

		// if we have to check & apply database settings
		if (!(mi->flags & CMIF_SYSTEM) && pmo->m_bUseUserDefinedItems) {
			char szModule[256], szSetting[256];
			mir_snprintf(szModule, "%s_Items", pmo->pszName);

			char menuItemName[256];
			GetMenuItemName(pmi, menuItemName, sizeof(menuItemName));

			// check if it visible
			mir_snprintf(szSetting, "%s_visible", menuItemName);
			if (!db_get_b(NULL, szModule, szSetting, 1))
				continue;

			// mi.name.t
			mir_snprintf(szSetting, "%s_name", menuItemName);
			TCHAR *tszCustomName = db_get_tsa(NULL, szModule, szSetting);
			if (tszCustomName != NULL) {
				mir_free(pmi->CustomName);
				pmi->CustomName = tszCustomName;
			}

			mir_snprintf(szSetting, "%s_pos", menuItemName);
			int pos = db_get_dw(NULL, szModule, szSetting, -1);
			if (pos == -1) {
				db_set_dw(NULL, szModule, szSetting, mi->position);
				if (pmi->submenu.first)
					mi->position = 0;
			}
			else mi->position = pos;
		}

		int i = WhereToPlace(hMenu, mi);

		MENUITEMINFO mii = { 0 };
		mii.cbSize = sizeof(mii);
		mii.dwItemData = (LPARAM)pmi;
		mii.fMask = MIIM_DATA | MIIM_ID | MIIM_STRING;
		if (pmi->iconId != -1) {
			mii.fMask |= MIIM_BITMAP;
			if (IsWinVerVistaPlus() && IsThemeActive()) {
				if (pmi->hBmp == NULL)
					pmi->hBmp = ConvertIconToBitmap(pmi->parent->m_hMenuIcons, pmi->iconId);
				mii.hbmpItem = pmi->hBmp;
			}
			else mii.hbmpItem = HBMMENU_CALLBACK;
		}

		mii.fMask |= MIIM_STATE;
		mii.fState = ((pmi->mi.flags & CMIF_GRAYED) ? MFS_GRAYED : MFS_ENABLED);
		mii.fState |= ((pmi->mi.flags & CMIF_CHECKED) ? MFS_CHECKED : MFS_UNCHECKED);
		if (pmi->mi.flags & CMIF_DEFAULT)
			mii.fState |= MFS_DEFAULT;

		mii.dwTypeData = (pmi->CustomName) ? pmi->CustomName : mi->name.t;

		// it's a submenu
		if (pmi->submenu.first) {
			mii.fMask |= MIIM_SUBMENU;
			mii.hSubMenu = CreatePopupMenu();

#ifdef PUTPOSITIONSONMENU
			if (GetKeyState(VK_CONTROL) & 0x8000) {
				TCHAR str[256];
				mir_sntprintf(str, _T("%s (%d, id %x)"), mi->name.a, mi->position, mii.dwItemData);
				mii.dwTypeData = str;
			}
#endif

			InsertMenuItemWithSeparators(hMenu, i, &mii);
			BuildRecursiveMenu(mii.hSubMenu, pmi->submenu.first, wParam, lParam);
		}
		else {
			mii.wID = pmi->iCommand;

#ifdef PUTPOSITIONSONMENU
			if (GetKeyState(VK_CONTROL) & 0x8000) {
				TCHAR str[256];
				mir_sntprintf(str, _T("%s (%d, id %x)"), mi->name.a, mi->position, mii.dwItemData);
				mii.dwTypeData = str;
			}
#endif

			if (pmo->onAddService != NULL)
				if (CallService(pmo->onAddService, (WPARAM)&mii, (LPARAM)pmi) == FALSE)
					continue;

			InsertMenuItemWithSeparators(hMenu, i, &mii);
		}
	}

	return hMenu;
}