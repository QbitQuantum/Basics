/* TODO: This code should be coalesced with the code that
adds items as well as the code that finds their icons.
ALL changes to an items name/internal properties/icon/overlay icon
should go through a central function. */
void CFolderView::RenameItem(int iItemInternal,TCHAR *szNewFileName)
{
	IShellFolder	*pShellFolder = NULL;
	LPITEMIDLIST	pidlFull = NULL;
	LPITEMIDLIST	pidlRelative = NULL;
	SHFILEINFO		shfi;
	LVFINDINFO		lvfi;
	TCHAR			szDisplayName[MAX_PATH];
	LVITEM			lvItem;
	TCHAR			szFullFileName[MAX_PATH];
	DWORD_PTR		res;
	HRESULT			hr;
	int				iItem;

	if(iItemInternal == -1)
		return;

	StringCchCopy(szFullFileName,MAX_PATH,m_CurDir);
	PathAppend(szFullFileName,szNewFileName);

	hr = GetIdlFromParsingName(szFullFileName,&pidlFull);

	if(SUCCEEDED(hr))
	{
		hr = SHBindToParent(pidlFull,IID_IShellFolder,(void **)&pShellFolder,(LPCITEMIDLIST *)&pidlRelative);

		if(SUCCEEDED(hr))
		{
			hr = GetDisplayName(szFullFileName,szDisplayName,SHGDN_INFOLDER|SHGDN_FORPARSING);

			if(SUCCEEDED(hr))
			{
				m_pExtraItemInfo[iItemInternal].pridl = ILClone(pidlRelative);
				StringCchCopy(m_pExtraItemInfo[iItemInternal].szDisplayName,
					SIZEOF_ARRAY(m_pExtraItemInfo[iItemInternal].szDisplayName),
					szDisplayName);

				/* Need to update internal storage for the item, since
				it's name has now changed. */
				StringCchCopy(m_pwfdFiles[iItemInternal].cFileName,
					SIZEOF_ARRAY(m_pwfdFiles[iItemInternal].cFileName),
					szNewFileName);

				/* The files' type may have changed, so retrieve the files'
				icon again. */
				res = SHGetFileInfo((LPTSTR)pidlFull,0,&shfi,
					sizeof(SHFILEINFO),SHGFI_PIDL|SHGFI_ICON|
					SHGFI_OVERLAYINDEX);

				if(res != 0)
				{
					/* Locate the item within the listview. */
					lvfi.flags	= LVFI_PARAM;
					lvfi.lParam	= iItemInternal;
					iItem = ListView_FindItem(m_hListView,-1,&lvfi);

					if(iItem != -1)
					{
						lvItem.mask			= LVIF_TEXT|LVIF_IMAGE|LVIF_STATE;
						lvItem.iItem		= iItem;
						lvItem.iSubItem		= 0;
						lvItem.iImage		= shfi.iIcon;
						lvItem.pszText		= ProcessItemFileName(iItemInternal);
						lvItem.stateMask	= LVIS_OVERLAYMASK;

						/* As well as resetting the items icon, we'll also set
						it's overlay again (the overlay could change, for example,
						if the file is changed to a shortcut). */
						lvItem.state		= INDEXTOOVERLAYMASK(shfi.iIcon >> 24);

						/* Update the item in the listview. */
						ListView_SetItem(m_hListView,&lvItem);

						/* TODO: Does the file need to be filtered out? */
						if(IsFileFiltered(iItemInternal))
						{
							RemoveFilteredItem(iItem,iItemInternal);
						}
					}

					DestroyIcon(shfi.hIcon);
				}
			}

			pShellFolder->Release();
		}