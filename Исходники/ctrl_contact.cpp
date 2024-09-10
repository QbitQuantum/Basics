/**
 * name:	CtrlContactWndProc
 * desc:	window procedure for the extended combobox class
 * param:	hwnd	- handle to a extended combobox window
 *			msg		- message to handle
 *			wParam	- message specific
 *			lParam	- message specific
 * return:	message specific
 **/
static LRESULT CALLBACK CtrlContactWndProc(HWND hwnd, UINT msg,	WPARAM wParam, LPARAM lParam) 
{
	LPCBEX	cbex = (LPCBEX)GetWindowLongPtr(hwnd, 0);

	switch (msg) {

	/**
	* name:	WM_NCCREATE
	* desc:	is called to initiate the window creation
	* param:	wParam - not used
	*			lParam - pointer to a CREATESTRUCT
	*
	* return:	FALSE on error, TRUE if initialisation was ok
	**/
	case WM_NCCREATE:
	{
		LPCREATESTRUCT cs = (LPCREATESTRUCT)lParam;

		if (!(cbex = (LPCBEX)mir_calloc(1*sizeof(CBEX))))
			return FALSE;
		SetWindowLongPtr(hwnd, 0, (LONG_PTR)cbex);
		cbex->bLocked = 1;
		cbex->hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
		cbex->hInstance = cs->hInstance;
		cbex->iSelectedItem = -1;
		cbex->rect.left = cs->x;
		cbex->rect.top = cs->y;
		cbex->rect.right = cs->x + cs->cx;
		cbex->rect.bottom = cs->y + cs->cy;
		return TRUE;
	}

	/**
		* name:	WM_NCCREATE
		* desc:	is called to create all subitems
		* param:	wParam - not used
		*			lParam - not used
		*
		* return:	FALSE on error, TRUE if initialisation was ok
		**/
	case WM_CREATE:
	{
		WORD wHeight = (WORD)(cbex->rect.bottom - cbex->rect.top);
		WORD wWidth = 130;
		WORD x = 0;

		if (!(cbex->hBtnEdit = CreateWindowEx(WS_EX_NOPARENTNOTIFY,
				UINFOBUTTONCLASS, 
				_T("none"),
				WS_VISIBLE|WS_CHILD|WS_TABSTOP, 0, 0,
				wWidth, wHeight,
				hwnd,
				NULL,
				cbex->hInstance, NULL))) {
			cbex->bLocked = 0;
			return FALSE;
		}
		x += wWidth + 2;
		wWidth = wHeight;
		if (!(cbex->hBtnMenu = CreateWindowEx(WS_EX_NOPARENTNOTIFY,
				UINFOBUTTONCLASS,
				NULL,
				WS_VISIBLE|WS_CHILD|WS_TABSTOP|MBS_PUSHBUTTON|MBS_DOWNARROW,
				x, 0,
				wWidth, wHeight,
				hwnd,
				NULL,
				cbex->hInstance, NULL))) {
			DestroyWindow(cbex->hBtnEdit);
			cbex->bLocked = 0;
			return FALSE;
		}
		x += wWidth + 2;
		wWidth = (WORD)(cbex->rect.right - cbex->rect.left - x - (2 * (wHeight + 2)));
		if (!(cbex->hEdit = CreateWindowEx(WS_EX_CLIENTEDGE,
				_T("Edit"), 
				NULL,
				WS_VISIBLE|WS_CHILD|WS_TABSTOP|ES_AUTOHSCROLL,
				x, 1,
				wWidth,	wHeight - 2,
				hwnd,
				NULL,
				cbex->hInstance, NULL))) {
			DestroyWindow(cbex->hBtnEdit);
			DestroyWindow(cbex->hBtnMenu);
			cbex->bLocked = 0;
			return FALSE;
		}
		x += wWidth + 2;
		wWidth = wHeight;
		if (!(cbex->hBtnAdd = CreateWindowEx(WS_EX_NOPARENTNOTIFY,
				UINFOBUTTONCLASS,
				NULL,
				WS_VISIBLE|WS_CHILD|WS_TABSTOP|MBS_FLAT,
				x, 0,
				wWidth, wHeight,
				hwnd,
				NULL,
				cbex->hInstance, NULL))) {
			DestroyWindow(cbex->hBtnEdit);
			DestroyWindow(cbex->hBtnMenu);
			DestroyWindow(cbex->hEdit);
			cbex->bLocked = 0;
			return FALSE;
		}
		x += wWidth + 2;
		if (!(cbex->hBtnDel = CreateWindowEx(WS_EX_NOPARENTNOTIFY,
				UINFOBUTTONCLASS,
				NULL,
				WS_VISIBLE|WS_CHILD|WS_TABSTOP|MBS_FLAT,
				x, 0,
				wWidth, wHeight,
				hwnd,
				NULL,
				cbex->hInstance, NULL))) {
			DestroyWindow(cbex->hBtnEdit);
			DestroyWindow(cbex->hBtnMenu);
			DestroyWindow(cbex->hEdit);
			DestroyWindow(cbex->hBtnAdd);
			cbex->bLocked = 0;
			return FALSE;
		}

		// set ids
		SetWindowLongPtr(cbex->hBtnEdit, GWLP_ID, BTN_EDIT);
		SetWindowLongPtr(cbex->hBtnMenu, GWLP_ID, BTN_MENU);
		SetWindowLongPtr(cbex->hEdit, GWLP_ID, EDIT_VALUE);
		SetWindowLongPtr(cbex->hBtnAdd, GWLP_ID, BTN_ADD);
		SetWindowLongPtr(cbex->hBtnDel, GWLP_ID, BTN_DEL);
		// set fonts & maximum edit control charachters
		SendMessage(cbex->hEdit, WM_SETFONT, (WPARAM)cbex->hFont, NULL);
		SendMessage(cbex->hEdit, EM_LIMITTEXT, (WPARAM)MAXDATASIZE, NULL);
		// add tooltips
		SendMessage(cbex->hBtnMenu, BUTTONADDTOOLTIP, (WPARAM)TranslateT("Choose the item to display"), MBBF_TCHAR);
		SendMessage(cbex->hBtnEdit, BUTTONADDTOOLTIP, (WPARAM)TranslateT("Edit the currently displayed item"), MBBF_TCHAR);
		SendMessage(cbex->hBtnAdd, BUTTONADDTOOLTIP, (WPARAM)TranslateT("Add a new custom item"), MBBF_TCHAR);
		SendMessage(cbex->hBtnDel, BUTTONADDTOOLTIP, (WPARAM)TranslateT("Delete the selected item"), MBBF_TCHAR);
		// reload icons
		CtrlContactWndProc(hwnd, WM_SETICON, NULL, NULL);
		cbex->bLocked = 0;
		return TRUE;
	}

	/**
		* name:	WM_DESTROY
		* desc:	default destroy message, so clear up memory
		* param:	wParam - not used
		*			lParam - not used
		* return:	return value of DefWindowProc
		**/
	case WM_DESTROY:
		CtrlContactWndProc(hwnd, CBEXM_DELALLITEMS, NULL, NULL);
		DestroyWindow(cbex->hBtnEdit);
		DestroyWindow(cbex->hBtnMenu);
		DestroyWindow(cbex->hBtnAdd);
		DestroyWindow(cbex->hBtnDel);
		DestroyWindow(cbex->hEdit);
		MIR_FREE(cbex);
		break;

	/**
		* name:	WM_CTLCOLOREDIT
		* desc:	is called on a paint message for a dialog item to determine its colour scheme
		* param:	wParam - pointer to a HDC
		*			lParam - pointer to a HWND
		* return:	a brush
		**/
	case WM_CTLCOLOREDIT:
		if (!db_get_b(NULL, MODNAME, SET_PROPSHEET_SHOWCOLOURS, 1) || (HWND)lParam != cbex->hEdit || !cbex->pItems || cbex->iSelectedItem < 0) 
			break;
		return Ctrl_SetTextColour((HDC)wParam, cbex->pItems[cbex->iSelectedItem].wFlags);

	case WM_CTLCOLORSTATIC:
		if ((HWND)lParam == cbex->hEdit)
			return (INT_PTR)GetSysColor(COLOR_WINDOW);
		return FALSE;
	/**
		* name:	WM_SETICON
		* desc:	updates the icons of this control
		* param:	wParam - not used
		*			lParam - not used
		* return:	always 0
		**/
	case WM_SETICON:
	{
		HICON hIcon = IcoLib_GetIcon(ICO_BTN_ADD);
		SendMessage(cbex->hBtnAdd, BM_SETIMAGE, IMAGE_ICON, (LPARAM)hIcon);
		SetWindowText(cbex->hBtnAdd, (hIcon ? _T("") : _T("+")));

		hIcon = IcoLib_GetIcon(ICO_BTN_DELETE);
		SendMessage(cbex->hBtnDel, BM_SETIMAGE, IMAGE_ICON, (LPARAM)hIcon);
		SetWindowText(cbex->hBtnDel, (hIcon ? _T("") : _T("-")));

		if (cbex->pItems && cbex->numItems > 0) {
			for (int i = 0; i < cbex->numItems; i++)
				cbex->pItems[i].hIcon = IcoLib_GetIcon(cbex->pItems[i].pszIcon);

			if (cbex->iSelectedItem >= 0 && cbex->iSelectedItem < cbex->numItems)
				SendMessage(cbex->hBtnEdit, BM_SETIMAGE, IMAGE_ICON, (LPARAM)cbex->pItems[cbex->iSelectedItem].hIcon);
		}
		return 0;
	}

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		/**
		* name:	BTN_MENU
		* desc:	the button to dropdown the list to show all items is pressed
		**/
		case BTN_MENU:
			if (HIWORD(wParam) == BN_CLICKED) {
				POINT pt = { 0, 0 };
				RECT rc;
				int i, nItems;
				HMENU hMenu;

				if (!(hMenu = CreatePopupMenu())) return 0;
				SetFocus((HWND)lParam);

				MENUITEMINFO mii = { 0 };
				mii.cbSize = sizeof(mii);
				mii.fMask = MIIM_ID|MIIM_STRING|MIIM_FTYPE|MIIM_STATE;
				mii.fType = MFT_STRING;

				// insert the items
				for (i = nItems = 0; i < cbex->numItems; i++) {
					if ((cbex->pItems[i].wFlags & CBEXIF_DELETED) || *cbex->pItems[i].szCat == 0) continue;
					mii.fState = (cbex->pItems[i].pszVal && *cbex->pItems[i].pszVal) ? MFS_CHECKED : MFS_UNCHECKED;
					mii.wID = CBEXM_MENIITEMFIRST + i;
					mii.dwTypeData = cbex->pItems[i].szCat;
					if (!InsertMenuItem(hMenu, i, TRUE, &mii)) {
						DestroyMenu(hMenu);
						return 0;
					}
					nItems++;
				}
				// add separator between default and custom items
				if (nItems > 3) {
					mii.fMask = MIIM_FTYPE;
					mii.fType = MFT_SEPARATOR;
					mii.wID = 0;
					mii.dwItemData = 0;
					InsertMenuItem(hMenu, 3, TRUE, &mii);
				}
				ClientToScreen((HWND)lParam, &pt);
				GetClientRect((HWND)lParam, &rc);
				i = TrackPopupMenuEx(hMenu, TPM_RIGHTALIGN|TPM_RETURNCMD, pt.x + rc.right, pt.y + rc.bottom, hwnd, NULL);
				SendMessage(cbex->hBtnMenu, BM_SETCHECK, NULL, NULL);
				if (i >= CBEXM_MENIITEMFIRST && i < CBEXM_MENIITEMFIRST + cbex->numItems) {
					CtrlContactWndProc(hwnd, CBEXM_SETCURSEL, (WPARAM)i - CBEXM_MENIITEMFIRST, NULL);
				}
				DestroyMenu(hMenu);
				return 0;
			}
			break;

		/**
			* name:	BTN_ADD
			* desc:	the button to add a new entry is pressed
			**/
		case BTN_ADD:
			if (HIWORD(wParam) == BN_CLICKED) {
				DLGPROC dlgProc;
				WORD dlgID;
				TCHAR szCat[MAX_CAT] = { 0 };
				TCHAR szVal[MAXDATASIZE] = { 0 };
				CBEXITEM cbi;
				HWND hDlgDetails;

				SetFocus((HWND)lParam);
				if (!(hDlgDetails = GetParent(GetParent(hwnd)))) return 1;
				if (SendMessage(hDlgDetails, PSM_ISLOCKED, NULL, NULL)) return 0;
						
				switch (GetWindowLongPtr(hwnd, GWLP_ID)) {
					case EDIT_PHONE:
						dlgID = IDD_ADDPHONE;
						dlgProc = DlgProc_Phone;
						cbi.pszIcon = ICO_BTN_CUSTOMPHONE;
						break;
					case EDIT_EMAIL:
						dlgID = IDD_ADDEMAIL;
						dlgProc = DlgProc_EMail;
						cbi.pszIcon = ICO_BTN_EMAIL;
						break;
					default:
						return 1;
				}
							
				cbi.iItem = -1;
				cbi.wMask = CBEXIM_CAT|CBEXIM_VAL|CBEXIM_FLAGS|CBEXIM_ICONTEXT;
				cbi.pszCat = szCat;
				cbi.pszVal = szVal;
				cbi.ccCat = MAX_CAT;
				cbi.ccVal = MAXDATASIZE;
				cbi.wFlags = 0;
				cbi.dwID = 0;

				if (DialogBoxParam(ghInst, MAKEINTRESOURCE(dlgID), GetParent(hwnd), dlgProc, (LPARAM)&cbi) == IDOK) {
					MCONTACT hContact = NULL;
							
					SendMessage(hDlgDetails, PSM_GETCONTACT, NULL, (LPARAM)&hContact);
					if (hContact) cbi.wFlags |= CTRLF_HASCUSTOM;
					cbi.wFlags |= CTRLF_CHANGED;
					if (SendMessage(hwnd, CBEXM_ADDITEM, NULL, (LPARAM)&cbi) > CB_ERR) {
						SendMessage(hDlgDetails, PSM_CHANGED, NULL, NULL);
						cbex->bIsChanged = TRUE;
						SendMessage(hwnd, CBEXM_SETCURSEL, cbex->numItems - 1, NULL);
					}
				}
				return 0;
			}
			break;

		/**
			* name:	BTN_EDIT
			* desc:	the button to edit an existing entry is pressed
			**/
		case BTN_EDIT:
			if (HIWORD(wParam) == BN_CLICKED) {
				DLGPROC dlgProc;
				WORD dlgID;
				TCHAR szCat[MAX_CAT] = { 0 };
				TCHAR szVal[MAXDATASIZE] = { 0 };
				CBEXITEM cbi;
				HWND hDlgDetails;

				SetFocus((HWND)lParam);
				if (!(hDlgDetails = GetParent(GetParent(hwnd)))) return 1;
				if (SendMessage(hDlgDetails, PSM_ISLOCKED, NULL, NULL)) return 0;
				if (!cbex->pItems || cbex->iSelectedItem == -1) return 0;

				switch (GetWindowLongPtr(hwnd, GWLP_ID)) {
					case EDIT_PHONE:
						dlgID = IDD_ADDPHONE;
						dlgProc = DlgProc_Phone;
						break;
					case EDIT_EMAIL:
						dlgID = IDD_ADDEMAIL;
						dlgProc = DlgProc_EMail;
						break;
					default:
						return 1;
				}
				cbi.iItem = cbex->iSelectedItem;
				cbi.dwID = 0;
				cbi.wMask = CBEXIM_CAT|CBEXIM_VAL|CBEXIM_FLAGS;
				cbi.pszCat = szCat;
				cbi.pszVal = szVal;
				cbi.ccCat = MAX_CAT;
				cbi.ccVal = MAXDATASIZE;
				if (!CtrlContactWndProc(hwnd, CBEXM_GETITEM, NULL, (LPARAM)&cbi)) {
					MsgErr(hwnd, LPGENT("CRITICAL: Unable to edit current entry!\nThis should not happen!"));
					return 1;
				}

				if (DialogBoxParam(ghInst, MAKEINTRESOURCE(dlgID), GetParent(hwnd), dlgProc, (LPARAM)&cbi) == IDOK) {
					MCONTACT hContact;

					SendMessage(hDlgDetails, PSM_GETCONTACT, NULL, (LPARAM)&hContact);
					if (hContact) cbi.wFlags |= CTRLF_HASCUSTOM;
					cbi.wFlags |= CTRLF_CHANGED;
					SendMessage(hwnd, CBEXM_SETITEM, NULL, (LPARAM)&cbi);
					SendMessage(hDlgDetails, PSM_CHANGED, NULL, NULL);
					cbex->bIsChanged = TRUE;
				}
				return 0;
			}
			break;

		/**
			* name:	BTN_DEL
			* desc:	the button to delete an existing entry is pressed
			**/
		case BTN_DEL:
			if (HIWORD(wParam) == BN_CLICKED) {
				HWND hDlgDetails;
				MSGBOX mBox;
				TCHAR szMsg[MAXDATASIZE];
					
				SetFocus((HWND)lParam);
				if (!(hDlgDetails = GetParent(GetParent(hwnd))) ||
						SendMessage(hDlgDetails, PSM_ISLOCKED, NULL, NULL) ||
						!cbex->pItems ||
						cbex->iSelectedItem < 0 ||
						cbex->iSelectedItem >= cbex->numItems ||
						FAILED(mir_sntprintf(szMsg, TranslateT("Do you really want to delete the current selected item?\n\t%s\n\t%s"),
						cbex->pItems[cbex->iSelectedItem].szCat, cbex->pItems[cbex->iSelectedItem].pszVal))
			)
				{
						return 1;
				}
				mBox.cbSize = sizeof(MSGBOX);
				mBox.hParent = hDlgDetails;
				mBox.hiLogo = IcoLib_GetIcon(ICO_DLG_PHONE);
				mBox.uType = MB_YESNO|MB_ICON_QUESTION|MB_NOPOPUP;
				mBox.ptszTitle = TranslateT("Delete");
				mBox.ptszMsg = szMsg;
				if (IDYES == MsgBoxService(NULL, (LPARAM)&mBox)) {
					// clear value for standard entry
					if (cbex->pItems[cbex->iSelectedItem].wFlags & CBEXIF_CATREADONLY) {
						MIR_FREE(cbex->pItems[cbex->iSelectedItem].pszVal);
						SetWindowText(cbex->hEdit, _T(""));
						cbex->pItems[cbex->iSelectedItem].wFlags &= ~CBEXIF_SMS;
						cbex->pItems[cbex->iSelectedItem].wFlags |= CTRLF_CHANGED;
					}
					// clear values for customized database entry
					else 
					if (cbex->pItems[cbex->iSelectedItem].dwID != 0) {
						MIR_FREE(cbex->pItems[cbex->iSelectedItem].pszVal);
						*cbex->pItems[cbex->iSelectedItem].szCat = 0;
						cbex->pItems[cbex->iSelectedItem].wFlags |= CTRLF_CHANGED|CBEXIF_DELETED;
						CtrlContactWndProc(hwnd, CBEXM_SETCURSEL, cbex->iSelectedItem - 1, FALSE);
					}
					// delete default entry
					else
						CtrlContactWndProc(hwnd, CBEXM_DELITEM, NULL, cbex->iSelectedItem);

					SendMessage(hDlgDetails, PSM_CHANGED, NULL, NULL);
					cbex->bIsChanged = TRUE;
				}
				return 0;
			}
			break;

		/**
			* name:	EDIT_VALUE
			* desc:	the edit control wants us to act
			**/
		case EDIT_VALUE:
			switch (HIWORD(wParam)) {
				case EN_UPDATE:
				{
					TCHAR szVal[MAXDATASIZE] = { 0 };
					int ccVal;
					MCONTACT hContact;
					HWND hDlgDetails = GetParent(GetParent(hwnd));
							
					EnableWindow(cbex->hBtnDel, GetWindowTextLength(cbex->hEdit) > 0);

					if (SendMessage(hDlgDetails, PSM_ISLOCKED, NULL, NULL) ||
						cbex->bLocked || 
						!cbex->pItems || 
						cbex->iSelectedItem < 0 || 
						cbex->iSelectedItem >= cbex->numItems) return 1;

					// get the edit control's text value and check it for syntax
					switch (GetWindowLongPtr(hwnd, GWLP_ID)) {
						case EDIT_PHONE:
						{
							int errorPos;
							TCHAR szEdit[MAXDATASIZE];

							if (ccVal = GetWindowText(cbex->hEdit, szEdit, _countof(szEdit))) {
								if (!(ccVal = CheckPhoneSyntax(szEdit, szVal, MAXDATASIZE, errorPos)) || errorPos > -1) {
									SetWindowText(cbex->hEdit, szVal);
									SendMessage(cbex->hEdit, EM_SETSEL, errorPos, errorPos);
								}
							}
							break;
						}
						case EDIT_EMAIL:
							ccVal = GetWindowText(cbex->hEdit, szVal, _countof(szVal));
							break;
						default:
							ccVal = GetWindowText(cbex->hEdit, szVal, _countof(szVal));
							break;
					}
							
					SendMessage(hDlgDetails, PSM_GETCONTACT, NULL, (LPARAM)&hContact);
					if ((cbex->pItems[cbex->iSelectedItem].wFlags & CTRLF_CHANGED) && !(hContact && (cbex->pItems[cbex->iSelectedItem].wFlags & CTRLF_HASCUSTOM))) return 0;
							
					if (*szVal == 0 || !cbex->pItems[cbex->iSelectedItem].pszVal || mir_tstrcmp(szVal, cbex->pItems[cbex->iSelectedItem].pszVal)) {
						cbex->pItems[cbex->iSelectedItem].wFlags |= CTRLF_CHANGED;
						cbex->pItems[cbex->iSelectedItem].wFlags |= (hContact ? CTRLF_HASCUSTOM : CTRLF_HASPROTO);
						cbex->bIsChanged = TRUE;
						InvalidateRect((HWND)lParam, NULL, TRUE);
						SendMessage(hDlgDetails, PSM_CHANGED, NULL, NULL);
					}
					return 0;
				}
				case EN_KILLFOCUS:
				{
					int ccText;
							
					if (!cbex->pItems || cbex->iSelectedItem < 0 || cbex->iSelectedItem >= cbex->numItems) return 1;
					if (!(cbex->pItems[cbex->iSelectedItem].wFlags & CTRLF_CHANGED)) return 0;

					if ((ccText = GetWindowTextLength(cbex->hEdit)) <= 0) {
						if (cbex->pItems[cbex->iSelectedItem].wFlags & CBEXIF_CATREADONLY) {
							MIR_FREE(cbex->pItems[cbex->iSelectedItem].pszVal);
							SetWindowText(cbex->hEdit, _T(""));
							cbex->pItems[cbex->iSelectedItem].wFlags &= ~CBEXIF_SMS;
						}
						else
							CtrlContactWndProc(hwnd, CBEXM_DELITEM, NULL, cbex->iSelectedItem);
						SendMessage(GetParent(GetParent(hwnd)), PSM_CHANGED, NULL, NULL);
						cbex->bIsChanged = TRUE;
					}
					else
					if (cbex->pItems[cbex->iSelectedItem].pszVal = (LPTSTR)mir_realloc(cbex->pItems[cbex->iSelectedItem].pszVal, (ccText + 2) * sizeof(TCHAR))) {
						cbex->pItems[cbex->iSelectedItem].pszVal[ccText + 1] = 0;
						GetWindowText(cbex->hEdit, cbex->pItems[cbex->iSelectedItem].pszVal, ccText + 1);
					}
					return 0;
				}
			}
			break;
		}
		break;

	/**
		* name:	CBEXM_ADDITEM
		* desc:	add a item to the control
		* param:	wParam - not used
		*			lParam - (LPCBEXITEM)&item
		* return:	CB_ERR on failure, new item index if successful
		**/
	case CBEXM_ADDITEM:
	{
		LPCBEXITEM	pItem = (LPCBEXITEM)lParam;

		if (!pItem) return FALSE;

		// if an item with the id of pItem exists, change it instead of adding a new one
		// but only if it has not been changed by the user yet.
		if ((pItem->wMask & CBEXIM_ID) && cbex->pItems && pItem->dwID != 0) {
			int iIndex;
				
			for (iIndex = 0; iIndex < cbex->numItems; iIndex++) {
				if (cbex->pItems[iIndex].dwID == pItem->dwID) {
					pItem->iItem = iIndex;
					if (cbex->pItems[iIndex].wFlags & CTRLF_CHANGED)
						pItem->wFlags |= CTRLF_CHANGED;
					else
						CtrlContactWndProc(hwnd, CBEXM_SETITEM, 0, lParam);
					return iIndex;
				}
			}
		}

		// add a new item to the combobox
		if (!(cbex->pItems = (LPCBEXITEMINTERN)mir_realloc(cbex->pItems, (cbex->numItems + 1) * sizeof(CBEXITEMINTERN)))) {
			cbex->numItems = 0;
			return CB_ERR;
		}
		
		// set the ID
		cbex->pItems[cbex->numItems].dwID = (pItem->wMask & CBEXIM_ID) ? pItem->dwID : 0;

		// set category string
		if (!pItem->pszCat || !pItem->pszCat[0] || !mir_tstrncpy(cbex->pItems[cbex->numItems].szCat, pItem->pszCat, MAX_CAT)) {
			mir_sntprintf(cbex->pItems[cbex->numItems].szCat, _T("%s %d"), TranslateT("Other"), ++cbex->numOther);
		}

		// set value string
		if ((pItem->wMask & CBEXIM_VAL) && pItem->pszVal && pItem->pszVal[0])
			cbex->pItems[cbex->numItems].pszVal = mir_tstrdup(pItem->pszVal);
		else
			cbex->pItems[cbex->numItems].pszVal = NULL;
		// set icon
		if ((pItem->wMask & CBEXIM_ICONTEXT) && pItem->pszIcon) {
			cbex->pItems[cbex->numItems].pszIcon = pItem->pszIcon;
			cbex->pItems[cbex->numItems].hIcon = IcoLib_GetIcon(pItem->pszIcon);
		}
		// set flags
		cbex->pItems[cbex->numItems].wFlags = (pItem->wMask & CBEXIM_CAT) ? pItem->wFlags : 0;

		cbex->numItems++;
		return cbex->numItems;
	}

	/**
		* name:	CBEXM_SETITEM
		* desc:	Set an item's information of the control.
		*			If iItem member of CBEXITEM is -1, the currently selected item is changed.
		* param:	wParam - not used
		*			lParam - (LPCBEXITEM)&item
		* return:	CB_ERR on failure, new item index if successful
		**/
	case CBEXM_SETITEM:
	{
		LPCBEXITEM	pItem = (LPCBEXITEM)lParam;

		if (!PtrIsValid(pItem) || !pItem->wMask || !PtrIsValid(cbex->pItems)) return FALSE;
		if (pItem->iItem == -1) pItem->iItem = cbex->iSelectedItem;
		if (pItem->iItem < 0 || pItem->iItem >= cbex->numItems) return FALSE;

		// set new category string
		if (pItem->wMask & CBEXIM_CAT) {
			// set category string
			if (!pItem->pszCat || !pItem->pszCat[0] || !mir_tstrncpy(cbex->pItems[pItem->iItem].szCat, pItem->pszCat, _countof(cbex->pItems[pItem->iItem].szCat))) 
				mir_sntprintf(cbex->pItems[pItem->iItem].szCat, _T("%s %d"), TranslateT("Other"), ++cbex->numOther);
			if (pItem->iItem == cbex->iSelectedItem)
				SetWindowText(cbex->hBtnEdit, cbex->pItems[pItem->iItem].szCat);
		}
		// set new value
		if (pItem->wMask & CBEXIM_VAL) {
			MIR_FREE(cbex->pItems[pItem->iItem].pszVal);
			if (pItem->pszVal && pItem->pszVal[0])
				cbex->pItems[pItem->iItem].pszVal = mir_tstrdup(pItem->pszVal);
			if (pItem->iItem == cbex->iSelectedItem)
				SetWindowText(cbex->hEdit, cbex->pItems[pItem->iItem].pszVal ? cbex->pItems[pItem->iItem].pszVal : _T(""));
		}

		// set icon
		if ((pItem->wMask & CBEXIM_ICONTEXT) && pItem->pszIcon) {
			cbex->pItems[pItem->iItem].pszIcon = pItem->pszIcon;
			cbex->pItems[pItem->iItem].hIcon = IcoLib_GetIcon(pItem->pszIcon);
			if (pItem->iItem == cbex->iSelectedItem)
				SendMessage(cbex->hBtnEdit, BM_SETIMAGE, IMAGE_ICON, (LPARAM)cbex->pItems[pItem->iItem].hIcon);
		}
		if (pItem->wMask & CBEXIM_FLAGS) {
			cbex->pItems[pItem->iItem].wFlags = pItem->wFlags;
			CtrlContactWndProc(hwnd, CBEXM_ENABLEITEM, NULL, NULL);
		}
		return TRUE;
	}

	/**
		* name:	CBEXM_GETITEM
		* desc:	Get an item from the control.
		*			If iItem member of CBEXITEM is -1, the currently selected item is returned.
		* param:	wParam - not used
		*			lParam - (LPCBEXITEM)&item
		* return:	CB_ERR on failure, new item index if successful
		**/
	case CBEXM_GETITEM:
	{
		LPCBEXITEM	pItem = (LPCBEXITEM)lParam;

		if (!pItem || !cbex->pItems) return FALSE;
			
		// try to find item by id
		if ((pItem->wMask & CBEXIM_ID) && pItem->dwID != 0) {
			int i;

			for (i = 0; i < cbex->numItems; i++) {
				if (cbex->pItems[i].dwID == pItem->dwID)
					break;
			}
			pItem->iItem = i;
		}
		else
		if (pItem->iItem == -1) pItem->iItem = cbex->iSelectedItem;
		if (pItem->iItem < 0 || pItem->iItem >= cbex->numItems) return FALSE;
			
		// return only currently selected itemindex
		if (!pItem->wMask) return TRUE;
		// return the unique id
		if (pItem->wMask & CBEXIM_ID) 
			pItem->dwID = cbex->pItems[pItem->iItem].dwID;
		// return category string
		if ((pItem->wMask & CBEXIM_CAT) && pItem->pszCat) {
			if (*cbex->pItems[pItem->iItem].szCat != 0)
				mir_tstrncpy(pItem->pszCat, cbex->pItems[pItem->iItem].szCat, pItem->ccCat - 1);
			else
				*pItem->pszCat = 0;
		}
		// return value string
		if ((pItem->wMask & CBEXIM_VAL) && pItem->pszVal) {
			if (cbex->pItems[pItem->iItem].pszVal)
				mir_tstrncpy(pItem->pszVal, cbex->pItems[pItem->iItem].pszVal, pItem->ccVal - 1);
			else
				*pItem->pszVal = 0;
		}
		// return the icon
		if (pItem->wMask & CBEXIM_ICONTEXT)
			pItem->pszIcon = cbex->pItems[pItem->iItem].pszIcon;
		// return the flags
		if (pItem->wMask & CBEXIM_FLAGS)
			pItem->wFlags = cbex->pItems[pItem->iItem].wFlags;
		return TRUE;
	}

	/**
		* name:	CBEXM_DELITEM
		* desc:	delete an item from the control
		* param:	wParam - not used
		*			lParam - item index
		* return:	CB_ERR on failure, new item index if successful
		**/
	case CBEXM_DELITEM:
	{
		if (!cbex->pItems || (int)lParam < 0 || (int)lParam >= cbex->numItems || (cbex->pItems[lParam].wFlags & CBEXIF_CATREADONLY))
			return FALSE;	
		MIR_FREE(cbex->pItems[(int)lParam].pszVal);
		memmove(cbex->pItems + (int)lParam, 
			cbex->pItems + (int)lParam + 1,
			(cbex->numItems - (int)lParam - 1) * sizeof(CBEXITEMINTERN));
		cbex->numItems--;
		memset((cbex->pItems + cbex->numItems), 0, sizeof(CBEXITEMINTERN));
		CtrlContactWndProc(hwnd, CBEXM_SETCURSEL, lParam - 1, FALSE);
		return TRUE;
	}

	/**
		* name:	CBEXM_DELITEM
		* desc:	delete an item from the control
		* param:	wParam - not used
		*			lParam - item index
		* return:	CB_ERR on failure, new item index if successful
		**/
	case CBEXM_DELALLITEMS:
	{
		int i;

		if (PtrIsValid(cbex)) {
			if (PtrIsValid(cbex->pItems)) {
				for (i = 0; i < cbex->numItems; i++) {
					MIR_FREE(cbex->pItems[i].pszVal);
				}
				MIR_FREE(cbex->pItems);
				cbex->pItems = NULL;
			}
			cbex->numItems = 0;
			cbex->iSelectedItem = -1;
			SetWindowText(cbex->hEdit, _T(""));
			SetWindowText(cbex->hBtnEdit, _T(""));
			SendMessage(cbex->hBtnEdit, WM_SETICON, NULL, NULL);
		}
		return TRUE;
	}

	/**
		* name:	CBEXM_ENABLEITEM
		* desc:	enables or disables the current item
		* param:	wParam - not used
		*			lParam - not used
		* return:	always 0
		**/
	case CBEXM_ENABLEITEM:
		if (cbex->iSelectedItem >= 0 && cbex->iSelectedItem < cbex->numItems) {
			MCONTACT hContact;
			BYTE bEnabled;
				
			PSGetContact(GetParent(hwnd), hContact);

			bEnabled	= !hContact ||
						(cbex->pItems[cbex->iSelectedItem].wFlags & CTRLF_HASCUSTOM) || 
						!(cbex->pItems[cbex->iSelectedItem].wFlags & (CTRLF_HASPROTO|CTRLF_HASMETA)) ||
						!db_get_b(NULL, MODNAME, SET_PROPSHEET_PCBIREADONLY, 0);

			EnableWindow(cbex->hBtnEdit, bEnabled);
			EnableWindow(cbex->hBtnDel, bEnabled && GetWindowTextLength(cbex->hEdit) > 0);
			EnableWindow(cbex->hEdit, bEnabled);
		}
		break;

	/**
		* name:	CBEXM_ISCHANGED
		* desc:	returns whether the control contains changed values or not
		* param:	wParam - not used
		*			lParam - not used
		* return:	TRUE if control was changed, FALSE if nothing was edited
		**/
	case CBEXM_ISCHANGED:
		return cbex->bIsChanged;

	/**
		* name:	CBEXM_RESETCHANGED
		* desc:	resets changed flag to FALSE
		* param:	wParam - not used
		*			lParam - not used
		* return:	always FALSE
		**/
	case CBEXM_RESETCHANGED:
		cbex->bIsChanged = 0;
		return 0;

	/**
		* name:	CBEXM_SETCURSEL
		* desc:	selects a certain item
		* param:	wParam - index of the item to select
		*			lParam - (BYTE)bValid - if TRUE, the next item with a value is selected
		* return:	always FALSE
		**/
	case CBEXM_SETCURSEL:
	{
		int i;

		if (!cbex->pItems) return 1;
		if ((int)wParam < 0 || (int)wParam >= cbex->numItems) wParam = max(cbex->iSelectedItem, 0);
		cbex->bLocked = 1;
			
		if ((BYTE)lParam == TRUE) {
			i = (int)wParam;

			cbex->iSelectedItem = (int)wParam;
			while (i < cbex->numItems) {
				if (cbex->pItems[i].pszVal && *cbex->pItems[i].pszVal) {
					cbex->iSelectedItem = i;
					break;
				}
				i++;
			}
		}
		else {
			// search for the next none deleted item
			for (i = (int)wParam; i < cbex->numItems && *cbex->pItems[i].szCat == 0; i++);
			if (i == cbex->numItems && (int)wParam > 0) {
				for (i = 0; i < (int)wParam && *cbex->pItems[i].szCat == 0; i++);
				cbex->iSelectedItem = i == (int)wParam ? 0 : i;
			}
			else
				cbex->iSelectedItem = i;

		}
		SetWindowText(cbex->hBtnEdit, cbex->pItems[cbex->iSelectedItem].szCat);
		SetWindowText(cbex->hEdit, cbex->pItems[cbex->iSelectedItem].pszVal ? cbex->pItems[cbex->iSelectedItem].pszVal : _T(""));
		SendMessage(cbex->hBtnEdit, BM_SETIMAGE, IMAGE_ICON, (LPARAM)cbex->pItems[cbex->iSelectedItem].hIcon);
		CtrlContactWndProc(hwnd, CBEXM_ENABLEITEM, NULL, NULL);
		cbex->bLocked = 0;
		return 0;
	}
	case CBEXM_SORT:
		if (cbex->numItems > 4) {
			qsort(cbex->pItems + 3, cbex->numItems - 3, sizeof(CBEXITEMINTERN), compareProc);
		}
		return 0;

	case WM_ERASEBKGND:
		return 1;

	case WM_SETFOCUS:
		SetFocus(cbex->hEdit);
		SendMessage(cbex->hEdit, EM_SETSEL, 0, (LPARAM)-1);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}