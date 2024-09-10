void CWndLog::OnRClick()
{
	CMenu menu;
	menu.LoadMenu (IDM_LOG);
	CMenu *pPopup = menu.GetSubMenu (0);
	ApplyLanguageToMenu (pPopup);

	if (m_bAutoScroll)
		pPopup->CheckMenuItem (ID_AUTOSCROLL, MF_CHECKED | MF_BYCOMMAND);

	if (GetItemCount () == 0)
	{
		pPopup->EnableMenuItem (ID_CLEAR, MF_BYCOMMAND | MF_GRAYED);
		pPopup->EnableMenuItem (ID_COPY_TO_CB, MF_BYCOMMAND | MF_GRAYED);
	}

	ClientToScreen (&m_rbPt);

	m_odmenu.Attach (&menu, FALSE);
	pPopup->TrackPopupMenu (TPM_RIGHTBUTTON | TPM_TOPALIGN | TPM_LEFTALIGN,	m_rbPt.x, m_rbPt.y, this);
	m_odmenu.Detach ();

	menu.DestroyMenu ();
}