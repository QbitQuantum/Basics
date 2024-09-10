void CMuleToolbarCtrl::OnNmRClick(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
	if (GetKeyState(VK_CONTROL) & 0x8000)
	{
		if (!thePrefs.GetToolbarBitmapSettings().IsEmpty())
			ChangeToolbarBitmap(thePrefs.GetToolbarBitmapSettings(), true);
		if (!thePrefs.GetSkinProfile().IsEmpty())
			theApp.ApplySkin(thePrefs.GetSkinProfile());

		*pResult = TRUE;
		return;
	}


	///////////////////////////////////////////////////////////////////////////
	// "Toolbar Bitmap" sub menu
	//
	CMenu menuBitmaps;
	menuBitmaps.CreateMenu();
	menuBitmaps.AppendMenu(MF_STRING, MP_SELECTTOOLBARBITMAP, GetResString(IDS_SELECTTOOLBARBITMAP));
	menuBitmaps.AppendMenu(MF_STRING, MP_SELECTTOOLBARBITMAPDIR, GetResString(IDS_SELECTTOOLBARBITMAPDIR));
	menuBitmaps.AppendMenu(MF_SEPARATOR);
	menuBitmaps.AppendMenu(MF_STRING, MP_TOOLBARBITMAP, GetResString(IDS_DEFAULT));
	
	m_astrToolbarPaths.RemoveAll();
	CString currentBitmapSettings = thePrefs.GetToolbarBitmapSettings();
	bool checked = false;
	if (currentBitmapSettings.IsEmpty())
	{
		menuBitmaps.CheckMenuItem(MP_TOOLBARBITMAP, MF_CHECKED);
		menuBitmaps.EnableMenuItem(MP_TOOLBARBITMAP, MF_DISABLED);
		checked = true;
	}
	m_astrToolbarPaths.Add(_T("")); // dummy entry for 'Default' menu item
	int i = 1;
	if (!thePrefs.GetMuleDirectory(EMULE_TOOLBARDIR).IsEmpty())
	{
		CStringArray astrToolbarFiles;
		for (int f = 0; f < _countof(s_apszTBFiles); f++)
		{
			WIN32_FIND_DATA FileData;
			HANDLE hSearch = FindFirstFile(thePrefs.GetMuleDirectory(EMULE_TOOLBARDIR) + CString(_T("\\")) + s_apszTBFiles[f], &FileData);
			if (hSearch != INVALID_HANDLE_VALUE)
			{
				do {
					astrToolbarFiles.Add(FileData.cFileName);
				}
				while (astrToolbarFiles.GetCount() < MAX_TOOLBAR_FILES && FindNextFile(hSearch, &FileData));
				FindClose(hSearch);
			}
		}

		if (astrToolbarFiles.GetCount() > 0)
		{
			Sort(astrToolbarFiles);
			for (int f = 0; f < astrToolbarFiles.GetCount(); f++)
			{
				const CString& bitmapFileName = astrToolbarFiles.GetAt(f);
				CString bitmapBaseName;
				LPCTSTR pszTbBaseExt = stristr(bitmapFileName, EMULTB_BASEEXT);
				if (pszTbBaseExt)
					bitmapBaseName = bitmapFileName.Left(pszTbBaseExt - (LPCTSTR)bitmapFileName - 1);
				else
					bitmapBaseName = bitmapFileName;
				menuBitmaps.AppendMenu(MF_STRING, MP_TOOLBARBITMAP + i, bitmapBaseName);
				m_astrToolbarPaths.Add(thePrefs.GetMuleDirectory(EMULE_TOOLBARDIR) + CString(_T("\\")) + bitmapFileName);
				if (!checked && currentBitmapSettings.CompareNoCase(m_astrToolbarPaths[i]) == 0)
				{
					menuBitmaps.CheckMenuItem(MP_TOOLBARBITMAP + i, MF_CHECKED);
					menuBitmaps.EnableMenuItem(MP_TOOLBARBITMAP + i, MF_DISABLED);
					checked = true;
				}
				i++;
			}
		}
		ASSERT( i-1 == astrToolbarFiles.GetCount() );
	}
	if (!checked)
	{
		menuBitmaps.AppendMenu(MF_STRING, MP_TOOLBARBITMAP + i, currentBitmapSettings);
		menuBitmaps.CheckMenuItem(MP_TOOLBARBITMAP + i, MF_CHECKED);
		menuBitmaps.EnableMenuItem(MP_TOOLBARBITMAP + i, MF_DISABLED);
		m_astrToolbarPaths.Add(currentBitmapSettings);
	}


	///////////////////////////////////////////////////////////////////////////
	// "Skin Profile" sub menu
	//
	CMenu menuSkins;
	menuSkins.CreateMenu();
	menuSkins.AppendMenu(MF_STRING, MP_SELECT_SKIN_FILE, GetResString(IDS_SEL_SKIN));
	menuSkins.AppendMenu(MF_STRING, MP_SELECT_SKIN_DIR, GetResString(IDS_SEL_SKINDIR));
	menuSkins.AppendMenu(MF_SEPARATOR);
	menuSkins.AppendMenu(MF_STRING, MP_SKIN_PROFILE,GetResString(IDS_DEFAULT));

	m_astrSkinPaths.RemoveAll();
	CString currentSkin = thePrefs.GetSkinProfile();
	checked = false;
	if (currentSkin.IsEmpty())
	{
		menuSkins.CheckMenuItem(MP_SKIN_PROFILE, MF_CHECKED);
		menuSkins.EnableMenuItem(MP_SKIN_PROFILE, MF_DISABLED);
		checked = true;
	}
	m_astrSkinPaths.Add(_T("")); // dummy entry for 'Default' menu item
	i = 1;
	if (!thePrefs.GetMuleDirectory(EMULE_SKINDIR, false).IsEmpty())
	{
		CStringArray astrSkinFiles;
		for (int f = 0; f < _countof(s_apszSkinFiles); f++)
		{
			WIN32_FIND_DATA FileData;
			HANDLE hSearch = FindFirstFile(thePrefs.GetMuleDirectory(EMULE_SKINDIR, false) + CString(_T("\\")) + s_apszSkinFiles[f], &FileData);
			if (hSearch != INVALID_HANDLE_VALUE)
			{
				do {
					astrSkinFiles.Add(FileData.cFileName);
				}
				while (astrSkinFiles.GetCount() < MAX_SKIN_FILES && FindNextFile(hSearch, &FileData));
				FindClose(hSearch);
			}
		}

		if (astrSkinFiles.GetCount() > 0)
		{
			Sort(astrSkinFiles);
			for (int f = 0; f < astrSkinFiles.GetCount(); f++)
			{
				const CString& skinFileName = astrSkinFiles.GetAt(f);
				CString skinBaseName;
				LPCTSTR pszSkinBaseExt = stristr(skinFileName, _T(".") EMULSKIN_BASEEXT _T(".ini"));
				if (pszSkinBaseExt)
					skinBaseName = skinFileName.Left(pszSkinBaseExt - (LPCTSTR)skinFileName);
				else
					skinBaseName = skinFileName;
				menuSkins.AppendMenu(MF_STRING, MP_SKIN_PROFILE + i, skinBaseName);
				m_astrSkinPaths.Add(thePrefs.GetMuleDirectory(EMULE_SKINDIR, false) + CString(_T("\\")) + skinFileName);
				if (!checked && currentSkin.CompareNoCase(m_astrSkinPaths[i]) == 0)
				{
					menuSkins.CheckMenuItem(MP_SKIN_PROFILE + i, MF_CHECKED);
					menuSkins.EnableMenuItem(MP_SKIN_PROFILE + i, MF_DISABLED);
					checked = true;
				}
				i++;
			}
		}
		ASSERT( i-1 == astrSkinFiles.GetCount() );
	}
	if (!checked)
	{
		menuSkins.AppendMenu(MF_STRING, MP_SKIN_PROFILE + i, currentSkin);
		menuSkins.CheckMenuItem(MP_SKIN_PROFILE + i, MF_CHECKED);
		menuSkins.EnableMenuItem(MP_SKIN_PROFILE + i, MF_DISABLED);
		m_astrSkinPaths.Add(currentSkin);
	}
	

	///////////////////////////////////////////////////////////////////////////
	// "Text Label" sub menu
	//
	CMenu menuTextLabels;
	menuTextLabels.CreateMenu();
	ASSERT( MP_NOTEXTLABELS == MP_TEXTLABELS-1 && MP_NOTEXTLABELS == MP_TEXTLABELSONRIGHT-2 );
	ASSERT( MP_NOTEXTLABELS + (int)NoLabels == MP_NOTEXTLABELS );
	ASSERT( MP_NOTEXTLABELS + (int)LabelsBelow == MP_TEXTLABELS );
	ASSERT( MP_NOTEXTLABELS + (int)LabelsRight == MP_TEXTLABELSONRIGHT );
	menuTextLabels.AppendMenu(MF_STRING | MF_ENABLED, MP_NOTEXTLABELS, GetResString(IDS_NOTEXTLABELS));
	menuTextLabels.AppendMenu(MF_STRING | MF_ENABLED, MP_TEXTLABELS, GetResString(IDS_ENABLETEXTLABELS));
	menuTextLabels.AppendMenu(MF_STRING | MF_ENABLED, MP_TEXTLABELSONRIGHT, GetResString(IDS_TEXTLABELSONRIGHT));
	menuTextLabels.CheckMenuRadioItem(MP_NOTEXTLABELS, MP_TEXTLABELSONRIGHT, MP_NOTEXTLABELS + (int)thePrefs.GetToolbarLabelSettings(), MF_BYCOMMAND);
	menuTextLabels.EnableMenuItem(MP_NOTEXTLABELS + (int)thePrefs.GetToolbarLabelSettings(), MF_BYCOMMAND | MF_DISABLED);

	menuTextLabels.AppendMenu(MF_SEPARATOR);
	menuTextLabels.AppendMenu(MF_STRING, MP_LARGEICONS, GetResString(IDS_LARGEICONS));
	menuTextLabels.AppendMenu(MF_STRING, MP_SMALLICONS, GetResString(IDS_SMALLICONS));
	ASSERT( MP_LARGEICONS == MP_SMALLICONS-1 );
	menuTextLabels.CheckMenuRadioItem(MP_LARGEICONS, MP_SMALLICONS, m_sizBtnBmp.cx == 16 ? MP_SMALLICONS : MP_LARGEICONS, MF_BYCOMMAND);
	menuTextLabels.EnableMenuItem(m_sizBtnBmp.cx == 16 ? MP_SMALLICONS : MP_LARGEICONS, MF_BYCOMMAND | MF_DISABLED);


	///////////////////////////////////////////////////////////////////////////
	// Toolbar context menu
	//
	CMenu menuToolbar;
	menuToolbar.CreatePopupMenu();
	menuToolbar.AppendMenu(MF_STRING | MF_POPUP, (UINT_PTR)menuBitmaps.m_hMenu, GetResString(IDS_TOOLBARSKINS));
	menuToolbar.AppendMenu(MF_STRING | MF_POPUP, (UINT_PTR)menuSkins.m_hMenu, GetResString(IDS_SKIN_PROF));
	menuToolbar.AppendMenu(MF_STRING | MF_POPUP, (UINT_PTR)menuTextLabels.m_hMenu, GetResString(IDS_TEXTLABELS));
	menuToolbar.AppendMenu(MF_STRING, MP_CUSTOMIZETOOLBAR, GetResString(IDS_CUSTOMIZETOOLBAR));
	CPoint point;
	GetCursorPos(&point);
	menuToolbar.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);

	*pResult = TRUE;
}