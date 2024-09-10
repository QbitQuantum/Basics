/**
 * name:	ProfileList_BeginLabelEdit
 * desc:	create an edit control to edit the label of the selected item
 * param:	pList	 - handle to listview control's info structure
 *			iItem	 - item index
 *			iSubItem - subitem (column) index
 * return:	handle to the edit control
 **/
static HWND ProfileList_BeginLabelEdit(LPLISTCTRL pList, INT iItem, INT iSubItem)
{
	LVITEM lvi;
	LPLCITEM pItem;
	HANDLE hContact;
	RECT rcList;
	
	if (!PtrIsValid(pList)) 
		return NULL;
	if (pList->labelEdit.hEdit)
		ProfileList_EndLabelEdit(pList, FALSE);

	lvi.mask = LVIF_PARAM|LVIF_STATE;
	lvi.stateMask = 0xFFFFFFFF;
	lvi.iItem = iItem;
	lvi.iSubItem = iSubItem;

	if (!ListView_GetItem(pList->hList, &lvi))
		return NULL;

	pItem = (LPLCITEM)lvi.lParam;

	PSGetContact(GetParent(pList->hList), hContact);
			
	// do not edit deviders or protocol based contact information
	if (!(lvi.state & LVIS_SELECTED) || !PtrIsValid(pItem) || (hContact && (pItem->wFlags & CTRLF_HASPROTO))) 
		return NULL;

	ListView_EnsureVisible(pList->hList, iItem, FALSE);
	ListView_GetSubItemRect(pList->hList, iItem, iSubItem, LVIR_BOUNDS, &pList->labelEdit.rcCombo);
		
	if (lvi.iSubItem == 0) {
		RECT rc2;
		
		ListView_GetSubItemRect(pList->hList, iItem, 1, LVIR_BOUNDS, &rc2);
		pList->labelEdit.rcCombo.right = rc2.left;
	}
	GetClientRect(pList->hList, &rcList);
	pList->labelEdit.rcCombo.right = min(pList->labelEdit.rcCombo.right, rcList.right);
	pList->labelEdit.rcCombo.left = max(pList->labelEdit.rcCombo.left, rcList.left);
	InflateRect(&pList->labelEdit.rcCombo, -1, -1);

	// create the button control for the combobox
	if (!iSubItem && pItem->idstrList) {
		pList->labelEdit.hBtn = CreateWindowEx(WS_EX_NOPARENTNOTIFY, UINFOBUTTONCLASS, NULL, 
					WS_VISIBLE|WS_CHILD|MBS_DOWNARROW,
					pList->labelEdit.rcCombo.right - (pList->labelEdit.rcCombo.bottom - pList->labelEdit.rcCombo.top), pList->labelEdit.rcCombo.top,
					pList->labelEdit.rcCombo.bottom - pList->labelEdit.rcCombo.top,
					pList->labelEdit.rcCombo.bottom - pList->labelEdit.rcCombo.top,
					pList->hList, NULL, ghInst, NULL);
		if (pList->labelEdit.hBtn) {
			SetWindowLongPtr(pList->labelEdit.hBtn, GWLP_ID, BTN_EDIT);
			pList->labelEdit.rcCombo.right -= pList->labelEdit.rcCombo.bottom - pList->labelEdit.rcCombo.top;
		}
	}
	else {
		pList->labelEdit.rcCombo.bottom = 3 * pList->labelEdit.rcCombo.bottom - 2 * pList->labelEdit.rcCombo.top;
		if (rcList.bottom < pList->labelEdit.rcCombo.bottom) {
			OffsetRect(&pList->labelEdit.rcCombo, 0, rcList.bottom - pList->labelEdit.rcCombo.bottom - 2);
		}
	}
	// create the edit control
	pList->labelEdit.hEdit = CreateWindowEx(WS_EX_NOPARENTNOTIFY|WS_EX_CLIENTEDGE,
				_T("EDIT"),
				(!iSubItem && pItem->idstrList && pItem->iListItem > 0 && pItem->iListItem < pItem->idstrListCount) 
					? pItem->idstrList[pItem->iListItem].ptszTranslated
					: (iSubItem >= 0 && iSubItem < 2 && pItem->pszText[iSubItem] && *pItem->pszText[iSubItem])
						? pItem->pszText[iSubItem] 
						: _T(""), 
						WS_VISIBLE|WS_CHILD|(iSubItem ? (WS_VSCROLL|ES_MULTILINE|ES_AUTOVSCROLL) : ES_AUTOHSCROLL),
				pList->labelEdit.rcCombo.left, pList->labelEdit.rcCombo.top,
				pList->labelEdit.rcCombo.right - pList->labelEdit.rcCombo.left,
				pList->labelEdit.rcCombo.bottom - pList->labelEdit.rcCombo.top,
				pList->hList, NULL, ghInst, NULL);
	if (!pList->labelEdit.hEdit)
		return NULL;
	SendMessage(pList->labelEdit.hEdit, WM_SETFONT, (WPARAM)(pList->hFont), 0);
	SendMessage(pList->labelEdit.hEdit, EM_SETSEL, 0, (LPARAM)-1);
	SetUserData(pList->labelEdit.hEdit, pList);
	pList->labelEdit.dropDown.iItem = pItem->iListItem;
	pList->labelEdit.iItem = iItem;
	pList->labelEdit.iSubItem = iSubItem;
	pList->labelEdit.iTopIndex = ListView_GetTopIndex(pList->hList);
	pList->labelEdit.pItem = pItem;
	SetFocus(pList->labelEdit.hEdit);
	OldEditProc = (WNDPROC)SetWindowLongPtr(pList->labelEdit.hEdit, GWLP_WNDPROC, (LONG_PTR)ProfileList_LabelEditProc);
	return pList->labelEdit.hEdit;
}