bool AutoSearchFrame::handleContextMenu(dwt::ScreenCoordinate pt) {
	if(pt.x() == -1 && pt.y() == -1) {
		pt = items->getContextMenuPos();
	}

	MenuPtr contextMenu = addChild(WinUtil::Seeds::menu);
	contextMenu->appendItem(IDC_ADD, T_("&New..."), std::tr1::bind(&AutoSearchFrame::handleAdd, this));
	contextMenu->appendItem(IDC_EDIT, T_("&Properties"), std::tr1::bind(&AutoSearchFrame::handleProperties, this));
	contextMenu->appendItem(IDC_REMOVE, T_("&Remove"), std::tr1::bind(&AutoSearchFrame::handleRemove, this));

	bool status = items->hasSelected();
	contextMenu->setItemEnabled(IDC_EDIT, false, status);
	contextMenu->setItemEnabled(IDC_REMOVE, false, status);

	contextMenu->trackPopupMenu(pt, TPM_LEFTALIGN | TPM_RIGHTBUTTON);
	return true;
}