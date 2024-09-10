void FolderTree::DisplayPath(const tstring &sPath, HTREEITEM hParent, bool bUseSetRedraw /* = true */)
{
	//CWaitCursor c;

	//Speed up the job by turning off redraw
	if (bUseSetRedraw)
		SetRedraw(false);

	//Remove all the items currently under hParent
	HTREEITEM hChild = GetChildItem(hParent);
	while (hChild)
	{
		DeleteItem(hChild);
		hChild = GetChildItem(hParent);
	}

	//Should we display the root folder
	if (m_bShowRootedFolder && (hParent == TVI_ROOT))
	{
		FolderTreeItemInfo* pItem = new FolderTreeItemInfo;
		pItem->m_sFQPath = m_sRootFolder;
		pItem->m_sRelativePath = m_sRootFolder;
		m_hRootedFolder = InsertFileItem(TVI_ROOT, pItem, false, GetIconIndex(m_sRootFolder), GetSelIconIndex(m_sRootFolder), true);
		Expand(m_hRootedFolder, TVE_EXPAND);
		return;
	}

	//find all the directories underneath sPath
	int nDirectories = 0;
	
	tstring sFile;
	if (sPath[sPath.size()-1] != _T('\\'))
		sFile = sPath + _T("\\");
	else
		sFile = sPath;

	WIN32_FIND_DATA fData;
	HANDLE hFind;
	hFind = FindFirstFile((sFile + _T("*")).c_str(), &fData);

	if(hFind != INVALID_HANDLE_VALUE)

	{
		do
		{
			tstring filename = fData.cFileName;
			if((fData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && 
				(filename != _T(".")) && (filename != _T("..")))
			{
				++nDirectories;
				tstring path = sFile + filename;

				TCHAR szPath[_MAX_PATH];
				TCHAR szFname[_MAX_FNAME];
				TCHAR szExt[_MAX_EXT];
				_tsplitpath(path.c_str(), NULL, NULL, szFname, szExt);
				_tmakepath(szPath, NULL, NULL, szFname, szExt);

				FolderTreeItemInfo* pItem = new FolderTreeItemInfo;
				pItem->m_sFQPath = path;
				pItem->m_sRelativePath = szPath;
				InsertFileItem(hParent, pItem, m_bShowSharedUsingDifferentIcon && IsShared(path), GetIconIndex(path), GetSelIconIndex(path), true);
			}
		} while (FindNextFile(hFind, &fData));
	}

	FindClose(hFind);

	//Now sort the items we just added
	TVSORTCB tvsortcb;
	tvsortcb.hParent = hParent;
	tvsortcb.lpfnCompare = CompareByFilenameNoCase;
	tvsortcb.lParam = 0;
	SortChildrenCB(&tvsortcb);

	//We want to add them before sorting
	checkRemovedDirs(sFile, hParent);

	//If no items were added then remove the "+" indicator from hParent
	if(nDirectories == 0)
		SetHasPlusButton(hParent, FALSE);

	//Turn back on the redraw flag
	if(bUseSetRedraw)
		SetRedraw(true);
}