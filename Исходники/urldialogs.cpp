INT_PTR CALLBACK DlgProcUrlSend(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	struct UrlSendData* dat = (struct UrlSendData*)GetWindowLongPtr(hwndDlg, GWLP_USERDATA);
	switch (msg) {
	case WM_INITDIALOG:
		TranslateDialogDefault(hwndDlg);
		Window_SetIcon_IcoLib(hwndDlg, SKINICON_EVENT_URL);
		Button_SetIcon_IcoLib(hwndDlg, IDC_ADD, SKINICON_OTHER_ADDCONTACT, LPGEN("Add contact permanently to list"));
		Button_SetIcon_IcoLib(hwndDlg, IDC_DETAILS, SKINICON_OTHER_USERDETAILS, LPGEN("View user's details"));
		Button_SetIcon_IcoLib(hwndDlg, IDC_HISTORY, SKINICON_OTHER_HISTORY, LPGEN("View user's history"));
		Button_SetIcon_IcoLib(hwndDlg, IDC_USERMENU, SKINICON_OTHER_DOWNARROW, LPGEN("User menu"));

		SendDlgItemMessage(hwndDlg, IDC_MESSAGE, EM_LIMITTEXT, 450, 0);
		dat = (struct UrlSendData*)mir_alloc(sizeof(struct UrlSendData));
		SetWindowLongPtr(hwndDlg, GWLP_USERDATA, (LONG_PTR)dat);
		dat->hContact = lParam;
		dat->hAckEvent = NULL;
		dat->hSendId = NULL;
		dat->sendBuffer = NULL;

		WindowList_Add(hUrlWindowList, hwndDlg, dat->hContact);
		{
			TCHAR *str = pcli->pfnGetContactDisplayName(dat->hContact, 0);
			SetDlgItemText(hwndDlg, IDC_NAME, str);
		}

		GetOpenBrowserUrls(hwndDlg, GetDlgItem(hwndDlg, IDC_URLS));
		SendDlgItemMessage(hwndDlg, IDC_URLS, CB_SETCURSEL, 0, 0);
		if (SendDlgItemMessage(hwndDlg, IDC_URLS, CB_GETCOUNT, 0, 0))SendMessage(hwndDlg, WM_COMMAND, MAKEWPARAM(IDC_URLS, CBN_SELCHANGE), 0);
		EnableWindow(GetDlgItem(hwndDlg, IDOK), (SendDlgItemMessage(hwndDlg, IDC_URLS, CB_GETCURSEL, 0, 0) == CB_ERR)?FALSE:TRUE);
		Utils_RestoreWindowPositionNoSize(hwndDlg, NULL, "SRUrl", "send");
		mir_subclassWindow( GetDlgItem(hwndDlg, IDC_MESSAGE), SendEditSubclassProc);
		mir_subclassWindow( GetWindow(GetDlgItem(hwndDlg, IDC_URLS), GW_CHILD), SendEditSubclassProc);

		// From message dlg
		if ( !db_get_b(dat->hContact, "CList", "NotOnList", 0))
			ShowWindow(GetDlgItem(hwndDlg, IDC_ADD), SW_HIDE);

		SendMessage(hwndDlg, DM_UPDATETITLE, 0, 0);
		// From message dlg end
		return TRUE;

	case WM_DDE_DATA:
	case WM_DDE_ACK:
		return DdeMessage(hwndDlg, msg, wParam, lParam);

	case WM_TIMER:
		if (wParam == 0) {
			//ICQ sendurl timed out
			KillTimer(hwndDlg, 0);
			MessageBox(hwndDlg, TranslateT("Send timed out"), _T(""), MB_OK);
			EnableWindow(GetDlgItem(hwndDlg, IDOK), TRUE);
			EnableWindow(GetDlgItem(hwndDlg, IDC_URLS), TRUE);
			SendDlgItemMessage(hwndDlg, IDC_MESSAGE, EM_SETREADONLY, FALSE, 0);
		}
		break;

	case WM_MEASUREITEM:
		return CallService(MS_CLIST_MENUMEASUREITEM, wParam, lParam);

	case WM_DRAWITEM:
		{
			LPDRAWITEMSTRUCT dis = (LPDRAWITEMSTRUCT)lParam;
			if (dis->hwndItem == GetDlgItem(hwndDlg, IDC_PROTOCOL)) {
				char *szProto = GetContactProto(dat->hContact);
				if (szProto) {
					HICON hIcon = (HICON)CallProtoService(szProto, PS_LOADICON, PLI_PROTOCOL|PLIF_SMALL, 0);
					if (hIcon) {
						DrawIconEx(dis->hDC, dis->rcItem.left, dis->rcItem.top, hIcon, GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON), 0, NULL, DI_NORMAL);
						DestroyIcon(hIcon);
		}	}	}	}
		return CallService(MS_CLIST_MENUDRAWITEM, wParam, lParam);

	case DM_UPDATETITLE:
		sttUpdateTitle(hwndDlg, dat->hContact);
		break;

	case WM_COMMAND:
		if (CallService(MS_CLIST_MENUPROCESSCOMMAND, MAKEWPARAM(LOWORD(wParam), MPCF_CONTACTMENU), (LPARAM)dat->hContact))
			break;

		switch (LOWORD(wParam)) {
		case IDOK:
			{
				char *body, *url;
				int bodySize, urlSize;

				urlSize = GetWindowTextLength(GetDlgItem(hwndDlg, IDC_URLS))+1;
				url = (char*)mir_alloc(urlSize);
				GetDlgItemTextA(hwndDlg, IDC_URLS, url, urlSize);
				if (url[0] == 0) {
					mir_free(url);
					break;
				}
				bodySize = GetWindowTextLength(GetDlgItem(hwndDlg, IDC_MESSAGE))+1;
				body = (char*)mir_alloc(bodySize);
				GetDlgItemTextA(hwndDlg, IDC_MESSAGE, body, bodySize);

				dat->sendBuffer = (char*)mir_realloc(dat->sendBuffer, lstrlenA(url)+lstrlenA(body)+2);
				lstrcpyA(dat->sendBuffer, url);
				lstrcpyA(dat->sendBuffer+lstrlenA(url)+1, body);
				dat->hAckEvent = HookEventMessage(ME_PROTO_ACK, hwndDlg, HM_EVENTSENT);
				dat->hSendId = (HANDLE)CallContactService(dat->hContact, PSS_URL, 0, (LPARAM)dat->sendBuffer);
				mir_free(url);
				mir_free(body);

				//create a timeout timer
				SetTimer(hwndDlg, 0, TIMEOUT_URLSEND, NULL);
				EnableWindow(GetDlgItem(hwndDlg, IDOK), FALSE);
				EnableWindow(GetDlgItem(hwndDlg, IDC_URLS), FALSE);
				SendDlgItemMessage(hwndDlg, IDC_MESSAGE, EM_SETREADONLY, TRUE, 0);

				return TRUE;
			}

		case IDCANCEL:
			DestroyWindow(hwndDlg);
			return TRUE;

		case IDC_URLS:
			if (HIWORD(wParam) == CBN_SELCHANGE) {
				int i, urlSize;
				char *title;
				i = SendDlgItemMessage(hwndDlg, IDC_URLS, CB_GETCURSEL, 0, 0);
				title = (char*)SendDlgItemMessage(hwndDlg, IDC_URLS, CB_GETITEMDATA, (WPARAM)i, 0);
				SetDlgItemTextA(hwndDlg, IDC_MESSAGE, title);
				urlSize = SendDlgItemMessage(hwndDlg, IDC_URLS, CB_GETLBTEXTLEN, (WPARAM)i, 0);
				EnableWindow(GetDlgItem(hwndDlg, IDOK), (urlSize>0));
			}
			else if (HIWORD(wParam) == CBN_EDITCHANGE) {
				int urlSize = GetWindowTextLength(GetDlgItem(hwndDlg, IDC_URLS));
				EnableWindow(GetDlgItem(hwndDlg, IDOK), (urlSize>0));
			}
			break;
		case IDC_USERMENU:
			{
				RECT rc;
				HMENU hMenu = (HMENU)CallService(MS_CLIST_MENUBUILDCONTACT, (WPARAM)dat->hContact, 0);
				GetWindowRect(GetDlgItem(hwndDlg, IDC_USERMENU), &rc);
				TrackPopupMenu(hMenu, 0, rc.left, rc.bottom, 0, hwndDlg, NULL);
				DestroyMenu(hMenu);
			}
			break;

		case IDC_HISTORY:
			CallService(MS_HISTORY_SHOWCONTACTHISTORY, (WPARAM)dat->hContact, 0);
			break;

		case IDC_DETAILS:
			CallService(MS_USERINFO_SHOWDIALOG, (WPARAM)dat->hContact, 0);
			break;

		case IDC_ADD:
			ADDCONTACTSTRUCT acs = {0};
			acs.hContact = dat->hContact;
			acs.handleType = HANDLE_CONTACT;
			acs.szProto = 0;
			CallService(MS_ADDCONTACT_SHOW, (WPARAM)hwndDlg, (LPARAM)&acs);

			if ( !db_get_b(dat->hContact, "CList", "NotOnList", 0))
				ShowWindow(GetDlgItem(hwndDlg, IDC_ADD), FALSE);
		}
		break;

	case HM_EVENTSENT:
		{
			ACKDATA *ack = (ACKDATA*)lParam;
			if (ack->hProcess != dat->hSendId) break;
			if (ack->hContact != dat->hContact) break;
			if (ack->type != ACKTYPE_URL || ack->result != ACKRESULT_SUCCESS) break;

			DBEVENTINFO dbei = { sizeof(dbei) };
			dbei.eventType = EVENTTYPE_URL;
			dbei.flags = DBEF_SENT;
			dbei.szModule = GetContactProto(dat->hContact);
			dbei.timestamp = time(NULL);
			dbei.cbBlob = (DWORD)(strlen(dat->sendBuffer)+strlen(dat->sendBuffer+strlen(dat->sendBuffer)+1)+2);
			dbei.pBlob = (PBYTE)dat->sendBuffer;
			db_event_add(dat->hContact, &dbei);
			KillTimer(hwndDlg, 0);
			DestroyWindow(hwndDlg);
		}
		break;

	case WM_DESTROY:
		Window_FreeIcon_IcoLib(hwndDlg);
		Button_FreeIcon_IcoLib(hwndDlg, IDC_ADD);
		Button_FreeIcon_IcoLib(hwndDlg, IDC_DETAILS);
		Button_FreeIcon_IcoLib(hwndDlg, IDC_HISTORY);
		Button_FreeIcon_IcoLib(hwndDlg, IDC_USERMENU);

		WindowList_Remove(hUrlWindowList, hwndDlg);
		if (dat->hAckEvent) UnhookEvent(dat->hAckEvent);
		if (dat->sendBuffer != NULL) mir_free(dat->sendBuffer);
		mir_free(dat);
		Utils_SaveWindowPosition(hwndDlg, NULL, "SRUrl", "send");

		for (int i = SendDlgItemMessage(hwndDlg, IDC_URLS, CB_GETCOUNT, 0, 0)-1;i>=0;i--)
			mir_free((char*)SendDlgItemMessage(hwndDlg, IDC_URLS, CB_GETITEMDATA, i, 0));
		break;
	}

	return FALSE;
}