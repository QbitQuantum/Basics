static INT_PTR CALLBACK ReadAwayMsgDlgProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	AwayMsgDlgData *dat = (AwayMsgDlgData *)GetWindowLongPtr(hwndDlg, GWLP_USERDATA);

	switch (message) {
		case WM_INITDIALOG:
			TranslateDialogDefault(hwndDlg);
			dat = (AwayMsgDlgData *)mir_alloc(sizeof(AwayMsgDlgData));
			SetWindowLongPtr(hwndDlg, GWLP_USERDATA, (LONG_PTR)dat);

			dat->hContact = lParam;
			dat->hSeq = (HANDLE)CallContactService(dat->hContact, PSS_GETAWAYMSG, 0, 0);
			dat->hAwayMsgEvent = dat->hSeq ? HookEventMessage(ME_PROTO_ACK, hwndDlg, HM_AWAYMSG) : NULL;
			WindowList_Add(hWindowList, hwndDlg, dat->hContact);
			{
				TCHAR str[256], format[128];
				TCHAR *contactName = (TCHAR *)pcli->pfnGetContactDisplayName(dat->hContact, 0);
				char *szProto = GetContactProto(dat->hContact);
				WORD dwStatus = db_get_w(dat->hContact, szProto, "Status", ID_STATUS_OFFLINE);
				TCHAR *status = pcli->pfnGetStatusModeDescription(dwStatus, 0);

				GetWindowText(hwndDlg, format, _countof(format));
				mir_sntprintf(str, format, status, contactName);
				SetWindowText(hwndDlg, str);
				if (dat->hSeq) {
					GetDlgItemText(hwndDlg, IDC_RETRIEVING, format, _countof(format));
					mir_sntprintf(str, format, status);
				}
				else {
					mir_sntprintf(str, TranslateT("Failed to retrieve %s message."), status);
					SetDlgItemText(hwndDlg, IDOK, TranslateT("&Close"));
				}
				SetDlgItemText(hwndDlg, IDC_RETRIEVING, str);
				SendMessage(hwndDlg, WM_SETICON, ICON_BIG, (LPARAM)Skin_LoadProtoIcon(szProto, dwStatus));
				SendMessage(hwndDlg, WM_SETICON, ICON_SMALL, (LPARAM)Skin_LoadProtoIcon(szProto, dwStatus));
				EnableWindow(GetDlgItem(hwndDlg, IDC_COPY), FALSE);
			}
			Utils_RestoreWindowPosition(hwndDlg, lParam, "SRAway", "AwayMsgDlg");
			return TRUE;

		case HM_AWAYMSG:
		{
			ACKDATA *ack = (ACKDATA *)lParam;
			if (ack->hContact != dat->hContact || ack->type != ACKTYPE_AWAYMSG)
				break;
			if (ack->result != ACKRESULT_SUCCESS)
				break;
			if (dat->hAwayMsgEvent && ack->hProcess == dat->hSeq) {
				UnhookEvent(dat->hAwayMsgEvent);
				dat->hAwayMsgEvent = NULL;
			}

			TCHAR *tszMsg = StrNormNewline((TCHAR *)ack->lParam);
			SetDlgItemText(hwndDlg, IDC_MSG, tszMsg);
			mir_free(tszMsg);

			if (ack->lParam && *((char *)ack->lParam) != '\0')
				EnableWindow(GetDlgItem(hwndDlg, IDC_COPY), TRUE);
			ShowWindow(GetDlgItem(hwndDlg, IDC_RETRIEVING), SW_HIDE);
			ShowWindow(GetDlgItem(hwndDlg, IDC_MSG), SW_SHOW);
			SetDlgItemText(hwndDlg, IDOK, TranslateT("&Close"));
			break;
		}

		case WM_COMMAND:
			switch (LOWORD(wParam)) {
				case IDCANCEL:
				case IDOK:
					DestroyWindow(hwndDlg);
					break;

				case IDC_COPY:
					if (!OpenClipboard(hwndDlg))
						break;
					if (EmptyClipboard()) {
						TCHAR msg[1024];
						int len = GetDlgItemText(hwndDlg, IDC_MSG, msg, _countof(msg));
						if (len) {
							LPTSTR lptstrCopy;
							HGLOBAL hglbCopy = GlobalAlloc(GMEM_MOVEABLE, (len + 1) * sizeof(TCHAR));
							if (hglbCopy == NULL) {
								CloseClipboard();
								break;
							}
							lptstrCopy = (LPTSTR)GlobalLock(hglbCopy);
							memcpy(lptstrCopy, msg, len * sizeof(TCHAR));
							lptstrCopy[len] = (TCHAR)0;
							GlobalUnlock(hglbCopy);

							SetClipboardData(CF_UNICODETEXT, hglbCopy);

						}
					}
					CloseClipboard();
					break;
			}
			break;

		case WM_CLOSE:
			DestroyWindow(hwndDlg);
			break;

		case WM_DESTROY:
			if (dat->hAwayMsgEvent)
				UnhookEvent(dat->hAwayMsgEvent);
			Utils_SaveWindowPosition(hwndDlg, dat->hContact, "SRAway", "AwayMsgDlg");
			WindowList_Remove(hWindowList, hwndDlg);
			IcoLib_ReleaseIcon((HICON)SendMessage(hwndDlg, WM_SETICON, ICON_BIG, NULL));
			IcoLib_ReleaseIcon((HICON)SendMessage(hwndDlg, WM_SETICON, ICON_SMALL, NULL));
			mir_free(dat);
			break;
	}
	return FALSE;
}