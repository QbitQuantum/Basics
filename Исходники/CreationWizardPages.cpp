void CCWArrangePage::OnRclickListTracks(NMHDR* pNMHDR, LRESULT* pResult) 
{
	POSITION pos = m_List.GetFirstSelectedItemPosition ();
	if (pos == NULL)
		return;

	int idx = m_List.GetNextSelectedItem (pos);

	BCMenu menu;

	if (m_List.GetItemText (idx, 0) == STR_SEPARATOR)
		menu.LoadMenu (IDR_MENU_SEP);
	else
	{
		menu.LoadMenu (IDR_MENU_TRACK);
		if (!m_pTracks->IsManuallyEditable ())
			((BCMenu*) menu.GetSubMenu (0))->RemoveMenu (ID_DELETETRACK, MF_BYCOMMAND);
	}
	menu.LoadToolbar (IDR_TOOLBAR_GRP);

	CPoint pt;
	GetCursorPos (&pt);
	menu.GetSubMenu (0)->TrackPopupMenu (TPM_RIGHTALIGN, pt.x, pt.y, this);

	menu.DestroyMenu ();

	*pResult = 0;
}