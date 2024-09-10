static LRESULT CALLBACK MsgTreeSubclassProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	CMsgTree *dat = CWndUserData(GetParent(hWnd)).GetMsgTree();
	switch (Msg) {
	case UM_MSGTREE_UPDATE: // returns TRUE if updated
		{
			bool Modified = dat->MsgTreePage.GetModified();
			TCString WndTitle;
			if (Modified) {
				WndTitle.GetBuffer(256);
				HWND hCurWnd = hWnd;
				do {
					hCurWnd = GetParent(hCurWnd);
				} while (hCurWnd && !GetWindowText(hCurWnd, WndTitle, 256));
				WndTitle.ReleaseBuffer();
			}
			if (!Modified || MessageBox(GetParent(hWnd), TCString(TranslateT("You've made changes to multiple message trees at a time.\r\nDo you want to leave changes in \"")) + WndTitle + TranslateT("\" dialog?\r\nPress Yes to leave changes in this dialog, or No to discard its changes and save changes of the other message tree instead."), WndTitle + _T(" - ") + TranslateT("New Away System"), MB_ICONQUESTION | MB_YESNO) == IDNO) {
				COptItem_TreeCtrl *TreeCtrl = dat->GetTreeCtrl();
				TCString OldTitle, OldMsg, NewTitle, NewMsg;
				int OldOrder = TreeCtrl->IDToOrder(TreeCtrl->GetSelectedItemID(GetParent(hWnd)));
				if (OldOrder != -1) {
					CBaseTreeItem* ItemOld = (OldOrder <= TREECTRL_ROOTORDEROFFS) ? (CBaseTreeItem*)&TreeCtrl->RootItems[ROOT_ORDER_TO_INDEX(OldOrder)] : (CBaseTreeItem*)&TreeCtrl->Value[OldOrder];
					OldTitle = ItemOld->Title;
					if (!(ItemOld->Flags & TIF_ROOTITEM))
						OldMsg = ((CTreeItem*)ItemOld)->User_Str1;
				}
				dat->UpdateLock++;
				dat->MsgTreePage.DBToMemToPage();
				dat->UpdateLock--;
				NMMSGTREE nm = { 0 };
				int Order = TreeCtrl->IDToOrder(TreeCtrl->GetSelectedItemID(GetParent(hWnd)));
				if (Order != -1) {
					nm.ItemNew = (Order <= TREECTRL_ROOTORDEROFFS) ? (CBaseTreeItem*)&TreeCtrl->RootItems[ROOT_ORDER_TO_INDEX(Order)] : (CBaseTreeItem*)&TreeCtrl->Value[Order];
					NewTitle = nm.ItemNew->Title;
					if (!(nm.ItemNew->Flags & TIF_ROOTITEM))
						NewMsg = ((CTreeItem*)nm.ItemNew)->User_Str1;
				}
				if (OldTitle.IsEmpty())
					OldTitle = _T(""); // to be sure that NULL will be equal to "" in the latter comparisons
				if (OldMsg.IsEmpty())
					OldMsg = _T("");
				if (NewTitle.IsEmpty())
					NewTitle = _T("");
				if (NewMsg.IsEmpty())
					NewMsg = _T("");

				if (OldTitle != (const TCHAR*)NewTitle || OldMsg != (const TCHAR*)NewMsg) {
					// probably it's better to leave nm.ItemOld = NULL, to prevent accidental rewriting of it with old data from an edit control etc.
					nm.hdr.code = MTN_SELCHANGED;
					nm.hdr.hwndFrom = hWnd;
					nm.hdr.idFrom = GetDlgCtrlID(hWnd);
					SendMessage(GetParent(hWnd), WM_NOTIFY, 0, (LPARAM)&nm);
				}
				return true;
			}
		}
		return false;

	case WM_KEYDOWN:
		switch (wParam) {
		case VK_DELETE:
			dat->DeleteSelectedItem();
			break;
		case VK_INSERT:
			dat->AddMessage();
			break;
		}
		break;

	case WM_RBUTTONDOWN:
		SetFocus(hWnd);
		{
			TVHITTESTINFO hitTest;
			hitTest.pt.x = (short)LOWORD(lParam);
			hitTest.pt.y = (short)HIWORD(lParam);
			TreeView_HitTest(hWnd, &hitTest);
			if (hitTest.hItem && hitTest.flags & TVHT_ONITEM)
				TreeView_SelectItem(hWnd, hitTest.hItem);

			return DefWindowProc(hWnd, Msg, wParam, lParam);
		}
		break;

	case WM_CONTEXTMENU:
		{
			TVHITTESTINFO ht;
			ht.pt.x = GET_X_LPARAM(lParam);
			ht.pt.y = GET_Y_LPARAM(lParam);
			TVITEM tvi = { 0 };
			if (ht.pt.x == -1 && ht.pt.y == -1) { // use selected item 
				if (tvi.hItem = TreeView_GetSelection(hWnd)) {
					TreeView_EnsureVisible(hWnd, tvi.hItem);
					RECT rc;
					TreeView_GetItemRect(hWnd, tvi.hItem, &rc, true);
					ht.pt.x = rc.left;
					ht.pt.y = rc.bottom;
				}
			}
			else {
				ScreenToClient(hWnd, &ht.pt);
				TreeView_HitTest(hWnd, &ht);
				if (ht.hItem && ht.flags & TVHT_ONITEM) {
					tvi.hItem = ht.hItem;
				}
			}
			if (tvi.hItem) {
				COptItem_TreeCtrl *TreeCtrl = dat->GetTreeCtrl();
				tvi.mask = TVIF_HANDLE | TVIF_PARAM;
				TreeView_GetItem(hWnd, &tvi);
				int Order = TreeCtrl->IDToOrder(tvi.lParam);
				if (Order >= 0) {
					HMENU hMenu;
					if (TreeCtrl->Value[Order].Flags & TIF_GROUP)
						hMenu = LoadMenu(g_hInstance, MAKEINTRESOURCE(IDR_MSGTREE_CATEGORYMENU));
					else
						hMenu = LoadMenu(g_hInstance, MAKEINTRESOURCE(IDR_MSGTREE_MESSAGEMENU));

					_ASSERT(hMenu);
					HMENU hPopupMenu = GetSubMenu(hMenu, 0);
					TranslateMenu(hPopupMenu);
					ClientToScreen(hWnd, &ht.pt);
					struct
					{
						int ItemID, IconID;
					}
					MenuItems[] = {
						IDM_MSGTREEMENU_NEWMESSAGE, IMGLIST_NEWMESSAGE,
						IDM_MSGTREEMENU_NEWCATEGORY, IMGLIST_NEWCATEGORY,
						IDM_MSGTREEMENU_DELETE, IMGLIST_DELETE
					};
					MENUITEMINFO mii = { 0 };
					mii.cbSize = sizeof(mii);
					mii.fMask = MIIM_BITMAP | MIIM_DATA | MIIM_STATE | MIIM_CHECKMARKS;
					mii.hbmpItem = HBMMENU_CALLBACK;
					int i;
					for (i = 0; i < _countof(MenuItems); i++) { // set icons
						mii.dwItemData = MenuItems[i].IconID;
						SetMenuItemInfo(hPopupMenu, MenuItems[i].ItemID, false, &mii);
					}
					mii.fMask = MIIM_STATE;
					mii.fState = MFS_CHECKED;
					for (i = 0; i < _countof(SettingsList); i++) // set checkmarks
						if (TreeCtrl->Value[Order].ID == dat->MsgTreePage.GetValue(SettingsList[i].DBSetting))
							SetMenuItemInfo(hPopupMenu, SettingsList[i].MenuItemID, false, &mii);

					int MenuResult = TrackPopupMenu(hPopupMenu, TPM_RIGHTBUTTON | TPM_RETURNCMD, ht.pt.x, ht.pt.y, 0, hWnd, NULL);
					switch (MenuResult) {
					case IDM_MSGTREEMENU_NEWMESSAGE:
						dat->AddMessage();
						break;
					case IDM_MSGTREEMENU_NEWCATEGORY:
						dat->AddCategory();
						break;
					case IDM_MSGTREEMENU_RENAME:
						TreeView_EditLabel(hWnd, tvi.hItem);
						break;
					case IDM_MSGTREEMENU_DELETE:
						dat->DeleteSelectedItem();
						break;
					case IDR_MSGTREEMENU_DEF_ONL:
					case IDR_MSGTREEMENU_DEF_AWAY:
					case IDR_MSGTREEMENU_DEF_NA:
					case IDR_MSGTREEMENU_DEF_OCC:
					case IDR_MSGTREEMENU_DEF_DND:
					case IDR_MSGTREEMENU_DEF_FFC:
					case IDR_MSGTREEMENU_DEF_INV:
					case IDR_MSGTREEMENU_DEF_OTP:
					case IDR_MSGTREEMENU_DEF_OTL:
						for (int i = 0; i < _countof(SettingsList); i++) {
							if (SettingsList[i].MenuItemID == MenuResult) {
								dat->SetDefMsg(SettingsList[i].Status, tvi.lParam);
								break;
							}
						}
					}
					DestroyMenu(hMenu);
					return 0;
				}
			}
		}
		break;

	case WM_MEASUREITEM:
		{
			LPMEASUREITEMSTRUCT lpmi = (LPMEASUREITEMSTRUCT)lParam;
			if (lpmi->CtlType == ODT_MENU) {
				lpmi->itemWidth = max(0, GetSystemMetrics(SM_CXSMICON) - GetSystemMetrics(SM_CXMENUCHECK) + 4);
				lpmi->itemHeight = GetSystemMetrics(SM_CYSMICON) + 2;
				return true;
			}
		}
		break;
	
	case WM_DRAWITEM:
		{
			LPDRAWITEMSTRUCT dis = (LPDRAWITEMSTRUCT)lParam;
			if (dis->CtlType == ODT_MENU) {
				ImageList_DrawEx(dat->hImageList, dis->itemData, dis->hDC, 2, (dis->rcItem.bottom + dis->rcItem.top - GetSystemMetrics(SM_CYSMICON)) / 2 + 1, 0, 0, GetSysColor(COLOR_WINDOW), CLR_NONE, ILD_NORMAL);
				return true;
			}
		} 
		break;
	}
	return CallWindowProc(dat->OrigTreeViewProc, hWnd, Msg, wParam, lParam);
}