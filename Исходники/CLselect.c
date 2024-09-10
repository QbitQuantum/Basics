static VOID
sMoveButtons (
		HWND	hwnd,
		WORD	wXsize,
		WORD	wYsize)
{
	HDWP	hdwp; 
	INT		iButtonWidth, iButtonHeight;
	RECT	rc;

	GetWindowRect (GetDlgItem (hwnd, IDOK), &rc);
	iButtonWidth = rc.right - rc.left;
	iButtonHeight = rc.bottom - rc.top;

	hdwp = BeginDeferWindowPos (4);

	// position the "cancel" button
	DeferWindowPos (hdwp, 
		GetDlgItem (hwnd, IDCANCEL), NULL, 
		wXsize - HOR_OFFSET - iButtonWidth, 
		wYsize - BOTTOM_BUTTON_OFFSET - iButtonHeight, 
		0, 0, SWP_NOSIZE|SWP_NOZORDER);

	// position the "OK" button
	DeferWindowPos (hdwp, 
		GetDlgItem (hwnd, IDOK), NULL, 
		wXsize - HOR_OFFSET - BUTTON_SPACING - 2*iButtonWidth, 
		wYsize - BOTTOM_BUTTON_OFFSET - iButtonHeight, 
		0, 0, SWP_NOSIZE|SWP_NOZORDER);

	// position the "unselectall" button
	DeferWindowPos (hdwp, 
		GetDlgItem (hwnd, IDC_UNSELECTALL), NULL, 
		wXsize - HOR_OFFSET - 2*BUTTON_SPACING - 3*iButtonWidth, 
		wYsize - BOTTOM_BUTTON_OFFSET - iButtonHeight, 
		0, 0, SWP_NOSIZE|SWP_NOZORDER);

	// position the "selectall" button
	DeferWindowPos (hdwp, 
		GetDlgItem (hwnd, IDC_SELECTALL), NULL, 
		wXsize - HOR_OFFSET - 3*BUTTON_SPACING - 4*iButtonWidth, 
		wYsize - BOTTOM_BUTTON_OFFSET - iButtonHeight, 
		0, 0, SWP_NOSIZE|SWP_NOZORDER);

	EndDeferWindowPos(hdwp);
}