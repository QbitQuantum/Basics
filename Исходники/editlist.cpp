void ChangeInfoData::BeginListEdit(int iItem, RECT *rc, int iSetting, WORD wVKey)
{
	if (dataListEdit)
		dataListEdit->EndListEdit(0);

	POINT pt = { 0, 0 };
	ClientToScreen(hwndList, &pt);
	OffsetRect(rc, pt.x, pt.y);
	InflateRect(rc, -2, -2);
	rc->left -= 2;
	iEditItem = iItem;
	ListView_RedrawItems(hwndList, iEditItem, iEditItem);
	UpdateWindow(hwndList);

	dataListEdit = this;
	hwndListEdit = CreateWindowEx(WS_EX_TOOLWINDOW | WS_EX_TOPMOST, _T("LISTBOX"), _T(""), WS_POPUP | WS_BORDER | WS_VSCROLL,
											rc->left, rc->bottom, rc->right - rc->left, 150, NULL, NULL, hInst, NULL);
	SendMessage(hwndListEdit, WM_SETFONT, (WPARAM)hListFont, 0);
	int itemHeight = SendMessage(hwndListEdit, LB_GETITEMHEIGHT, 0, 0);

	const SettingItem &si = setting[iSetting];
	SettingItemData &sid = settingData[iSetting];
	FieldNamesItem *list = (FieldNamesItem*)si.pList;

	// some country codes were changed leaving old details uknown, convert it for the user
	if (list == countryField) {
		if (sid.value == 420)
			sid.value = 42; // conversion of obsolete codes (OMG!)
		else if (sid.value == 421)
			sid.value = 4201;
		else if (sid.value == 102)
			sid.value = 1201;
	}

	if (list == timezonesField) {
		tmi.prepareList(NULL, ppro->m_szModuleName, hwndListEdit, TZF_PLF_LB);
	}
	else {
		int j, n = ListBoxAddStringUtf(hwndListEdit, "Unspecified");
		for (j = 0;; j++)
			if (!list[j].text) {
				SendMessage(hwndListEdit, LB_SETITEMDATA, n, j);
				if ((sid.value == 0 && list[j].code == 0) || (si.dbType != DBVT_ASCIIZ && sid.value == list[j].code))
					SendMessage(hwndListEdit, LB_SETCURSEL, n, 0);
				break;
			}

		for (j = 0; list[j].text; j++) {
			char str[MAX_PATH];
			n = ListBoxAddStringUtf(hwndListEdit, list[j].text);
			SendMessage(hwndListEdit, LB_SETITEMDATA, n, j);
			if ((si.dbType == DBVT_ASCIIZ && (!strcmpnull((char*)sid.value, list[j].text))
				|| (si.dbType == DBVT_ASCIIZ && (!strcmpnull((char*)sid.value, ICQTranslateUtfStatic(list[j].text, str, MAX_PATH))))
				|| ((char*)sid.value == NULL && list[j].code == 0))
				|| (si.dbType != DBVT_ASCIIZ && sid.value == list[j].code))
				SendMessage(hwndListEdit, LB_SETCURSEL, n, 0);
		}
		SendMessage(hwndListEdit, LB_SETTOPINDEX, SendMessage(hwndListEdit, LB_GETCURSEL, 0, 0) - 3, 0);
	}

	int listCount = SendMessage(hwndListEdit, LB_GETCOUNT, 0, 0);
	if (itemHeight * listCount < 150)
		SetWindowPos(hwndListEdit, 0, 0, 0, rc->right - rc->left, itemHeight * listCount + GetSystemMetrics(SM_CYBORDER) * 2, SWP_NOZORDER | SWP_NOMOVE);
	mir_subclassWindow(hwndListEdit, ListEditSubclassProc);
	AnimateWindow(hwndListEdit, 200, AW_SLIDE | AW_ACTIVATE | AW_VER_POSITIVE);
	ShowWindow(hwndListEdit, SW_SHOW);
	SetFocus(hwndListEdit);
	if (wVKey)
		PostMessage(hwndListEdit, WM_KEYDOWN, wVKey, 0);
}