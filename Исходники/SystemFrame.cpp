LRESULT SystemFrame::onContextMenu(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/) {
	POINT pt = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };        // location of mouse click

	if(pt.x == -1 && pt.y == -1) {
		CRect erc;
		ctrlPad.GetRect(&erc);
		pt.x = erc.Width() / 2;
		pt.y = erc.Height() / 2;
		ClientToScreen(&pt);
	}

	POINT ptCl = pt;
	ScreenToClient(&ptCl); 
	OnRButtonDown(ptCl); 

	OMenu menu;
	menu.CreatePopupMenu();

	menu.AppendMenu(MF_STRING, ID_EDIT_COPY, CTSTRING(COPY));

	menu.AppendMenu(MF_SEPARATOR);
	if(SETTING(LOG_SYSTEM)) {
		menu.AppendMenu(MF_STRING, IDC_OPEN_SYSTEM_LOG, CTSTRING(OPEN_SYSTEM_LOG));
		menu.AppendMenu(MF_SEPARATOR);
	}
	menu.AppendMenu(MF_STRING, ID_EDIT_SELECT_ALL, CTSTRING(SELECT_ALL));
	menu.AppendMenu(MF_STRING, ID_EDIT_CLEAR_ALL, CTSTRING(CLEAR_MESSAGES));

	if (!selWord.empty()) {
		menu.AppendMenu(MF_STRING, IDC_COPY_DIR, CTSTRING(COPY_DIRECTORY));
		menu.AppendMenu(MF_SEPARATOR);
		menu.AppendMenu(MF_STRING, IDC_SEARCHDIR, CTSTRING(SEARCH_DIRECTORY));
		menu.AppendMenu(MF_STRING, IDC_ADD_AUTO_SEARCH_DIR, CTSTRING(ADD_AUTO_SEARCH_DIR));
		if (selWord[selWord.length() - 1] != PATH_SEPARATOR) {
			menu.AppendMenu(MF_STRING, IDC_SEARCH, CTSTRING(SEARCH_FILENAME));
			auto path = Text::fromT(selWord);
			if (Util::fileExists(path)) {
				menu.AppendMenu(MF_STRING, IDC_DELETE_FILE, CTSTRING(DELETE_FILE));
			} else {
				menu.AppendMenu(MF_STRING, IDC_ADD_AUTO_SEARCH_FILE, CTSTRING(ADD_AUTO_SEARCH_FILE));
				menu.AppendMenu(MF_SEPARATOR);
			}
		}

		menu.AppendMenu(MF_STRING, IDC_OPEN_FOLDER, CTSTRING(OPEN_FOLDER));
	}
	
	menu.open(m_hWnd, TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt);
	return 0;

}