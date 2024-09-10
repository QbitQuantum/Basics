// Message handler for about box.
INT_PTR CALLBACK DecryptProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);

	switch (message) {
	case WM_INITDIALOG:
		// Get the owner window and dialog box rectangles. 
		HWND hwndOwner;
		RECT rc, rcDlg, rcOwner;

		if ((hwndOwner = GetParent(hDlg)) == NULL) {
			hwndOwner = GetDesktopWindow();
		}

		GetWindowRect(hwndOwner, &rcOwner);
		GetWindowRect(hDlg, &rcDlg);
		CopyRect(&rc, &rcOwner);

		// Offset the owner and dialog box rectangles so that right and bottom 
		// values represent the width and height, and then offset the owner again 
		// to discard space taken up by the dialog box. 

		OffsetRect(&rcDlg, -rcDlg.left, -rcDlg.top);
		OffsetRect(&rc, -rc.left, -rc.top);
		OffsetRect(&rc, -rcDlg.right, -rcDlg.bottom);

		// The new position is the sum of half the remaining space and the owner's 
		// original position. 

		SetWindowPos(hDlg,
			HWND_TOP,
			rcOwner.left + (rc.right / 2),
			rcOwner.top + (rc.bottom / 2),
			0, 0,          // Ignores size arguments. 
			SWP_NOSIZE);

		SetWindowText(hDlg, szFile);
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK) {
			TCHAR pwd[MAX_PASSWORD];

			GetDlgItemText(hDlg, IDC_PWD, pwd, MAX_PASSWORD);

			if (!wcslen(pwd)) {
				MessageBox(hDlg, L"Password cannot be empty", L"Password error", MB_ICONERROR);
				break;
			}

			if (!SodiumDecryptFile(pwd)) {
				sodium_memzero(pwd, MAX_PASSWORD);
				break;
			}

			sodium_memzero(pwd, MAX_PASSWORD);

			EndDialog(hDlg, LOWORD(wParam));
			PostQuitMessage(0);
			return (INT_PTR)TRUE;

		} else if (LOWORD(wParam) == IDCANCEL) {
			EndDialog(hDlg, LOWORD(wParam));
			PostQuitMessage(0);
			return (INT_PTR)TRUE;

		}
		break;
	}

	return (INT_PTR)FALSE;
}