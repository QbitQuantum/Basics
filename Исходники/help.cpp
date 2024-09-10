static INT_PTR CALLBACK helpDlgProc(HWND hwndDlg,UINT msg,WPARAM wParam,LPARAM lParam)
{
	HELPDLGDATA *dat = (HELPDLGDATA *)GetWindowLongPtr(hwndDlg, GWLP_USERDATA);

	switch(msg) {
	case WM_INITDIALOG:
		TranslateDialogDefault(hwndDlg);
		{
			hwndHelpDialog = hwndDlg;
			dat = (HELPDLGDATA*)mir_calloc(sizeof(HELPDLGDATA));
			SetWindowLongPtr(hwndDlg, GWLP_USERDATA, (LONG_PTR)dat);
			dat->vhs = (VARHELPINFO *)lParam;

			// set tabs
			int tabCount = 0;
			RECT rcTabs, rcParent;
			HWND hTab = GetDlgItem(hwndDlg, IDC_TABS);
			GetWindowRect(hTab, &rcTabs);
			GetWindowRect(hwndDlg, &rcParent);

			TCITEM tci = { 0 };
			HWND hPage, hShow = 0;
			if (dat->vhs->flags&VHF_TOKENS) {
				// token tab
				tci.mask = TCIF_TEXT | TCIF_PARAM;
				tci.pszText = TranslateT("Tokens");
				hPage = CreateDialogParam(hInst, MAKEINTRESOURCE(IDD_TOKENS_DIALOG), hwndDlg, tokenHelpDlgProc, (LPARAM)GetParent(hwndDlg));
				EnableThemeDialogTexture(hPage, ETDT_ENABLETAB);

				tci.lParam = (LPARAM)hPage;
				MoveWindow(hPage, (rcTabs.left - rcParent.left), (rcTabs.top - rcParent.top), (rcTabs.right - rcTabs.left) - 2 * iFrameX, (rcTabs.bottom - rcTabs.top) - 2 * iFrameY, TRUE);
				ShowWindow(hPage, SW_HIDE);
				TabCtrl_InsertItem(hTab, tabCount++, &tci);
				hShow = hShow == 0 ? hPage : hShow;
			}
			if (dat->vhs->flags&VHF_INPUT) {
				// input tab
				tci.mask = TCIF_TEXT | TCIF_PARAM;
				tci.pszText = TranslateT("Input");
				dat->hwndInputDlg = hPage = CreateDialogParam(hInst, MAKEINTRESOURCE(IDD_INPUT_DIALOG), hwndDlg, inputDlgProc, (LPARAM)GetParent(hwndDlg));
				EnableThemeDialogTexture(hPage, ETDT_ENABLETAB);

				tci.lParam = (LPARAM)hPage;
				MoveWindow(hPage, (rcTabs.left - rcParent.left), (rcTabs.top - rcParent.top), (rcTabs.right - rcTabs.left) - 2 * iFrameX, (rcTabs.bottom - rcTabs.top) - 2 * iFrameY, TRUE);
				ShowWindow(hPage, SW_HIDE);
				TabCtrl_InsertItem(hTab, tabCount++, &tci);
				hShow = hShow == 0 ? hPage : hShow;
				if ((dat->vhs->fi != NULL) && (dat->vhs->fi->szFormat != NULL)) {
					if (dat->vhs->fi->flags & FIF_UNICODE)
						SendMessage(hwndDlg, VARM_SETINPUTTEXT, 0, (LPARAM)dat->vhs->fi->tszFormat);
					else {

						WCHAR *wszFormatString = mir_a2t(dat->vhs->fi->szFormat);
						SendMessage(hwndDlg, VARM_SETINPUTTEXT, 0, (LPARAM)wszFormatString);
						mir_free(wszFormatString);

					}
				}
				else if (dat->vhs->hwndCtrl != NULL) {
					TCHAR *tszText = Hlp_GetWindowText(dat->vhs->hwndCtrl);
					if (tszText != NULL) {
						SendMessage(hwndDlg, VARM_SETINPUTTEXT, 0, (LPARAM)tszText);
						mir_free(tszText);
					}
				}
				if (dat->vhs->fi != NULL || dat->vhs->hwndCtrl != NULL) {
					SetDlgItemText(hwndDlg, IDC_CANCEL, TranslateT("Cancel"));
					ShowWindow(GetDlgItem(hwndDlg, IDC_OK), SW_SHOW);
				}
			}
			if ((dat->vhs->flags&VHF_SUBJECT) ||
				((dat->vhs->flags&VHF_INPUT) && (((dat->vhs->fi != NULL) && (dat->vhs->fi->hContact != NULL)) || (dat->vhs->flags&VHF_SETLASTSUBJECT)))) {
				// subject window is created, but not necessarily shown
				dat->hwndSubjectDlg = hPage = CreateDialogParam(hInst, MAKEINTRESOURCE(IDD_CLIST_DIALOG), hwndDlg, clistDlgProc, (LPARAM)GetParent(hwndDlg));
				EnableThemeDialogTexture(hPage, ETDT_ENABLETAB);

				MoveWindow(hPage, (rcTabs.left - rcParent.left), (rcTabs.top - rcParent.top), (rcTabs.right - rcTabs.left) - 2 * iFrameX, (rcTabs.bottom - rcTabs.top) - 2 * iFrameY, TRUE);
				ShowWindow(hPage, SW_HIDE);

				if ((dat->vhs->fi != NULL) && (dat->vhs->fi->hContact != NULL))
					SendMessage(hwndDlg, VARM_SETSUBJECT, (WPARAM)dat->vhs->fi->hContact, 0);
				else if (dat->vhs->flags&VHF_SETLASTSUBJECT)
					SendMessage(hwndDlg, VARM_SETSUBJECT, (WPARAM)INVALID_HANDLE_VALUE, 0);

				if (dat->vhs->flags&VHF_SUBJECT) {
					// create subject tab
					tci.lParam = (LPARAM)hPage;
					tci.mask = TCIF_TEXT | TCIF_PARAM;
					tci.pszText = TranslateT("%subject%");
					TabCtrl_InsertItem(hTab, tabCount++, &tci);
					hShow = hShow == 0 ? hPage : hShow;
				}
			}
			if ((dat->vhs->flags&VHF_EXTRATEXT) ||
				((dat->vhs->flags&VHF_INPUT) && (dat->vhs->fi != NULL) && (dat->vhs->fi->tszExtraText != NULL))) {
				// extratext window is created, but not necessarily shown
				dat->hwndExtraTextDlg = hPage = CreateDialogParam(hInst, MAKEINTRESOURCE(IDD_EXTRATEXT_DIALOG), hwndDlg, extratextDlgProc, (LPARAM)GetParent(hwndDlg));
				EnableThemeDialogTexture(hPage, ETDT_ENABLETAB);

				MoveWindow(hPage, (rcTabs.left - rcParent.left), (rcTabs.top - rcParent.top), (rcTabs.right - rcTabs.left) - 2 * iFrameX, (rcTabs.bottom - rcTabs.top) - 2 * iFrameY, TRUE);
				ShowWindow(hPage, SW_HIDE);
				if ((dat->vhs->fi != NULL) && (dat->vhs->fi->tszExtraText != NULL)) {
					if (dat->vhs->fi->flags & FIF_UNICODE)
						SendMessage(hwndDlg, VARM_SETEXTRATEXT, 0, (LPARAM)dat->vhs->fi->tszExtraText);
					else {

						WCHAR *wszSource = mir_a2t(dat->vhs->fi->szExtraText);
						SendMessage(hwndDlg, VARM_SETEXTRATEXT, 0, (LPARAM)wszSource);
						mir_free(wszSource);

					}
				}
				if (dat->vhs->flags&VHF_EXTRATEXT) {
					// create extratext tab
					tci.mask = TCIF_TEXT | TCIF_PARAM;
					tci.pszText = TranslateT("%extratext%");
					tci.lParam = (LPARAM)hPage;
					TabCtrl_InsertItem(hTab, tabCount++, &tci);
					hShow = hShow == 0 ? hPage : hShow;
				}
			}
			if (dat->vhs->flags&VHF_HELP) {
				// helpinfo tab
				tci.mask = TCIF_TEXT | TCIF_PARAM;
				tci.pszText = TranslateT("Help");
				hPage = CreateDialogParam(hInst, MAKEINTRESOURCE(IDD_HELPINFO_DIALOG), hwndDlg, helpInfoDlgProc, (LPARAM)GetParent(hwndDlg));
				EnableThemeDialogTexture(hPage, ETDT_ENABLETAB);

				tci.lParam = (LPARAM)hPage;
				MoveWindow(hPage, (rcTabs.left - rcParent.left), (rcTabs.top - rcParent.top), (rcTabs.right - rcTabs.left) - 2 * iFrameX, (rcTabs.bottom - rcTabs.top) - 2 * iFrameY, TRUE);
				ShowWindow(hPage, SW_HIDE);
				TabCtrl_InsertItem(hTab, tabCount++, &tci);
				hShow = hShow == 0 ? hPage : hShow;
			}
			Utils_RestoreWindowPositionNoMove(hwndDlg, NULL, MODULENAME, "help");
			SetWindowText(hwndDlg, TranslateT("Variables Help"));
			ShowWindow(hShow, SW_SHOW);
			break;
		}

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_OK:
			if ((dat->vhs->fi != NULL) && (!(dat->vhs->flags&VHF_DONTFILLSTRUCT))) {
				int len = SendMessage(hwndDlg, VARM_GETINPUTTEXTLENGTH, 0, 0);
				if (len > 0) {
					if ((dat->vhs->fi != NULL) && (!(dat->vhs->flags&VHF_DONTFILLSTRUCT))) {
						if (dat->vhs->fi->flags&FIF_UNICODE) {
							dat->vhs->fi->tszFormat = (TCHAR*)mir_calloc((len + 1)*sizeof(WCHAR));
							SendMessage(hwndDlg, VARM_GETINPUTTEXT, (WPARAM)len + 1, (LPARAM)dat->vhs->fi->tszFormat);
						}
						else {
							dat->vhs->fi->szFormat = (char*)mir_calloc(len + 1);
							SendMessageA(hwndDlg, VARM_GETINPUTTEXT, (WPARAM)len + 1, (LPARAM)dat->vhs->fi->szFormat);
						}
					}
				}
			}

			if (dat->vhs->hwndCtrl != NULL) {
				int len = SendMessage(hwndDlg, VARM_GETINPUTTEXTLENGTH, 0, 0);
				if (len > 0) {
					TCHAR *tszText;

					tszText = (TCHAR*)mir_calloc((len + 1)*sizeof(TCHAR));
					if (tszText != NULL) {
						SendMessage(hwndDlg, VARM_GETINPUTTEXT, (WPARAM)len + 1, (LPARAM)tszText);
						SetWindowText(dat->vhs->hwndCtrl, tszText);
						mir_free(tszText);
					}
				}
				SendMessage(GetParent(dat->vhs->hwndCtrl),
					WM_COMMAND,
					MAKEWPARAM(GetDlgCtrlID(dat->vhs->hwndCtrl),
					EN_CHANGE),
					(LPARAM)dat->vhs->hwndCtrl);
			}

			if ((dat->vhs->flags&VHF_FULLFILLSTRUCT) && (dat->vhs->fi != NULL)) {
				int len = SendMessage(hwndDlg, VARM_GETEXTRATEXTLENGTH, 0, 0);
				if (len > 0) {
					if (dat->vhs->fi->flags&FIF_UNICODE) {
						dat->vhs->fi->tszExtraText = (TCHAR*)mir_calloc((len + 1)*sizeof(WCHAR));
						SendMessage(hwndDlg, VARM_GETEXTRATEXT, (WPARAM)len + 1, (LPARAM)dat->vhs->fi->tszExtraText);
					}
					else {
						dat->vhs->fi->szExtraText = (char*)mir_calloc(len + 1);
						SendMessageA(hwndDlg, VARM_GETEXTRATEXT, (WPARAM)len + 1, (LPARAM)dat->vhs->fi->szExtraText);
					}
				}
				dat->vhs->fi->hContact = (MCONTACT)SendMessage(hwndDlg, VARM_GETSUBJECT, 0, 0);
			}
			// fall through

		case IDC_CANCEL:
			if (GetParent(hwndDlg) == NULL)
				DestroyWindow(hwndDlg);
			else
				EndDialog(hwndDlg, 0);
			break;
		}
		break;

	case VARM_SETSUBJECT:
		SetWindowLongPtr(hwndDlg, DWLP_MSGRESULT,
			SendMessage(dat->hwndSubjectDlg, VARM_SETSUBJECT, wParam, lParam));
		return TRUE;

	case VARM_GETSUBJECT:
		SetWindowLongPtr(hwndDlg, DWLP_MSGRESULT,
			SendMessage(dat->hwndSubjectDlg, VARM_GETSUBJECT, wParam, lParam));
		return TRUE;

	case VARM_SETEXTRATEXT:
		SetWindowLongPtr(hwndDlg, DWLP_MSGRESULT,
			SendMessage(dat->hwndExtraTextDlg, VARM_SETEXTRATEXT, wParam, lParam));
		return TRUE;

	case VARM_GETEXTRATEXTLENGTH:
		SetWindowLongPtr(hwndDlg, DWLP_MSGRESULT,
			SendMessage(dat->hwndExtraTextDlg, VARM_GETEXTRATEXTLENGTH, wParam, lParam));
		return TRUE;

	case VARM_GETEXTRATEXT:
		SetWindowLongPtr(hwndDlg, DWLP_MSGRESULT,
			SendMessage(dat->hwndExtraTextDlg, VARM_GETEXTRATEXT, wParam, lParam));
		return TRUE;

	case VARM_SETINPUTTEXT:
		SetWindowLongPtr(hwndDlg, DWLP_MSGRESULT,
			SendMessage(dat->hwndInputDlg, VARM_SETINPUTTEXT, wParam, lParam));
		return TRUE;

	case VARM_GETINPUTTEXTLENGTH:
		SetWindowLongPtr(hwndDlg, DWLP_MSGRESULT,
			SendMessage(dat->hwndInputDlg, VARM_GETINPUTTEXTLENGTH, wParam, lParam));
		return TRUE;

	case VARM_GETINPUTTEXT:
		SetWindowLongPtr(hwndDlg, DWLP_MSGRESULT,
			SendMessage(dat->hwndInputDlg, VARM_GETINPUTTEXT, wParam, lParam));
		return TRUE;

	case VARM_GETDIALOG:
		switch (wParam) {
		case VHF_INPUT:
			SetWindowLongPtr(hwndDlg, DWLP_MSGRESULT, (LONG_PTR)dat->hwndInputDlg);
			return TRUE;
		}
		break;

	case WM_GETMINMAXINFO:
		{
			int i, count;
			TCITEM tci;
			RECT rcParent;
			HWND hTab;
			MINMAXINFO pageMinMax;

			GetWindowRect(hwndDlg, &rcParent);
			// defaults
			((MINMAXINFO*)lParam)->ptMinTrackSize.x = 400;
			((MINMAXINFO*)lParam)->ptMinTrackSize.y = 400;
			hTab = GetDlgItem(hwndDlg, IDC_TABS);
			tci.mask = TCIF_PARAM;
			count = TabCtrl_GetItemCount(hTab);
			// return the largest of all pages
			for (i = 0; i < count; i++) {
				TabCtrl_GetItem(hTab, i, &tci);
				memset(&pageMinMax, 0, sizeof(pageMinMax));
				SendMessage((HWND)tci.lParam, WM_GETMINMAXINFO, wParam, (LPARAM)&pageMinMax);
				((MINMAXINFO*)lParam)->ptMinTrackSize.x = max(((MINMAXINFO*)lParam)->ptMinTrackSize.x, pageMinMax.ptMinTrackSize.x);
				((MINMAXINFO*)lParam)->ptMinTrackSize.y = max(((MINMAXINFO*)lParam)->ptMinTrackSize.y, pageMinMax.ptMinTrackSize.y);
			}
		}
		break;

	case WM_SIZE:
		if (!IsIconic(hwndDlg)) {
			UTILRESIZEDIALOG urd = { 0 };
			urd.cbSize = sizeof(urd);
			urd.hInstance = hInst;
			urd.hwndDlg = hwndDlg;
			urd.lParam = 0;
			// ! uses ANSI version !
			urd.lpTemplate = MAKEINTRESOURCEA(IDD_HELP_DIALOG);
			urd.pfnResizer = helpDialogResize;
			CallService(MS_UTILS_RESIZEDIALOG, 0, (LPARAM)&urd);

			SendMessage(hwndDlg, WM_MOVE, 0, 0);

			RECT rcTabs, rcParent;
			HWND hTab = GetDlgItem(hwndDlg, IDC_TABS);
			GetWindowRect(hTab, &rcTabs);
			GetWindowRect(hwndDlg, &rcParent);

			TCITEM tci;
			tci.mask = TCIF_PARAM;
			int count = TabCtrl_GetItemCount(hTab);
			for (int i = 0; i < count; i++) {
				TabCtrl_GetItem(GetDlgItem(hwndDlg, IDC_TABS), i, &tci);
				MoveWindow((HWND)tci.lParam, (rcTabs.left - rcParent.left), (rcTabs.top - rcParent.top), (rcTabs.right - rcTabs.left) - 2 * iFrameX, (rcTabs.bottom - rcTabs.top) - 2 * iFrameY, TRUE);
			}
		}
		break;

	case WM_NOTIFY:
		if ((((NMHDR*)lParam)->idFrom == IDC_TABS)) {
			if (((NMHDR*)lParam)->code == TCN_SELCHANGING) {
				TCITEM tci;

				tci.mask = TCIF_PARAM;
				TabCtrl_GetItem(GetDlgItem(hwndDlg, IDC_TABS), TabCtrl_GetCurSel(GetDlgItem(hwndDlg, IDC_TABS)), &tci);
				ShowWindow((HWND)tci.lParam, SW_HIDE);
			}
			else if (((NMHDR*)lParam)->code == TCN_SELCHANGE) {
				TCITEM tci;

				tci.mask = TCIF_PARAM;
				TabCtrl_GetItem(GetDlgItem(hwndDlg, IDC_TABS), TabCtrl_GetCurSel(GetDlgItem(hwndDlg, IDC_TABS)), &tci);
				ShowWindow((HWND)tci.lParam, SW_SHOW);
			}
		}
		break;

	case WM_CLOSE:
		if (GetParent(hwndDlg) == NULL)
			DestroyWindow(hwndDlg);
		else
			EndDialog(hwndDlg, 0);
		break;

	case WM_DESTROY:
		Utils_SaveWindowPosition(hwndDlg, NULL, MODULENAME, "help");

		HWND hTab = GetDlgItem(hwndDlg, IDC_TABS);

		TCITEM tci;
		tci.mask = TCIF_PARAM;
		int count = TabCtrl_GetItemCount(hTab);
		for (int i = 0; i < count; i++) {
			TabCtrl_GetItem(hTab, i, &tci);
			if (((HWND)tci.lParam != dat->hwndSubjectDlg) && ((HWND)tci.lParam != dat->hwndExtraTextDlg))
				DestroyWindow((HWND)tci.lParam);
		}

		// these windows might have been created, but not inserted as tabs
		if (IsWindow(dat->hwndSubjectDlg))
			DestroyWindow(dat->hwndSubjectDlg);

		if (IsWindow(dat->hwndExtraTextDlg))
			DestroyWindow(dat->hwndExtraTextDlg);

		mir_free(dat);
		dat = NULL;
		SetWindowLongPtr(hwndDlg, GWLP_USERDATA, 0);
		break;
	}

	return FALSE;
}