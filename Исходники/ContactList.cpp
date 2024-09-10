LRESULT CALLBACK ParentSubclassProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	CCList *dat = CWndUserData(hWnd).GetCList();
	switch (Msg) {
	case WM_NOTIFY:
		{
			LPNMHDR pnmh = (LPNMHDR)lParam;
			if (pnmh->hwndFrom == dat->hTreeView) {
				switch (pnmh->code) {
				case TVN_ITEMEXPANDED: // just set an appropriate group image
					{
						LPNMTREEVIEW pnmtv = (LPNMTREEVIEW)lParam;
						TVITEM tvItem;
						tvItem.hItem = pnmtv->itemNew.hItem;
						tvItem.mask = TVIF_HANDLE | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
						tvItem.iImage = tvItem.iSelectedImage = (pnmtv->itemNew.state & TVIS_EXPANDED) ? IMAGE_GROUPOPEN : IMAGE_GROUPSHUT;
						TreeView_SetItem(dat->hTreeView, &tvItem);
					}
					break;
				case TVN_SELCHANGED:
					{
						LPNMTREEVIEW pnmtv = (LPNMTREEVIEW)lParam;
						TREEITEMARRAY OldSelection = dat->SelectedItems;
						for (int i = 0; i < dat->SelectedItems.GetSize(); i++) {
							if (dat->SelectedItems[i] != pnmtv->itemNew.hItem) {
								TreeView_SetItemState(dat->hTreeView, dat->SelectedItems[i], 0, TVIS_SELECTED);
							}
						}
						dat->SelectedItems.RemoveAll();
						if (pnmtv->itemNew.hItem) {
							dat->SelectedItems.AddElem(pnmtv->itemNew.hItem);
							dat->SelectGroups(pnmtv->itemNew.hItem, true);
						}
						NMCLIST nm;
						nm.hdr.code = MCLN_SELCHANGED;
						nm.hdr.hwndFrom = dat->hTreeView;
						nm.hdr.idFrom = GetDlgCtrlID(dat->hTreeView);
						nm.OldSelection = &OldSelection;
						nm.NewSelection = &dat->SelectedItems;
						SendMessage(hWnd, WM_NOTIFY, 0, (LPARAM)&nm);
					}
					break;

				case TVN_DELETEITEM:
					if (dat->Items.GetSize()) { // if Items size = 0, then this TVN_DELETEITEM came after WM_DESTROY, so there is no need to do anything
						LPNMTREEVIEW pnmtv = (LPNMTREEVIEW)lParam;
						TREEITEMARRAY OldSelection = dat->SelectedItems;
						int Index = dat->SelectedItems.Find(pnmtv->itemOld.hItem);
						if (Index != -1)
							dat->SelectedItems.RemoveElem(Index);

						// find an item to pass to SelectGroups()
						HTREEITEM hItem = TreeView_GetNextSibling(dat->hTreeView, pnmtv->itemOld.hItem);
						if (!hItem) {
							hItem = TreeView_GetPrevSibling(dat->hTreeView, pnmtv->itemOld.hItem);
							if (!hItem)
								hItem = TreeView_GetParent(dat->hTreeView, pnmtv->itemOld.hItem);
						}
						if (hItem) // if it wasn't one of the root items
							dat->SelectGroups(hItem, dat->SelectedItems.Find(hItem) != -1);

						NMCLIST nm;
						nm.hdr.code = MCLN_SELCHANGED;
						nm.hdr.hwndFrom = dat->hTreeView;
						nm.hdr.idFrom = GetDlgCtrlID(dat->hTreeView);
						nm.OldSelection = &OldSelection;
						nm.NewSelection = &dat->SelectedItems;
						SendMessage(hWnd, WM_NOTIFY, 0, (LPARAM)&nm);
						dat->Items[pnmtv->itemOld.lParam].hContact = INVALID_CONTACT_ID;
					}
					break;

				case NM_CUSTOMDRAW:
					LPNMTVCUSTOMDRAW lpNMCD = (LPNMTVCUSTOMDRAW)lParam;
					switch (lpNMCD->nmcd.dwDrawStage) {
					case CDDS_PREPAINT: // the control is about to start painting
						return CDRF_NOTIFYITEMDRAW; // instruct the control to return information when it draws items
					case CDDS_ITEMPREPAINT:
						return CDRF_NOTIFYPOSTPAINT;
					case CDDS_ITEMPOSTPAINT:
						RECT rc;
						if (TreeView_GetItemRect(dat->hTreeView, (HTREEITEM)lpNMCD->nmcd.dwItemSpec, &rc, false)) {
							for (int i = 0; i < MAXEXTRAICONS; i++) {
								BYTE nIndex = dat->Items[lpNMCD->nmcd.lItemlParam].ExtraIcons[i];
								if (nIndex != CLC_EXTRAICON_EMPTY) {
									ImageList_DrawEx(dat->ExtraImageList, nIndex, lpNMCD->nmcd.hdc, rc.right - EXTRAICON_XSTEP * (i + 1), rc.top, 0, 0, /*GetSysColor(COLOR_WINDOW)*/CLR_NONE, CLR_NONE, ILD_NORMAL);
								}
							}
						}
						break;
					}
				}
				break;
			}
		}
	}
	return CallWindowProc(dat->OrigParentProc, hWnd, Msg, wParam, lParam);
}