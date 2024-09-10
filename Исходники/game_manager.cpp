void CGameManager::update() {
	updateMovies();
	frameMessage(getRoom());
	_timers.update(g_vm->_events->getTicksCount());
	_trueTalkManager.removeCompleted();

	CScreenManager::_screenManagerPtr->_mouseCursor->update();

	CViewItem *view = getView();
	if (view) {
		// Expand the game manager's bounds to encompass all the view's items
		for (CTreeItem *item = view; item; item = item->scan(view)) {
			Rect r = item->getBounds();
			if (!r.isEmpty())
				_bounds.extend(r);
		}

		// Also include the PET control in the bounds
		if (_project) {
			CPetControl *pet = _project->getPetControl();
			if (pet)
				_bounds.extend(pet->getBounds());
		}

		// And the text cursor
		CScreenManager *screenManager = CScreenManager::_screenManagerPtr;
		CTextCursor *textCursor = screenManager->_textCursor;
		if (textCursor && textCursor->_active)
			_bounds.extend(textCursor->getCursorBounds());
		
		// Set the surface bounds
		screenManager->setSurfaceBounds(SURFACE_BACKBUFFER, _bounds);

		// Handle redrawing the view
		if (!_bounds.isEmpty()) {
			_gameView->draw(_bounds);
			_bounds = Rect();
		}

		_gameState.checkForViewChange();
	}
}