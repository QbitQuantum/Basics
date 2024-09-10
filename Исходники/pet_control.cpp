bool CPetControl::isBotInView(const CString &name) const {
	CGameManager *gameManager = getGameManager();
	if (!gameManager)
		return false;
	CViewItem *view = gameManager->getView();
	if (!view)
		return false;

	// Iterate to find NPC
	for (CTreeItem *child = view->getFirstChild(); child; child = child->scan(view)) {
		CGameObject *gameObject = dynamic_cast<CGameObject *>(child);
		if (gameObject) {
			if (!gameObject->getName().compareToIgnoreCase(name))
				return true;
		}
	}

	return false;
}