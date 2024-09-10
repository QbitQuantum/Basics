HWND CreateToolbarFromResource(HWND hWndParent)
{
	INITCOMMONCONTROLSEX icex;
	icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
	icex.dwICC  = ICC_WIN95_CLASSES|ICC_COOL_CLASSES|ICC_BAR_CLASSES|ICC_USEREX_CLASSES;
	InitCommonControlsEx(&icex);

	// Declare and initialize local constants.
	int ImageListID;
	int resourceId = IDB_FILE_VIEW_24;
	int numButtons = 31;
	const int bmHeight = 16;
	const int bmWidth = 16;
	
	const DWORD buttonStylesasdfasdf = BTNS_AUTOSIZE;

	// Create the toolbar.
	HWND hWndToolbar = CreateWindowEx(0, TOOLBARCLASSNAME, NULL, 
									  WS_CHILD | TBSTYLE_WRAPABLE, 0, 0, 0, 0,
									  hWndParent, NULL, hInst, NULL);
	if (hWndToolbar == NULL)
		return NULL;


	resourceId = IDB_TOOLBAR256;

	HBITMAP hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(resourceId));

	// Create the image list.
	int cx = bmWidth;
	int cy = bmHeight;
	UINT nFlags = ILC_COLOR24 | ILC_MASK;
	int nInitial = 0;
	int nGrow = 0;
	hImageList = ImageList_Create(bmWidth, bmHeight, nFlags, 0, nGrow);
	ImageListID = ImageList_AddMasked(hImageList, hBitmap, RGB(0, 255, 0));


	// Set the image list.
	LRESULT r1 = SendMessage(hWndToolbar, TB_SETIMAGELIST, (WPARAM)ImageListID, (LPARAM)hImageList); 

	// Load the button images.
	//LRESULT r2 = SendMessage(hWndToolbar, TB_LOADIMAGES, 
				//(WPARAM)IDB_STD_SMALL_COLOR, 
				//(LPARAM)HINST_COMMCTRL);
	// Load the text from a resource.
	
	// In the string table, the text for all buttons is a single entry that 
	// appears as "~New~Open~Save~~". The separator character is arbitrary, 
	// but it must appear as the first character of the string. The message 
	// returns the index of the first item, and the items are numbered 
	// consecutively.
	
	int iNew = SendMessage(hWndToolbar, TB_ADDSTRING, (WPARAM)hInst, (LPARAM)0); 
 
	// Initialize button info.
	// IDM_NEW, IDM_OPEN, and IDM_SAVE are application-defined command constants.
	
	::SendMessage(hWndToolbar, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);
	::SendMessage(hWndToolbar, TB_SETEXTENDEDSTYLE, 0, (LPARAM)TBSTYLE_EX_HIDECLIPPEDBUTTONS);

	TBBUTTON *pButtons = new TBBUTTON[numButtons];

	for (int i = 0 ; i < numButtons ; i++)
	{
		pButtons[i].iBitmap = i;
		pButtons[i].idCommand = 20 + i;
		pButtons[i].fsState = (BYTE)TBSTATE_ENABLED;
		pButtons[i].fsStyle = (BYTE)TBSTYLE_FLAT;
		pButtons[i].dwData = 0;
		pButtons[i].iString = NULL;
	}

	//typedef struct _TBBUTTON {
	//    int iBitmap;
	//    int idCommand;
	//    BYTE fsState;
	//    BYTE fsStyle;
	//#ifdef _WIN64
	//    BYTE bReserved[6];          // padding for alignment
	//#elif defined(_WIN32)
	//    BYTE bReserved[2];          // padding for alignment
	//#endif
	//    DWORD_PTR dwData;
	//    INT_PTR iString;
	//} TBBUTTON, NEAR* PTBBUTTON, *LPTBBUTTON;

	BOOL b = IsAppThemed();

	// Add buttons.
	LRESULT a1 = SendMessage(hWndToolbar, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);
	LRESULT a2 = SendMessage(hWndToolbar, TB_ADDBUTTONS,       (WPARAM)numButtons,       (LPARAM)pButtons);

	// Resize the toolbar, and then show it.
	LRESULT a3 = SendMessage(hWndToolbar, TB_AUTOSIZE, 0, 0); 
	LRESULT a4 = ShowWindow(hWndToolbar,  TRUE);
	return hWndToolbar;
}