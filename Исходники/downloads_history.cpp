void CDownloads_History::OnRClick()
{
	CMenu menu;
	menu.LoadMenu (IDM_HISTORYITEMS);
	ApplyLanguageToMenu (&menu);
	CMenu *pPopup = menu.GetSubMenu (0);

	if (GetSelectedCount () != 1)
	{
		pPopup->EnableMenuItem (ID_LAUNCH, MF_BYCOMMAND | MF_GRAYED);
		pPopup->EnableMenuItem (ID_OPENFOLDER, MF_BYCOMMAND | MF_GRAYED);
		pPopup->EnableMenuItem (ID_URLTOCLIPBOARD, MF_BYCOMMAND | MF_GRAYED);
	}

	if (GetSelectedCount () == 0)
		pPopup->EnableMenuItem (ID_HSTITEM_DELETE, MF_BYCOMMAND | MF_GRAYED);

	m_odmenu.Attach (&menu, FALSE);
	
	CPoint pt (0,0);
	GetCursorPos (&pt);
	pPopup->TrackPopupMenu (TPM_RIGHTBUTTON | TPM_TOPALIGN | TPM_LEFTALIGN,	pt.x, pt.y, this);
	m_odmenu.Detach ();

	menu.DestroyMenu ();
}