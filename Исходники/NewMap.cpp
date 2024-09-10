bool CALLBACK CNewMap::_newMapProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	int pow;

	switch(iMessage)
	{
	case WM_INITDIALOG:
		int x, y, w, h;
		RECT parentRect, dlgRect;
		newMap->m_hWnd = hDlg;

		GetWindowRect(newMap->m_parentHandle, &parentRect);
		GetClientRect(hDlg, &dlgRect);

		x = parentRect.left + (parentRect.right - parentRect.left) / 2 - (dlgRect.right - dlgRect.left) / 2;
		y = parentRect.top+100;
		w = dlgRect.right - dlgRect.left;
		h = dlgRect.bottom - dlgRect.top;

		MoveWindow(hDlg, x, y, w, h, true);
		newMap->_Init();

		return 0;

	case WM_CLOSE:
		newMap->_btCancel(hDlg);
		return false;

	case WM_COMMAND:

		switch(LOWORD(wParam))
		{
		case IDC_BT_CANCEL:
			newMap->_btCancel(hDlg);
			break;
		case IDC_BT_CREATE:
			newMap->_btCreate(hDlg);
			break;

		case IDC_RADIO_CELL_4:
		case IDC_RADIO_CELL_8:
		case IDC_RADIO_CELL_16:
			pow = LOWORD(wParam) - IDC_RADIO_CELL_4 + 2;
			newMap->_calcCell(pow);
			break;

		case IDC_RADIO_TILE_8:
		case IDC_RADIO_TILE_16:
		case IDC_RADIO_TILE_32:
			pow = LOWORD(wParam) - IDC_RADIO_TILE_8 + 3;
			newMap->_calcTile(pow);
			break;

		case IDC_LIST_NEW_TEXTURE:
			newMap->_SelListBox(LOWORD(wParam), HIWORD(wParam));
			break;
		}

		break;

	case WM_HSCROLL:
		newMap->_SlideBar(reinterpret_cast<HWND>(lParam));
		break;

	case WM_PAINT:
		hdc = BeginPaint(hDlg, &ps);
		newMap->m_preview.Render();
		EndPaint(hDlg, &ps);
		break;
	}

	return false;
}