void GfxTransitions::copyRectToScreen(const Common::Rect rect, bool blackoutFlag) {
	if (!blackoutFlag) {
		_screen->copyRectToScreen(rect);
	} else {
		Graphics::Surface *surface = g_system->lockScreen();
		if (!_screen->getUpscaledHires()) {
			surface->fillRect(rect, 0);
		} else {
			Common::Rect upscaledRect = rect;
			_screen->adjustToUpscaledCoordinates(upscaledRect.top, upscaledRect.left);
			_screen->adjustToUpscaledCoordinates(upscaledRect.bottom, upscaledRect.right);
			surface->fillRect(upscaledRect, 0);
		}
		g_system->unlockScreen();
	}
}