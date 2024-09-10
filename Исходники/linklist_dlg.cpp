/*
MainDlgProc handles messages to the main dialog box
*/
INT_PTR CALLBACK MainDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	DIALOGPARAM *DlgParam = (DIALOGPARAM*)GetWindowLongPtr(hDlg, GWLP_USERDATA);
	HMENU listMenu;

	switch (msg) {
	case WM_INITDIALOG: {
		MCONTACT hContact;
		TCHAR title[256];
		TCHAR filter[FILTERTEXT];
		RECT rc;
		POINT pt;
			
		SetWindowLongPtr(hDlg, GWLP_USERDATA, lParam);
		DlgParam = (DIALOGPARAM*)lParam;
		listMenu = GetMenu(hDlg);
		TranslateDialogDefault(hDlg);
		TranslateMenu(listMenu);

		hContact = ((db_get_b(NULL, LINKLIST_MODULE, LINKLIST_SAVESPECIAL, 0) == 0) ? NULL: DlgParam->hContact);
		if (db_get_b(hContact, LINKLIST_MODULE, LINKLIST_FIRST, 0) == 0) {
			// First use of this plugin! Set default size!
			db_set_dw(hContact, LINKLIST_MODULE, "LinklistWidth", 400);
			db_set_dw(hContact, LINKLIST_MODULE, "LinklistHeight", 450);
			db_set_dw(hContact, LINKLIST_MODULE, "LinklistX", 0);
			db_set_dw(hContact, LINKLIST_MODULE, "LinklistY", 0);
				
			db_set_b(hContact, LINKLIST_MODULE, LINKLIST_FIRST, 1);
		}

		DlgParam->splitterPosNew = (int)db_get_dw(hContact, LINKLIST_MODULE, LINKLIST_SPLITPOS, -1);

		GetWindowRect(GetDlgItem(hDlg, IDC_MAIN), &rc);
		DlgParam->minSize.cx = rc.right - rc.left;
		DlgParam->minSize.cy = rc.bottom - rc.top;

		GetWindowRect(GetDlgItem(hDlg, IDC_SPLITTER), &rc);
		pt.y = (rc.top + rc.bottom) / 2;
		pt.x = 0;
		ScreenToClient(hDlg, &pt);
			
		DlgParam->splitterPosOld = rc.bottom - 20 - pt.y;
		if(DlgParam->splitterPosNew == -1)
			DlgParam->splitterPosNew = DlgParam->splitterPosOld;
			
		Utils_RestoreWindowPosition(hDlg, hContact, LINKLIST_MODULE, "Linklist");

		SetClassLongPtr(hDlg, GCLP_HICON, (LONG_PTR)LoadIcon(hInst, MAKEINTRESOURCE(IDI_LINKLISTICON))); 
		WindowList_Add(hWindowList, hDlg, DlgParam->hContact);
		mir_sntprintf(title, _T("%s [%s]"), TranslateT("Linklist plugin"), pcli->pfnGetContactDisplayName(DlgParam->hContact, 0));
		SetWindowText(hDlg, title);
		GetFilterText(listMenu, filter, _countof(filter));
		SetDlgItemText(hDlg, IDC_STATUS, filter);
			
		mir_subclassWindow(GetDlgItem(hDlg, IDC_SPLITTER), SplitterProc);
			
		SendDlgItemMessage( hDlg, IDC_MAIN, EM_SETEVENTMASK, 0, (LPARAM)ENM_LINK);
		SendDlgItemMessage( hDlg, IDC_MAIN, EM_AUTOURLDETECT, TRUE, 0 );
		// This is used in srmm... and I think he knew what he did... :)
		SendDlgItemMessage(hDlg, IDC_MAIN, EM_LIMITTEXT, (WPARAM)-1, 0);

		WriteLinkList(hDlg, WLL_ALL, (LISTELEMENT*)DlgParam->listStart, NULL, 0);

		return TRUE;
		} break;
	// open browser an load url if link is pressed
	// found at
	// http://www.tech-archive.net/Archive/Development/microsoft.public.win32.programmer.ui/2004-03/0133.html
	//
	// Popup menu on right mouse button is mainly taken from the miranda 
	// send/receive messaging plugin.
	case WM_NOTIFY: {  
		if (lParam == NULL)
			break;
		if (((LPNMHDR)lParam)->code != EN_LINK)
			break;
		LPTSTR link;
		BYTE mouseEvent;
		ENLINK *pENLink = (ENLINK*)lParam;

		mouseEvent = db_get_b(NULL, LINKLIST_MODULE, LINKLIST_MOUSE_EVENT, 0xFF);

		switch (pENLink->msg) {
		case WM_MOUSEMOVE:
			if (mouseEvent != 0x01)
				break;
			memcpy(&DlgParam->chrg, &pENLink->chrg, sizeof(CHARRANGE));
			SendDlgItemMessage(hDlg, IDC_MAIN, EM_EXSETSEL, 0, (LPARAM)&pENLink->chrg);
			WriteMessage(hDlg, DlgParam->listStart, SendDlgItemMessage(hDlg, IDC_MAIN, EM_LINEFROMCHAR, -1, 0));
			break;
		case WM_LBUTTONUP:
			link = (LPTSTR)mir_alloc((pENLink->chrg.cpMax - pENLink->chrg.cpMin + 2) * sizeof(TCHAR));
			if (link == NULL)
				break;
			SendDlgItemMessage(hDlg, IDC_MAIN, EM_EXSETSEL, 0, (LPARAM)&pENLink->chrg); 
			SendDlgItemMessage(hDlg, IDC_MAIN, EM_GETSELTEXT, 0, (LPARAM)link);
			if (_tcsstr(link, _T("mailto:")) != NULL)
				ShellExecute(HWND_TOP, NULL, link, NULL, NULL, SW_SHOWNORMAL); 
			else {
				bool openNewWindow = db_get_b(NULL, LINKLIST_MODULE, LINKLIST_OPEN_WINDOW, 0xFF) != 0xFF;
				Utils_OpenUrlT(link,openNewWindow);
			}
			mir_free(link);
			break;
		case WM_RBUTTONDOWN: { 
			HMENU hPopup, hSubMenu;
			POINT pt;
			hPopup = LoadMenu(hInst, MAKEINTRESOURCE(IDR_MENU2));
			hSubMenu = GetSubMenu(hPopup, 0);

			// Disable Menuoption if "mouse over" events are active
			mouseEvent = db_get_b(NULL, LINKLIST_MODULE, LINKLIST_MOUSE_EVENT, 0xFF);
			if (mouseEvent == 0x01)
				EnableMenuItem(hSubMenu, IDM_SHOWMESSAGE, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);	
			TranslateMenu(hSubMenu);
			link = (LPTSTR)mir_alloc((pENLink->chrg.cpMax - pENLink->chrg.cpMin + 4) * sizeof(TCHAR));
			if (link == NULL)
				break;
			SendDlgItemMessage(hDlg, IDC_MAIN, EM_EXSETSEL, 0, (LPARAM)&pENLink->chrg); 
			SendDlgItemMessage(hDlg, IDC_MAIN, EM_GETSELTEXT, 0, (LPARAM)link);

			pt.x = (short)LOWORD(pENLink->lParam);
			pt.y = (short)HIWORD(pENLink->lParam);
			ClientToScreen(((NMHDR*)lParam)->hwndFrom, &pt);

			switch (TrackPopupMenu(hSubMenu, TPM_RETURNCMD, pt.x, pt.y, 0, hDlg, NULL)) {
			case IDM_LINK_OPEN:
				if (_tcsstr(link, _T("mailto:")) != NULL)
					ShellExecute(HWND_TOP, NULL, link, NULL, NULL, SW_SHOWNORMAL); 
				else
					Utils_OpenUrlT(link,false);
				break;
			case IDM_LINK_OPENNEW:
				if (_tcsstr(link, _T("mailto:")) != NULL)
					ShellExecute(HWND_TOP, NULL, link, NULL, NULL, SW_SHOWNORMAL); 
				else
					Utils_OpenUrlT(link);
				break;
			case IDM_LINK_COPY: {
				if (!OpenClipboard(hDlg))
					break;
				EmptyClipboard();

				size_t dataLen = ((mir_tstrlen(link) + 1) * sizeof(TCHAR));
				HGLOBAL hData = GlobalAlloc(GMEM_MOVEABLE, dataLen);
				memcpy((LPTSTR)GlobalLock(hData), link, dataLen);
				GlobalUnlock(hData);
				SetClipboardData(CF_UNICODETEXT, hData);
				CloseClipboard();
				} break;
			case IDM_SHOWMESSAGE:
				WriteMessage(hDlg, DlgParam->listStart, SendDlgItemMessage(hDlg, IDC_MAIN, EM_LINEFROMCHAR, -1, 0));
				break;
			}
			mir_free(link);
			DestroyMenu(hPopup);
			} break;
		}
		} break;
	case WM_COMMAND: {
		TCHAR filter[40];

		listMenu = GetMenu(hDlg);
		switch (wParam) {
		case IDM_SEARCH: // open Search Box
			if (DlgParam != 0) {	
				HWND hWndSearchDlg = CreateDialogParam(hInst, MAKEINTRESOURCE(IDD_SEARCH_DLG), hDlg, SearchDlgProc, (LPARAM)DlgParam);
				EnableMenuItem(listMenu, IDM_SEARCH, (MF_BYCOMMAND | MF_DISABLED | MF_GRAYED));
				ShowWindow(hWndSearchDlg, SW_SHOW);
				SetFocus(GetDlgItem(hWndSearchDlg, IDC_SEARCHSTRING));
			}
			break;
		case IDM_CLEARSEARCH: // clear search results
			GetFilterText(listMenu, filter, _countof(filter));
			SetDlgItemText(hDlg, IDC_STATUS, filter);
			SetDlgItemText(hDlg, IDC_MAIN, _T(""));
			WriteLinkList(hDlg, GetFlags(listMenu), DlgParam->listStart, NULL, 0);
			break;
		case IDM_SAVE: // save button
			SaveEditAsStream(hDlg);
			SetFocus(GetDlgItem(hDlg, IDC_MAIN));
			break;
		case IDCANCEL: // Esc or Close pressed
		case IDM_CLOSE:
			SendMessage(hDlg, WM_CLOSE, 0, 0);
			break;
		case IDM_DIR_IN: // view only incoming messages
			GetFilterText(listMenu, filter, _countof(filter));
			SetDlgItemText(hDlg, IDC_STATUS, filter);
			if ((GetMenuState(listMenu, IDM_SEARCH, MF_BYCOMMAND) & MF_DISABLED))
				break; // not possible if search dialog is open
			SetDlgItemText(hDlg, IDC_MAIN, _T(""));
			if (GetMenuState(listMenu, IDM_DIR_IN, MF_BYCOMMAND) == MF_CHECKED) {
				CheckMenuItem(listMenu, IDM_DIR_IN, MF_UNCHECKED);
				WriteLinkList(hDlg, GetFlags(listMenu), DlgParam->listStart, NULL, 0);
			} else {
				CheckMenuItem(listMenu, IDM_DIR_IN, MF_CHECKED);
				CheckMenuItem(listMenu, IDM_DIR_OUT, MF_UNCHECKED);
				WriteLinkList(hDlg, GetFlags(listMenu), DlgParam->listStart, NULL, 0);
			}		
			GetFilterText(GetMenu(hDlg), filter, _countof(filter));
			SetDlgItemText(hDlg, IDC_STATUS, filter);
			break;
		case IDM_DIR_OUT: // view only outgoing messages
			GetFilterText(listMenu, filter, _countof(filter));
			SetDlgItemText(hDlg, IDC_STATUS, filter);
			if ((GetMenuState(listMenu, IDM_SEARCH, MF_BYCOMMAND) & MF_DISABLED))
				break; // not possible if search dialog is open
			SetDlgItemText(hDlg, IDC_MAIN, _T(""));
			if (GetMenuState(listMenu, IDM_DIR_OUT, MF_BYCOMMAND) == MF_CHECKED) {
				CheckMenuItem(listMenu, IDM_DIR_OUT, MF_UNCHECKED);		
				WriteLinkList(hDlg, GetFlags(listMenu), DlgParam->listStart, NULL, 0);
			} else {
				CheckMenuItem(listMenu, IDM_DIR_OUT, MF_CHECKED);
				CheckMenuItem(listMenu, IDM_DIR_IN, MF_UNCHECKED);
				WriteLinkList(hDlg, GetFlags(listMenu), DlgParam->listStart, NULL, 0);
			}
			GetFilterText(listMenu, filter, _countof(filter));
			SetDlgItemText(hDlg, IDC_STATUS, filter);
			break;
		case IDM_TYPE_WEB: // view only e-mail addresses
			GetFilterText(listMenu, filter, _countof(filter));
			SetDlgItemText(hDlg, IDC_STATUS, filter);
			// not possible if search dialog is open
			if ((GetMenuState(listMenu, IDM_SEARCH, MF_BYCOMMAND) & MF_DISABLED))
				break;
			SetDlgItemText(hDlg, IDC_MAIN, _T(""));
			if (GetMenuState(listMenu, IDM_TYPE_WEB, MF_BYCOMMAND) == MF_CHECKED) {
				CheckMenuItem(listMenu, IDM_TYPE_WEB, MF_UNCHECKED);		
				WriteLinkList(hDlg, GetFlags(listMenu), DlgParam->listStart, NULL, 0);
			} else {
				CheckMenuItem(listMenu, IDM_TYPE_WEB, MF_CHECKED);
				CheckMenuItem(listMenu, IDM_TYPE_MAIL, MF_UNCHECKED);
				WriteLinkList(hDlg, GetFlags(listMenu), DlgParam->listStart, NULL, 0);
			}
			GetFilterText(listMenu, filter, _countof(filter));
			SetDlgItemText(hDlg, IDC_STATUS, filter);
			break;
		case IDM_TYPE_MAIL: // view only URLs
			if ((GetMenuState(listMenu, IDM_SEARCH, MF_BYCOMMAND) & MF_DISABLED))
				break; // not possible if search dialog is open
			SetDlgItemText(hDlg, IDC_MAIN, _T(""));
			if (GetMenuState(listMenu, IDM_TYPE_MAIL, MF_BYCOMMAND) == MF_CHECKED) {
				CheckMenuItem(listMenu, IDM_TYPE_MAIL, MF_UNCHECKED);		
				WriteLinkList(hDlg, GetFlags(listMenu), DlgParam->listStart, NULL, 0);				
			} else {
				CheckMenuItem(listMenu, IDM_TYPE_MAIL, MF_CHECKED);
				CheckMenuItem(listMenu, IDM_TYPE_WEB, MF_UNCHECKED);
				WriteLinkList(hDlg, GetFlags(listMenu), DlgParam->listStart, NULL, 0);
			}
			GetFilterText(listMenu, filter, _countof(filter));
			SetDlgItemText(hDlg, IDC_STATUS, filter);
			break;
		}
		} break;
	// Taken from srmm.
	// Btw: The longer I searched the source of this plugin
	// to learn how things work, the more I became a fan of
	// the programmer! 
	case WM_GETMINMAXINFO: {
		MINMAXINFO *mmi = (MINMAXINFO *)lParam;
		RECT rcWindow, rcMain;

		GetWindowRect(hDlg, &rcWindow);
		GetWindowRect(GetDlgItem(hDlg, IDC_MAIN), &rcMain);
		mmi->ptMinTrackSize.x = rcWindow.right - rcWindow.left - ((rcMain.right - rcMain.left) - DlgParam->minSize.cx);
		mmi->ptMinTrackSize.y = rcWindow.bottom - rcWindow.top - ((rcMain.bottom - rcMain.top) - DlgParam->minSize.cy);
		} break;
	case WM_SIZE:
		Utils_ResizeDialog(hDlg, hInst, MAKEINTRESOURCEA(IDD_MAIN_DLG), LinklistResizer, (LPARAM)DlgParam);
		// To get some scrollbars if needed...
		RedrawWindow(GetDlgItem(hDlg, IDC_MAIN), NULL, NULL, RDW_INVALIDATE);
		RedrawWindow(GetDlgItem(hDlg, IDC_MESSAGE), NULL, NULL, RDW_INVALIDATE);
		break;
	
	case DM_LINKSPLITTER: {
		POINT pt;
		RECT rc;
		int splitPosOld;

		GetClientRect(hDlg, &rc);
		pt.x = 0;
		pt.y = wParam;
		ScreenToClient(hDlg, &pt);

		splitPosOld = DlgParam->splitterPosNew;
		DlgParam->splitterPosNew = rc.bottom - pt.y;
			
		GetWindowRect(GetDlgItem(hDlg, IDC_MESSAGE), &rc);
		if (rc.bottom - rc.top + (DlgParam->splitterPosNew - splitPosOld) < 0)
			DlgParam->splitterPosNew = splitPosOld + 0 - (rc.bottom - rc.top);

		GetWindowRect(GetDlgItem(hDlg, IDC_MAIN), &rc);
		if (rc.bottom - rc.top - (DlgParam->splitterPosNew - splitPosOld) < DlgParam->minSize.cy)
			DlgParam->splitterPosNew = splitPosOld - DlgParam->minSize.cy + (rc.bottom - rc.top);
		SendMessage(hDlg, WM_SIZE, 0, 0);
		} break;
	case WM_CLOSE:
		DestroyWindow(hDlg);
		break;
	case WM_DESTROY:
		if (DlgParam != NULL) {
			MCONTACT hContact = ((db_get_b(NULL, LINKLIST_MODULE, LINKLIST_SAVESPECIAL, 0) == 0) ? NULL: DlgParam->hContact);
			Utils_SaveWindowPosition(hDlg, hContact, LINKLIST_MODULE, "Linklist");
			db_set_dw(NULL, LINKLIST_MODULE, LINKLIST_SPLITPOS, DlgParam->splitterPosNew);
			RemoveList(DlgParam->listStart);
			mir_free(DlgParam);
		}
		// Remove entry from Window list
		WindowList_Remove(hWindowList, hDlg);
		break;
	}
	return FALSE;
}