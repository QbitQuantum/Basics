void CMainGameWindow::drawViewContents(CScreenManager *screenManager) {
	// Get a reference to the reference, validating that it's present
	if (!screenManager)
		return;
	CViewItem *view = _gameManager->getView();
	if (!view)
		return;
	CNodeItem *node = view->findNode();
	if (!node)
		return;
	CRoomItem *room = node->findRoom();
	if (!room)
		return;

	double xVal = 0.0, yVal = 0.0;
	room->calcNodePosition(node->_nodePos, xVal, yVal);

	// Iterate through drawing all the items in the scene except any item
	// that's currently being dragged
	for (CTreeItem *treeItem = view; treeItem; treeItem = treeItem->scan(view)) {
		if (treeItem != _gameManager->_dragItem)
			treeItem->draw(screenManager);
	}

	// Finally draw the drag item if there is one
	if (_gameManager->_dragItem)
		_gameManager->_dragItem->draw(screenManager);
}