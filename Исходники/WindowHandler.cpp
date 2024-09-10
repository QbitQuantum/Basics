HWND Explorerplusplus::CreateTabToolbar(HWND hParent,int idCommand,TCHAR *szTip)
{
	HWND TabToolbar = CreateToolbar(hParent,WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS|
		TBSTYLE_TOOLTIPS|TBSTYLE_LIST|TBSTYLE_TRANSPARENT|TBSTYLE_FLAT|CCS_NODIVIDER|
		CCS_NOPARENTALIGN|CCS_NORESIZE,TBSTYLE_EX_MIXEDBUTTONS|TBSTYLE_EX_DOUBLEBUFFER);
	
	SendMessage(TabToolbar,TB_SETBITMAPSIZE,0,MAKELONG(7,7));
	SendMessage(TabToolbar,TB_BUTTONSTRUCTSIZE,sizeof(TBBUTTON),0);
	SendMessage(TabToolbar,TB_SETBUTTONSIZE,0,MAKELPARAM(16,16));

	/* TODO: The image list is been leaked. */
	HIMAGELIST himl = ImageList_Create(7,7,ILC_COLOR32|ILC_MASK,0,2);
	HBITMAP hb = LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDB_TABTOOLBAR_CLOSE));
	int iIndex = ImageList_Add(himl,hb,NULL);
	SendMessage(TabToolbar,TB_SETIMAGELIST,0,reinterpret_cast<LPARAM>(himl));
	DeleteObject(hb);

	/* Add the close button, used to close tabs. */
	TBBUTTON tbButton;
	tbButton.iBitmap	= iIndex;
	tbButton.idCommand	= idCommand;
	tbButton.fsState	= TBSTATE_ENABLED;
	tbButton.fsStyle	= TBSTYLE_BUTTON|TBSTYLE_AUTOSIZE;
	tbButton.dwData		= 0;
	tbButton.iString	= reinterpret_cast<INT_PTR>(szTip);
	SendMessage(TabToolbar,TB_INSERTBUTTON,0,reinterpret_cast<LPARAM>(&tbButton));

	SendMessage(TabToolbar,TB_AUTOSIZE,0,0);

	return TabToolbar;
}