bool UsersFrame::handleContextMenu(dwt::ScreenCoordinate pt) {
	if (users->hasSelected()) {
		if(pt.x() == -1 && pt.y() == -1) {
			pt = users->getContextMenuPos();
		}

		MenuPtr menu = addChild(WinUtil::Seeds::menu);
		appendUserItems(getParent(), menu);
		menu->appendSeparatorItem();
		menu->appendItem(IDC_EDIT, T_("&Description"), std::tr1::bind(&UsersFrame::handleDescription, this));
		menu->appendItem(IDC_REMOVE, T_("&Remove"), std::tr1::bind(&UsersFrame::handleRemove, this));
		
		menu->trackPopupMenu(pt, TPM_LEFTALIGN | TPM_RIGHTBUTTON);

		return true;
	}
	return false;
}