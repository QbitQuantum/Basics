static INT_PTR CALLBACK JabberAddBookmarkDlgProc(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	JabberAddBookmarkDlgParam* param = (JabberAddBookmarkDlgParam*)GetWindowLongPtr(hwndDlg, GWLP_USERDATA);

	TCHAR text[512];
	JABBER_LIST_ITEM *item;

	switch (msg) {
	case WM_INITDIALOG:
		param = (JabberAddBookmarkDlgParam*)lParam;
		SetWindowLongPtr(hwndDlg, GWLP_USERDATA, lParam);

		param->ppro->m_hwndJabberAddBookmark = hwndDlg;
		TranslateDialogDefault(hwndDlg);
		if (item = param->m_item) {
			if (!lstrcmp(item->type, _T("conference"))) {
				if (!_tcschr(item->jid, _T('@'))) {	  //no room name - consider it is transport
					SendDlgItemMessage(hwndDlg, IDC_AGENT_RADIO, BM_SETCHECK, BST_CHECKED, 0);
					EnableWindow(GetDlgItem(hwndDlg, IDC_NICK), FALSE);
					EnableWindow(GetDlgItem(hwndDlg, IDC_PASSWORD), FALSE);
				}
				else SendDlgItemMessage(hwndDlg, IDC_ROOM_RADIO, BM_SETCHECK, BST_CHECKED, 0);
			}
			else {
				SendDlgItemMessage(hwndDlg, IDC_URL_RADIO, BM_SETCHECK, BST_CHECKED, 0);
				EnableWindow(GetDlgItem(hwndDlg, IDC_NICK), FALSE);
				EnableWindow(GetDlgItem(hwndDlg, IDC_PASSWORD), FALSE);
				SendDlgItemMessage(hwndDlg, IDC_CHECK_BM_AUTOJOIN, BM_SETCHECK, BST_UNCHECKED, 0);
				EnableWindow(GetDlgItem(hwndDlg, IDC_CHECK_BM_AUTOJOIN), FALSE);
			}

			EnableWindow(GetDlgItem(hwndDlg, IDC_ROOM_RADIO), FALSE);
			EnableWindow(GetDlgItem(hwndDlg, IDC_URL_RADIO), FALSE);
			EnableWindow(GetDlgItem(hwndDlg, IDC_AGENT_RADIO), FALSE);
			EnableWindow(GetDlgItem(hwndDlg, IDC_CHECK_BM_AUTOJOIN), FALSE);

			if (item->jid) SetDlgItemText(hwndDlg, IDC_ROOM_JID, item->jid);
			if (item->name) SetDlgItemText(hwndDlg, IDC_NAME, item->name);
			if (item->nick) SetDlgItemText(hwndDlg, IDC_NICK, item->nick);
			if (item->password) SetDlgItemText(hwndDlg, IDC_PASSWORD, item->password);
			if (item->bAutoJoin) SendDlgItemMessage(hwndDlg, IDC_CHECK_BM_AUTOJOIN, BM_SETCHECK, BST_CHECKED, 0);
			if (SendDlgItemMessage(hwndDlg, IDC_ROOM_RADIO, BM_GETCHECK,0, 0) == BST_CHECKED)
				EnableWindow(GetDlgItem(hwndDlg, IDC_CHECK_BM_AUTOJOIN), TRUE);
		}
		else {
			EnableWindow(GetDlgItem(hwndDlg, IDOK), FALSE);
			SendDlgItemMessage(hwndDlg, IDC_ROOM_RADIO, BM_SETCHECK, BST_CHECKED, 0);
		}
		return TRUE;

	case WM_COMMAND:
		switch (HIWORD(wParam)) {
		case BN_CLICKED:
			switch (LOWORD (wParam)) {
			case IDC_ROOM_RADIO:
				EnableWindow(GetDlgItem(hwndDlg, IDC_NICK), TRUE);
				EnableWindow(GetDlgItem(hwndDlg, IDC_PASSWORD), TRUE);
				EnableWindow(GetDlgItem(hwndDlg, IDC_CHECK_BM_AUTOJOIN), TRUE);
				break;
			case IDC_AGENT_RADIO:
			case IDC_URL_RADIO:
				EnableWindow(GetDlgItem(hwndDlg, IDC_NICK), FALSE);
				EnableWindow(GetDlgItem(hwndDlg, IDC_PASSWORD), FALSE);
				SendDlgItemMessage(hwndDlg, IDC_CHECK_BM_AUTOJOIN, BM_SETCHECK, BST_UNCHECKED, 0);
				EnableWindow(GetDlgItem(hwndDlg, IDC_CHECK_BM_AUTOJOIN), FALSE);
				break;
			}
		}

		switch (LOWORD(wParam)) {
		case IDC_ROOM_JID:
			if ((HWND)lParam==GetFocus() && HIWORD(wParam)==EN_CHANGE)
				EnableWindow(GetDlgItem(hwndDlg, IDOK), GetDlgItemText(hwndDlg, IDC_ROOM_JID, text, SIZEOF(text)));
			break;

		case IDOK:
			{
				GetDlgItemText(hwndDlg, IDC_ROOM_JID, text, SIZEOF(text));
				TCHAR *roomJID = NEWTSTR_ALLOCA(text);

				if (param->m_item)
					param->ppro->ListRemove(LIST_BOOKMARK, param->m_item->jid);

				item = param->ppro->ListAdd(LIST_BOOKMARK, roomJID);

				if (SendDlgItemMessage(hwndDlg, IDC_URL_RADIO, BM_GETCHECK,0, 0) == BST_CHECKED)
					replaceStrT(item->type, _T("url"));
				else
					replaceStrT(item->type, _T("conference"));

				GetDlgItemText(hwndDlg, IDC_NICK, text, SIZEOF(text));
				replaceStrT(item->nick, text);

				GetDlgItemText(hwndDlg, IDC_PASSWORD, text, SIZEOF(text));
				replaceStrT(item->password, text);

				GetDlgItemText(hwndDlg, IDC_NAME, text, SIZEOF(text));
				replaceStrT(item->name, (text[0] == 0) ? roomJID : text);

				item->bAutoJoin = (SendDlgItemMessage(hwndDlg, IDC_CHECK_BM_AUTOJOIN, BM_GETCHECK,0, 0) == BST_CHECKED);

				XmlNodeIq iq( param->ppro->AddIQ(&CJabberProto::OnIqResultSetBookmarks, JABBER_IQ_TYPE_SET));
				param->ppro->SetBookmarkRequest(iq);
				param->ppro->m_ThreadInfo->send(iq);
			}
			// fall through
		case IDCANCEL:
			EndDialog(hwndDlg, 0);
			break;
		}
		break;

	case WM_JABBER_CHECK_ONLINE:
		if (!param->ppro->m_bJabberOnline)
			EndDialog(hwndDlg, 0);
		break;

	case WM_DESTROY:
		param->ppro->m_hwndJabberAddBookmark = NULL;
		break;
	}
	return FALSE;
}