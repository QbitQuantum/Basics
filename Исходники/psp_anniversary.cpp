/**
 * Dialog procedure for the anniversary add/edit dialog
 *
 * @param	 hDlg	- handle to the dialog window
 * @param	 uMsg	- the message to handle
 * @param	 wParam	- parameter
 * @param	 lParam	- parameter
 *
 * @return	different values
 **/
static INT_PTR CALLBACK DlgProc_AnniversaryEditor(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	MAnnivDate *pDlgEditAnniv = (MAnnivDate *)GetUserData(hDlg);

	switch (uMsg) {
	case WM_INITDIALOG:
		pDlgEditAnniv = (MAnnivDate *)lParam;
		if (!PtrIsValid(pDlgEditAnniv))
			break;

		SetUserData(hDlg, lParam);

		// set icons
		if (db_get_b(NULL, MODNAME, SET_ICONS_BUTTONS, 1)) {
			SendDlgItemMessage(hDlg, IDOK, BM_SETIMAGE, IMAGE_ICON, (LPARAM)IcoLib_GetIcon(ICO_BTN_OK));
			SendDlgItemMessage(hDlg, IDCANCEL, BM_SETIMAGE, IMAGE_ICON, (LPARAM)IcoLib_GetIcon(ICO_BTN_CANCEL));
		}
		SendDlgItemMessage(hDlg, IDC_HEADERBAR, WM_SETICON, 0, (LPARAM)IcoLib_GetIcon(ICO_DLG_ANNIVERSARY, TRUE));

		// translate controls
		SendDlgItemMessage(hDlg, IDOK, BUTTONTRANSLATE, NULL, NULL);
		SendDlgItemMessage(hDlg, IDCANCEL, BUTTONTRANSLATE, NULL, NULL);
		TranslateDialogDefault(hDlg);

		// init controls
		EnableWindow(GetDlgItem(hDlg, EDIT_CATEGORY), pDlgEditAnniv->Id() != ANID_BIRTHDAY);
		SetDlgItemText(hDlg, EDIT_CATEGORY, pDlgEditAnniv->Description());
		return TRUE;

	case WM_CTLCOLORSTATIC:
		SetBkColor((HDC)wParam, RGB(255, 255, 255));
		return (INT_PTR)GetStockObject(WHITE_BRUSH);

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case EDIT_CATEGORY:
			if (HIWORD(wParam) == EN_UPDATE)
				EnableWindow(GetDlgItem(hDlg, IDOK), GetWindowTextLength((HWND)lParam) > 0);
			break;

		case IDOK: {
			// read new description
			HWND hEdit = GetDlgItem(hDlg, EDIT_CATEGORY);
			int len = Edit_GetTextLength(hEdit);
			LPTSTR pszText;

			if (len == 0
				|| (pszText = (LPTSTR)_alloca((len + 1) * sizeof(TCHAR))) == NULL
				|| !Edit_GetText(hEdit, pszText, len + 1))
			{
				MsgErr(hDlg, LPGENT("Please enter a valid description first!"));
				break;
			}

			if (mir_tstrcmpi(pszText, pDlgEditAnniv->Description())) {
				pDlgEditAnniv->Description(pszText);
				pDlgEditAnniv->SetFlags(MAnnivDate::MADF_HASCUSTOM | MAnnivDate::MADF_CHANGED);
			}
		}
		// fall through
		case IDCANCEL:
			return EndDialog(hDlg, LOWORD(wParam));

		}
	}
	return FALSE;
}