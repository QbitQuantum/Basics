void COggSplitter::ShowPopupMenu()
{
	int				groupID[16];
	HMENU			groupMenu[16];
	int				cGroups = 0;
	MENUITEMINFO	myItem;

	int				i = 0;

	AM_MEDIA_TYPE*	pmt;
	DWORD			dwGroup;
	DWORD			dwFlags;
	wchar_t*		pwzCaption;

	HMENU	hPopup = CreatePopupMenu();

	while (Info(i, &pmt, &dwFlags, NULL, &dwGroup, &pwzCaption, NULL, NULL) == NOERROR)
	{
		// Is there already a submenu for this group?
		int	j = 0;
		while ((j < cGroups) && (groupID[j] != dwGroup)) j++;

		if (j == cGroups)	// There is still no submenu ..
		{
            char*	pMenuType;

			if (!pmt)
				pMenuType = GetLocString(sidTypeOther);
			else if (pmt->majortype == MEDIATYPE_Audio)
				pMenuType = GetLocString(sidTypeAudio);
			else if (pmt->majortype == MEDIATYPE_Text)
				pMenuType = GetLocString(sidTypeSubtitle);
			else if (pmt->majortype == MEDIATYPE_Video)
			{			
				if (pmt->pbFormat)
					pMenuType = GetLocString(sidTypeVideo);
				else
					pMenuType = GetLocString(sidTypeChapter);
			}

			groupMenu[j] = CreatePopupMenu();
			groupID[j] = dwGroup;
			
			memset(&myItem, 0, sizeof(myItem));
			myItem.cbSize = sizeof(myItem);
			myItem.fMask = MIIM_TYPE | MIIM_SUBMENU;
			myItem.fType = MFT_STRING;
			myItem.hSubMenu = groupMenu[j];
			myItem.dwTypeData = pMenuType;
			myItem.cch = strlen(pMenuType);
			InsertMenuItem(hPopup, -1, TRUE, &myItem);
			cGroups++;
		}
		
		char		szItemText[128];
		wchar_t*	pwzItemText = pwzCaption;
		
		// Let´s skip the first word if not chapter
		if (pmt && ((pmt->majortype != MEDIATYPE_Video) || pmt->pbFormat))
		{
			pwzItemText = wcsstr(pwzItemText, L" ");
			pwzItemText++;
		}

		wsprintf(szItemText, "%S", pwzItemText);

		memset(&myItem, 0, sizeof(myItem));
		myItem.cbSize = sizeof(myItem);
		myItem.fMask = MIIM_TYPE | MIIM_ID | MIIM_STATE;
		myItem.fType = MFT_STRING | MFT_RADIOCHECK;
		myItem.fState = MFS_ENABLED;
		if (dwFlags == AMSTREAMSELECTINFO_ENABLED)
			myItem.fState |= MFS_CHECKED;
		myItem.wID = i;
		myItem.dwTypeData = szItemText;
		myItem.cch = strlen(myItem.dwTypeData);

		InsertMenuItem(groupMenu[j], -1, TRUE, &myItem);

		if (pmt)
			DeleteMediaType(pmt);
		CoTaskMemFree(pwzCaption);
		i++;
	}

	HMENU	hPropMenu = NULL;
	char	szName[MAX_FILTER_NAME];
	
	// If we are in the graph find all filters with property pages
	if (m_pGraph)
	{
		hPropMenu = CreatePopupMenu();

		// Insert the separator
		memset(&myItem, 0, sizeof(myItem));
		myItem.cbSize = sizeof(myItem);
		myItem.fMask = MIIM_TYPE;
		myItem.fType = MFT_SEPARATOR;
		InsertMenuItem(hPopup, -1, TRUE, &myItem);

		// Insert the properties item
		memset(&myItem, 0, sizeof(myItem));
		myItem.cbSize = sizeof(myItem);
		myItem.fMask = MIIM_TYPE | MIIM_SUBMENU;
		myItem.fType = MFT_STRING;
		myItem.hSubMenu = hPropMenu;
		myItem.dwTypeData = GetLocString(sidProperties);
		myItem.cch = strlen(myItem.dwTypeData);
		InsertMenuItem(hPopup, -1, TRUE, &myItem);

		IEnumFilters*			pEnum;
		IBaseFilter*			pFilter;
		ISpecifyPropertyPages*	pSPP;
		ULONG					cFetched;
		DWORD					dwID = ID_MENUITEM_PROPERTIES;

		m_pGraph->EnumFilters(&pEnum);

		do
		{
			if (FAILED(pEnum->Next(1, &pFilter, &cFetched)))
				cFetched = 0;

			if (cFetched)
			{
				if (SUCCEEDED(pFilter->QueryInterface(IID_ISpecifyPropertyPages,
														(void**)&pSPP)))
				{
					pSPP->Release();

					FILTER_INFO	Info;

					pFilter->QueryFilterInfo(&Info);
					wsprintf(szName, "%S", Info.achName);
					Info.pGraph->Release();

					memset(&myItem, 0, sizeof(myItem));
					myItem.cbSize = sizeof(myItem);
					myItem.fMask = MIIM_TYPE | MIIM_ID;
					myItem.fType = MFT_STRING;
					myItem.wID = dwID;
					myItem.dwTypeData = szName;
					myItem.cch = strlen(myItem.dwTypeData);
					InsertMenuItem(hPropMenu, -1, TRUE, &myItem);
					dwID++;
				}
				pFilter->Release();
			}
		} while (cFetched);
		pEnum->Release();
	}

	POINT	ptCursorPos;
	DWORD	dwSelection;

	GetCursorPos(&ptCursorPos);
	SetForegroundWindow(m_hTrayWnd);
	PostMessage(m_hTrayWnd, WM_NULL, 0, 0); 
	dwSelection = TrackPopupMenu(hPopup, TPM_NONOTIFY | TPM_RETURNCMD,
					ptCursorPos.x, ptCursorPos.y, 0, m_hTrayWnd, NULL);

	if (dwSelection <  ID_MENUITEM_PROPERTIES)
	{
		Enable(dwSelection, AMSTREAMSELECTENABLE_ENABLE);
		return;
	}

	GetMenuString(hPropMenu, dwSelection, szName, MAX_FILTER_NAME, MF_BYCOMMAND);
	if (m_pGraph)
	{
		wchar_t					wszName[MAX_FILTER_NAME];
		IBaseFilter*			pFilter;
		ISpecifyPropertyPages*	pSPP;
		
		wsprintfW(wszName, L"%s", szName);
		if (SUCCEEDED(m_pGraph->FindFilterByName(wszName, &pFilter)))
		{
			if (SUCCEEDED(pFilter->QueryInterface(IID_ISpecifyPropertyPages,
													(void**)&pSPP)))
			{
				IUnknown*	pFilterUnk;
				pFilter->QueryInterface(IID_IUnknown, (void **)&pFilterUnk);
				
				CAUUID caGUID;
				pSPP->GetPages(&caGUID);
				pSPP->Release();
			    OleCreatePropertyFrame(m_hTrayWnd, 0, 0, wszName, 1, &pFilterUnk,
										caGUID.cElems, caGUID.pElems, 0, 0, NULL);
				pFilterUnk->Release();
				CoTaskMemFree(caGUID.pElems);
			}
			pFilter->Release();
		}
	}

	DestroyMenu(hPopup);
}