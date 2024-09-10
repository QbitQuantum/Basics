void CDownloads_Deleted::OnRClick()
{
	CMenu menu;
	menu.LoadMenu (IDM_DELETEDITEMS);
	ApplyLanguageToMenu (&menu);
	CMenu *pPopup = menu.GetSubMenu (0);

	if (GetSelectedCount () == 0)
	{
		pPopup->EnableMenuItem (ID_DELETED_RESTORE, MF_BYCOMMAND | MF_GRAYED);
		pPopup->EnableMenuItem (ID_DELETED_DELETE, MF_BYCOMMAND | MF_GRAYED);
	}

	m_odmenu.Attach (&menu, FALSE);
	
	CPoint pt (0,0);
	GetCursorPos (&pt);
	pPopup->TrackPopupMenu (TPM_RIGHTBUTTON | TPM_TOPALIGN | TPM_LEFTALIGN,	pt.x, pt.y, this);
	m_odmenu.Detach ();

	menu.DestroyMenu ();
}