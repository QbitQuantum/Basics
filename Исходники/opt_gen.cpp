INT_PTR CALLBACK DlgProcPopupGeneral(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static bool bDlgInit = false;	// some controls send WM_COMMAND before or during WM_INITDIALOG

	static OPTTREE_OPTION *statusOptions = NULL;
	static int statusOptionsCount = 0;
	if (statusOptions) {
		int index;
		if (OptTree_ProcessMessage(hwnd, msg, wParam, lParam, &index, IDC_STATUSES, statusOptions, statusOptionsCount))
			return TRUE;
	}

	switch (msg) {
	case WM_INITDIALOG:
		// Seconds of delay
		CheckDlgButton(hwnd, IDC_INFINITEDELAY, PopupOptions.InfiniteDelay ? BST_CHECKED : BST_UNCHECKED);
		CheckDlgButton(hwnd, IDC_LEAVEHOVERED, PopupOptions.LeaveHovered ? BST_CHECKED : BST_UNCHECKED);
		EnableWindow(GetDlgItem(hwnd, IDC_SECONDS), !PopupOptions.InfiniteDelay);
		EnableWindow(GetDlgItem(hwnd, IDC_SECONDS_STATIC1), !PopupOptions.InfiniteDelay);
		EnableWindow(GetDlgItem(hwnd, IDC_SECONDS_STATIC2), !PopupOptions.InfiniteDelay);
		EnableWindow(GetDlgItem(hwnd, IDC_LEAVEHOVERED), !PopupOptions.InfiniteDelay);
		SetDlgItemInt(hwnd, IDC_SECONDS, PopupOptions.Seconds, FALSE);
		SendDlgItemMessage(hwnd, IDC_SECONDS_SPIN, UDM_SETRANGE, 0, (LPARAM)MAKELONG(SETTING_LIFETIME_MAX, SETTING_LIFETIME_MIN));

		// Dynamic Resize
		CheckDlgButton(hwnd, IDC_DYNAMICRESIZE, PopupOptions.DynamicResize ? BST_CHECKED : BST_UNCHECKED);
		SetDlgItemText(hwnd, IDC_USEMAXIMUMWIDTH, PopupOptions.DynamicResize ? LPGENT("Maximum width") : LPGENT("Width"));
		// Minimum Width
		CheckDlgButton(hwnd, IDC_USEMINIMUMWIDTH, PopupOptions.UseMinimumWidth ? BST_CHECKED : BST_UNCHECKED);
		SendDlgItemMessage(hwnd, IDC_MINIMUMWIDTH_SPIN, UDM_SETRANGE, 0, (LPARAM)MAKELONG(SETTING_MAXIMUMWIDTH_MAX, SETTING_MINIMUMWIDTH_MIN));
		SetDlgItemInt(hwnd, IDC_MINIMUMWIDTH, PopupOptions.MinimumWidth, FALSE);
		// Maximum Width
		PopupOptions.UseMaximumWidth = PopupOptions.DynamicResize ? PopupOptions.UseMaximumWidth : TRUE;
		CheckDlgButton(hwnd, IDC_USEMAXIMUMWIDTH, PopupOptions.UseMaximumWidth ? BST_CHECKED : BST_UNCHECKED);
		SendDlgItemMessage(hwnd, IDC_MAXIMUMWIDTH_SPIN, UDM_SETRANGE, 0, (LPARAM)MAKELONG(SETTING_MAXIMUMWIDTH_MAX, SETTING_MINIMUMWIDTH_MIN));
		SetDlgItemInt(hwnd, IDC_MAXIMUMWIDTH, PopupOptions.MaximumWidth, FALSE);
		// And finally let's enable/disable them.
		EnableWindow(GetDlgItem(hwnd, IDC_USEMINIMUMWIDTH), PopupOptions.DynamicResize);
		EnableWindow(GetDlgItem(hwnd, IDC_MINIMUMWIDTH), PopupOptions.DynamicResize && PopupOptions.UseMinimumWidth);
		EnableWindow(GetDlgItem(hwnd, IDC_MINIMUMWIDTH_SPIN), PopupOptions.DynamicResize && PopupOptions.UseMinimumWidth);
		EnableWindow(GetDlgItem(hwnd, IDC_MAXIMUMWIDTH), PopupOptions.UseMaximumWidth);
		EnableWindow(GetDlgItem(hwnd, IDC_MAXIMUMWIDTH_SPIN), PopupOptions.UseMaximumWidth);

		// Position combobox.
		{
			HWND hCtrl = GetDlgItem(hwnd, IDC_WHERE);
			ComboBox_SetItemData(hCtrl, ComboBox_AddString(hCtrl, TranslateT("Upper left corner")), POS_UPPERLEFT);
			ComboBox_SetItemData(hCtrl, ComboBox_AddString(hCtrl, TranslateT("Lower left corner")), POS_LOWERLEFT);
			ComboBox_SetItemData(hCtrl, ComboBox_AddString(hCtrl, TranslateT("Lower right corner")), POS_LOWERRIGHT);
			ComboBox_SetItemData(hCtrl, ComboBox_AddString(hCtrl, TranslateT("Upper right corner")), POS_UPPERRIGHT);
			SendDlgItemMessage(hwnd, IDC_WHERE, CB_SETCURSEL, PopupOptions.Position, 0);
		}
		// Configure popup area
		{
			HWND hCtrl = GetDlgItem(hwnd, IDC_CUSTOMPOS);
			SendMessage(hCtrl, BUTTONSETASFLATBTN, TRUE, 0);
			SendMessage(hCtrl, BUTTONADDTOOLTIP, (WPARAM)_T("Popup area"), BATF_TCHAR);
			SendMessage(hCtrl, BM_SETIMAGE, IMAGE_ICON, (LPARAM)LoadIconEx(IDI_RESIZE));
		}
		// Spreading combobox
		{
			HWND hCtrl = GetDlgItem(hwnd, IDC_LAYOUT);
			ComboBox_SetItemData(hCtrl, ComboBox_AddString(hCtrl, TranslateT("Horizontal")), SPREADING_HORIZONTAL);
			ComboBox_SetItemData(hCtrl, ComboBox_AddString(hCtrl, TranslateT("Vertical")), SPREADING_VERTICAL);
			SendDlgItemMessage(hwnd, IDC_LAYOUT, CB_SETCURSEL, PopupOptions.Spreading, 0);
		}
		// miscellaneous
		CheckDlgButton(hwnd, IDC_REORDERPOPUPS, PopupOptions.ReorderPopups ? BST_CHECKED : BST_UNCHECKED);

		// Popup enabled
		CheckDlgButton(hwnd, IDC_POPUPENABLED, PopupOptions.ModuleIsEnabled ? BST_UNCHECKED : BST_CHECKED);
		CheckDlgButton(hwnd, IDC_DISABLEINFS, PopupOptions.DisableWhenFullscreen ? BST_CHECKED : BST_UNCHECKED);
		EnableWindow(GetDlgItem(hwnd, IDC_DISABLEINFS), PopupOptions.ModuleIsEnabled);
		EnableWindow(GetDlgItem(hwnd, IDC_STATUSES), PopupOptions.ModuleIsEnabled);

		// new status options
		{
			int protocolCount = 0;
			PROTOACCOUNT **protocols;
			Proto_EnumAccounts(&protocolCount, &protocols);
			DWORD globalFlags = 0;
			for (int i = 0; i < protocolCount; ++i) {
				if (!protocols[i]->bIsVirtual) {
					DWORD protoFlags = CallProtoService(protocols[i]->szModuleName, PS_GETCAPS, PFLAGNUM_2, 0);
					globalFlags |= protoFlags;
					statusOptionsCount += CountStatusModes(protoFlags);
				}
			}
			statusOptionsCount += CountStatusModes(globalFlags);

			statusOptions = new OPTTREE_OPTION[statusOptionsCount];

			int pos = AddStatusModes(statusOptions, 0, LPGENT("Global Status"), globalFlags);
			for (int i = 0; i < protocolCount; ++i) {
				if (!protocols[i]->bIsVirtual) {
					DWORD protoFlags = CallProtoService(protocols[i]->szModuleName, PS_GETCAPS, PFLAGNUM_2, 0);
					if (!CountStatusModes(protoFlags))
						continue;

					TCHAR prefix[128];
					mir_sntprintf(prefix, _countof(prefix), LPGENT("Protocol Status")_T("/%s"), protocols[i]->tszAccountName);
					pos = AddStatusModes(statusOptions, pos, prefix, protoFlags);
				}
			}

			int index;
			OptTree_ProcessMessage(hwnd, msg, wParam, lParam, &index, IDC_STATUSES, statusOptions, statusOptionsCount);

			for (int i = 0; i < protocolCount; ++i) {
				if (!protocols[i]->bIsVirtual) {
					DWORD protoFlags = CallProtoService(protocols[i]->szModuleName, PS_GETCAPS, PFLAGNUM_2, 0);
					if (!CountStatusModes(protoFlags))
						continue;

					char prefix[128];
					mir_snprintf(prefix, _countof(prefix), "Protocol Status/%s", protocols[i]->szModuleName);

					TCHAR pszSettingName[256];
					mir_sntprintf(pszSettingName, _countof(pszSettingName), LPGENT("Protocol Status")_T("/%s"), protocols[i]->tszAccountName);
					OptTree_SetOptions(hwnd, IDC_STATUSES, statusOptions, statusOptionsCount, db_get_dw(NULL, MODULNAME, prefix, 0), pszSettingName);
				}
			}
			OptTree_SetOptions(hwnd, IDC_STATUSES, statusOptions, statusOptionsCount, db_get_dw(NULL, MODULNAME, "Global Status", 0), LPGENT("Global Status"));
		}

		TranslateDialogDefault(hwnd);	// do it on end of WM_INITDIALOG
		bDlgInit = true;
		return TRUE;

	case WM_COMMAND:
		switch (HIWORD(wParam)) {
		case BN_CLICKED:	// Button controls
			switch (LOWORD(wParam)) {
			case IDC_INFINITEDELAY:
				PopupOptions.InfiniteDelay = !PopupOptions.InfiniteDelay;
				EnableWindow(GetDlgItem(hwnd, IDC_SECONDS), !PopupOptions.InfiniteDelay);
				EnableWindow(GetDlgItem(hwnd, IDC_SECONDS_STATIC1), !PopupOptions.InfiniteDelay);
				EnableWindow(GetDlgItem(hwnd, IDC_SECONDS_STATIC2), !PopupOptions.InfiniteDelay);
				EnableWindow(GetDlgItem(hwnd, IDC_LEAVEHOVERED), !PopupOptions.InfiniteDelay);
				SendMessage(GetParent(hwnd), PSM_CHANGED, 0, 0);
				break;

			case IDC_LEAVEHOVERED:
				PopupOptions.LeaveHovered = !PopupOptions.LeaveHovered;
				SendMessage(GetParent(hwnd), PSM_CHANGED, 0, 0);
				break;

			case IDC_DYNAMICRESIZE:
				PopupOptions.DynamicResize = !PopupOptions.DynamicResize;
				EnableWindow(GetDlgItem(hwnd, IDC_USEMINIMUMWIDTH), PopupOptions.DynamicResize);
				EnableWindow(GetDlgItem(hwnd, IDC_MINIMUMWIDTH), PopupOptions.DynamicResize && PopupOptions.UseMinimumWidth);
				EnableWindow(GetDlgItem(hwnd, IDC_MINIMUMWIDTH_SPIN), PopupOptions.DynamicResize && PopupOptions.UseMinimumWidth);
				SetDlgItemText(hwnd, IDC_USEMAXIMUMWIDTH, PopupOptions.DynamicResize ? TranslateT("Maximum width") : TranslateT("Width"));
				if (!PopupOptions.DynamicResize) {
					PopupOptions.UseMaximumWidth = TRUE;
					CheckDlgButton(hwnd, IDC_USEMAXIMUMWIDTH, BST_CHECKED);
					EnableWindow(GetDlgItem(hwnd, IDC_USEMAXIMUMWIDTH), TRUE);
					EnableWindow(GetDlgItem(hwnd, IDC_MAXIMUMWIDTH), TRUE);
					EnableWindow(GetDlgItem(hwnd, IDC_MAXIMUMWIDTH_SPIN), TRUE);
				}
				SendMessage(GetParent(hwnd), PSM_CHANGED, 0, 0);
				break;

			case IDC_USEMINIMUMWIDTH:
				PopupOptions.UseMinimumWidth = !PopupOptions.UseMinimumWidth;
				EnableWindow(GetDlgItem(hwnd, IDC_MINIMUMWIDTH), PopupOptions.UseMinimumWidth);
				EnableWindow(GetDlgItem(hwnd, IDC_MINIMUMWIDTH_SPIN), PopupOptions.UseMinimumWidth);
				SendMessage(GetParent(hwnd), PSM_CHANGED, 0, 0);
				break;

			case IDC_USEMAXIMUMWIDTH:
				PopupOptions.UseMaximumWidth = Button_GetCheck((HWND)lParam);
				if (!PopupOptions.DynamicResize) { // ugly - set always on if DynamicResize = off
					CheckDlgButton(hwnd, LOWORD(wParam), BST_CHECKED);
					PopupOptions.UseMaximumWidth = TRUE;
				}
				EnableWindow(GetDlgItem(hwnd, IDC_MAXIMUMWIDTH), PopupOptions.UseMaximumWidth);
				EnableWindow(GetDlgItem(hwnd, IDC_MAXIMUMWIDTH_SPIN), PopupOptions.UseMaximumWidth);
				SendMessage(GetParent(hwnd), PSM_CHANGED, 0, 0);
				break;

			case IDC_CUSTOMPOS:
			{
				RECT rcButton, rcBox;
				HWND hwndBox = CreateDialog(hInst, MAKEINTRESOURCE(IDD_POSITION), NULL, PositionBoxDlgProc);
				GetWindowRect((HWND)lParam, &rcButton);
				GetWindowRect(hwndBox, &rcBox);
				MoveWindow(hwndBox,
					rcButton.right - (rcBox.right - rcBox.left) + 15,
					rcButton.bottom + 3,
					rcBox.right - rcBox.left,
					rcBox.bottom - rcBox.top,
					FALSE);

				SetWindowLongPtr(hwndBox, GWL_EXSTYLE, GetWindowLongPtr(hwndBox, GWL_EXSTYLE) | WS_EX_LAYERED);
				SetLayeredWindowAttributes(hwndBox, NULL, 0, LWA_ALPHA);
				ShowWindow(hwndBox, SW_SHOW);
				for (int i = 0; i <= 255; i += 15) {
					SetLayeredWindowAttributes(hwndBox, NULL, i, LWA_ALPHA);
					UpdateWindow(hwndBox);
					Sleep(1);
				}
				SetWindowLongPtr(hwndBox, GWL_EXSTYLE, GetWindowLongPtr(hwndBox, GWL_EXSTYLE) & ~WS_EX_LAYERED);

				ShowWindow(hwndBox, SW_SHOW);
				SendMessage(GetParent(hwnd), PSM_CHANGED, 0, 0);
			}
			break;

			case IDC_REORDERPOPUPS:
			{
				PopupOptions.ReorderPopups = !PopupOptions.ReorderPopups;
				PopupOptions.ReorderPopupsWarning = PopupOptions.ReorderPopups ? db_get_b(NULL, MODULNAME, "ReorderPopupsWarning", TRUE) : TRUE;
				SendMessage(GetParent(hwnd), PSM_CHANGED, 0, 0);
			}
			break;

			case IDC_POPUPENABLED:
			{
				int chk = IsDlgButtonChecked(hwnd, IDC_POPUPENABLED);
				if (PopupOptions.ModuleIsEnabled&&chk || !PopupOptions.ModuleIsEnabled && !chk)
					svcEnableDisableMenuCommand(0, 0);
				EnableWindow(GetDlgItem(hwnd, IDC_STATUSES), PopupOptions.ModuleIsEnabled);
				EnableWindow(GetDlgItem(hwnd, IDC_DISABLEINFS), PopupOptions.ModuleIsEnabled);
			}
			break;

			case IDC_DISABLEINFS:
				PopupOptions.DisableWhenFullscreen = !PopupOptions.DisableWhenFullscreen;
				SendMessage(GetParent(hwnd), PSM_CHANGED, 0, 0);
				break;

			case IDC_PREVIEW:
				PopupPreview();
				break;
			}
			break;

		case CBN_SELCHANGE:		// ComboBox controls
			switch (LOWORD(wParam)) {
				// lParam = Handle to the control
			case IDC_WHERE:
				PopupOptions.Position = ComboBox_GetItemData((HWND)lParam, ComboBox_GetCurSel((HWND)lParam));
				SendMessage(GetParent(hwnd), PSM_CHANGED, 0, 0);
				break;
			case IDC_LAYOUT:
				PopupOptions.Spreading = ComboBox_GetItemData((HWND)lParam, ComboBox_GetCurSel((HWND)lParam));
				SendMessage(GetParent(hwnd), PSM_CHANGED, 0, 0);
				break;
			}
			break;

		case EN_CHANGE:			// Edit controls change
			if (!bDlgInit) break;
			switch (LOWORD(wParam)) {
				// lParam = Handle to the control
			case IDC_SECONDS:
			{
				int seconds = GetDlgItemInt(hwnd, LOWORD(wParam), NULL, FALSE);
				if (seconds >= SETTING_LIFETIME_MIN &&
					seconds <= SETTING_LIFETIME_MAX &&
					seconds != PopupOptions.Seconds) {
					PopupOptions.Seconds = seconds;
					SendMessage(GetParent(hwnd), PSM_CHANGED, 0, 0);
				}
			}
			break;
			case IDC_MINIMUMWIDTH:
			{
				int temp = GetDlgItemInt(hwnd, IDC_MINIMUMWIDTH, NULL, FALSE);
				if (temp >= SETTING_MINIMUMWIDTH_MIN &&
					temp <= SETTING_MAXIMUMWIDTH_MAX &&
					temp != PopupOptions.MinimumWidth) {
					PopupOptions.MinimumWidth = temp;
					SendMessage(GetParent(hwnd), PSM_CHANGED, 0, 0);
				}
			}
			break;
			case IDC_MAXIMUMWIDTH:
			{
				int temp = GetDlgItemInt(hwnd, IDC_MAXIMUMWIDTH, NULL, FALSE);
				if (temp >= SETTING_MINIMUMWIDTH_MIN &&
					temp <= SETTING_MAXIMUMWIDTH_MAX &&
					temp != PopupOptions.MaximumWidth) {
					PopupOptions.MaximumWidth = temp;
					SendMessage(GetParent(hwnd), PSM_CHANGED, 0, 0);
				}
			}
			break;
			}// end switch(idCtrl)
			break;

		case EN_KILLFOCUS:		// Edit controls lost fokus
			switch (LOWORD(wParam)) {
				// lParam = Handle to the control
			case IDC_SECONDS:
			{
				int seconds = GetDlgItemInt(hwnd, LOWORD(wParam), NULL, FALSE);
				if (seconds > SETTING_LIFETIME_MAX)
					PopupOptions.Seconds = SETTING_LIFETIME_MAX;
				else if (seconds < SETTING_LIFETIME_MIN)
					PopupOptions.Seconds = SETTING_LIFETIME_MIN;
				if (seconds != PopupOptions.Seconds) {
					SetDlgItemInt(hwnd, LOWORD(wParam), PopupOptions.Seconds, FALSE);
					ErrorMSG(SETTING_LIFETIME_MIN, SETTING_LIFETIME_MAX);
					SetFocus((HWND)lParam);
				}
			}
			break;
			case IDC_MINIMUMWIDTH:
			{
				int temp = GetDlgItemInt(hwnd, LOWORD(wParam), NULL, FALSE);
				if (temp < SETTING_MINIMUMWIDTH_MIN)
					PopupOptions.MinimumWidth = SETTING_MINIMUMWIDTH_MIN;
				else if (temp > SETTING_MAXIMUMWIDTH_MAX)
					PopupOptions.MinimumWidth = SETTING_MAXIMUMWIDTH_MAX;
				if (temp != PopupOptions.MinimumWidth) {
					SetDlgItemInt(hwnd, LOWORD(wParam), PopupOptions.MinimumWidth, FALSE);
					ErrorMSG(SETTING_MINIMUMWIDTH_MIN, SETTING_MAXIMUMWIDTH_MAX);
					SetFocus((HWND)lParam);
					break;
				}
				if (temp > PopupOptions.MaximumWidth) {
					PopupOptions.MaximumWidth = min(temp, SETTING_MAXIMUMWIDTH_MAX);
					SetDlgItemInt(hwnd, IDC_MAXIMUMWIDTH, PopupOptions.MaximumWidth, FALSE);
				}
			}
			break;
			case IDC_MAXIMUMWIDTH:
			{
				int temp = GetDlgItemInt(hwnd, LOWORD(wParam), NULL, FALSE);
				if (temp >= SETTING_MAXIMUMWIDTH_MAX)
					PopupOptions.MaximumWidth = SETTING_MAXIMUMWIDTH_MAX;
				else if (temp < SETTING_MINIMUMWIDTH_MIN)
					PopupOptions.MaximumWidth = SETTING_MINIMUMWIDTH_MIN;
				if (temp != PopupOptions.MaximumWidth) {
					SetDlgItemInt(hwnd, LOWORD(wParam), PopupOptions.MaximumWidth, FALSE);
					ErrorMSG(SETTING_MINIMUMWIDTH_MIN, SETTING_MAXIMUMWIDTH_MAX);
					SetFocus((HWND)lParam);
					break;
				}
				if (temp < PopupOptions.MinimumWidth) {
					PopupOptions.MinimumWidth = max(temp, SETTING_MINIMUMWIDTH_MIN);
					SetDlgItemInt(hwnd, IDC_MINIMUMWIDTH, PopupOptions.MinimumWidth, FALSE);
				}
			}
			break;
			}
			break;
		}
		break;

	case WM_NOTIFY:
		switch (((LPNMHDR)lParam)->idFrom) {
		case 0:
			switch (((LPNMHDR)lParam)->code) {
			case PSN_RESET:
				LoadOption_General();
				return TRUE;

			case PSN_APPLY:
				// Seconds
				db_set_b(NULL, MODULNAME, "InfiniteDelay", PopupOptions.InfiniteDelay);
				db_set_w(NULL, MODULNAME, "Seconds", (WORD)PopupOptions.Seconds);
				db_set_b(NULL, MODULNAME, "LeaveHovered", PopupOptions.LeaveHovered);

				// Dynamic Resize
				db_set_b(NULL, MODULNAME, "DynamicResize", PopupOptions.DynamicResize);
				db_set_b(NULL, MODULNAME, "UseMinimumWidth", PopupOptions.UseMinimumWidth);
				db_set_w(NULL, MODULNAME, "MinimumWidth", PopupOptions.MinimumWidth);
				db_set_b(NULL, MODULNAME, "UseMaximumWidth", PopupOptions.UseMaximumWidth);
				db_set_w(NULL, MODULNAME, "MaximumWidth", PopupOptions.MaximumWidth);

				// Position
				db_set_b(NULL, MODULNAME, "Position", (BYTE)PopupOptions.Position);

				// Configure popup area
				db_set_w(NULL, MODULNAME, "gapTop", (WORD)PopupOptions.gapTop);
				db_set_w(NULL, MODULNAME, "gapBottom", (WORD)PopupOptions.gapBottom);
				db_set_w(NULL, MODULNAME, "gapLeft", (WORD)PopupOptions.gapLeft);
				db_set_w(NULL, MODULNAME, "gapRight", (WORD)PopupOptions.gapRight);
				db_set_w(NULL, MODULNAME, "spacing", (WORD)PopupOptions.spacing);

				// Spreading
				db_set_b(NULL, MODULNAME, "Spreading", (BYTE)PopupOptions.Spreading);

				// miscellaneous
				Check_ReorderPopups(hwnd);	// this save also PopupOptions.ReorderPopups

				// disable When
				db_set_b(NULL, MODULNAME, "DisableWhenFullscreen", PopupOptions.DisableWhenFullscreen);

				// new status options
				{
					int protocolCount;
					PROTOACCOUNT **protocols;
					Proto_EnumAccounts(&protocolCount, &protocols);

					for (int i = 0; i < protocolCount; ++i) {
						if (!protocols[i]->bIsVirtual) {
							char prefix[128];
							mir_snprintf(prefix, _countof(prefix), "Protocol Status/%s", protocols[i]->szModuleName);

							TCHAR pszSettingName[256];
							mir_sntprintf(pszSettingName, _countof(pszSettingName), _T("Protocol Status/%s"), protocols[i]->tszAccountName);
							db_set_dw(NULL, MODULNAME, prefix, OptTree_GetOptions(hwnd, IDC_STATUSES, statusOptions, statusOptionsCount, pszSettingName));
						}
					}
					db_set_dw(NULL, MODULNAME, "Global Status", OptTree_GetOptions(hwnd, IDC_STATUSES, statusOptions, statusOptionsCount, _T("Global Status")));
				}
				return TRUE;
			}
			break;

		case IDC_MINIMUMWIDTH_SPIN:
		{
			LPNMUPDOWN lpnmud = (LPNMUPDOWN)lParam;
			int temp = lpnmud->iPos + lpnmud->iDelta;
			if (temp > PopupOptions.MaximumWidth) {
				PopupOptions.MaximumWidth = min(temp, SETTING_MAXIMUMWIDTH_MAX);
				SetDlgItemInt(hwnd, IDC_MAXIMUMWIDTH, PopupOptions.MaximumWidth, FALSE);
			}
		}
		break;

		case IDC_MAXIMUMWIDTH_SPIN:
		{
			LPNMUPDOWN lpnmud = (LPNMUPDOWN)lParam;
			int temp = lpnmud->iPos + lpnmud->iDelta;
			if (temp < PopupOptions.MinimumWidth) {
				PopupOptions.MinimumWidth = max(temp, SETTING_MINIMUMWIDTH_MIN);
				SetDlgItemInt(hwnd, IDC_MINIMUMWIDTH, PopupOptions.MinimumWidth, FALSE);
			}
		}
		}
		break;

	case WM_DESTROY:
		if (statusOptions) {
			for (int i = 0; i < statusOptionsCount; ++i) {
				mir_free(statusOptions[i].pszOptionName);
				mir_free(statusOptions[i].pszSettingName);
			}
			delete[] statusOptions;
			statusOptions = NULL;
			statusOptionsCount = 0;
			bDlgInit = false;
		}
		break;
	}
	return FALSE;
}