void OSystem_Wii::initSize(uint width, uint height) {
	if (_gameWidth != width || _gameHeight != height) {
		printf("initSize %u %u\n", width, height);

		assert((width <= 640) && (height <= 480));

		_gameWidth = width;
		_gameHeight = height;

		if(_gamePixels)
			free(_gamePixels);

		_gamePixels = (u8 *) memalign(32, _gameWidth * _gameHeight);
		memset(_gamePixels, 0, _gameWidth * _gameHeight);

		if (!_overlayVisible) {
			_currentWidth = _gameWidth;
			_currentHeight = _gameHeight;
			updateEventScreenResolution();
		}

		setGraphicsMode(_activeGraphicsMode);
	}
}