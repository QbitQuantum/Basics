/*
 * Sets the menubar into the mIRC window, and automatically destroys the old menubar
 * if it isnt the original mIRC menubar.
 */
void XMenuBar::setMenuBar(HMENU oldMenuBar, HMENU newMenuBar) {
	if (newMenuBar != g_OriginalMenuBar) {
		MENUINFO mi;

		ZeroMemory(&mi, sizeof(MENUINFO));
		mi.cbSize = sizeof(MENUINFO);
		mi.fMask = MIM_BACKGROUND | MIM_HELPID | MIM_MAXHEIGHT | MIM_MENUDATA | MIM_STYLE;

		GetMenuInfo(oldMenuBar, &mi);
		SetMenuInfo(newMenuBar, &mi);
	}

	SetMenu(Dcx::mIRC.getHWND(), newMenuBar);

	// Go through old menubar items and detach them
	VectorOfXPopupMenu temp;
	VectorOfXPopupMenu::iterator itStart = this->m_vpXMenuBar.begin();
	VectorOfXPopupMenu::iterator itEnd = this->m_vpXMenuBar.end();

	// Add menus to a temporary list to prevent errors in looping
	while (itStart != itEnd) {
		temp.push_back(*itStart);
		++itStart;
	}

	itStart = temp.begin();
	itEnd = temp.end();

	// Begin detaching ...
	while (itStart != itEnd) {
		(*itStart)->detachFromMenuBar(oldMenuBar);
		++itStart;
	}

	// Destroy the menu if it isnt the original mIRC menubar.
	if (g_OriginalMenuBar == NULL)
		g_OriginalMenuBar = oldMenuBar;
	else
		DestroyMenu(oldMenuBar);

	DrawMenuBar(Dcx::mIRC.getHWND());
}