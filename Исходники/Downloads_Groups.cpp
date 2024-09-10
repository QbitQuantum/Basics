void CDownloads_Groups::ShowHistoryContextMenu()
{
	CMenu menu;
	menu.LoadMenu (IDM_GROUP);
	CMenu *pPopup = menu.GetSubMenu (2);

	ApplyLanguageToMenu_History (pPopup);

	pPopup->SetDefaultItem (ID_HISTORY_SETTINGS);

	if (_DldsMgr.m_histmgr.GetRecordCount () == 0)
		pPopup->EnableMenuItem (ID_HISTORY_CLEAR, MF_BYCOMMAND | MF_GRAYED);

	CPoint pt (m_rbX, m_rbY);
	ClientToScreen (&pt);

	m_odmenu.Attach (&menu, FALSE);

	fsSetImage images [] =
	{
		fsSetImage (ID_HISTORY_CLEAR, 2),
		fsSetImage (ID_HISTORY_SETTINGS, 3),
	};

	m_odmenu.SetImages (images, sizeof (images) / sizeof (fsSetImage));

	pPopup->TrackPopupMenu (TPM_RIGHTBUTTON | TPM_TOPALIGN | TPM_LEFTALIGN,	pt.x, pt.y, this);
	m_odmenu.Detach ();

	menu.DestroyMenu ();
}