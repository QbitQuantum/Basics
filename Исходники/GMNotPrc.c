PGPError PGPgmExport 
PGPgmDefaultNotificationProc (
		HGROUPMAN	hGM, 
		LPARAM		lParam) 
{
	PGROUPMAN	pGM = (PGROUPMAN)hGM;

	HTLITEM		hFocused;
	BOOL		bMultiple;
	INT			i, iField;
	POINT		pt;

	if (!hGM) return kPGPError_BadParams;

	switch (((LPNM_TREELIST)lParam)->hdr.code) {

	case TLN_SELCHANGED :
		bMultiple = (((LPNM_TREELIST)lParam)->flags & TLC_MULTIPLE);
		hFocused = ((LPNM_TREELIST)lParam)->itemNew.hItem;
		GMSetFocus (pGM, hFocused, bMultiple);
		((LPNM_TREELIST)lParam)->flags = GMSelectedFlags (pGM);
		break;

	case TLN_ITEMDBLCLICKED :
		if (PGPgmIsActionEnabled (hGM, GM_PROPERTIES)) {
			PGPgmPerformAction (hGM, GM_LOCATEKEYS);
			PGPkmPerformAction (pGM->hKM, KM_PROPERTIES); 
		}
		break;

	case TLN_DRAGGEDOVER :
		hFocused = ((LPNM_TREELIST)lParam)->itemNew.hItem;
		if (GMFocusedItem (pGM) != hFocused) {
			GMSetFocus (pGM, hFocused, FALSE);
			((LPNM_TREELIST)lParam)->flags = GMSelectedFlags (pGM);

			ImageList_DragLeave (pGM->hWndParent);
			InvalidateRect (pGM->hWndTree, NULL, TRUE);
			UpdateWindow (pGM->hWndTree);
			ImageList_DragEnter (pGM->hWndParent, 0, 0);
		}
		pt = ((LPNM_TREELIST)lParam)->ptDrag;
		MapWindowPoints (pGM->hWndTree, pGM->hWndParent, &pt, 1);
		ImageList_DragMove (pt.x + pGM->iXCursorOffset, 
							pt.y + pGM->iYCursorOffset);
		break;

	case TLN_AUTOSCROLLED :
		ImageList_DragLeave (pGM->hWndParent);
		InvalidateRect (pGM->hWndTree, NULL, TRUE);
		UpdateWindow (pGM->hWndTree);
		ImageList_DragEnter (pGM->hWndParent, 0, 0);
		break;

	case TLN_KEYDOWN :
		switch (((TL_KEYDOWN*)lParam)->wVKey) {
		case VK_DELETE :
			GMDeleteObject (pGM);
			break;
		}
		break;

	case TLN_CONTEXTMENU :
		((LPNM_TREELIST)lParam)->flags = GMSelectedFlags (pGM);
		break;

	case TLN_HEADERREORDERED :
		sReorderColumns (pGM);
		break;

	case TLN_BEGINDRAG :
		pGM->hFocusedItemDragging = GMFocusedItem (pGM);
		GMEnableDropTarget (pGM->pDropTarget, FALSE);
		sBeginDrag (pGM);
		break;

	case TLN_DROP :
		if (((LPNM_TREELIST)lParam)->index) {
			GMAddSelectedToFocused (pGM);
		}
		sEndDrag (pGM);
		GMEnableDropTarget (pGM->pDropTarget, TRUE);
		GMSetFocus (pGM, pGM->hFocusedItemDragging, FALSE);
		break;

	case TLN_HEADERCLICKED :
		i = pGM->lKeyListSortField;
		iField = pGM->wColumnField[((LPNM_TREELIST)lParam)->index];
		switch (iField) {
			case GMI_NAME : 
				if (pGM->lKeyListSortField == kPGPUserIDOrdering)
					i = kPGPReverseUserIDOrdering; 
				else 
					i = kPGPUserIDOrdering; 
				break;

			case GMI_VALIDITY :
				if (pGM->lKeyListSortField == kPGPValidityOrdering)
					i = kPGPReverseValidityOrdering;
				else
					i = kPGPValidityOrdering;
				break;

			default : break;
		}
		if (i != pGM->lKeyListSortField) {
			pGM->lKeyListSortField = i;
			TreeList_DeleteTree (pGM->hWndTree, FALSE);
			InvalidateRect (pGM->hWndTree, NULL, TRUE);
			UpdateWindow (pGM->hWndTree);
			GMSortGroupSet (pGM);
			GMLoadGroupsIntoTree (pGM, TRUE, FALSE, FALSE);
			InvalidateRect (pGM->hWndTree, NULL, TRUE);
		}
		break;
	}
	return 0;
}