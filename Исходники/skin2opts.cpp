INT_PTR CALLBACK DlgProcIconImport(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HWND hwndParent, hwndDragOver;
	static int dragging;
	static int dragItem, dropHiLite;
	static HWND hPreview = NULL;

	switch (msg) {
	case WM_INITDIALOG:
		TranslateDialogDefault(hwndDlg);
		hwndParent = (HWND)lParam;
		hPreview = GetDlgItem(hwndDlg, IDC_PREVIEW);
		dragging = dragItem = 0;
		ListView_SetImageList(hPreview, ImageList_Create(GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON), ILC_COLOR32|ILC_MASK, 0, 100), LVSIL_NORMAL);
		ListView_SetIconSpacing(hPreview, 56, 67);
		{
			RECT rcThis, rcParent;
			int cxScreen = GetSystemMetrics(SM_CXSCREEN);

			GetWindowRect(hwndDlg, &rcThis);
			GetWindowRect(hwndParent, &rcParent);
			OffsetRect(&rcThis, rcParent.right-rcThis.left, 0);
			OffsetRect(&rcThis, 0, rcParent.top-rcThis.top);
			GetWindowRect(GetParent(hwndParent), &rcParent);
			if (rcThis.right > cxScreen) {
				OffsetRect(&rcParent, cxScreen-rcThis.right, 0);
				OffsetRect(&rcThis, cxScreen-rcThis.right, 0);
				MoveWindow(GetParent(hwndParent), rcParent.left, rcParent.top, rcParent.right-rcParent.left, rcParent.bottom-rcParent.top, TRUE);
			}
			MoveWindow(hwndDlg, rcThis.left, rcThis.top, rcThis.right-rcThis.left, rcThis.bottom-rcThis.top, FALSE);
			GetClientRect(hwndDlg, &rcThis);
			SendMessage(hwndDlg, WM_SIZE, 0, MAKELPARAM(rcThis.right-rcThis.left, rcThis.bottom-rcThis.top));
		}

		SHAutoComplete( GetDlgItem(hwndDlg, IDC_ICONSET), 1);

		SetDlgItemText(hwndDlg, IDC_ICONSET, _T("icons.dll"));
		return TRUE;

	case DM_REBUILDICONSPREVIEW:
		{
			MySetCursor(IDC_WAIT);
			ListView_DeleteAllItems(hPreview);
			HIMAGELIST hIml = ListView_GetImageList(hPreview, LVSIL_NORMAL);
			ImageList_RemoveAll(hIml);

			TCHAR filename[MAX_PATH], caption[64];
			GetDlgItemText(hwndDlg, IDC_ICONSET, filename, SIZEOF(filename));
			{
				RECT rcPreview, rcGroup;

				GetWindowRect(hPreview, &rcPreview);
				GetWindowRect( GetDlgItem(hwndDlg, IDC_IMPORTMULTI), &rcGroup);
				//SetWindowPos(hPreview, 0, 0, 0, rcPreview.right-rcPreview.left, rcGroup.bottom-rcPreview.top, SWP_NOZORDER|SWP_NOMOVE);
			}

			if ( _taccess(filename, 0) != 0) {
				MySetCursor(IDC_ARROW);
				break;
			}

			LVITEM lvi;
			lvi.mask = LVIF_TEXT|LVIF_IMAGE|LVIF_PARAM;
			lvi.iSubItem = 0;
			lvi.iItem = 0;
			int count = (int)_ExtractIconEx(filename, -1, 16, 16, NULL, LR_DEFAULTCOLOR);
			for (int i=0; i < count; lvi.iItem++, i++) {
				mir_sntprintf(caption, SIZEOF(caption), _T("%d"), i+1);
				lvi.pszText = caption;

				HICON hIcon;
				_ExtractIconEx(filename, i, 16, 16, &hIcon, LR_DEFAULTCOLOR);
				lvi.iImage = ImageList_AddIcon(hIml, hIcon);
				DestroyIcon(hIcon);
				lvi.lParam = i;
				ListView_InsertItem(hPreview, &lvi);
			}
			MySetCursor(IDC_ARROW);
		}
		break;

	case WM_COMMAND:
		switch(LOWORD(wParam)) {
		case IDC_BROWSE:
			{
				TCHAR str[MAX_PATH], *file;
				GetDlgItemText(hwndDlg, IDC_ICONSET, str, SIZEOF(str));
				if (!(file = OpenFileDlg(GetParent(hwndDlg), str, TRUE)))
					break;
				SetDlgItemText(hwndDlg, IDC_ICONSET, file);
				SAFE_FREE((void**)&file);
			}
			break;

		case IDC_GETMORE:
			OpenIconsPage();
			break;

		case IDC_ICONSET:
			if (HIWORD(wParam) == EN_CHANGE)
				SendMessage(hwndDlg, DM_REBUILDICONSPREVIEW, 0, 0);
			break;
		}
		break;

	case WM_MOUSEMOVE:
		if (dragging) {
			LVHITTESTINFO lvhti;
			int onItem = 0;
			HWND hwndOver;
			RECT rc;
			POINT ptDrag;
			HWND hPPreview = GetDlgItem(hwndParent, IDC_PREVIEW);

			lvhti.pt.x = (short)LOWORD(lParam); lvhti.pt.y = (short)HIWORD(lParam);
			ClientToScreen(hwndDlg, &lvhti.pt);
			hwndOver = WindowFromPoint(lvhti.pt);
			GetWindowRect(hwndOver, &rc);
			ptDrag.x = lvhti.pt.x - rc.left; ptDrag.y = lvhti.pt.y - rc.top;
			if (hwndOver != hwndDragOver) {
				ImageList_DragLeave(hwndDragOver);
				hwndDragOver = hwndOver;
				ImageList_DragEnter(hwndDragOver, ptDrag.x, ptDrag.y);
			}

			ImageList_DragMove(ptDrag.x, ptDrag.y);
			if (hwndOver == hPPreview) {
				ScreenToClient(hPPreview, &lvhti.pt);

				if (ListView_HitTest(hPPreview, &lvhti) != -1) {
					if (lvhti.iItem != dropHiLite) {
						ImageList_DragLeave(hwndDragOver);
						if (dropHiLite != -1)
							ListView_SetItemState(hPPreview, dropHiLite, 0, LVIS_DROPHILITED);
						dropHiLite = lvhti.iItem;
						ListView_SetItemState(hPPreview, dropHiLite, LVIS_DROPHILITED, LVIS_DROPHILITED);
						UpdateWindow(hPPreview);
						ImageList_DragEnter(hwndDragOver, ptDrag.x, ptDrag.y);
					}
					onItem = 1;
				}
			}

			if (!onItem && dropHiLite != -1) {
				ImageList_DragLeave(hwndDragOver);
				ListView_SetItemState(hPPreview, dropHiLite, 0, LVIS_DROPHILITED);
				UpdateWindow(hPPreview);
				ImageList_DragEnter(hwndDragOver, ptDrag.x, ptDrag.y);
				dropHiLite = -1;
			}
			MySetCursor(onItem ? IDC_ARROW : IDC_NO);
		}
		break;

	case WM_LBUTTONUP:
		if (dragging) {
			ReleaseCapture();
			ImageList_EndDrag();
			dragging = 0;
			if (dropHiLite != -1) {
				TCHAR path[MAX_PATH], fullPath[MAX_PATH], filename[MAX_PATH];
				LVITEM lvi;

				GetDlgItemText(hwndDlg, IDC_ICONSET, fullPath, SIZEOF(fullPath));
				PathToRelativeT(fullPath, filename);
				lvi.mask = LVIF_PARAM;
				lvi.iItem = dragItem; lvi.iSubItem = 0;
				ListView_GetItem(hPreview, &lvi);
				mir_sntprintf(path, SIZEOF(path), _T("%s,%d"), filename, (int)lvi.lParam);
				SendMessage(hwndParent, DM_CHANGEICON, dropHiLite, (LPARAM)path);
				ListView_SetItemState( GetDlgItem(hwndParent, IDC_PREVIEW), dropHiLite, 0, LVIS_DROPHILITED);
			}
		}
		break;

	case WM_NOTIFY:
		switch (((LPNMHDR)lParam)->idFrom) {
		case IDC_PREVIEW:
			switch (((LPNMHDR)lParam)->code) {
			case LVN_BEGINDRAG:
				SetCapture(hwndDlg);
				dragging = 1;
				dragItem = ((LPNMLISTVIEW)lParam)->iItem;
				dropHiLite = -1;
				ImageList_BeginDrag(ListView_GetImageList(hPreview, LVSIL_NORMAL), dragItem, GetSystemMetrics(SM_CXICON)/2, GetSystemMetrics(SM_CYICON)/2);
				{
					POINT pt;
					RECT rc;

					GetCursorPos(&pt);
					GetWindowRect(hwndDlg, &rc);
					ImageList_DragEnter(hwndDlg, pt.x - rc.left, pt.y - rc.top);
					hwndDragOver = hwndDlg;
				}
				break;
			}
			break;
		}
		break;

	case WM_SIZE: // make the dlg resizeable
		if (!IsIconic(hwndDlg)) {
			UTILRESIZEDIALOG urd = {0};
			urd.cbSize = sizeof(urd);
			urd.hInstance = hInst;
			urd.hwndDlg = hwndDlg;
			urd.lParam = 0; // user-defined
			urd.lpTemplate = MAKEINTRESOURCEA(IDD_ICOLIB_IMPORT);
			urd.pfnResizer = IconDlg_Resize;
			CallService(MS_UTILS_RESIZEDIALOG, 0, (LPARAM)&urd);
		}
		break;

	case WM_CLOSE:
		DestroyWindow(hwndDlg);
		EnableWindow( GetDlgItem(hwndParent, IDC_IMPORT), TRUE);
		break;

	}

	return FALSE;
}