//
//	Create a toolbar with one button in it, for
//  the pin-button
//
HWND CreatePinToolbar(HWND hwndDlg, UINT nCtrlId, BOOL fRightAligned)
{
	RECT    rect;
	RECT	rc1, rc2;
	HWND	hwndPin;
	
	static TBBUTTON tbbPin[] = 
	{	
		{	0,	0, TBSTATE_ENABLED, TBSTYLE_CHECK,  {0}	},
	};	

	tbbPin[0].idCommand = nCtrlId;

	// Create the toolbar to hold pin bitmap
	hwndPin = CreateToolbarEx(
			hwndDlg,	
			TOOLBAR_PIN_STYLES,				//,
			nCtrlId,						// toolbar ID (don't need)
			2,								// number of button images
			g_hInstance,					// where the bitmap is
			IDB_PIN_BITMAP,					// bitmap resource name
			tbbPin,							// TBBUTTON structure
			sizeof(tbbPin) / sizeof(tbbPin[0]),
			15,14,15,14,					// 
			sizeof(TBBUTTON) );


	// Find out how big the button is, so we can resize the
	// toolbar to fit perfectly
	SendMessage(hwndPin, TB_GETITEMRECT, 0, (LPARAM)&rect);
	
	SetWindowPos(hwndPin, HWND_TOP, 0,0, 
		rect.right-rect.left, 
		rect.bottom-rect.top, SWP_NOMOVE);

	// Setup the bitmap image
	SendMessage(hwndPin, TB_CHANGEBITMAP, nCtrlId, (LPARAM)MAKELPARAM(g_fKeepVisible, 0)); 

	// Checked / Unchecked
	SendMessage(hwndPin, TB_CHECKBUTTON, nCtrlId, MAKELONG(g_fKeepVisible, 0));

	GetClientRect(hwndDlg, &rc1);
	GetClientRect(hwndPin, &rc2);
	
	if(fRightAligned)
		SetWindowPos(hwndPin, 0, rc1.right - rc2.right-10, rc1.bottom-rc2.bottom-8,0,0,SWP_NOSIZE);
	else
		SetWindowPos(hwndPin, 0, rc1.left+10, rc1.bottom-rc2.bottom-8,0,0,SWP_NOSIZE);

	return hwndPin;
}