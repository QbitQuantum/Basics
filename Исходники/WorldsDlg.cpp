void CWorldsDlg::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	// TODO: Add your message handler code here
	CMenu menu;
	
	if(!GetProjectBar()->IsProjectOpen())
		return;

	CWnd* pWndPopupOwner = GetProjectBar();

	if(pWnd->m_hWnd == m_WorldTree.m_hWnd)
	{
		VERIFY(menu.LoadMenu(CG_IDR_POPUP_WORLDTREE));
	}
	else if(pWnd->m_hWnd == m_WorldList.m_hWnd)
	{
		// Nothing active unless a directory is selected.
		if(!IsDirectorySelected())
		{
			return;
		}

		//make sure that the user is depressing this over an actual world, so that
		//the action is not ambiguious to what it is acting upon

		//get the point in terms of this window
		CPoint ClientPoint(point);
		m_WorldList.ScreenToClient(&ClientPoint);

		int iIndex = m_WorldList.HitTest(ClientPoint);
		//see if we are hitting any items
		if(iIndex == -1)
		{
			//no item under the cursor, so just make a menu that can only create a new map
			VERIFY(menu.LoadMenu(CG_IDR_POPUP_WORLDLIST_NOITEM));
			pWndPopupOwner = this;
		}
		else
		{
			//we have an item, so display all the options that can be done on that item
			VERIFY(menu.LoadMenu(CG_IDR_POPUP_WORLDLIST));
			pWndPopupOwner = this;

			//now we need to see if this file is compressed and only enable the opposite
			//menu item to be enable so the user doesn't get confused
			DFileIdent *pIdent = (DFileIdent*)m_WorldList.GetItemData(iIndex);

			if(CLTAUtil::IsFileCompressed(pIdent->m_Filename))
			{
				menu.RemoveMenu(ID_WORLD_COMPRESS, MF_BYCOMMAND);
			}
			else
			{
				menu.RemoveMenu(ID_WORLD_DECOMPRESS, MF_BYCOMMAND);
			}

		}
	}
	else return;


	CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup != NULL);

	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
		pWndPopupOwner);	
}