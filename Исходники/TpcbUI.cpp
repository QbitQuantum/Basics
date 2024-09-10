// Message handler for the Advanced dialog box
LRESULT CALLBACK AdvancedDialog(HWND hDlg, UINT message,
				WPARAM wParam, LPARAM lParam)
{
	RECT rt;
	HWND hCurrentCheckBox;
	int currentInt, valid;

	switch (message)
	{
		case WM_INITDIALOG:
			GetClientRect(GetParent(hDlg), &rt);
			SetWindowPos(hDlg, HWND_TOP, 0, 0, rt.right, rt.bottom,
			    SWP_SHOWWINDOW);
			if (tpcb->fast_mode == 0) {
				hCurrentCheckBox =
				    GetDlgItem(hDlg, IDC_FASTMODE_CHECK);
				SendMessage(hCurrentCheckBox, BM_SETCHECK,
				    BST_CHECKED, 0);
			}
			if (tpcb->verbose == 1) {
				hCurrentCheckBox =
				    GetDlgItem(hDlg, IDC_VERBOSE_CHECK);
				SendMessage(hCurrentCheckBox, BM_SETCHECK,
				    BST_CHECKED, 0);
			}
			if (tpcb->cachesize != 0) {
				SetDlgItemInt(hDlg, IDC_CACHE_EDIT,
				    tpcb->cachesize/1024, FALSE);
			}
			break;
		case WM_COMMAND:
			if (LOWORD(wParam) == IDC_DONE_BUTTON) {
				hCurrentCheckBox =
				    GetDlgItem(hDlg, IDC_FASTMODE_CHECK);
				if(BST_CHECKED == SendMessage(hCurrentCheckBox,
				    BM_GETCHECK, NULL, NULL))
					tpcb->fast_mode = 0;
				else
					tpcb->fast_mode = 1;
				hCurrentCheckBox =
				    GetDlgItem(hDlg, IDC_VERBOSE_CHECK);
				if(BST_CHECKED == SendMessage(hCurrentCheckBox,
				    BM_GETCHECK, NULL, NULL))
					tpcb->verbose = 1;
				else
					tpcb->verbose = 0;
				currentInt = GetDlgItemInt(hDlg,
				    IDC_RANDOM_EDIT, &valid, FALSE);
				if (valid != FALSE)
					tpcb->rand_seed = currentInt;
				currentInt = GetDlgItemInt(hDlg,
				    IDC_CACHE_EDIT, &valid, FALSE);
				if (valid != FALSE) {
					if (currentInt < 20) {
						MessageBox(hDlg,
						    L"Min cache size is 20kb.",
						    L"Error", MB_OK);
						return FALSE;
					}
					tpcb->cachesize = currentInt*1024;
				}
				EndDialog(hDlg, LOWORD(wParam));
				DestroyWindow(hDlg);
			}
			break;
		default:
			return DefWindowProc(hDlg, message, wParam, lParam);
	}
	return TRUE;
}