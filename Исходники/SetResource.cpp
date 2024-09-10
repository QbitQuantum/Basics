BOOL CALLBACK ConfDialogBoxProc( HWND hWnd, UINT wmes, UINT wparam, LONG lparam )
{
	int			i;
	switch( wmes ){
	  case WM_INITDIALOG:
		CreateMyProp(hWnd);
		GetClientRect(hWnd, &rect);
		SendMessage(hWnd, WM_SIZE, 0, MAKELPARAM(rect.right, rect.bottom-40));
		break;
	  case WM_SIZE:
		GetClientRect(hWnd, &rect);
		rect.bottom -= 40;
		TabCtrl_AdjustRect(hTabWnd, FALSE, &rect);
		MoveWindow(hTabWnd, 0, 0, LOWORD(lparam), HIWORD(lparam), TRUE);
		for(i=0;i<4;i++){
			MoveWindow(hPage[i],
				rect.left, rect.top,
				rect.right - rect.left,
				rect.bottom - rect.top,
				TRUE);
		}
		break;
	  case WM_NOTIFY:
		switch(TabCtrl_GetCurSel(((NMHDR *)lparam)->hwndFrom)) {
		  case 0:
			ShowWindow(hPage[0], SW_SHOW);
			ShowWindow(hPage[1], SW_HIDE);
			ShowWindow(hPage[2], SW_HIDE);
			break;
		  case 1:
			ShowWindow(hPage[1], SW_SHOW);
			ShowWindow(hPage[0], SW_HIDE);
			ShowWindow(hPage[2], SW_HIDE);
			break;
		  case 2:
			ShowWindow(hPage[2], SW_SHOW);
			ShowWindow(hPage[0], SW_HIDE);
			ShowWindow(hPage[1], SW_HIDE);
			break;
		}
		break;
	  case WM_COMMAND:
		switch( LOWORD( wparam ) ){
		  case IDC_CFGUPDATE:
			UpdateMyPop(hWnd);
			break;
		  case IDOK:
			UpdateMyPop(hWnd);
			EndDialog( hWnd, IDOK );
			break;
		  case IDCANCEL:
			EndDialog( hWnd, IDCANCEL);
			break;
		}
		break;
	  case WM_CLOSE:
		EndDialog( hWnd, TRUE );
		break;
	}
	return 0;
} // ConfDialogBoxProc