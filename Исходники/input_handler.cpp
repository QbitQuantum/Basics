CGameObject *CInputHandler::dragEnd(const Point &pt, CTreeItem *dragItem) {
	CViewItem *view = _gameManager->getView();
	if (!view)
		return nullptr;

	// Scan through the view items to find the item being dropped on
	CGameObject *target = nullptr;
	for (CTreeItem *treeItem = view->scan(view); treeItem; treeItem = treeItem->scan(view)) {
		CGameObject *gameObject = dynamic_cast<CGameObject *>(treeItem);
		if (gameObject && gameObject != dragItem) {
			if (gameObject->checkPoint(pt))
				target = gameObject;
		}
	}

	if (target) {
		// Check if the cursor is on the PET. If so, pass to the PET
		// to see what specific element the drag ended on
		CProjectItem *project = view->getRoot();
		if (project) {
			CPetControl *petControl = project->getPetControl();
			if (petControl && petControl->contains(pt)) {
				target = petControl->dragEnd(pt);
				if (!target)
					target = petControl;
			}
		}
	}

	return target;
}