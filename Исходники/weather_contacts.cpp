// edit weather settings
// lParam = current contact
INT_PTR CALLBACK DlgProcChange(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam) 
{
	DBVARIANT dbv;
	TCHAR str[256], str2[256], city[256], filter[256], *pfilter, *chop;
	char loc[512];
	OPENFILENAME ofn;       // common dialog box structure
	MCONTACT hContact;
	WIDATA *sData;
	CntSetWndDataType *wndData = NULL;

	switch (msg) {
	case WM_INITDIALOG:
		TranslateDialogDefault(hwndDlg);

		wndData = ( CntSetWndDataType* )mir_alloc(sizeof(CntSetWndDataType));
		wndData->hContact = hContact = lParam;
		wndData->hRename = LoadSkinnedIcon(SKINICON_OTHER_RENAME);
		wndData->hUserDetail = LoadSkinnedIcon(SKINICON_OTHER_USERDETAILS);
		wndData->hFile = LoadSkinnedIcon(SKINICON_EVENT_FILE);
		wndData->hSrchAll = LoadSkinnedIcon(SKINICON_OTHER_SEARCHALL);

		SetWindowLongPtr(hwndDlg, GWLP_USERDATA, (LONG_PTR)wndData);

		// set button images
		SendDlgItemMessage(hwndDlg, IDC_GETNAME, BM_SETIMAGE, IMAGE_ICON, (LPARAM)wndData->hRename);
		SendDlgItemMessage(hwndDlg, IDC_SVCINFO, BM_SETIMAGE, IMAGE_ICON, (LPARAM)wndData->hUserDetail);
		SendDlgItemMessage(hwndDlg, IDC_BROWSE,  BM_SETIMAGE, IMAGE_ICON, (LPARAM)wndData->hFile);
		SendDlgItemMessage(hwndDlg, IDC_VIEW1,   BM_SETIMAGE, IMAGE_ICON, (LPARAM)wndData->hSrchAll);
		SendDlgItemMessage(hwndDlg, IDC_RESET1,  BM_SETIMAGE, IMAGE_ICON, (LPARAM)wndData->hRename);
		SendDlgItemMessage(hwndDlg, IDC_VIEW2,   BM_SETIMAGE, IMAGE_ICON, (LPARAM)wndData->hSrchAll);
		SendDlgItemMessage(hwndDlg, IDC_RESET2,  BM_SETIMAGE, IMAGE_ICON, (LPARAM)wndData->hRename);

		// make all buttons flat
		SendDlgItemMessage(hwndDlg, IDC_GETNAME, BUTTONSETASFLATBTN, TRUE, 0);
		SendDlgItemMessage(hwndDlg, IDC_SVCINFO, BUTTONSETASFLATBTN, TRUE, 0);
		SendDlgItemMessage(hwndDlg, IDC_BROWSE, BUTTONSETASFLATBTN, TRUE, 0);
		SendDlgItemMessage(hwndDlg, IDC_VIEW1, BUTTONSETASFLATBTN, TRUE, 0);
		SendDlgItemMessage(hwndDlg, IDC_RESET1, BUTTONSETASFLATBTN, TRUE, 0);
		SendDlgItemMessage(hwndDlg, IDC_VIEW2, BUTTONSETASFLATBTN, TRUE, 0);
		SendDlgItemMessage(hwndDlg, IDC_RESET2, BUTTONSETASFLATBTN, TRUE, 0);

		// set tooltip for the buttons
		SendDlgItemMessage(hwndDlg, IDC_GETNAME, BUTTONADDTOOLTIP, (WPARAM) LPGENT("Get city name from ID"), BATF_TCHAR);
		SendDlgItemMessage(hwndDlg, IDC_SVCINFO, BUTTONADDTOOLTIP, (WPARAM) LPGENT("Weather INI information"), BATF_TCHAR);
		SendDlgItemMessage(hwndDlg, IDC_BROWSE, BUTTONADDTOOLTIP, (WPARAM) LPGENT("Browse"), BATF_TCHAR);
		SendDlgItemMessage(hwndDlg, IDC_VIEW1, BUTTONADDTOOLTIP, (WPARAM) LPGENT("View webpage"), BATF_TCHAR);
		SendDlgItemMessage(hwndDlg, IDC_RESET1, BUTTONADDTOOLTIP, (WPARAM) LPGENT("Reset to default"), BATF_TCHAR);
		SendDlgItemMessage(hwndDlg, IDC_VIEW2, BUTTONADDTOOLTIP, (WPARAM) LPGENT("View webpage"), BATF_TCHAR);
		SendDlgItemMessage(hwndDlg, IDC_RESET2, BUTTONADDTOOLTIP, (WPARAM) LPGENT("Reset to default"), BATF_TCHAR);

		// save the handle for the contact
		WindowList_Add(hWindowList, hwndDlg, hContact);

		// start to get the settings
		// if the setting not exist, leave the dialog box blank
		if ( !db_get_ts(hContact, WEATHERPROTONAME, "ID", &dbv)) {
			SetDlgItemText(hwndDlg, IDC_ID, dbv.ptszVal);
			// check if the station is a default station
			CheckDlgButton(hwndDlg, IDC_DEFA, _tcscmp(dbv.ptszVal, opt.Default) != 0 ? BST_CHECKED : BST_UNCHECKED);
			db_free(&dbv);
		}
		if ( !db_get_ts(hContact, WEATHERPROTONAME, "Nick", &dbv)) {
			SetDlgItemText(hwndDlg, IDC_NAME, dbv.ptszVal);
			db_free(&dbv);
		}
		if ( !db_get_ts(hContact, WEATHERPROTONAME, "Log", &dbv)) {
			SetDlgItemText(hwndDlg, IDC_LOG, dbv.ptszVal);
			// if the log path is not empty, check the checkbox for external log
			if (dbv.ptszVal[0]) CheckDlgButton(hwndDlg, IDC_External, BST_CHECKED);
			db_free(&dbv);
		}
		// enable/disable the browse button depending on the value of external log checkbox
		EnableWindow(GetDlgItem(hwndDlg, IDC_BROWSE), (BYTE)IsDlgButtonChecked(hwndDlg, IDC_External));

		// other checkbox options
		CheckDlgButton(hwndDlg, IDC_DPop, db_get_b(hContact, WEATHERPROTONAME, "DPopUp", FALSE) ? BST_CHECKED : BST_UNCHECKED);
		CheckDlgButton(hwndDlg, IDC_DAutoUpdate, db_get_b(hContact, WEATHERPROTONAME, "DAutoUpdate", FALSE) ? BST_CHECKED : BST_UNCHECKED);
		CheckDlgButton(hwndDlg, IDC_Internal, db_get_b(hContact, WEATHERPROTONAME, "History", 0) ? BST_CHECKED : BST_UNCHECKED);

		if ( !db_get_ts(hContact, WEATHERPROTONAME, "InfoURL", &dbv)) {
			SetDlgItemText(hwndDlg, IDC_IURL, dbv.ptszVal);
			db_free(&dbv);
		}
		if ( !db_get_ts(hContact, WEATHERPROTONAME, "MapURL", &dbv)) {
			SetDlgItemText(hwndDlg, IDC_MURL, dbv.ptszVal);
			db_free(&dbv);
		}

		// display the dialog box and free memory
		Utils_RestoreWindowPositionNoMove(hwndDlg, NULL, WEATHERPROTONAME, "EditSetting_");
		ShowWindow(hwndDlg, SW_SHOW);
		break;

	case WM_COMMAND:
		wndData = (CntSetWndDataType*)GetWindowLongPtr(hwndDlg, GWLP_USERDATA);
		hContact = wndData ? wndData->hContact : NULL;

		switch(LOWORD(wParam)) {
		case IDC_ID:
			// check if there are 2 parts in the ID (svc/id) seperated by "/"
			// if not, don't let user change the setting
			GetDlgItemText(hwndDlg, IDC_ID, str, SIZEOF(str));
			chop = _tcsstr(str, _T("/"));
			if (chop == NULL)
				EnableWindow(GetDlgItem(hwndDlg, IDC_CHANGE), FALSE);
			else
				EnableWindow(GetDlgItem(hwndDlg, IDC_CHANGE), TRUE);
			break;

		case IDC_NAME:
			// check if station name is entered
			// if not, don't let user change the setting
			GetDlgItemText(hwndDlg, IDC_NAME, str, SIZEOF(str));
			EnableWindow(GetDlgItem(hwndDlg, IDC_CHANGE), str[0] != 0);
			break;

		case IDC_GETNAME: 
			{
				// the button for getting station name from the internet
				// this function uses the ID search for add/find weather station

				if ( !CheckSearch()) return TRUE;	// don't download if update is in progress
				// get the weather update data using the string in the ID field
				GetDlgItemText(hwndDlg, IDC_ID, str, SIZEOF(str));
				GetSvc(str);
				WIDATA *sData = GetWIData(str);
				GetDlgItemText(hwndDlg, IDC_ID, str, SIZEOF(str));
				GetID(str);
				// if ID search is available, do it
				if (sData->IDSearch.Available) {
					TCHAR *szData = NULL;

					// load the page
					mir_snprintf(loc, SIZEOF(loc), sData->IDSearch.SearchURL, str);
					str[0] = 0;
					if (InternetDownloadFile(loc, NULL, sData->UserAgent, &szData) == 0) {
						TCHAR *szInfo = szData;
						TCHAR* search = _tcsstr(szInfo, sData->IDSearch.NotFoundStr);

						// if the page is found (ie. valid ID), get the name of the city
						if (search == NULL)
							GetDataValue(&sData->IDSearch.Name, str, &szInfo);
					}
					// free memory
					mir_free(szData);

					NetlibHttpDisconnect();
				}
				// give no station name but only ID if the search is unavailable
				if (str[0] != 0)	SetDlgItemText(hwndDlg, IDC_NAME, str);
				break;
			}
		case IDC_External:
			// enable/disable the borwse button depending if the external log is enabled
			EnableWindow(GetDlgItem(hwndDlg, IDC_BROWSE), (BYTE)IsDlgButtonChecked(hwndDlg, IDC_External));
			if ( !(BYTE)IsDlgButtonChecked(hwndDlg, IDC_External)) return TRUE;

		case IDC_BROWSE:	// fall through
			// browse for the external log file
			GetDlgItemText(hwndDlg, IDC_LOG, str, SIZEOF(str));
			// Initialize OPENFILENAME
			memset(&ofn, 0, sizeof(OPENFILENAME));
			ofn.lStructSize = sizeof(OPENFILENAME);
			ofn.hwndOwner = hwndDlg;
			ofn.lpstrFile = str;
			ofn.nMaxFile = SIZEOF(str);
			// set filters
			_tcscpy(filter, TranslateT("Text Files"));
			_tcscat(filter, _T(" (*.txt)"));
			pfilter = filter + _tcslen(filter)+1;
			_tcscpy(pfilter, _T("*.txt"));
			pfilter = pfilter + _tcslen(pfilter)+1;
			_tcscpy(pfilter, TranslateT("All Files"));
			_tcscat(pfilter, _T(" (*.*)"));
			pfilter = pfilter + _tcslen(pfilter)+1;
			_tcscpy(pfilter, _T("*.*"));
			pfilter = pfilter + _tcslen(pfilter)+1;
			*pfilter = '\0';
			ofn.lpstrFilter = filter;
			ofn.nFilterIndex = 1;
			ofn.lpstrFileTitle = NULL;
			ofn.nMaxFileTitle = 0;
			ofn.lpstrInitialDir = NULL;
			ofn.Flags = OFN_PATHMUSTEXIST;

			// Display a Open dialog box and put the file name on the dialog
			if (GetOpenFileName(&ofn))
				SetDlgItemText(hwndDlg, IDC_LOG, ofn.lpstrFile);
			// if there is no log file specified, disable external logging
			EnableWindow(GetDlgItem(hwndDlg, IDC_CHANGE), ofn.lpstrFile[0] != 0);
			break;

		case IDC_VIEW1:
			// view the page for more info
			GetDlgItemText(hwndDlg, IDC_IURL, str, SIZEOF(str));
			if (str[0] == 0) return TRUE;
			GetDlgItemText(hwndDlg, IDC_ID, str2, SIZEOF(str2));
			OpenUrl(str, str2);
			break;

		case IDC_VIEW2:
			// view the page for weather map
			GetDlgItemText(hwndDlg, IDC_MURL, str, SIZEOF(str));
			if (str[0] == 0) return TRUE;
			GetDlgItemText(hwndDlg, IDC_ID, str2, SIZEOF(str2));
			OpenUrl(str, str2);
			break;

		case IDC_RESET1:
			// reset the more info url to service default
			GetDlgItemText(hwndDlg, IDC_ID, str, SIZEOF(str));
			GetSvc(str);
			sData = GetWIData(str);
			SetDlgItemTextA(hwndDlg, IDC_IURL, sData->DefaultURL);
			break;

		case IDC_RESET2:
			// reset the weathe map url to service default
			GetDlgItemText(hwndDlg, IDC_ID, str, SIZEOF(str));
			GetSvc(str);
			sData = GetWIData(str);
			SetDlgItemText(hwndDlg, IDC_MURL, sData->DefaultMap);
			break;

		case IDC_SVCINFO:
			// display the information of the ini file used by the weather station
			GetDlgItemText(hwndDlg, IDC_ID, str, SIZEOF(str));
			GetSvc(str);
			GetINIInfo(str);
			break;

		case IDC_CHANGE:
			// temporary disable the protocol while applying the change
			// start writing the new settings to database
			GetDlgItemText(hwndDlg, IDC_ID, str, SIZEOF(str));
			db_set_ts(hContact, WEATHERPROTONAME, "ID", str);
			if ((BYTE)IsDlgButtonChecked(hwndDlg, IDC_DEFA)) {	// if default station is set
				_tcscpy(opt.Default, str);
				opt.DefStn = hContact;
				db_set_ts(NULL, WEATHERPROTONAME, "Default", opt.Default);
			}
			GetDlgItemText(hwndDlg, IDC_NAME, city, SIZEOF(city));
			db_set_ts(hContact, WEATHERPROTONAME, "Nick", city);
			mir_sntprintf(str2, SIZEOF(str2), TranslateT("Current weather information for %s."), city);
			if ((BYTE)IsDlgButtonChecked(hwndDlg, IDC_External)) {
				GetDlgItemText(hwndDlg, IDC_LOG, str, SIZEOF(str));
				db_set_ts(hContact, WEATHERPROTONAME, "Log", str);
			}
			else db_unset(hContact, WEATHERPROTONAME, "Log");

			GetDlgItemText(hwndDlg, IDC_IURL, str, SIZEOF(str));
			db_set_ts(hContact, WEATHERPROTONAME, "InfoURL", str);

			GetDlgItemText(hwndDlg, IDC_MURL, str, SIZEOF(str));
			db_set_ts(hContact, WEATHERPROTONAME, "MapURL", str);
			db_set_w(hContact, WEATHERPROTONAME, "Status", ID_STATUS_OFFLINE);
			db_set_w(hContact, WEATHERPROTONAME, "StatusIcon", ID_STATUS_OFFLINE);
			AvatarDownloaded(hContact);
			db_set_ts(hContact, WEATHERPROTONAME, "About", str2);
			db_set_b(hContact, WEATHERPROTONAME, "History", (BYTE)IsDlgButtonChecked(hwndDlg, IDC_Internal));
			db_set_b(hContact, WEATHERPROTONAME, "Overwrite", (BYTE)IsDlgButtonChecked(hwndDlg, IDC_Overwrite));
			db_set_b(hContact, WEATHERPROTONAME, "File", (BYTE)IsDlgButtonChecked(hwndDlg, IDC_External));
			db_set_b(hContact, WEATHERPROTONAME, "DPopUp", (BYTE)IsDlgButtonChecked(hwndDlg, IDC_DPop));
			db_set_b(hContact, WEATHERPROTONAME, "DAutoUpdate", (BYTE)IsDlgButtonChecked(hwndDlg, IDC_DAutoUpdate));

			// re-enable the protocol and update the data for the station
			db_set_s(hContact, WEATHERPROTONAME, "LastCondition", "None");
			UpdateSingleStation(hContact, 0);

		case IDCANCEL:		// fall through
			// remove the dialog from window list and close it
			DestroyWindow(hwndDlg);
			break;
		}
		break;

	case WM_CLOSE:
		// remove the dialog from window list and close it
		DestroyWindow(hwndDlg);
		break;

	case WM_DESTROY:
		wndData = (CntSetWndDataType*)GetWindowLongPtr(hwndDlg, GWLP_USERDATA);
		Skin_ReleaseIcon(wndData->hFile);
		Skin_ReleaseIcon(wndData->hRename);
		Skin_ReleaseIcon(wndData->hSrchAll);
		Skin_ReleaseIcon(wndData->hUserDetail);
		mir_free(wndData);
		SetWindowLongPtr(hwndDlg, GWLP_USERDATA, 0);

		WindowList_Remove(hWindowList, hwndDlg);
		Utils_SaveWindowPosition(hwndDlg, NULL, WEATHERPROTONAME, "EditSetting_");
		break;
	}
	return FALSE;
}