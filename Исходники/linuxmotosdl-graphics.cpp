bool LinuxmotoSdlGraphicsManager::loadGFXMode() {
	debug("Game ScreenMode = %d*%d",_videoMode.screenWidth, _videoMode.screenHeight);
	if (_videoMode.screenWidth > 320 || _videoMode.screenHeight > 240) {
		_videoMode.aspectRatioCorrection = false;
		setGraphicsMode(GFX_HALF);
		debug("GraphicsMode set to HALF");
	} else {
		setGraphicsMode(GFX_NORMAL);
		debug("GraphicsMode set to NORMAL");
	}
	if (_videoMode.mode == GFX_HALF && !_overlayVisible) {
		_videoMode.overlayWidth = 320;
		_videoMode.overlayHeight = 240;
		_videoMode.fullscreen = true;
	} else {

		_videoMode.overlayWidth = _videoMode.screenWidth * _videoMode.scaleFactor;
		_videoMode.overlayHeight = _videoMode.screenHeight * _videoMode.scaleFactor;

		if (_videoMode.aspectRatioCorrection)
			_videoMode.overlayHeight = real2Aspect(_videoMode.overlayHeight);

		_videoMode.hardwareWidth = _videoMode.screenWidth * _videoMode.scaleFactor;
		_videoMode.hardwareHeight = effectiveScreenHeight();
	}

	return SdlGraphicsManager::loadGFXMode();
}