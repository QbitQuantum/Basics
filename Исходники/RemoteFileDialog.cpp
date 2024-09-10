void CRemoteFileDialog::OnViewMenu()
{
	// build the view menu manually (because we're a non-resource dependent file)
	CMenu menu;

	if (menu.CreatePopupMenu())
	{
		menu.InsertMenu(0, MF_STRING | MF_BYPOSITION, ID_VIEW_LARGEICON, _T("Lar&ge Icons"));
		menu.InsertMenu(1, MF_STRING | MF_BYPOSITION, ID_VIEW_SMALLICON, _T("S&mall Icons"));
		menu.InsertMenu(2, MF_STRING | MF_BYPOSITION, ID_VIEW_LIST, _T("&List"));
		menu.InsertMenu(3, MF_STRING | MF_BYPOSITION, ID_VIEW_DETAILS, _T("&Details"));

		// check the appropriate one
		int nView = (m_lcFiles.GetStyle() & LVS_TYPEMASK);
		menu.CheckMenuRadioItem(ID_VIEW_LARGEICON, ID_VIEW_DETAILS, VIEWIDS[nView], MF_BYCOMMAND);

		// get the button rect in screen coords
		CRect rButton;

		m_toolbar.GetItemRect(1, rButton);
		m_toolbar.ClientToScreen(rButton);
		m_toolbar.GetToolBarCtrl().PressButton(ID_VIEWMENU);

		menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON, rButton.left, rButton.bottom, this);

		m_toolbar.GetToolBarCtrl().PressButton(ID_VIEWMENU, FALSE);
	}
}