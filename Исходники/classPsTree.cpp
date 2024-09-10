void CPsTree::PopupMenu()
{
	HMENU hPopup;
	MENUITEMINFO mii;
	TVHITTESTINFO hti;
	TVITEM tvi;
	POINT pt;
	int iItem, i;

	// init popup menu
	if (!(hPopup = CreatePopupMenu()))
		return;
	ZeroMemory(&mii, sizeof(MENUITEMINFO));
	mii.cbSize = sizeof(mii);
	mii.fMask = MIIM_STRING|MIIM_ID;

	// get cursor postion
	GetCursorPos(&pt);
	hti.pt = pt;
	ScreenToClient(_hWndTree, &hti.pt);

	tvi.mask = TVIF_PARAM|TVIF_CHILDREN;
	// find treeitem under cursor
	TreeView_HitTest(_hWndTree, &hti);
	if (hti.flags & (TVHT_ONITEM|TVHT_ONITEMRIGHT)) {
		tvi.hItem = hti.hItem;
		TreeView_GetItem(_hWndTree, &tvi);

		if (!db_get_b(NULL, MODNAME, SET_PROPSHEET_READONLYLABEL, FALSE)) {
			mii.dwTypeData = TranslateT("Rename Item");
			mii.wID = 32001;
			InsertMenuItem(hPopup, 0, FALSE, &mii);
		}
		
		// do not allow hiding groups
		if (tvi.cChildren) {
			mii.fMask |= MIIM_STATE;
			mii.fState = MFS_DISABLED;
		}
		mii.dwTypeData = TranslateT("Hide Item");
		mii.wID = 32000;
		InsertMenuItem(hPopup, 0, FALSE, &mii);
	}
	else {
		// add hidden items to menu
		mii.wID = 0;
		for (i = 0; i < _numItems; i++) {
			if (!_pItems[i]->Hti()) {
				mii.dwTypeData = _pItems[i]->Label();
				mii.wID = 100 + i;
				InsertMenuItem(hPopup, 0, FALSE, &mii);
			}
		}
		// add headline
		if (mii.wID > 0) {
			mii.fMask |= MIIM_STATE;
			mii.fState = MFS_DISABLED;
			mii.dwTypeData = TranslateT("Show Items:");
			mii.wID = 0;
			InsertMenuItem(hPopup, 0, TRUE, &mii);
			mii.fMask |= MIIM_FTYPE;
			mii.fType = MFT_SEPARATOR;
			InsertMenuItem(hPopup, 1, TRUE, &mii);
			InsertMenuItem(hPopup, ++i, TRUE, &mii);
		}
		mii.fMask &= ~(MIIM_FTYPE|MIIM_STATE);
		mii.dwTypeData = TranslateT("Reset to defaults");
		mii.wID = 32004;
		InsertMenuItem(hPopup, ++i, TRUE, &mii);
	}
	// show the popup menu
	iItem = TrackPopupMenu(hPopup, TPM_RETURNCMD, pt.x, pt.y, 0, _hWndTree, NULL);
	DestroyMenu(hPopup);
	
	switch (iItem) {
		// hide the item
		case 32000:
			HideItem(tvi.lParam);
			break;
		// rename the item
		case 32001:
			BeginLabelEdit(tvi.hItem);
			break;
		// reset current tree
		case 32004:
			DBResetState();
			break;
		// show a hidden item
		default:
			if ((iItem -= 100) >= 0 && ShowItem(iItem, NULL))
				AddFlags(PSTVF_STATE_CHANGED|PSTVF_POS_CHANGED);
			break;
	}
}