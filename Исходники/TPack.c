static BOOL TPack_InitializeDialog (HWND hwnd)
{
	TPack_WindowData *	pData;
	HFONT				Font;
	HWND				ListWnd;

	// allocate window local data structure
	pData = GE_RAM_ALLOCATE_STRUCT (TPack_WindowData);
	if (pData == NULL)
	{
		DestroyWindow (hwnd);
		return TRUE;
	}

	// and initialize it
	pData->Instance		 = (HINSTANCE)GetWindowLong (hwnd, GWL_HINSTANCE);
	pData->hwnd			 = hwnd;
	pData->BitmapCount	 = 0;
	pData->Bitmaps		 = NULL;
	pData->SelectedEntry = NULL;
	pData->FileNameIsValid = FALSE;
	pData->Dirty		 = FALSE;
	// Set the window data pointer in the GWL_USERDATA field
	SetWindowLong(hwnd, GWL_USERDATA, (LONG)pData);
	SetWindowLong(GetDlgItem(hwnd, IDC_PREVIEW), GWL_USERDATA, (LONG)pData);
	SetWindowLong(GetDlgItem(hwnd, IDC_PREVIEW), GWL_WNDPROC, (LONG)TPack_PreviewWndProc);

	ListWnd = GetDlgItem(hwnd, IDC_TEXTURELIST);
	SetWindowLong(ListWnd, GWL_USERDATA, (LONG)GetWindowLong(ListWnd, GWL_WNDPROC));
	SetWindowLong(ListWnd, GWL_WNDPROC, (LONG)TPack_ListBoxWndProc);
	
	Font = CreateFont( -24,
    					    0,0,0, 0,
    					    0,0,0,0,OUT_TT_ONLY_PRECIS ,0,0,0, "Arial Black");
    SendDlgItemMessage(hwnd, IDC_TEXTURESIZE, WM_SETFONT, (WPARAM)Font, MAKELPARAM(TRUE, 0));

	// set the program icon on the dialog window
	SendMessage (hwnd, WM_SETICON, ICON_BIG, (LPARAM)LoadIcon (pData->Instance, MAKEINTRESOURCE (IDI_MAINICON)));

	DragAcceptFiles (hwnd, TRUE);

	return TRUE;
}