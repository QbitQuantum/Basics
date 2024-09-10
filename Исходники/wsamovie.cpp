void WSAMovie_v1::displayFrame(int frameNum, int pageNum, int x, int y, uint16 flags, const uint8 *table1, const uint8 *table2) {
	if (frameNum >= _numFrames || frameNum < 0 || !_opened)
		return;

	_x = x;
	_y = y;
	_drawPage = pageNum;

	uint8 *dst = 0;
	if (_flags & WF_OFFSCREEN_DECODE)
		dst = _offscreenBuffer;
	else
		dst = _screen->getPageRect(_drawPage, _x, _y, _width, _height);

	if (_currentFrame == _numFrames) {
		if (!(_flags & WF_NO_FIRST_FRAME)) {
			if (_flags & WF_OFFSCREEN_DECODE)
				Screen::decodeFrameDelta(dst, _deltaBuffer);
			else
				Screen::decodeFrameDeltaPage(dst, _deltaBuffer, _width, (_flags & WF_XOR) == 0);
		}
		_currentFrame = 0;
	}

	// try to reduce the number of needed frame operations
	int diffCount = ABS(_currentFrame - frameNum);
	int frameStep = 1;
	int frameCount;
	if (_currentFrame < frameNum) {
		frameCount = _numFrames - frameNum + _currentFrame;
		if (diffCount > frameCount && !(_flags & WF_NO_LAST_FRAME))
			frameStep = -1;
		else
			frameCount = diffCount;
	} else {
		frameCount = _numFrames - _currentFrame + frameNum;
		if (frameCount >= diffCount || (_flags & WF_NO_LAST_FRAME)) {
			frameStep = -1;
			frameCount = diffCount;
		}
	}

	// process
	if (frameStep > 0) {
		uint16 cf = _currentFrame;
		while (frameCount--) {
			cf += frameStep;
			processFrame(cf, dst);
			if (cf == _numFrames)
				cf = 0;
		}
	} else {
		uint16 cf = _currentFrame;
		while (frameCount--) {
			if (cf == 0)
				cf = _numFrames;
			processFrame(cf, dst);
			cf += frameStep;
		}
	}

	// display
	_currentFrame = frameNum;
	if (_flags & WF_OFFSCREEN_DECODE) {
		int pageBackUp = _screen->setCurPage(_drawPage);

		int plotFunc = (flags & 0xFF00) >> 12;
		int unk1 = flags & 0xFF;

		_screen->copyWsaRect(_x, _y, _width, _height, 0, plotFunc, _offscreenBuffer, unk1, table1, table2);

		_screen->_curPage = pageBackUp;
	}