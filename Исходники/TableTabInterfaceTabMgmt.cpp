// adds buttons to the toolbar
void 
TableTabInterfaceTabMgmt::AddToolButtons()
{
	INT			i=0,j, size;
	LONG		ret;
	HICON		hicon;
	TBBUTTON	tbb[30];

    wyInt32 command[] = {   IDI_ADDROW,
						    IDI_DELETEROW,
						    IDM_SEPARATOR,
						    IDI_MOVEUP,
						    IDI_MOVEDOWN 
						};

	wyUInt32 states[][2] = {
							{TBSTATE_ENABLED, TBSTYLE_BUTTON},
							{TBSTATE_ENABLED, TBSTYLE_BUTTON},
							{TBSTATE_ENABLED, TBSTYLE_SEP},
							{TBSTATE_ENABLED, TBSTYLE_BUTTON},
                            {TBSTATE_ENABLED, TBSTYLE_BUTTON}
						   };

	wyInt32 imgres[] = {
						IDI_ADDROW, 
						IDI_DELETEROW,
						IDI_USERS,
						IDI_MOVEUP,
						IDI_MOVEDOWN
					  };

	VERIFY(m_himglist = ImageList_Create(ICON_SIZE, ICON_SIZE, ILC_COLOR32  | ILC_MASK, 1, 0));

 	SendMessage(m_hwndtool, TB_SETIMAGELIST, 0, (LPARAM)m_himglist);
	SendMessage(m_hwndtool, TB_SETEXTENDEDSTYLE, 0 , (LPARAM)TBSTYLE_EX_DRAWDDARROWS);
    SendMessage(m_hwndtool, TB_BUTTONSTRUCTSIZE, sizeof(TBBUTTON), 0);

	size = sizeof(command)/sizeof(command[0]);

	// set some required values
	SendMessage(m_hwndtool, TB_BUTTONSTRUCTSIZE, sizeof(TBBUTTON), 0);

	// now create everything for the toolbar.
	for(j=0; j < size; j++)	
	{
		hicon = (HICON)LoadImage(pGlobals->m_hinstance, MAKEINTRESOURCE ( imgres[j] ), IMAGE_ICON, ICON_SIZE, ICON_SIZE, LR_DEFAULTCOLOR);
		VERIFY((i = ImageList_AddIcon(m_himglist, hicon))!= -1);
		VERIFY(DestroyIcon(hicon));
		
		memset(&tbb[j], 0, sizeof(TBBUTTON));

		tbb[j].iBitmap = MAKELONG(i, 0);
		tbb[j].idCommand = command[j];
		tbb[j].fsState = (UCHAR)states[j][0];
		tbb[j].fsStyle = (UCHAR)states[j][1];
	}  

	VERIFY((ret = SendMessage(m_hwndtool, TB_ADDBUTTONS, (WPARAM)size,(LPARAM) &tbb)!= FALSE));

    /* Now set and show the toolbar */
	SendMessage(m_hwndtool, TB_AUTOSIZE, 0, 0);
	ShowWindow(m_hwndtool, SW_SHOW);
}