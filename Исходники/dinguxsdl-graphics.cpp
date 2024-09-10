void DINGUXSdlGraphicsManager::initSize(uint w, uint h) {
	assert(_transactionMode == kTransactionActive);

	// Avoid redundant res changes
	if ((int)w == _videoMode.screenWidth && (int)h == _videoMode.screenHeight)
		return;

	_videoMode.screenWidth = w;
	_videoMode.screenHeight = h;
	if (w > 320 || h > 240) {
		setGraphicsMode(GFX_HALF);
		setGraphicsModeIntern();
		_window->toggleMouseGrab();
	}

	_transactionDetails.sizeChanged = true;
}