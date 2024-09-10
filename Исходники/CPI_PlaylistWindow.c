void CPlaylistWindow_CreateIPEdit(const int iItem, const int iSubItem)
{
	RECT rSubItem;
	const char* pcClass;
	DWORD dwStyle;
	int iSearchItemIDX;
	UINT uiControlID;
	BOOL bClearNonSelectedItems;
	CP_HPLAYLISTITEM hClickedItem;
	HWND hWndList;
	int iNumItemsSelected;
	
	// If the clicked item is not read/write then skip this
	hClickedItem = (CP_HPLAYLISTITEM)CLV_GetItemData(globals.m_hPlaylistViewControl, iItem);
	
	if (CPLI_GetReadWriteState(hClickedItem) != rwsReadWrite)
	{
		MessageBox(windows.m_hWndPlaylist, "This file's ID3 tag cannot be updated.  This is because CoolPlayer cannot write to this file.", "Cannot update tag", MB_OK | MB_ICONSTOP);
		return;
	}
	
	// For some sub items it is not logical to multi update - action these
	
	if (iSubItem == PLAYLIST_TITLE)
		bClearNonSelectedItems = TRUE;
	else
		bClearNonSelectedItems = FALSE;
		
	// Go through the selected items and remove the selection of items that
	// cannot be written to (eg because of a read only file)
	iSearchItemIDX = CLV_GetNextSelectedItem(globals.m_hPlaylistViewControl, CPC_INVALIDITEM);
	
	iNumItemsSelected = 1;
	
	for (;iSearchItemIDX != -1; iSearchItemIDX = CLV_GetNextSelectedItem(globals.m_hPlaylistViewControl, iSearchItemIDX))
	{
		CP_HPLAYLISTITEM hItem = (CP_HPLAYLISTITEM)CLV_GetItemData(globals.m_hPlaylistViewControl, iSearchItemIDX);
		CPLI_ReadTag(hItem);
		
		// We've already checked this item
		
		if (iSearchItemIDX == iItem)
			continue;
			
		iNumItemsSelected++;
		
		if (bClearNonSelectedItems == TRUE || CPLI_GetReadWriteState(hItem) != rwsReadWrite)
			CLV_SetItemSelected(globals.m_hPlaylistViewControl, iSearchItemIDX, FALSE);
	}
	
	// If the "track number" column was clicked - and there are multiple selections - auto number them
	
	if (iSubItem == PLAYLIST_TRACKNUM && iNumItemsSelected > 1)
	{
		char cStatusMessage[1024];
		int iTrackNumber;
		
		// Autonumber
		SetCursor(LoadCursor(NULL, IDC_WAIT));
		iSearchItemIDX = CLV_GetNextSelectedItem(globals.m_hPlaylistViewControl, CPC_INVALIDITEM);
		iTrackNumber = 1;
		
		for (;iSearchItemIDX != CPC_INVALIDITEM; iSearchItemIDX = CLV_GetNextSelectedItem(globals.m_hPlaylistViewControl, iSearchItemIDX))
		{
			CP_HPLAYLISTITEM hItem = (CP_HPLAYLISTITEM)CLV_GetItemData(globals.m_hPlaylistViewControl, iSearchItemIDX);
			
			sprintf(cStatusMessage, "Tagging \"%s\"", CPLI_GetFilename(hItem));
			CP_TRACE1("status: %s", cStatusMessage);
			CPIC_SetIndicatorValue("status", cStatusMessage);
			UpdateWindow(IF_GetHWnd(windows.m_hifPlaylist));
			
			CPLI_SetTrackNum(hItem, iTrackNumber);
			CPLI_WriteTag(hItem);
			iTrackNumber++;
		}
		
		SetCursor(LoadCursor(NULL, IDC_ARROW));
		
		CPIC_SetIndicatorValue("status", NULL);
		return;
	}
	
	// If the length was clicked - work out the lengths for all selected items
	
	if (iSubItem == PLAYLIST_LENGTH)
	{
		char cStatusMessage[1024];
		
		SetCursor(LoadCursor(NULL, IDC_WAIT));
		iSearchItemIDX = CLV_GetNextSelectedItem(globals.m_hPlaylistViewControl, CPC_INVALIDITEM);
		
		for (; iSearchItemIDX != CPC_INVALIDITEM; iSearchItemIDX = CLV_GetNextSelectedItem(globals.m_hPlaylistViewControl, iSearchItemIDX))
		{
			CP_HPLAYLISTITEM hItem = (CP_HPLAYLISTITEM)CLV_GetItemData(globals.m_hPlaylistViewControl, iSearchItemIDX);
			
			CPLI_CalculateLength(hItem);
			sprintf(cStatusMessage, "Tagging \"%s\"", CPLI_GetFilename(hItem));
			
			CPIC_SetIndicatorValue("status", cStatusMessage);
			CP_TRACE1("status: %s", cStatusMessage);
			UpdateWindow(IF_GetHWnd(windows.m_hifPlaylist));
			
			CPLI_WriteTag(hItem);
		}
		
		SetCursor(LoadCursor(NULL, IDC_ARROW));
		
		CPIC_SetIndicatorValue("status", NULL);
		return;
	}
	
	// We want to get the subitem's rect in the co-ordinate space of the dialog
	hWndList = CLV_GetHWND(globals.m_hPlaylistViewControl);
	
	CLV_GetItemSubRect(globals.m_hPlaylistViewControl, &rSubItem, iItem, iSubItem);
	ClientToScreen(hWndList, (POINT*)&rSubItem);
	ClientToScreen(hWndList, ((POINT*)&rSubItem) + 1);
	ScreenToClient(IF_GetHWnd(windows.m_hifPlaylist), (POINT*)&rSubItem);
	ScreenToClient(IF_GetHWnd(windows.m_hifPlaylist), ((POINT*)&rSubItem) + 1);
	
	if (iSubItem == PLAYLIST_GENRE)
	{
		// int iRectHeight = rSubItem.bottom-rSubItem.top;
		// int iListHeight = iRectHeight<<3;
		
		InflateRect(&rSubItem, 2, 2);
		pcClass = "COMBOBOX";
		uiControlID = IDC_PL_FLOATINGCOMBO;
		dwStyle = CBS_DROPDOWNLIST | CBS_SORT | WS_VSCROLL;
		
		rSubItem.bottom += (rSubItem.bottom - rSubItem.top) << 3;
	}
	
	else
	{
		InflateRect(&rSubItem, 2, 2);
		pcClass = "EDIT";
		dwStyle = ES_AUTOHSCROLL;
		uiControlID = IDC_PL_FLOATINGEDIT;
		
		if (iSubItem == PLAYLIST_TRACKNUM || iSubItem == PLAYLIST_YEAR)
			dwStyle |= ES_NUMBER;
	}
	
	// Setup window class and style (the Genre window will be a combo)
	globals.m_bIP_InhibitUpdates = TRUE;
	
	windows.wnd_playlist_IPEdit = CreateWindow(pcClass,
								  "",
								  WS_CHILD
								  | WS_BORDER
								  | WS_CLIPSIBLINGS
								  | dwStyle,
								  rSubItem.left, rSubItem.top,
								  rSubItem.right - rSubItem.left, rSubItem.bottom - rSubItem.top,
								  IF_GetHWnd(windows.m_hifPlaylist),
								  (HMENU)uiControlID,
								  GetModuleHandle(NULL), NULL);
	                              
	SetWindowPos(windows.wnd_playlist_IPEdit, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	ShowWindow(windows.wnd_playlist_IPEdit, SW_SHOW);
	SetFocus(windows.wnd_playlist_IPEdit);
	
	// Setup the font in the control
	SendMessage(windows.wnd_playlist_IPEdit, WM_SETFONT, (WPARAM)glb_pSkin->mpl_hfFont, MAKELPARAM(TRUE, 0));
	
	// Hook the listview window (so that we can dismiss on VScroll)
	globals.m_hhkListView_Posted = SetWindowsHookEx(WH_GETMESSAGE, exp_ListViewHookProc_Posted, NULL, GetCurrentThreadId());
	
	// Add the genre items to the list
	if (iSubItem == PLAYLIST_GENRE)
	{
		int iGenreIDX;
		
		for (iGenreIDX = 0; iGenreIDX < CIC_NUMGENRES; iGenreIDX++)
		{
			int iNewItemIDX = SendMessage(windows.wnd_playlist_IPEdit,
										  CB_ADDSTRING,
										  0L,
										  (LPARAM)glb_pcGenres[iGenreIDX]);
			SendMessage(windows.wnd_playlist_IPEdit, CB_SETITEMDATA, (WPARAM)iNewItemIDX, (LPARAM)iGenreIDX);
		}
	}
	
	// Setup the initial string
	globals.m_iInPlaceSubItem = iSubItem;
	
	{
		switch (iSubItem)
		{
		
			case PLAYLIST_TITLE:
				SendMessage(windows.wnd_playlist_IPEdit, WM_SETTEXT, 0L, (LPARAM)CPLI_GetTrackName(hClickedItem));
				
				if (!options.support_id3v2)
					SendMessage(windows.wnd_playlist_IPEdit, EM_LIMITTEXT, 30, 0);
					
				break;
				
			case PLAYLIST_ARTIST:
				SendMessage(windows.wnd_playlist_IPEdit, WM_SETTEXT, 0L, (LPARAM)CPLI_GetArtist(hClickedItem));
				
				if (!options.support_id3v2)
					SendMessage(windows.wnd_playlist_IPEdit, EM_LIMITTEXT, 30, 0);
					
				break;
				
			case PLAYLIST_ALBUM:
				SendMessage(windows.wnd_playlist_IPEdit, WM_SETTEXT, 0L, (LPARAM)CPLI_GetAlbum(hClickedItem));
				
				if (!options.support_id3v2)
					SendMessage(windows.wnd_playlist_IPEdit, EM_LIMITTEXT, 30, 0);
					
				break;
				
			case PLAYLIST_YEAR:
				SendMessage(windows.wnd_playlist_IPEdit, WM_SETTEXT, 0L, (LPARAM)CPLI_GetYear(hClickedItem));
				
				if (!options.support_id3v2)
					SendMessage(windows.wnd_playlist_IPEdit, EM_LIMITTEXT, 4, 0);
					
				break;
				
			case PLAYLIST_TRACKNUM:
			{
				char cTrackNum[33];
				unsigned char iTrackNum;
				
				iTrackNum = CPLI_GetTrackNum(hClickedItem);
				
				if (iTrackNum != CIC_INVALIDTRACKNUM && iTrackNum != 0)
					SendMessage(windows.wnd_playlist_IPEdit, WM_SETTEXT, 0L, (LPARAM)_itoa(iTrackNum, cTrackNum, 10));
			}
			
			SendMessage(windows.wnd_playlist_IPEdit, EM_LIMITTEXT, 3, 0);
			
			break;
			
			case PLAYLIST_COMMENT:
				SendMessage(windows.wnd_playlist_IPEdit, WM_SETTEXT, 0L, (LPARAM)CPLI_GetComment(hClickedItem));
				
				if (!options.support_id3v2)
					SendMessage(windows.wnd_playlist_IPEdit, EM_LIMITTEXT, 28, 0);
					
				break;
				
			case PLAYLIST_GENRE:
				SendMessage(windows.wnd_playlist_IPEdit, CB_SELECTSTRING, (WPARAM) - 1, (LPARAM)CPLI_GetGenre(hClickedItem));
				
				break;
		}
	}
	
	globals.m_bIP_InhibitUpdates = FALSE;
}