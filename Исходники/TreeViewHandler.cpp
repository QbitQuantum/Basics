void Explorerplusplus::OnTreeViewRightClick(WPARAM wParam,LPARAM lParam)
{
	LPITEMIDLIST pidl = NULL;
	POINT *ppt = NULL;
	HTREEITEM hItem;
	HTREEITEM hPrevItem;
	IShellFolder *pShellParentFolder = NULL;
	LPITEMIDLIST pidlRelative = NULL;
	HRESULT hr;

	hItem	= (HTREEITEM)wParam;
	ppt		= (POINT *)lParam;

	m_bTreeViewRightClick = TRUE;

	hPrevItem = TreeView_GetSelection(m_hTreeView);
	TreeView_SelectItem(m_hTreeView,hItem);
	pidl = m_pMyTreeView->BuildPath(hItem);

	hr = SHBindToParent(pidl, IID_PPV_ARGS(&pShellParentFolder),
	(LPCITEMIDLIST *)&pidlRelative);

	if(SUCCEEDED(hr))
	{
		HTREEITEM hParent;
		LPITEMIDLIST pidlParent	= NULL;

		hParent = TreeView_GetParent(m_hTreeView,hItem);

		/* If we right-click on the "Desktop" item in the treeview, there is no parent.
		   In such case, use "Desktop" as parent item as well, to allow the context menu
		   to be shown. */
		if(hParent == NULL)
		{
			hParent = hItem;
		}

		if(hParent != NULL)
		{
			pidlParent = m_pMyTreeView->BuildPath(hParent);

			if(pidlParent != NULL)
			{
				m_bTreeViewOpenInNewTab = FALSE;

				std::list<LPITEMIDLIST> pidlList;

				pidlList.push_back(pidlRelative);

				CFileContextMenuManager fcmm(m_hContainer,pidlParent,
					pidlList);

				FileContextMenuInfo_t fcmi;
				fcmi.uFrom = FROM_TREEVIEW;

				CStatusBar StatusBar(m_hStatusBar);

				fcmm.ShowMenu(this,MIN_SHELL_MENU_ID,MAX_SHELL_MENU_ID,ppt,&StatusBar,
					reinterpret_cast<DWORD_PTR>(&fcmi),TRUE,GetKeyState(VK_SHIFT) & 0x80);

				CoTaskMemFree(pidlParent);
			}
		}

		pShellParentFolder->Release();
	}

	/* Don't switch back to the previous folder if
	the folder that was right-clicked was opened in
	a new tab (i.e. can just keep the selection the
	same). */
	if(!m_bTreeViewOpenInNewTab)
		TreeView_SelectItem(m_hTreeView,hPrevItem);

	m_bTreeViewRightClick = FALSE;

	CoTaskMemFree(pidl);
}