static INT_PTR CALLBACK DlgProcIcqFeaturesOpts(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	CIcqProto* ppro = (CIcqProto*)GetWindowLongPtr(hwndDlg, GWLP_USERDATA);

	switch (msg) {
	case WM_INITDIALOG:
		TranslateDialogDefault(hwndDlg);

		ppro = (CIcqProto*)lParam;
		SetWindowLongPtr(hwndDlg, GWLP_USERDATA, lParam);
		{
			LoadDBCheckState(ppro, hwndDlg, IDC_TEMPVISIBLE, "TempVisListEnabled", DEFAULT_TEMPVIS_ENABLED);
			LoadDBCheckState(ppro, hwndDlg, IDC_SLOWSEND, "SlowSend", DEFAULT_SLOWSEND);
			BOOL byData = ppro->getByte("DirectMessaging", DEFAULT_DCMSG_ENABLED);
			CheckDlgButton(hwndDlg, IDC_DCENABLE, byData ? BST_CHECKED : BST_UNCHECKED);
			CheckDlgButton(hwndDlg, IDC_DCPASSIVE, byData == 1 ? BST_CHECKED : BST_UNCHECKED);
			icq_EnableMultipleControls(hwndDlg, icqDCMsgControls, _countof(icqDCMsgControls), byData ? TRUE : FALSE);
			BYTE byXStatusEnabled = ppro->getByte("XStatusEnabled", DEFAULT_XSTATUS_ENABLED);
			CheckDlgButton(hwndDlg, IDC_XSTATUSENABLE, byXStatusEnabled ? BST_CHECKED : BST_UNCHECKED);
			BYTE byMoodsEnabled = ppro->getByte("MoodsEnabled", DEFAULT_MOODS_ENABLED);
			CheckDlgButton(hwndDlg, IDC_MOODSENABLE, byMoodsEnabled ? BST_CHECKED : BST_UNCHECKED);
			icq_EnableMultipleControls(hwndDlg, icqXStatusControls, _countof(icqXStatusControls), byXStatusEnabled);
			icq_EnableMultipleControls(hwndDlg, icqCustomStatusControls, _countof(icqCustomStatusControls), byXStatusEnabled || byMoodsEnabled);
			LoadDBCheckState(ppro, hwndDlg, IDC_XSTATUSAUTO, "XStatusAuto", DEFAULT_XSTATUS_AUTO);
			LoadDBCheckState(ppro, hwndDlg, IDC_XSTATUSRESET, "XStatusReset", DEFAULT_XSTATUS_RESET);
			LoadDBCheckState(ppro, hwndDlg, IDC_KILLSPAMBOTS, "KillSpambots", DEFAULT_KILLSPAM_ENABLED);
			LoadDBCheckState(ppro, hwndDlg, IDC_AIMENABLE, "AimEnabled", DEFAULT_AIM_ENABLED);
			icq_EnableMultipleControls(hwndDlg, icqAimControls, _countof(icqAimControls), ppro->icqOnline() ? FALSE : TRUE);

			hCpCombo = GetDlgItem(hwndDlg, IDC_UTFCODEPAGE);
			int sCodePage = ppro->getWord("AnsiCodePage", CP_ACP);
			ComboBoxAddStringUtf(GetDlgItem(hwndDlg, IDC_UTFCODEPAGE), LPGEN("System default codepage"), 0);
			EnumSystemCodePagesA(FillCpCombo, CP_INSTALLED);
			if (sCodePage == 0)
				SendDlgItemMessage(hwndDlg, IDC_UTFCODEPAGE, CB_SETCURSEL, 0, 0);
			else {
				for (int i = 0; i < SendDlgItemMessage(hwndDlg, IDC_UTFCODEPAGE, CB_GETCOUNT, 0, 0); i++) {
					if (SendDlgItemMessage(hwndDlg, IDC_UTFCODEPAGE, CB_GETITEMDATA, (WPARAM)i, 0) == sCodePage) {
						SendDlgItemMessage(hwndDlg, IDC_UTFCODEPAGE, CB_SETCURSEL, (WPARAM)i, 0);
						break;
					}
				}
			}
		}
		return TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_UTFCODEPAGE:
			if (HIWORD(wParam) == CBN_SELCHANGE)
				OptDlgChanged(hwndDlg);
			break;
		case IDC_DCENABLE:
			icq_EnableMultipleControls(hwndDlg, icqDCMsgControls, _countof(icqDCMsgControls), IsDlgButtonChecked(hwndDlg, IDC_DCENABLE));
			OptDlgChanged(hwndDlg);
			break;
		case IDC_XSTATUSENABLE:
			icq_EnableMultipleControls(hwndDlg, icqXStatusControls, _countof(icqXStatusControls), IsDlgButtonChecked(hwndDlg, IDC_XSTATUSENABLE));
		case IDC_MOODSENABLE:
			icq_EnableMultipleControls(hwndDlg, icqCustomStatusControls, _countof(icqCustomStatusControls), IsDlgButtonChecked(hwndDlg, IDC_XSTATUSENABLE) || IsDlgButtonChecked(hwndDlg, IDC_MOODSENABLE));
		default:
			OptDlgChanged(hwndDlg);
			break;
		}
		break;

	case WM_NOTIFY:
		switch (((LPNMHDR)lParam)->code) {
		case PSN_APPLY:
			int i = SendDlgItemMessage(hwndDlg, IDC_UTFCODEPAGE, CB_GETCURSEL, 0, 0);
			ppro->m_wAnsiCodepage = (WORD)SendDlgItemMessage(hwndDlg, IDC_UTFCODEPAGE, CB_GETITEMDATA, (WPARAM)i, 0);
			ppro->setWord("AnsiCodePage", ppro->m_wAnsiCodepage);

			ppro->m_bTempVisListEnabled = (BYTE)IsDlgButtonChecked(hwndDlg, IDC_TEMPVISIBLE);
			ppro->setByte("TempVisListEnabled", ppro->m_bTempVisListEnabled);
			StoreDBCheckState(ppro, hwndDlg, IDC_SLOWSEND, "SlowSend");
			if (IsDlgButtonChecked(hwndDlg, IDC_DCENABLE))
				ppro->m_bDCMsgEnabled = IsDlgButtonChecked(hwndDlg, IDC_DCPASSIVE) ? 1 : 2;
			else
				ppro->m_bDCMsgEnabled = 0;
			ppro->setByte("DirectMessaging", ppro->m_bDCMsgEnabled);
			ppro->m_bXStatusEnabled = (BYTE)IsDlgButtonChecked(hwndDlg, IDC_XSTATUSENABLE);
			ppro->setByte("XStatusEnabled", ppro->m_bXStatusEnabled);
			ppro->m_bMoodsEnabled = (BYTE)IsDlgButtonChecked(hwndDlg, IDC_MOODSENABLE);
			ppro->setByte("MoodsEnabled", ppro->m_bMoodsEnabled);
			StoreDBCheckState(ppro, hwndDlg, IDC_XSTATUSAUTO, "XStatusAuto");
			StoreDBCheckState(ppro, hwndDlg, IDC_XSTATUSRESET, "XStatusReset");
			StoreDBCheckState(ppro, hwndDlg, IDC_KILLSPAMBOTS, "KillSpambots");
			StoreDBCheckState(ppro, hwndDlg, IDC_AIMENABLE, "AimEnabled");
			return TRUE;
		}
		break;
	}
	return FALSE;
}