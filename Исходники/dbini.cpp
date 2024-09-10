static INT_PTR CALLBACK WarnIniChangeDlgProc(HWND hwndDlg,UINT message,WPARAM wParam,LPARAM lParam)
{
	static struct warnSettingChangeInfo_t *warnInfo;

	switch(message) {
		case WM_INITDIALOG:
		{	char szSettingName[256];
			const TCHAR *pszSecurityInfo;
			warnInfo = (warnSettingChangeInfo_t*)lParam;
			TranslateDialogDefault(hwndDlg);
			SetDlgItemText(hwndDlg, IDC_ININAME, warnInfo->szIniPath);
			lstrcpyA(szSettingName, warnInfo->szSection);
			lstrcatA(szSettingName," / ");
			lstrcatA(szSettingName,warnInfo->szName);
			SetDlgItemTextA(hwndDlg,IDC_SETTINGNAME,szSettingName);
			SetDlgItemTextA(hwndDlg,IDC_NEWVALUE,warnInfo->szValue);
			if(IsInSpaceSeparatedList(warnInfo->szSection,warnInfo->szSafeSections))
				pszSecurityInfo=LPGENT("This change is known to be safe.");
			else if(IsInSpaceSeparatedList(warnInfo->szSection,warnInfo->szUnsafeSections))
				pszSecurityInfo=LPGENT("This change is known to be potentially hazardous.");
			else
				pszSecurityInfo=LPGENT("This change is not known to be safe.");
			SetDlgItemText(hwndDlg,IDC_SECURITYINFO,TranslateTS(pszSecurityInfo));
			return TRUE;
		}
		case WM_COMMAND:
			switch(LOWORD(wParam)) {
				case IDCANCEL:
					warnInfo->cancel=1;
				case IDYES:
				case IDNO:
					warnInfo->warnNoMore=IsDlgButtonChecked(hwndDlg,IDC_WARNNOMORE);
					EndDialog(hwndDlg,LOWORD(wParam));
					break;
			}
			break;
	}
	return FALSE;
}