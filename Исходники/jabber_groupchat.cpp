INT_PTR CJabberDlgGcJoin::DlgProc(UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
	case WM_DELETEITEM:
		{
			LPDELETEITEMSTRUCT lpdis = (LPDELETEITEMSTRUCT)lParam;
			if (lpdis->CtlID != IDC_ROOM)
				break;

			RoomInfo *info = (RoomInfo *)lpdis->itemData;
			mir_free(info->line1);
			mir_free(info->line2);
			mir_free(info);
		}
		break;

	case WM_MEASUREITEM:
		{
			LPMEASUREITEMSTRUCT lpmis = (LPMEASUREITEMSTRUCT)lParam;
			if (lpmis->CtlID != IDC_ROOM)
				break;

			lpmis->itemHeight = 2 * sttTextLineHeight;
			if (lpmis->itemID == -1)
				lpmis->itemHeight = sttTextLineHeight - 1;

		}
		break;

	case WM_DRAWITEM:
		{
			LPDRAWITEMSTRUCT lpdis = (LPDRAWITEMSTRUCT)lParam;
			if (lpdis->CtlID != IDC_ROOM)
				break;

			RoomInfo *info = (RoomInfo *)SendDlgItemMessage(m_hwnd, IDC_ROOM, CB_GETITEMDATA, lpdis->itemID, 0);
			COLORREF clLine1, clBack;

			if (lpdis->itemState & ODS_SELECTED) {
				FillRect(lpdis->hDC, &lpdis->rcItem, GetSysColorBrush(COLOR_HIGHLIGHT));
				clBack = GetSysColor(COLOR_HIGHLIGHT);
				clLine1 = GetSysColor(COLOR_HIGHLIGHTTEXT);
			}
			else {
				FillRect(lpdis->hDC, &lpdis->rcItem, GetSysColorBrush(COLOR_WINDOW));
				clBack = GetSysColor(COLOR_WINDOW);
				clLine1 = GetSysColor(COLOR_WINDOWTEXT);
			}
			COLORREF clLine2 = RGB(
				GetRValue(clLine1) * 0.66 + GetRValue(clBack) * 0.34,
				GetGValue(clLine1) * 0.66 + GetGValue(clBack) * 0.34,
				GetBValue(clLine1) * 0.66 + GetBValue(clBack) * 0.34);

			SetBkMode(lpdis->hDC, TRANSPARENT);

			RECT rc = lpdis->rcItem;
			rc.bottom -= (rc.bottom - rc.top) / 2;
			rc.left += 20;
			SetTextColor(lpdis->hDC, clLine1);
			DrawText(lpdis->hDC, info->line1, -1, &rc, DT_LEFT | DT_NOPREFIX | DT_SINGLELINE | DT_VCENTER | DT_WORD_ELLIPSIS);

			rc = lpdis->rcItem;
			rc.top += (rc.bottom - rc.top) / 2;
			rc.left += 20;
			SetTextColor(lpdis->hDC, clLine2);
			DrawText(lpdis->hDC, info->line2, -1, &rc, DT_LEFT | DT_NOPREFIX | DT_SINGLELINE | DT_VCENTER | DT_WORD_ELLIPSIS);

			DrawIconEx(lpdis->hDC, lpdis->rcItem.left + 1, lpdis->rcItem.top + 1, m_proto->LoadIconEx("group"), 16, 16, 0, NULL, DI_NORMAL);
			switch (info->overlay) {
			case RoomInfo::ROOM_WAIT:
				DrawIconEx(lpdis->hDC, lpdis->rcItem.left + 1, lpdis->rcItem.top + 1, m_proto->LoadIconEx("disco_progress"), 16, 16, 0, NULL, DI_NORMAL);
				break;
			case RoomInfo::ROOM_FAIL:
				DrawIconEx(lpdis->hDC, lpdis->rcItem.left + 1, lpdis->rcItem.top + 1, m_proto->LoadIconEx("disco_fail"), 16, 16, 0, NULL, DI_NORMAL);
				break;
			case RoomInfo::ROOM_BOOKMARK:
				DrawIconEx(lpdis->hDC, lpdis->rcItem.left + 1, lpdis->rcItem.top + 1, m_proto->LoadIconEx("disco_ok"), 16, 16, 0, NULL, DI_NORMAL);
				break;
			}
		}
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_SERVER:
			switch (HIWORD(wParam)) {
			case CBN_EDITCHANGE:
			case CBN_SELCHANGE:
				{
					int iqid = GetWindowLongPtr(GetDlgItem(m_hwnd, IDC_ROOM), GWLP_USERDATA);
					if (iqid) {
						m_proto->m_iqManager.ExpireIq(iqid);
						SetWindowLongPtr(GetDlgItem(m_hwnd, IDC_ROOM), GWLP_USERDATA, 0);
					}
					SendDlgItemMessage(m_hwnd, IDC_ROOM, CB_RESETCONTENT, 0, 0);
				}
				break;
			}
			break;

		case IDC_ROOM:
			switch (HIWORD(wParam)) {
			case CBN_DROPDOWN:
				if (!SendDlgItemMessage(m_hwnd, IDC_ROOM, CB_GETCOUNT, 0, 0)) {
					int iqid = GetWindowLongPtr(GetDlgItem(m_hwnd, IDC_ROOM), GWLP_USERDATA);
					if (iqid) {
						m_proto->m_iqManager.ExpireIq(iqid);
						SetWindowLongPtr(GetDlgItem(m_hwnd, IDC_ROOM), GWLP_USERDATA, 0);
					}

					SendDlgItemMessage(m_hwnd, IDC_ROOM, CB_RESETCONTENT, 0, 0);

					int len = GetWindowTextLength(GetDlgItem(m_hwnd, IDC_SERVER)) + 1;
					TCHAR *server = (TCHAR*)_alloca(len * sizeof(TCHAR));
					GetDlgItemText(m_hwnd, IDC_SERVER, server, len);

					if (*server) {
						sttRoomListAppend(GetDlgItem(m_hwnd, IDC_ROOM), RoomInfo::ROOM_WAIT, TranslateT("Loading..."), TranslateT("Please wait for room list to download."), _T(""));

						CJabberIqInfo *pInfo = m_proto->AddIQ(&CJabberProto::OnIqResultDiscovery, JABBER_IQ_TYPE_GET, server, 0, -1, (void*)GetDlgItem(m_hwnd, IDC_ROOM));
						pInfo->SetTimeout(30000);
						XmlNodeIq iq(pInfo);
						iq << XQUERY(JABBER_FEAT_DISCO_ITEMS);
						m_proto->m_ThreadInfo->send(iq);

						SetWindowLongPtr(GetDlgItem(m_hwnd, IDC_ROOM), GWLP_USERDATA, pInfo->GetIqId());
					}
					else
						sttRoomListAppend(GetDlgItem(m_hwnd, IDC_ROOM), RoomInfo::ROOM_FAIL,
						TranslateT("Jabber Error"),
						TranslateT("Please specify group chat directory first."),
						_T(""));
				}
				break;
			}
			break;

		case IDC_BOOKMARKS:
			{
				HMENU hMenu = CreatePopupMenu();

				LISTFOREACH(i, m_proto, LIST_BOOKMARK)
				{
					JABBER_LIST_ITEM *item = 0;
					if (item = m_proto->ListGetItemPtrFromIndex(i))
						if (!mir_tstrcmp(item->type, _T("conference")))
							AppendMenu(hMenu, MF_STRING, (UINT_PTR)item, item->name);
				}
				AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);
				AppendMenu(hMenu, MF_STRING, (UINT_PTR)-1, TranslateT("Bookmarks..."));
				AppendMenu(hMenu, MF_STRING, (UINT_PTR)0, TranslateT("Cancel"));

				RECT rc; GetWindowRect(GetDlgItem(m_hwnd, IDC_BOOKMARKS), &rc);
				CheckDlgButton(m_hwnd, IDC_BOOKMARKS, BST_CHECKED);
				int res = TrackPopupMenu(hMenu, TPM_RETURNCMD, rc.left, rc.bottom, 0, m_hwnd, NULL);
				CheckDlgButton(m_hwnd, IDC_BOOKMARKS, BST_UNCHECKED);
				DestroyMenu(hMenu);

				if (res == -1)
					m_proto->OnMenuHandleBookmarks(0, 0);
				else if (res) {
					JABBER_LIST_ITEM *item = (JABBER_LIST_ITEM *)res;
					TCHAR *room = NEWTSTR_ALLOCA(item->jid);
					if (room) {
						TCHAR *server = _tcschr(room, _T('@'));
						if (server) {
							*server++ = 0;

							SendMessage(m_hwnd, WM_COMMAND, MAKEWPARAM(IDC_SERVER, CBN_EDITCHANGE), (LPARAM)GetDlgItem(m_hwnd, IDC_SERVER));

							SetDlgItemText(m_hwnd, IDC_SERVER, server);
							SetDlgItemText(m_hwnd, IDC_ROOM, room);
							SetDlgItemText(m_hwnd, IDC_NICK, item->nick);
							SetDlgItemText(m_hwnd, IDC_PASSWORD, item->password);
						}
					}
				}
			}
			break;

		case IDC_RECENT1:
		case IDC_RECENT2:
		case IDC_RECENT3:
		case IDC_RECENT4:
		case IDC_RECENT5:
			JabberGcRecentInfo info(m_proto, LOWORD(wParam) - IDC_RECENT1);
			info.fillForm(m_hwnd);
			if (GetAsyncKeyState(VK_CONTROL))
				break;

			OnBtnOk(NULL);
			Close();
		}
		break;

	case WM_JABBER_CHECK_ONLINE:
		if (!m_proto->m_bJabberOnline)
			EndDialog(m_hwnd, 0);
		break;
	}