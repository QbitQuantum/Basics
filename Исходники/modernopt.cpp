////////////////////////////////////////////////////////////////////////////////
// UI utilities
static HWND ModernOptUI_ShowPage_Impl(HWND hwndDlg, struct ModernOptionsData *dat, int iPage, int dx, HWND hwndInsertAfter)
{
	if ((iPage < 0) || (iPage >= dat->pObjectList.getCount()))
		return NULL;

	dat->iPage = iPage;
	struct ModernOptionsObject *obj = (struct ModernOptionsObject *)dat->pObjectList[dat->iPage];
	if (!obj->hwnd) {
		RECT rc1, rc2;
		GetWindowRect(GetDlgItem(hwndDlg, IDC_TV_SUBSECTIONS), &rc1);
		GetWindowRect(GetDlgItem(hwndDlg, IDC_TXT_DUMMY), &rc2);
		MapWindowPoints(NULL, hwndDlg, (LPPOINT)&rc1, 2);
		MapWindowPoints(NULL, hwndDlg, (LPPOINT)&rc2, 2);
		rc1.top += dx; rc2.top += dx;

		obj->hwnd = CreateDialogParamA(obj->optObject.hInstance, obj->optObject.lpzTemplate, hwndDlg, obj->optObject.pfnDlgProc, (LPARAM)&obj->optObject);
		if (obj->hwnd) {
			DWORD dwShowFlags =
				SWP_SHOWWINDOW |
				((obj->optObject.dwFlags & MODEROPT_FLG_NORESIZE) ? SWP_NOSIZE : 0);

			int i = 0;

			if (obj->optObject.iBoldControls)
				for (i = 0; obj->optObject.iBoldControls[i]; ++i) {
					HWND hwndChild = GetDlgItem(obj->hwnd, obj->optObject.iBoldControls[i]);
					if (!hwndChild) continue;
					SendMessage(hwndChild, WM_SETFONT, (WPARAM)dat->hfntBold, TRUE);
				}

			if (obj->optObject.iType == MODERNOPT_TYPE_SECTIONPAGE)
				SetWindowPos(obj->hwnd, hwndInsertAfter, rc1.left, rc1.top, rc2.right-rc1.left, rc2.bottom-rc1.top, dwShowFlags);
			else
				SetWindowPos(obj->hwnd, hwndInsertAfter, rc2.left, rc2.top, rc2.right-rc2.left, rc2.bottom-rc2.top, dwShowFlags);

			if (obj->optObject.iSection == MODERNOPT_PAGE_IGNORE) {
				for (i = 0; i < dat->pObjectList.getCount(); ++i) {
					struct ModernOptionsObject *ignoreObj = (struct ModernOptionsObject *)dat->pObjectList[i];
					if (ignoreObj->optObject.iType == MODERNOPT_TYPE_IGNOREOBJECT)
						ModernOptIgnore_AddItem(&ignoreObj->optObject);
		}	}	}
	}
	else ShowWindow(obj->hwnd, SW_SHOW);

	ShowWindow(GetDlgItem(hwndDlg, IDC_BTN_EXPERT), (obj->optObject.lpzClassicGroup || obj->optObject.lpzClassicPage) ? SW_SHOW : SW_HIDE);
	ShowWindow(GetDlgItem(hwndDlg, IDC_BTN_HELP), obj->optObject.lpzHelpUrl ? SW_SHOW : SW_HIDE);

	return obj->hwnd;
}