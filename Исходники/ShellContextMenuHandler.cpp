void Explorerplusplus::AddMenuEntries(LPITEMIDLIST pidlParent,
	const std::list<LPITEMIDLIST> &pidlItemList,DWORD_PTR dwData,HMENU hMenu)
{
	assert(dwData != NULL);

	FileContextMenuInfo_t *pfcmi = reinterpret_cast<FileContextMenuInfo_t *>(dwData);

	bool AddNewTabMenuItem = false;

	if(pfcmi->uFrom == FROM_LISTVIEW)
	{
		if(pidlItemList.size() == 1)
		{
			SFGAOF FileAttributes = SFGAO_FOLDER;

			LPITEMIDLIST pidlComplete = ILCombine(pidlParent,pidlItemList.front());
			GetItemAttributes(pidlComplete,&FileAttributes);
			CoTaskMemFree(pidlComplete);

			if(FileAttributes & SFGAO_FOLDER)
			{
				AddNewTabMenuItem = true;
			}
		}
	}
	else if(pfcmi->uFrom == FROM_TREEVIEW)
	{
		/* The treeview only contains folders,
		so the new tab menu item will always
		be shown. */
		AddNewTabMenuItem = true;
	}

	if(AddNewTabMenuItem)
	{
		MENUITEMINFO mii;
		TCHAR szTemp[64];

		LoadString(m_hLanguageModule,IDS_GENERAL_OPEN_IN_NEW_TAB,szTemp,SIZEOF_ARRAY(szTemp));
		mii.cbSize		= sizeof(mii);
		mii.fMask		= MIIM_STRING|MIIM_ID;
		mii.wID			= MENU_OPEN_IN_NEW_TAB;
		mii.dwTypeData	= szTemp;
		InsertMenuItem(hMenu,1,TRUE,&mii);
	}
}