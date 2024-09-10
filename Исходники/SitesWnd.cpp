void CSitesWnd::OnRClick()
{
	CMenu menu;
	menu.LoadMenu (IDM_SITES);
	ApplyLanguageToMenu (&menu);
	CMenu *pPopup = menu.GetSubMenu (0);

	UpdateMenu (pPopup);

	ClientToScreen (&m_rbPt);

	m_odmenu.Attach (&menu, FALSE);

	m_odmenu.SetImageList (&((CMainFrame*)AfxGetApp ()->m_pMainWnd)->m_imgsMenu, &((CMainFrame*)AfxGetApp ()->m_pMainWnd)->m_dimgsMenu);
	fsSetImage *pImages;
	int cImages;
	CSitesWnd::Plugin_GetMenuImages (&pImages, &cImages);
	m_odmenu.SetImages (pImages, cImages);

	pPopup->TrackPopupMenu (TPM_RIGHTBUTTON | TPM_TOPALIGN | TPM_LEFTALIGN,	m_rbPt.x, m_rbPt.y, this);
	m_odmenu.Detach ();

	menu.DestroyMenu ();
}