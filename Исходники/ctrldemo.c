void
CreateToolbar(HWND hwOwner)
{

	TBBUTTON Buttons[3];

	Buttons[0].iBitmap = 1;
	Buttons[0].idCommand = IDM_PROPSHEET;
	Buttons[0].fsState = TBSTATE_ENABLED;
	Buttons[0].fsStyle = TBSTYLE_BUTTON;
	Buttons[0].dwData = 0L;
	Buttons[0].iString = 0;

    Buttons[1].iBitmap = 2; 
    Buttons[1].idCommand = IDM_UPDOWN;
    Buttons[1].fsState = TBSTATE_ENABLED;
    Buttons[1].fsStyle = TBSTYLE_BUTTON;
    Buttons[1].dwData = 0L;
    Buttons[1].iString = 0;

    Buttons[2].iBitmap = 0; 
    Buttons[2].idCommand = IDM_ABOUT;
    Buttons[2].fsState = TBSTATE_ENABLED;
    Buttons[2].fsStyle = TBSTYLE_BUTTON;
    Buttons[2].dwData = 0L;
    Buttons[2].iString = 0;

	hWndToolbar=CreateToolbarEx (hwOwner,
			WS_VISIBLE | WS_CHILD | WS_BORDER | CCS_TOP |
			TBSTYLE_TOOLTIPS,
			ID_TOOLBAR,
			3,
			hInstance, 
			IDB_TOOLBAR,
			Buttons,
			3,
			16, 16, 
			16, 16,	
			sizeof(TBBUTTON));
}