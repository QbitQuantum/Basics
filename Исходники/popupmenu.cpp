HRESULT STDMETHODCALLTYPE CPopupMenu::QueryContextMenu(THIS_ HMENU hmenu, UINT indexMenu, UINT idCmdFirst, UINT idCmdLast, UINT uFlags)
{
	if(!IsWorkCopy(&m_Files, m_NumFiles, m_WcPath)){
		if(m_NumFiles >= 2){
		}
		else{
			if (FILE_ATTRIBUTE_DIRECTORY == GetFileAttributes(m_Files[0].c_str())){
				int i = 0;
				HMENU SubMenu = CreatePopupMenu();
				m_hInstance = GetModuleHandle("TeamExplorerShellMenu.dll");

				InsertMenu(SubMenu, i++, MF_STRING | MF_BYPOSITION, idCmdFirst + 1, _T("Set Environment"));
				m_hSetEnv = ::LoadBitmap(m_hInstance, MAKEINTRESOURCE(IDB_SETENV)); 
				SetMenuItemBitmaps(SubMenu, i-1, MF_BYPOSITION, m_hSetEnv, m_hSetEnv);

				InsertMenu(hmenu, indexMenu, MF_SEPARATOR | MF_BYPOSITION, 0, NULL);

				InsertMenu(hmenu, indexMenu+1, MF_POPUP | MF_BYPOSITION, (UINT)SubMenu, _T("Team Explorer"));
				m_hPopupMenu = ::LoadBitmap(m_hInstance, MAKEINTRESOURCE(IDB_POPUPMENU)); 
				SetMenuItemBitmaps(hmenu, indexMenu+1, MF_BYPOSITION, m_hPopupMenu, m_hPopupMenu);

				InsertMenu(hmenu, indexMenu+2, MF_SEPARATOR | MF_BYPOSITION, 0, NULL);

				DestroyMenu(SubMenu);
			}
		}
	}
	else{
		if(!IsTeamExplorer(m_WcPath)){
			return MAKE_HRESULT(SEVERITY_SUCCESS, 0, USHORT(13 + 1));
		}

		int i = 0;
		HMENU SubMenu = CreatePopupMenu();
		m_hInstance = GetModuleHandle("TeamExplorerShellMenu.dll");

		if(IsProductOrTags(m_WcPath)){
			InsertMenu(SubMenu, i++, MF_STRING | MF_BYPOSITION, idCmdFirst + 2, _T("Update"));
			m_hUpdate = ::LoadBitmap(m_hInstance, MAKEINTRESOURCE(IDB_UPDATE)); 
			SetMenuItemBitmaps(SubMenu, i-1, MF_BYPOSITION, m_hUpdate, m_hUpdate);
		}
		else{
			if(CouldWrite(&m_Files, &m_WriteFiles, m_NumFiles)){
				InsertMenu(SubMenu, i++, MF_STRING | MF_BYPOSITION, idCmdFirst + 3, _T("Check out"));
				m_hCheckout = ::LoadBitmap(m_hInstance, MAKEINTRESOURCE(IDB_CHECKOUT)); 
				SetMenuItemBitmaps(SubMenu, i-1, MF_BYPOSITION, m_hCheckout, m_hCheckout);

				InsertMenu(SubMenu, i++, MF_STRING | MF_BYPOSITION, idCmdFirst + 4, _T("Commit"));
				m_hCommit = ::LoadBitmap(m_hInstance, MAKEINTRESOURCE(IDB_COMMIT)); 
				SetMenuItemBitmaps(SubMenu, i-1, MF_BYPOSITION, m_hCommit, m_hCommit);

				InsertMenu(SubMenu, i++, MF_STRING | MF_BYPOSITION, idCmdFirst + 5, _T("Check in"));
				m_hCheckin = ::LoadBitmap(m_hInstance, MAKEINTRESOURCE(IDB_CHECKIN)); 
				SetMenuItemBitmaps(SubMenu, i-1, MF_BYPOSITION, m_hCheckin, m_hCheckin);

				InsertMenu(SubMenu, i++, MF_SEPARATOR | MF_BYPOSITION, 0, NULL);

				InsertMenu(SubMenu, i++, MF_STRING | MF_BYPOSITION, idCmdFirst + 2, _T("Update"));
				m_hUpdate = ::LoadBitmap(m_hInstance, MAKEINTRESOURCE(IDB_UPDATE)); 
				SetMenuItemBitmaps(SubMenu, i-1, MF_BYPOSITION, m_hUpdate, m_hUpdate);

				InsertMenu(SubMenu, i++, MF_STRING | MF_BYPOSITION, idCmdFirst + 6, _T("Cancel"));
				m_hCancel = ::LoadBitmap(m_hInstance, MAKEINTRESOURCE(IDB_CANCEL)); 
				SetMenuItemBitmaps(SubMenu, i-1, MF_BYPOSITION, m_hCancel, m_hCancel);

				InsertMenu(SubMenu, i++, MF_SEPARATOR | MF_BYPOSITION, 0, NULL);

				InsertMenu(SubMenu, i++, MF_STRING | MF_BYPOSITION, idCmdFirst + 8, _T("Revert"));
				m_hRevert = ::LoadBitmap(m_hInstance, MAKEINTRESOURCE(IDB_REVERT)); 
				SetMenuItemBitmaps(SubMenu, i-1, MF_BYPOSITION, m_hRevert, m_hRevert);

				InsertMenu(SubMenu, i++, MF_STRING | MF_BYPOSITION, idCmdFirst + 9, _T("Merge"));
				m_hMerge = ::LoadBitmap(m_hInstance, MAKEINTRESOURCE(IDB_MERGE)); 
				SetMenuItemBitmaps(SubMenu, i-1, MF_BYPOSITION, m_hMerge, m_hMerge);
			}
			else{
				InsertMenu(SubMenu, i++, MF_STRING | MF_BYPOSITION, idCmdFirst + 3, _T("Check out"));
				m_hCheckout = ::LoadBitmap(m_hInstance, MAKEINTRESOURCE(IDB_CHECKOUT)); 
				SetMenuItemBitmaps(SubMenu, i-1, MF_BYPOSITION, m_hCheckout, m_hCheckout);

				InsertMenu(SubMenu, i++, MF_SEPARATOR | MF_BYPOSITION, 0, NULL);

				InsertMenu(SubMenu, i++, MF_STRING | MF_BYPOSITION, idCmdFirst + 7, _T("Add"));
				m_hAdd = ::LoadBitmap(m_hInstance, MAKEINTRESOURCE(IDB_ADD)); 
				SetMenuItemBitmaps(SubMenu, i-1, MF_BYPOSITION, m_hAdd, m_hAdd);

				InsertMenu(SubMenu, i++, MF_STRING | MF_BYPOSITION, idCmdFirst + 2, _T("Update"));
				m_hUpdate = ::LoadBitmap(m_hInstance, MAKEINTRESOURCE(IDB_UPDATE)); 
				SetMenuItemBitmaps(SubMenu, i-1, MF_BYPOSITION, m_hUpdate, m_hUpdate);
			}
		}

		InsertMenu(SubMenu, i++, MF_STRING | MF_BYPOSITION, idCmdFirst + 10, _T("Show log"));
		m_hShowLog = ::LoadBitmap(m_hInstance, MAKEINTRESOURCE(IDB_SHOWLOG)); 
		SetMenuItemBitmaps(SubMenu, i-1, MF_BYPOSITION, m_hShowLog, m_hShowLog);

		InsertMenu(SubMenu, i++, MF_BYPOSITION | MF_SEPARATOR, 0, NULL);

		InsertMenu(SubMenu, i++, MF_STRING | MF_BYPOSITION, idCmdFirst + 11, _T("Diff"));
		m_hDiff = ::LoadBitmap(m_hInstance, MAKEINTRESOURCE(IDB_DIFF));
		SetMenuItemBitmaps(SubMenu, i-1, MF_BYPOSITION, m_hDiff, m_hDiff);

		InsertMenu(SubMenu, i++, MF_STRING | MF_BYPOSITION, idCmdFirst + 12, _T("Compare"));
		m_hCompare = ::LoadBitmap(m_hInstance, MAKEINTRESOURCE(IDB_COMPARE));
		SetMenuItemBitmaps(SubMenu, i-1, MF_BYPOSITION, m_hCompare, m_hCompare);

		InsertMenu(SubMenu, i++, MF_BYPOSITION | MF_STRING, idCmdFirst + 13, _T("Update Rely Files"));
		m_hDownload = ::LoadBitmap(m_hInstance, MAKEINTRESOURCE(IDB_DOWNLOAD));
		SetMenuItemBitmaps(SubMenu, i-1, MF_BYPOSITION, m_hDownload, m_hDownload);

		InsertMenu(hmenu, indexMenu, MF_SEPARATOR | MF_BYPOSITION, 0, NULL);

		InsertMenu(hmenu, indexMenu+1, MF_POPUP | MF_BYPOSITION, (UINT)SubMenu, _T("Team Explorer"));
		m_hPopupMenu = ::LoadBitmap(m_hInstance, MAKEINTRESOURCE(IDB_POPUPMENU)); 
		SetMenuItemBitmaps(hmenu, indexMenu+1, MF_BYPOSITION, m_hPopupMenu, m_hPopupMenu);

		InsertMenu(hmenu, indexMenu+2, MF_SEPARATOR | MF_BYPOSITION, 0, NULL);

		DestroyMenu(SubMenu);
	}

	return MAKE_HRESULT(SEVERITY_SUCCESS, 0, USHORT(13 + 1));
}