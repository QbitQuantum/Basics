static INT_PTR CALLBACK DlgProfileNew(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	struct DlgProfData *dat = (struct DlgProfData *)GetWindowLongPtr(hwndDlg, GWLP_USERDATA);
	switch (msg) {
	case WM_INITDIALOG:
		TranslateDialogDefault(hwndDlg);
		SetWindowLongPtr(hwndDlg, GWLP_USERDATA, lParam);
		dat = (struct DlgProfData *)lParam;
		{
			HWND hwndCombo = GetDlgItem(hwndDlg, IDC_PROFILEDRIVERS);

			// what, no plugins?!
			if (arDbPlugins.getCount() == 0) {
				EnableWindow(hwndCombo, FALSE);
				EnableWindow(GetDlgItem(hwndDlg, IDC_PROFILENAME), FALSE);
				ShowWindow(GetDlgItem(hwndDlg, IDC_NODBDRIVERS), TRUE);
			}
			else {
				for (int i = 0; i < arDbPlugins.getCount(); i++) {
					DATABASELINK *p = arDbPlugins[i];
					LRESULT index = SendMessage(hwndCombo, CB_ADDSTRING, 0, (LPARAM)TranslateTS(p->szFullName));
					SendMessage(hwndCombo, CB_SETITEMDATA, index, (LPARAM)p);
				}
			}

			// default item
			SendMessage(hwndCombo, CB_SETCURSEL, 0, 0);

			// subclass the profile name box
			mir_subclassWindow(GetDlgItem(hwndDlg, IDC_PROFILENAME), ProfileNameValidate);
		}

		// decide if there is a default profile name given in the INI and if it should be used
		if (dat->pd->noProfiles || (shouldAutoCreate(dat->pd->szProfile) && _taccess(dat->pd->szProfile, 0))) {
			TCHAR *profile = _tcsrchr(dat->pd->szProfile, '\\');
			if (profile) ++profile;
			else profile = dat->pd->szProfile;

			TCHAR *p = _tcsrchr(profile, '.');
			TCHAR c = 0;
			if (p) { c = *p; *p = 0; }

			SetDlgItemText(hwndDlg, IDC_PROFILENAME, profile);
			if (c) *p = c;
		}

		// focus on the textbox
		PostMessage(hwndDlg, WM_FOCUSTEXTBOX, 0, 0);
		return TRUE;

	case WM_FOCUSTEXTBOX:
		SetFocus(GetDlgItem(hwndDlg, IDC_PROFILENAME));
		break;

	case WM_INPUTCHANGED: // when input in the edit box changes
		SendMessage(GetParent(hwndDlg), PSM_CHANGED, 0, 0);
		EnableWindow(dat->hwndOK, GetWindowTextLength(GetDlgItem(hwndDlg, IDC_PROFILENAME)) > 0);
		break;

	case WM_SHOWWINDOW:
		if (wParam) {
			EnableWindow(dat->hwndSM, FALSE);
			SetWindowText(dat->hwndOK, TranslateT("&Create"));
			SendMessage(hwndDlg, WM_INPUTCHANGED, 0, 0);
		}
		break;

	case WM_NOTIFY:
		NMHDR *hdr = (NMHDR*)lParam;
		if (hdr && hdr->code == PSN_APPLY && dat && IsWindowVisible(hwndDlg)) {
			TCHAR szName[MAX_PATH];
			LRESULT curSel = SendDlgItemMessage(hwndDlg, IDC_PROFILEDRIVERS, CB_GETCURSEL, 0, 0);
			if (curSel == CB_ERR)
				break; // should never happen

			GetDlgItemText(hwndDlg, IDC_PROFILENAME, szName, SIZEOF(szName));
			if (szName[0] == 0)
				break;

			// profile placed in "profile_name" subfolder
			mir_sntprintf(dat->pd->szProfile, MAX_PATH, _T("%s\\%s\\%s.dat"), dat->pd->szProfileDir, szName, szName);
			dat->pd->newProfile = 1;
			dat->pd->dblink = (DATABASELINK *)SendDlgItemMessage(hwndDlg, IDC_PROFILEDRIVERS, CB_GETITEMDATA, (WPARAM)curSel, 0);

			if (CreateProfile(dat->pd->szProfile, dat->pd->dblink, hwndDlg) == 0)
				SetWindowLongPtr(hwndDlg, DWLP_MSGRESULT, PSNRET_INVALID_NOCHANGEPAGE);
		}
		break;
	}

	return FALSE;
}