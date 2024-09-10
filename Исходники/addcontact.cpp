INT_PTR CALLBACK AddContactDlgProc(HWND hdlg, UINT msg, WPARAM wparam, LPARAM lparam)
{
	AddDialogParam *acs = (AddDialogParam*)GetWindowLongPtr(hdlg, GWLP_USERDATA);

	switch (msg) {
	case WM_INITDIALOG:
		acs = new AddDialogParam();
		acs->handleType = HANDLE_SEARCHRESULT;
		SetWindowLongPtr(hdlg, GWLP_USERDATA, (LONG_PTR)acs);

		Utils_RestoreWindowPositionNoSize(hdlg, NULL, "AddContact", "");
		TranslateDialogDefault(hdlg);
		SendMessage(hdlg, WM_SETICON, ICON_BIG, (LPARAM)Skin_GetIcon(ICON_ADD,1));
		SendMessage(hdlg, WM_SETICON, ICON_SMALL, (LPARAM)Skin_GetIcon(ICON_ADD));
		HookEventMessage(ME_SKIN2_ICONSCHANGED, hdlg, DM_ADDCONTACT_CHANGEICONS);
		HookEventMessage(ME_PROTO_ACCLISTCHANGED, hdlg, DM_ADDCONTACT_CHANGEACCLIST);
		{
			TCHAR *szGroup;
			for (int i = 1; (szGroup = pcli->pfnGetGroupName(i, NULL)) != NULL; i++) {
				int id = SendDlgItemMessage(hdlg, IDC_GROUP, CB_ADDSTRING, 0, (LPARAM)szGroup);
				SendDlgItemMessage(hdlg, IDC_GROUP, CB_SETITEMDATA, (WPARAM)id, (LPARAM)i);
			}
		}
		SendDlgItemMessage(hdlg, IDC_GROUP, CB_INSERTSTRING, 0, (LPARAM)TranslateT("None"));
		SendDlgItemMessage(hdlg, IDC_GROUP, CB_SETCURSEL, 0, 0);
		{
			ptrA szProto(db_get_sa(NULL, "AddContact", "LastProto"));
			if (szProto)
				acs->proto = szProto;
		}
		if (AddContactDlgAccounts(hdlg, acs)) {
			// By default check these checkboxes
			CheckDlgButton(hdlg, IDC_ADDED, BST_CHECKED);
			CheckDlgButton(hdlg, IDC_AUTH, BST_CHECKED);
			AddContactDlgOpts(hdlg, acs->proto);
			EnableWindow(GetDlgItem(hdlg, IDOK), FALSE);
		}
		break;

	case WM_COMMAND:
		switch (LOWORD(wparam)) {
		case IDC_USERID:
			if (HIWORD(wparam) == EN_CHANGE) {
				TCHAR szUserId[256];
				if (GetDlgItemText(hdlg, IDC_USERID, szUserId, SIZEOF(szUserId))) {
					if (!IsWindowEnabled(GetDlgItem(hdlg, IDOK)))
						EnableWindow(GetDlgItem(hdlg, IDOK), TRUE);
				}
				else if (IsWindowEnabled(GetDlgItem(hdlg, IDOK)))
					EnableWindow(GetDlgItem(hdlg, IDOK), FALSE);
			}
			break;

		case IDC_PROTO:
			if (HIWORD(wparam) == CBN_SELCHANGE || HIWORD(wparam) == CBN_SELENDOK) {
				acs->proto = (char*)SendDlgItemMessage(hdlg, IDC_PROTO, CB_GETITEMDATA, (WPARAM)SendDlgItemMessage(hdlg, IDC_PROTO, CB_GETCURSEL, 0, 0), 0);
				// TODO remember last setting for each proto?
				AddContactDlgOpts(hdlg, acs->proto);
			}
			break;

		case IDC_ADDTEMP:
			AddContactDlgOpts(hdlg, acs->proto, TRUE);
			break;

		case IDC_AUTH:
			{
				DWORD flags = CallProtoService(acs->proto, PS_GETCAPS, PFLAGNUM_4, 0);
				if (flags & PF4_NOCUSTOMAUTH) {
					EnableWindow(GetDlgItem(hdlg, IDC_AUTHREQ), FALSE);
					EnableWindow(GetDlgItem(hdlg, IDC_AUTHGB), FALSE);
				}
				else {
					EnableWindow(GetDlgItem(hdlg, IDC_AUTHREQ), IsDlgButtonChecked(hdlg, IDC_AUTH));
					EnableWindow(GetDlgItem(hdlg, IDC_AUTHGB), IsDlgButtonChecked(hdlg, IDC_AUTH));
				}
			}
			break;

		case IDOK:
			{
				TCHAR szUserId[256];
				GetDlgItemText(hdlg, IDC_USERID, szUserId, SIZEOF(szUserId));

				if (*rtrimt(szUserId) == 0 ||
					(strstr(acs->proto, "GG") && _tcstoul(szUserId, NULL, 10) > INT_MAX) || // Gadu-Gadu protocol
					((CallProtoService(acs->proto, PS_GETCAPS, PFLAGNUM_1, 0) & PF1_NUMERICUSERID) && !_tcstoul(szUserId, NULL, 10)))
				{
					MessageBox(NULL,
						TranslateT("The contact cannot be added to your contact list. Please make sure the contact ID is entered correctly."),
						TranslateT("Add contact"), MB_OK | MB_ICONWARNING | MB_SETFOREGROUND | MB_TOPMOST);
					break;
				}

				PROTOSEARCHRESULT *psr;
				if (strstr(acs->proto, "TLEN")) { // Tlen protocol
					if (_tcschr(szUserId, '@') == NULL) {
						MessageBox(NULL,
							TranslateT("The contact cannot be added to your contact list. Please make sure the contact ID is entered correctly."),
							TranslateT("Add contact"), MB_OK | MB_ICONWARNING | MB_SETFOREGROUND | MB_TOPMOST);
						break;
					}
					psr = (PROTOSEARCHRESULT*)mir_calloc(sizeof(TLEN_SEARCH_RESULT));
					psr->cbSize = sizeof(TLEN_SEARCH_RESULT);
					mir_snprintf(((TLEN_SEARCH_RESULT*)psr)->jid, SIZEOF(((TLEN_SEARCH_RESULT*)psr)->jid), "%S", szUserId);
				}
				else {
					psr = (PROTOSEARCHRESULT*)mir_calloc(sizeof(PROTOSEARCHRESULT));
					psr->cbSize = sizeof(PROTOSEARCHRESULT);
				}

				psr->flags = PSR_TCHAR;
				psr->id = mir_tstrdup(szUserId);
				acs->psr = psr;

				HANDLE hContact = (HANDLE)CallProtoService(acs->proto, PS_ADDTOLIST, IsDlgButtonChecked(hdlg, IDC_ADDTEMP) ? PALF_TEMPORARY : 0, (LPARAM)acs->psr);
				if (hContact == NULL) {
					MessageBox(NULL,
						TranslateT("The contact cannot be added to your contact list. If you are not logged into the selected account, please try to do so. Also, make sure the contact ID is entered correctly."),
						TranslateT("Add contact"), MB_OK | MB_ICONWARNING | MB_SETFOREGROUND | MB_TOPMOST);
					break;
				}

				TCHAR szHandle[256];
				if (GetDlgItemText(hdlg, IDC_MYHANDLE, szHandle, SIZEOF(szHandle)))
					db_set_ts(hContact, "CList", "MyHandle", szHandle);

				int item = SendDlgItemMessage(hdlg, IDC_GROUP, CB_GETCURSEL, 0, 0);
				if (item > 0) {
					item = SendDlgItemMessage(hdlg, IDC_GROUP, CB_GETITEMDATA, item, 0);
					CallService(MS_CLIST_CONTACTCHANGEGROUP, (WPARAM)hContact, item);
				}

				if (!IsDlgButtonChecked(hdlg, IDC_ADDTEMP)) {
					db_unset(hContact, "CList", "NotOnList");

					if (IsDlgButtonChecked(hdlg, IDC_ADDED))
						CallContactService(hContact, PSS_ADDED, 0, 0);

					if (IsDlgButtonChecked(hdlg, IDC_AUTH)) {
						DWORD flags = CallProtoService(acs->proto, PS_GETCAPS, PFLAGNUM_4, 0);
						if (flags & PF4_NOCUSTOMAUTH)
							CallContactService(hContact, PSS_AUTHREQUESTT, 0, 0);
						else {
							TCHAR szReason[512];
							GetDlgItemText(hdlg, IDC_AUTHREQ, szReason, SIZEOF(szReason));
							CallContactService(hContact, PSS_AUTHREQUESTT, 0, (LPARAM)szReason);
						}
					}
				}

				if (GetAsyncKeyState(VK_CONTROL))
					CallService(MS_MSG_SENDMESSAGE, (WPARAM)hContact, (LPARAM)(const char*)NULL);
			}
			// fall through
		case IDCANCEL:
			if (GetParent(hdlg) == NULL)
				DestroyWindow(hdlg);
			else
				EndDialog(hdlg, 0);
		}
		break;

	case WM_CLOSE:
		/* if there is no parent for the dialog, its a modeless dialog and can't be killed using EndDialog() */
		if (GetParent(hdlg) == NULL)
			DestroyWindow(hdlg);
		else
			EndDialog(hdlg, 0);
		break;

	case DM_ADDCONTACT_CHANGEICONS:
		Skin_ReleaseIcon((HICON)SendMessage(hdlg, WM_SETICON, ICON_BIG, (LPARAM)Skin_GetIcon(ICON_ADD, 1)));
		Skin_ReleaseIcon((HICON)SendMessage(hdlg, WM_SETICON, ICON_SMALL, (LPARAM)Skin_GetIcon(ICON_ADD)));
		break;

	case DM_ADDCONTACT_CHANGEACCLIST:
		AddContactDlgAccounts(hdlg, acs);
		break;

	case WM_DESTROY:
		hAddDlg = NULL;
		Skin_ReleaseIcon((HICON)SendMessage(hdlg, WM_SETICON, ICON_BIG, 0));
		Skin_ReleaseIcon((HICON)SendMessage(hdlg, WM_SETICON, ICON_SMALL, 0));
		ImageList_Destroy((HIMAGELIST)SendDlgItemMessage(hdlg, IDC_PROTO, CBEM_GETIMAGELIST, 0, 0));
		if (acs) {
			db_set_s(NULL, "AddContact", "LastProto", acs->proto);
			if (acs->psr) {
				mir_free(acs->psr->nick);
				mir_free(acs->psr->firstName);
				mir_free(acs->psr->lastName);
				mir_free(acs->psr->email);
				mir_free(acs->psr);
			}
			delete acs;
		}
		Utils_SaveWindowPosition(hdlg, NULL, "AddContact", "");
		break;
	}

	return FALSE;
}